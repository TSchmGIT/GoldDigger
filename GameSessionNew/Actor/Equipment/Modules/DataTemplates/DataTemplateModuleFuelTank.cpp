#include "stdafx.h"
#include "DataTemplateModuleFuelTank.h"

#include "GameSessionNew/Actor/Equipment/Modules/ModuleHelper.h"

//////////////////////////////////////////////////////////////////////////

namespace hvda
{

//////////////////////////////////////////////////////////////////////////

CDataTemplateModuleFuelTank::CDataTemplateModuleFuelTank(const JSON& json)
	: CDataTemplateModuleBase(json)
{
	auto fuelTypeString = json["fueltype"].get<hvgs::String>();
	m_FuelType = CModuleHelper::ConvertStringToFuelType(fuelTypeString);
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

hvgs::FuelAmount CDataTemplateModuleFuelTank::GetCapacity() const
{
	return m_Capacity;
}

//////////////////////////////////////////////////////////////////////////

} // hvda
