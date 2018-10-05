#include "stdafx.h"
#include "ModuleHelper.h"

//////////////////////////////////////////////////////////////////////////

namespace hvda
{

//////////////////////////////////////////////////////////////////////////

const hvgs::String& CModuleHelper::ConvertFuelTypeToString(hvgs::FuelType fuelType)
{
	switch (fuelType)
	{
	case hvgs::FuelType::Oil:
	{
		static const hvgs::String oilString = "Oil";
		return oilString;
	}
	case hvgs::FuelType::Gas:
	{
		static const hvgs::String gasString = "Gas";
		return gasString;
	}
	default:
	{
		static const hvgs::String invalidString = "Invalid";
		return invalidString;
	}
	}
}

//////////////////////////////////////////////////////////////////////////

hvgs::FuelType CModuleHelper::ConvertStringToFuelType(const hvgs::String& fuelTypeString)
{
	if (fuelTypeString == "Oil")
	{
		return hvgs::FuelType::Oil;
	}
	else if (fuelTypeString == "Gas")
	{
		return hvgs::FuelType::Gas;
	}
	else
	{
		return hvgs::FuelType::Invalid;
	}
}

//////////////////////////////////////////////////////////////////////////

} // hvda
