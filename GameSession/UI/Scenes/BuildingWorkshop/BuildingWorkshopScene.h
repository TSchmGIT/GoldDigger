#pragma once
#include "GameSession/UI/Scenes/BuildingWorkshop/BuildingWorkshopSceneBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

/////////////////////////////////////////////////////////////////////////////

class CBuildingWorkshopScene : public CBuildingWorkshopSceneBase
{

public:
	CBuildingWorkshopScene() = default;
	virtual ~CBuildingWorkshopScene() = default;

	void Draw() const override;

protected:
	virtual void Enter() override;

};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui
