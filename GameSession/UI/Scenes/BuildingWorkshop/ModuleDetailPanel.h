#pragma once
#include "GameSession/Actor/Equipment/Modules/EnumsModules.h"
#include "GameSession/Data/DataDefines.h"
#include "UI/Elements/UIButton.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvda
{
class CDataTemplateModuleBase;
}


namespace hvgs::ui
{
class CBuildingWorkshopSceneBase;
}

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui::BuildingWorkshop
{

/////////////////////////////////////////////////////////////////////////////

class CModuleDetailPanel
{

public:
	CModuleDetailPanel() = delete;
	CModuleDetailPanel(const CBuildingWorkshopSceneBase& workshopScene);
	virtual ~CModuleDetailPanel() = default;


public:
	void Draw() const;

public:
	void UpdateSelectedModule(ModuleGUID moduleGUID, ModuleType moduleType);

public:
	CUIButton& GetPurchaseButton();
	const CUIButton& GetPurchaseButton() const;

private:
	const hvda::CDataTemplateModuleBase* GetSelectedModule() const;

private:
	void InitPurchaseButton();

	void DrawModuleIcon() const;

	void DrawName() const;
	void DrawCosts() const;
	void DrawPurchaseButton() const;

	void DrawModuleDetails() const;
	void DrawDetailsHull() const;
	void DrawDetailsMotor() const;
	void DrawDetailsDrill() const;
	void DrawDetailsCargo() const;
	void DrawDetailsFuelTank() const;

private:
	const CBuildingWorkshopSceneBase& m_WorkshopScene;

	const hvda::CDataTemplateModuleBase* m_SelectedModule = nullptr;

private:
	CUIButton	m_PurchaseButton;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui::BuildingWorkshop
