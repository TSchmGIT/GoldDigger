#pragma once
#include "GameSession/UI/Scenes/BuildingWorkshop/BuildingWorkshopSceneBase.h"

#include "GameSession/Actor/Equipment/Modules/EnumsModules.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

/////////////////////////////////////////////////////////////////////////////

class CBuildingWorkshopScene : public CBuildingWorkshopSceneBase
{

public:
	CBuildingWorkshopScene() = default;
	virtual ~CBuildingWorkshopScene() = default;

	void Draw() const override;

public:
	ModuleGUID GetSelectedModuleGUID() const override;
	ModuleType GetSelectedModuleType() const override;

protected:
	void Enter() override;
	void SyncTickVisible() override;

	void UpdateCategoryList();
	void UpdateModuleList();
	void UpdateModuleDetailPanel();

protected:
	void SetSelectedModuleType(ModuleType moduleType);
	void SetSelectedModuleGUID(ModuleGUID moduleGUID);

protected:
	void OnCategoryButtonPressed(const CUIButton& button);
	void OnModuleElementPressed(const BuildingWorkshop::CModuleElement& moduleElement);

	void OnPurchaseButtonPressed() override;

protected:
	ModuleType		m_SelectedModuleType = ModuleType::Invalid;
	ModuleGUID		m_SelectedModuleGUID = MODULE_GUID_INVALID;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui
