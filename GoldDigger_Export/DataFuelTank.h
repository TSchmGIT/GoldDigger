#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CDataFuelTank
{
public:
	CDataFuelTank() = default;
	virtual ~CDataFuelTank() = default;

public:
    int GetCapacity() const;
    float GetFuelEfficiency() const;
    int GetAnotherValue() const;

protected:
    int m_Capacity = 100;
    float m_FuelEfficiency = 1.0f;
    int m_AnotherValue = 0;
}
};

/////////////////////////////////////////////////////////////////////////////

    } // hvgs
