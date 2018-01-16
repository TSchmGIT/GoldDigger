#pragma once
#include "GameSession/Buildings/BuildingBase.h"

#include "GameSession/Actor/Economy/EconomyTypes.h"
#include "GameSession/Actor/Interaction/IInteractionObject.h"
#include "GameSession/World/WorldEnums.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CActor;
}

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CBuildingBroker
	: public CBuildingBase
	, public IInteractionObject
{

public:
	CBuildingBroker();
	virtual ~CBuildingBroker() = default;

	// IInteractionObject
public:
	virtual bool IsInInteractionDistance(const WorldPos& position) const override;
	virtual void StartInteraction() override;
	virtual void StopInteraction() override;
	virtual WorldPos GetInteractionButtonPosition() const override;

protected:
	virtual const WorldPos& GetInteractionOriginPosition() const override;

public:
	void PerformTransactionBuy(CActor& actor) const;

	MoneyAmount GetPrice(TileType tileType) const;
protected:
	void FillPriceChart();


protected:
	Map<TileType, MoneyAmount> m_PriceChart;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
