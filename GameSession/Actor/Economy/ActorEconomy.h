#pragma once
#include "GameSession/Actor/Economy/EconomyTypes.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CActorEconomy
{

public:
	CActorEconomy();
	virtual ~CActorEconomy();

	/// Gets / Sets the current money
	MoneyAmount GetMoney() const;
	void SetMoney(MoneyAmount amount);
	void AddMoney(MoneyAmount amount);
	MoneyAmount RemoveMoney(MoneyAmount amount);

protected:
	MoneyAmount m_Money = MoneyAmount(0); ///< The money of the actor
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
