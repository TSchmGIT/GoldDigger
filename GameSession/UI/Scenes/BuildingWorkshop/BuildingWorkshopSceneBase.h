#pragma once
#include "BuildingWorkshopSceneObject.h"

#include "GameSession/UI/Elements/UIButton.h"
#include "GameSession/UI/Scenes/BaseScene.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

/////////////////////////////////////////////////////////////////////////////

class CBuildingWorkshopSceneBase : public CBaseScene
{

public:
	CBuildingWorkshopSceneBase() = default;
	virtual ~CBuildingWorkshopSceneBase() = default;

	void Draw() const override;

	virtual SceneID GetSceneID() const override;

	virtual bool IsFullscreenMenu() const override;

	virtual void SyncTick() override;

	Vector2 GetPivotPoint() const override;

protected:
	BuildingWorkshop::CCategorySelectionList&	GetCategoryButtonList();

protected:
	void DrawBackground() const;
	void DrawCategorySelection() const;
	void DrawModuleList() const;

protected:
	BuildingWorkshop::CCategorySelectionList	m_CategoryButtonList = BuildingWorkshop::CCategorySelectionList(*this);
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui
