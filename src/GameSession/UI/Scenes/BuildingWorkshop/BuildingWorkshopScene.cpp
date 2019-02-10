#include "stdafx.h"
#include "BuildingWorkshopScene.h"

#include "GameSession/Actor/Actor.h"
#include "GameSession/Actor/Economy/ActorEconomy.h"
#include "GameSession/Actor/Equipment/Equipment.h"
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleBase.h"
#include "GameSession/Actor/Equipment/Modules/DefinesModules.h"
#include "GameSession/Actor/Equipment/Modules/EnumsModules.h"
#include "GameSession/Buildings/BuildingWorkshop.h"
#include "GameSession/Data/DataModuleManager.h"
#include "GameSession/UI/Scenes/BuildingWorkshop/ModuleElement.h"
#include "GameSession/UI/Scenes/Meta/SceneManager.h"
#include "GameSession/World/World.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopScene::Draw() const
{
	CBuildingWorkshopSceneBase::Draw();
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopScene::Enter()
{
	SetSelectedModuleType(ModuleType::FuelTank);

	UpdateCategoryList();
	UpdateModuleList();
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopScene::SyncTickVisible()
{
	CBuildingWorkshopSceneBase::SyncTickVisible();

	// Disable purchase button
	auto& moduleDetailPanel = GetModuleDetailPanel();

	auto& purchaseButton = moduleDetailPanel.GetPurchaseButton();
	if (auto& economy = CWorld::Get().GetActor().GetEconomy();
		economy.HasOwnership(m_SelectedModuleGUID, m_SelectedModuleType))
	{
		purchaseButton.SetIsDisabled(true);
	}
	else
	{
		const auto* selectedModule = hvda::CDataModuleManager::Get().GetModuleTemplate(GetSelectedModuleGUID(), GetSelectedModuleType());
		ASSERT_OR_EXECUTE(selectedModule, return);
		MoneyAmount selectedModulePrice = selectedModule->GetPrice();
		MoneyAmount currentMoney = CWorld::Get().GetActor().GetEconomy().GetMoney();

		purchaseButton.SetIsDisabled(currentMoney < selectedModulePrice);
	}
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopScene::UpdateCategoryList()
{
	auto& categoryButtonList = GetCategoryButtonList();
	categoryButtonList.Resize(size_t(ModuleType::Count));

	auto& buttonList = categoryButtonList.GetButtonList();
	for (size_t i = 0; i < buttonList.size(); ++i)
	{
		auto& button = buttonList[i];
		auto moduleType = ModuleType(i);

		std::string moduleTypeText = "";
		switch (moduleType)
		{
		case hvgs::ModuleType::Hull:
			moduleTypeText = "Hull";
			button.SetIsDisabled(true);
			break;
		case hvgs::ModuleType::Motor:
			moduleTypeText = "Motor";
			break;
		case hvgs::ModuleType::Drill:
			moduleTypeText = "Drill";
			button.SetIsDisabled(true);
			break;
		case hvgs::ModuleType::Cargo:
			moduleTypeText = "Cargo";
			button.SetIsDisabled(true);
			break;
		case hvgs::ModuleType::FuelTank:
			moduleTypeText = "Fuel Tank";
			break;
		}

		button.SetText(moduleTypeText);
		button.SetTextSize(FontSize(30));
		button.SetTextFont(FontName::FiraSans_Regular);

		button.SetIsSelected(m_SelectedModuleType == moduleType);
		button.SetMetaData(int(moduleType));

		button.SetAction(boost::bind(&CBuildingWorkshopScene::OnCategoryButtonPressed, this, boost::cref(button)));
	}
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopScene::UpdateModuleList()
{
	auto& moduleList = GetModuleList();

	const auto& moduleMap = hvda::CDataModuleManager::Get().GetModuleMap(m_SelectedModuleType);
	moduleList.Resize(moduleMap.size());


	const auto& actor = CWorld::Get().GetActor();
	const auto& economy = actor.GetEconomy();
	const auto& equipment = actor.GetEquipment();
	const auto* currentModule = equipment.GetModule(m_SelectedModuleType);
	ASSERT_OR_EXECUTE(currentModule, return);
	auto currentModuleGUID = currentModule->GetGUID();

	size_t index = 0;
	for (const auto& kvPair : moduleMap)
	{
		auto& moduleElement = moduleList.GetElement(index);
		index++;

		const hvda::CDataTemplateModuleBase& dataModule = *kvPair.second;
		auto moduleGUID = dataModule.GetGUID();

		if (moduleGUID == currentModuleGUID)
		{
			moduleElement.SetModuleState(BuildingWorkshop::CModuleElement::ModulePurchaseState::Equipped);
		}
		else if (economy.HasOwnership(moduleGUID, m_SelectedModuleType))
		{
			moduleElement.SetModuleState(BuildingWorkshop::CModuleElement::ModulePurchaseState::Owned);
		}
		else if (auto modulePrice = dataModule.GetPrice(); modulePrice == MoneyAmount(0))
		{
			moduleElement.SetModuleState(BuildingWorkshop::CModuleElement::ModulePurchaseState::Free);
		}
		else
		{
			moduleElement.SetModuleState(BuildingWorkshop::CModuleElement::ModulePurchaseState::ForSale);
			moduleElement.SetModulePrice(modulePrice);
		}

		TextureName texture = dataModule.GetTexture();
		moduleElement.SetModuleTexture(texture);

		auto& buttonIcon = moduleElement.GetIconButton();

		buttonIcon.SetMetaData(int(moduleGUID));
		buttonIcon.SetIsSelected(moduleGUID == m_SelectedModuleGUID);
		buttonIcon.SetAction(boost::bind(&CBuildingWorkshopScene::OnModuleElementPressed, this, boost::cref(moduleElement)));
	}
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopScene::OnCategoryButtonPressed(const CUIButton& button)
{
	auto moduleType = ModuleType(button.GetMetaData());
	SetSelectedModuleType(moduleType);
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopScene::OnModuleElementPressed(const BuildingWorkshop::CModuleElement& moduleElement)
{
	ModuleGUID moduleGUID = ModuleGUID(moduleElement.GetIconButton().GetMetaData());

	SetSelectedModuleGUID(moduleGUID);
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopScene::UpdateModuleDetailPanel()
{
	auto& moduleDetailPanel = GetModuleDetailPanel();
	moduleDetailPanel.UpdateSelectedModule(m_SelectedModuleGUID, m_SelectedModuleType);
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopScene::SetSelectedModuleType(ModuleType moduleType)
{
	if (moduleType == m_SelectedModuleType)
	{
		return;
	}

	m_SelectedModuleType = moduleType;

	const auto& moduleMap = hvda::CDataModuleManager::Get().GetModuleMap(m_SelectedModuleType);
	ASSERT_OR_EXECUTE(!moduleMap.empty(), return);

	ModuleGUID firstModuleGUID = moduleMap.begin()->first;
	SetSelectedModuleGUID(firstModuleGUID);

	UpdateCategoryList();
	UpdateModuleList();
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopScene::SetSelectedModuleGUID(ModuleGUID moduleGUID)
{
	if (moduleGUID == m_SelectedModuleGUID)
	{
		return;
	}

	m_SelectedModuleGUID = moduleGUID;
	UpdateModuleList();
	UpdateModuleDetailPanel();
}

//////////////////////////////////////////////////////////////////////////

ModuleGUID CBuildingWorkshopScene::GetSelectedModuleGUID() const
{
	return m_SelectedModuleGUID;
}

//////////////////////////////////////////////////////////////////////////

hvgs::ModuleType CBuildingWorkshopScene::GetSelectedModuleType() const
{
	return m_SelectedModuleType;
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopScene::OnPurchaseButtonPressed()
{
	auto buildingWorkshop = CWorld::Get().GetBuilding<hvgs::CBuildingWorkshop>();
	ASSERT_OR_EXECUTE(buildingWorkshop, return);

	auto& actor = CWorld::Get().GetActor();
	auto& economy = actor.GetEconomy();
	auto& equipment = actor.GetEquipment();

	buildingWorkshop->PurchaseModule(economy, equipment, m_SelectedModuleType, m_SelectedModuleGUID);

	UpdateModuleList();
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopScene::OnCloseButtonPressed()
{
	CSceneManager::GetMutable().LeaveState(GetSceneID());
}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui
