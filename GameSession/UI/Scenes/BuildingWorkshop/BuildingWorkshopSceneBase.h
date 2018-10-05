#pragma once
#include "CategorySelectionList.h"

#include "GameSession/Actor/Equipment/Modules/EnumsModules.h"
#include "GameSession/Data/DataDefines.h"
#include "GameSession/UI/Elements/UIButton.h"
#include "GameSession/UI/Scenes/BaseScene.h"
#include "GameSession/UI/Scenes/BuildingWorkshop/ModuleList.h"
#include "ModuleDetailPanel.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

/////////////////////////////////////////////////////////////////////////////

class CBuildingWorkshopSceneBase : public CBaseScene
{

public:
	CBuildingWorkshopSceneBase();
	virtual ~CBuildingWorkshopSceneBase() = default;

	void Init() override;

	void Draw() const override;

	virtual SceneID GetSceneID() const override;

	virtual bool IsFullscreenMenu() const override;

	virtual void SyncTick() override;

	Vector2 GetPivotPoint() const override;

	virtual ModuleGUID			GetSelectedModuleGUID()	const = 0;
	virtual hvgs::ModuleType	GetSelectedModuleType()	const = 0;

protected:
	BuildingWorkshop::CCategorySelectionList&	GetCategoryButtonList();
	BuildingWorkshop::CModuleList&				GetModuleList();
	BuildingWorkshop::CModuleDetailPanel&		GetModuleDetailPanel();

protected:
	void DrawBackground() const;
	void DrawCategorySelection() const;
	void DrawModuleList() const;
	void DrawModuleDetailView() const;

protected:
	virtual void OnPurchaseButtonPressed() = 0;

private:
	BuildingWorkshop::CCategorySelectionList	m_CategoryButtonList = BuildingWorkshop::CCategorySelectionList(*this);
	BuildingWorkshop::CModuleList				m_ModuleList = BuildingWorkshop::CModuleList(*this);
	BuildingWorkshop::CModuleDetailPanel		m_ModuleDetailPanel = BuildingWorkshop::CModuleDetailPanel(*this);
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui
