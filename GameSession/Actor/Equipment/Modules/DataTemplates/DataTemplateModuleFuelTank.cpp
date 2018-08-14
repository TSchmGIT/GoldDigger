#include "stdafx.h"
#include "DataTemplateModuleFuelTank.h"

//////////////////////////////////////////////////////////////////////////

namespace hvda
{

//////////////////////////////////////////////////////////////////////////

CDataTemplateModuleFuelTank::CDataTemplateModuleFuelTank(const JSON& json)
	: CDataTemplateModuleBase(json)
{
	//m_FuelType = json["fueltype"].get<hvgs::FuelType>();
	m_Consumption = hvgs::FuelConsumption(json["consumption"].get<hvgs::FuelConsumption::value_type>());
	m_Capacity = hvgs::FuelAmount(json["capacity"].get<hvgs::FuelAmount::value_type>());
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
