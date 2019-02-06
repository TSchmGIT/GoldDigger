#pragma once
#include "GameSession/Actor/Economy/EconomyTypes.h"
#include "GameSession/Actor/Equipment/Modules/EnumsModules.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CActorEconomy
{
	using ModuleOwnershipArray = Array<Set<ModuleGUID>, size_t(ModuleType::Count)>;

public:
	CActorEconomy() = default;
	virtual ~CActorEconomy() = default;

	/// Gets / Sets the current money
	MoneyAmount GetMoney() const;
	void SetMoney(MoneyAmount amount);
	void AddMoney(MoneyAmount amount);
	MoneyAmount RemoveMoney(MoneyAmount amount);

	/// Gets / Sets owned modules
	const ModuleOwnershipArray& GetOwnedModuleList() const;
	void AddOwnedModule(ModuleGUID moduleGUID, ModuleType moduleType = ModuleType::Invalid);
	bool HasOwnership(ModuleGUID moduleGUID, ModuleType moduleType = ModuleType::Invalid) const;

protected:
	MoneyAmount m_Money = MoneyAmount(10000); ///< The money of the actor
	ModuleOwnershipArray m_OwnedModuleList;

};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
