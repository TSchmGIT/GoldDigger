#include "stdafx.h"
#include "DataTemplateModuleFuelTank.h"

#include "GameSession/Actor/Equipment/Modules/ModuleHelper.h"

//////////////////////////////////////////////////////////////////////////

namespace hvda
{

//////////////////////////////////////////////////////////////////////////

CDataTemplateModuleFuelTank::CDataTemplateModuleFuelTank(const JSON& json)
	: CDataTemplateModuleBase(json)
{
	auto fuelTypeString = json["fueltype"].get<hvgs::String>();
	m_FuelType = CModuleHelper::ConvertStringToFuelType(fuelTypeString);
	m_Consumption = hvgs::FuelConsumption(json["consumption"].get<hvgs::FuelConsumption::value_type>());
	m_Capacity = hvgs::FuelAmount(json["capacity"].get<hvgs::FuelAmount::value_type>());
}

//////////////////////////////////////////////////////////////////////////

hvgs::ModuleType CDataTemplateModuleFuelTank::GetType() const
{
	return hvgs::ModuleType::FuelTank;
}

//////////////////////////////////////////////////////////////////////////

hvgs::FuelType CDataTemplateModuleFuelTank::GetFuelType() const
{
	return m_FuelType;
}

//////////////////////////////////////////////////////////////////////////

hvgs::FuelConsumption CDataTemplateModuleFuelTank::GetConsumption() const
{
	return m_Consumption;
}

//////////////////////////////////////////////////////////////////////////

hvgs::FuelAmount CDataTemplateModuleFuelTank::GetCapacity() const
{
	return m_Capacity;
}

//////////////////////////////////////////////////////////////////////////

} // hvda
