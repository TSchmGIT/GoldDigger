#pragma once
#include "GameSession/Actor/Interaction/IInteractionObject.h"
#include "GameSession/Buildings/BuildingBase.h"

#include "GameSession/UI/Scenes/Meta/SceneEnum.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CBuildingInteractiveBase
	: public CBuildingBase
	, public IInteractionObject
{

public:
	CBuildingInteractiveBase() = default;
	virtual ~CBuildingInteractiveBase() = default;

	virtual bool IsInInteractionDistance(const WorldPos& position) const final;
	virtual void StartInteraction() override;
	virtual void StopInteraction() override;
	virtual WorldPos GetInteractionButtonPosition() const override;

protected:
	virtual const WorldPos& GetInteractionOriginPosition() const override;

	virtual ui::SceneID GetUISceneID() const = 0;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
