#include "stdafx.h"
#include "ModuleFuelTank.h"
#include "Manager/TimeManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CModuleFuelTank::CModuleFuelTank(ModuleID moduleID, CEquipment& equipment, const hvda::CDataTemplateModuleFuelTank& dataTemplate)
	: CModuleBase(moduleID, equipment, dataTemplate)
	, m_FuelAmount(dataTemplate.GetCapacity())
{

}

//////////////////////////////////////////////////////////////////////////

void CModuleFuelTank::Tick()
{
	CModuleBase::Tick();

	TickFuelConsumption();
}

//////////////////////////////////////////////////////////////////////////

hvgs::FuelAmount CModuleFuelTank::GetCurrentFuelAmount() const
{
	return m_FuelAmount;
}

//////////////////////////////////////////////////////////////////////////

void CModuleFuelTank::SetCurrentFuelAmount(FuelAmount fuelAmount)
{
	m_FuelAmount = fuelAmount;
}

//////////////////////////////////////////////////////////////////////////

hvgs::FuelType CModuleFuelTank::GetFuelType() const
{
	return GetTemplate().GetFuelType();
}

//////////////////////////////////////////////////////////////////////////

hvgs::FuelAmount CModuleFuelTank::GetMaximumFuelAmount() const
{
	return GetTemplate().GetCapacity();
}

//////////////////////////////////////////////////////////////////////////

bool CModuleFuelTank::IsEmpty() const
{
	return m_FuelAmount == FuelAmount(0.0f);
}

//////////////////////////////////////////////////////////////////////////

float CModuleFuelTank::GetFuelPercentage() const
{
	return float(m_FuelAmount.get()) / float(GetTemplate().GetCapacity().get());
}

//////////////////////////////////////////////////////////////////////////

void CModuleFuelTank::SetFuelPenalty(FuelPenalty fuelPenalty, bool isSet)
{
	m_PenaltyMask.set(int(fuelPenalty), isSet);
}

//////////////////////////////////////////////////////////////////////////

hvgs::FuelAmount CModuleFuelTank::Refuel()
{
	auto fuelDifference = GetMaximumFuelAmount() - GetCurrentFuelAmount();
	SetCurrentFuelAmount(GetMaximumFuelAmount());

	return fuelDifference;
}

//////////////////////////////////////////////////////////////////////////

const hvda::CDataTemplateModuleFuelTank& CModuleFuelTank::GetTemplate() const
{
	return static_cast<const hvda::CDataTemplateModuleFuelTank&>(m_Template);
}

//////////////////////////////////////////////////////////////////////////

void CModuleFuelTank::TickFuelConsumption()
{
	const auto& templateFuelConsumption = GetTemplate();

	FuelConsumption consumption = templateFuelConsumption.GetConsumption();


	// Calculate penalties
	float penaltyFactor = GetPenaltyConsumptionFactor();
	consumption *= FuelConsumption(penaltyFactor);

	// Calculate base consumption
	auto amountDecreased = FuelAmount(consumption.get() * CTimeManager::Get().GetGameDeltaTime());
	m_FuelAmount = hvmath::Max({ FuelAmount(0.0f), m_FuelAmount - amountDecreased });
}

//////////////////////////////////////////////////////////////////////////

float CModuleFuelTank::GetPenaltyConsumptionFactor() const
{
	float factor = 1.0f;

	for (size_t i = 0; i < size_t(FuelPenalty::Count); ++i)
	{
		auto currentPenalty = FuelPenalty(i);

		// Check if penalty needs to be applied
		if (!m_PenaltyMask.test(i))
		{
			continue;
		}

		switch (currentPenalty)
		{
		case hvgs::FuelPenalty::Moving:
			factor *= 2.5f;
			break;
		case hvgs::FuelPenalty::Digging:
			factor *= 7.5f;
			break;
		}
	}

	return factor;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
