#pragma once
#include "GameSession/Buildings/BuildingInteractiveBase.h"

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
	: public CBuildingInteractiveBase
{

public:
	CBuildingBroker();
	virtual ~CBuildingBroker() = default;

public:
	void PerformTransactionBuy(CActor& actor) const;

	MoneyAmount GetPrice(TileType tileType) const;

protected:
	ui::SceneID GetUISceneID() const override;
	TextureName GetBuildingTexture() const override;

protected:
	void FillPriceChart();

protected:
	Map<TileType, MoneyAmount> m_PriceChart;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
