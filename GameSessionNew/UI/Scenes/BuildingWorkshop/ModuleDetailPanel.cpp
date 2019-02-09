#include "stdafx.h"
#include "ModuleDetailPanel.h"

#include "GameSessionNew/UI/Scenes/BuildingWorkshop/BuildingWorkshopSceneBase.h"

#include "GameSessionNew/Data/DataModuleManager.h"
#include "GameSessionNew/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleBase.h"

#include "GameSessionNew/Actor/Actor.h"
#include "GameSessionNew/Actor/Economy/ActorEconomy.h"
#include "GameSessionNew/Actor/Economy/EconomyTypes.h"
#include "GameSessionNew/Manager/RenderManager.h"
#include "GameSessionNew/World/World.h"
#include "Actor/Equipment/Modules/ModuleHelper.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui::BuildingWorkshop
{

//////////////////////////////////////////////////////////////////////////

CModuleDetailPanel::CModuleDetailPanel(const CBuildingWorkshopSceneBase& workshopScene)
	: m_WorkshopScene(workshopScene)
	, m_PurchaseButton(workshopScene)
{
	InitPurchaseButton();
}

//////////////////////////////////////////////////////////////////////////

void CModuleDetailPanel::Draw() const
{
	DrawModuleIcon();

	DrawName();
	DrawModuleDetails();
	DrawCosts();

	DrawPurchaseButton();
}

//////////////////////////////////////////////////////////////////////////

void CModuleDetailPanel::UpdateSelectedModule(ModuleGUID moduleGUID, ModuleType moduleType)
{
	const auto* moduleTemplate = hvda::CDataModuleManager::Get().GetModuleTemplate(moduleGUID, moduleType);
	m_SelectedModule = moduleTemplate;
}

//////////////////////////////////////////////////////////////////////////

const hvda::CDataTemplateModuleBase* CModuleDetailPanel::GetSelectedModule() const
{
	return m_SelectedModule;
}

//////////////////////////////////////////////////////////////////////////

void CModuleDetailPanel::DrawModuleIcon() const
{
	const auto* moduleTemplate = GetSelectedModule();
	ASSERT_OR_EXECUTE(moduleTemplate, return);

	TextureName moduleTexture = moduleTemplate->GetTexture();

	constexpr Vector2 spritePos{ 1199.0f, 194.0f };
	constexpr Vector2 spriteSize{ 191.0f, 191.0f };

	CRenderManager::GetMutable().DrawSpriteUI(spritePos, moduleTexture, spriteSize, Alignment::TopLeft);
}

//////////////////////////////////////////////////////////////////////////

void CModuleDetailPanel::DrawName() const
{
	const auto* moduleTemplate = GetSelectedModule();
	ASSERT_OR_EXECUTE(moduleTemplate, return);

	constexpr Vector2 textPos{ 1294.0f, 424.0f };

	const auto& moduleName = moduleTemplate->GetName();
	CRenderManager::GetMutable().DrawTextUI(textPos, moduleName, Alignment::Center, FontName::FiraSans_Regular, FontSize(39), sf::Color::Black);
}

//////////////////////////////////////////////////////////////////////////

void CModuleDetailPanel::DrawModuleDetails() const
{
	const auto* moduleTemplate = GetSelectedModule();
	ASSERT_OR_EXECUTE(moduleTemplate, return);

	switch (moduleTemplate->GetType())
	{
	case hvgs::ModuleType::Hull:
		return DrawDetailsHull();
	case hvgs::ModuleType::Motor:
		return DrawDetailsMotor();
	case hvgs::ModuleType::Drill:
		return DrawDetailsDrill();
	case hvgs::ModuleType::Cargo:
		return DrawDetailsCargo();
	case hvgs::ModuleType::FuelTank:
		return DrawDetailsFuelTank();
	}
}

//////////////////////////////////////////////////////////////////////////

void CModuleDetailPanel::DrawCosts() const
{

	const auto* moduleTemplate = GetSelectedModule();
	ASSERT_OR_EXECUTE(moduleTemplate, return);

	MoneyAmount currentMoney = CWorld::Get().GetActor().GetEconomy().GetMoney();

	{
		auto currentMoneyString = std::to_string(currentMoney.get()) + " $";

		constexpr Vector2 currentMoneyLabelPos{ 1109.0f, 656.0f };
		constexpr Vector2 currentMoneyPos{ 1481.0f, 656.0f };
		CRenderManager::GetMutable().DrawTextUI(currentMoneyLabelPos, "Money:", Alignment::TopLeft, FontName::FiraSans_Regular, FontSize(25), sf::Color::Black);
		CRenderManager::GetMutable().DrawTextUI(currentMoneyPos, currentMoneyString, Alignment::TopRight, FontName::FiraSans_Regular, FontSize(25), sf::Color::Black);
	}

	//////////////////////////////////////////////////////////////////////////

	MoneyAmount moduleCosts = moduleTemplate->GetPrice();

	{
		auto moduleCostsString = std::to_string(moduleCosts.get()) + " $";

		constexpr Vector2 moduleCostsLabelPos{ 1109.0f, 693.0f };
		constexpr Vector2 moduleCostsPos{ 1481.0f, 693.0f };
		CRenderManager::GetMutable().DrawTextUI(moduleCostsLabelPos, "Costs:", Alignment::TopLeft, FontName::FiraSans_Bold, FontSize(25), sf::Color::Black);
		CRenderManager::GetMutable().DrawTextUI(moduleCostsPos, moduleCostsString, Alignment::TopRight, FontName::FiraSans_Bold, FontSize(25), sf::Color::Black);
	}

	//////////////////////////////////////////////////////////////////////////

	MoneyAmount moneyAfterPurchase = currentMoney - moduleCosts;

	{
		auto moneyAfterPurchaseString = std::to_string(moneyAfterPurchase.get()) + " $";

		constexpr Vector2 moneyAfterPurchaseLabelPos{ 1109.0f, 730.0f };
		constexpr Vector2 moneyAfterPurchasePos{ 1481.0f, 730.0f };
		CRenderManager::GetMutable().DrawTextUI(moneyAfterPurchaseLabelPos, "After purchase:", Alignment::TopLeft, FontName::FiraSans_Regular, FontSize(25), sf::Color::Black);
		CRenderManager::GetMutable().DrawTextUI(moneyAfterPurchasePos, moneyAfterPurchaseString, Alignment::TopRight, FontName::FiraSans_Regular, FontSize(25), sf::Color::Black);
	}
}

//////////////////////////////////////////////////////////////////////////

void CModuleDetailPanel::DrawPurchaseButton() const
{
	m_PurchaseButton.Draw();
}

//////////////////////////////////////////////////////////////////////////

void CModuleDetailPanel::InitPurchaseButton()
{
	constexpr ScreenPos purchaseButtonPos{ 1294.0f, 808.0f };
	constexpr ScreenPos purchaseButtonSize{ 372.0f, 48.0f };

	m_PurchaseButton.SetPosition(purchaseButtonPos);
	m_PurchaseButton.SetSize(purchaseButtonSize);
	m_PurchaseButton.SetAlignment(Alignment::Center);

	m_PurchaseButton.SetText("Purchase");
	m_PurchaseButton.SetTextAlignment(Alignment::Center);
	m_PurchaseButton.SetTextFont(FontName::FiraSans_Regular);
	m_PurchaseButton.SetTextSize(FontSize(25));
}

//////////////////////////////////////////////////////////////////////////

hvgs::ui::CUIButton& CModuleDetailPanel::GetPurchaseButton()
{
	return m_PurchaseButton;
}

//////////////////////////////////////////////////////////////////////////

const hvgs::ui::CUIButton& CModuleDetailPanel::GetPurchaseButton() const
{
	return m_PurchaseButton;
}

//////////////////////////////////////////////////////////////////////////

void CModuleDetailPanel::DrawDetailsHull() const
{

}

//////////////////////////////////////////////////////////////////////////

void CModuleDetailPanel::DrawDetailsMotor() const
{

}

//////////////////////////////////////////////////////////////////////////

void CModuleDetailPanel::DrawDetailsDrill() const
{

}

//////////////////////////////////////////////////////////////////////////

void CModuleDetailPanel::DrawDetailsCargo() const
{

}

//////////////////////////////////////////////////////////////////////////

void CModuleDetailPanel::DrawDetailsFuelTank() const
{
	const auto* moduleTemplate = GetSelectedModule();
	const auto* moduleTemplateFuelTank = dynamic_cast<const hvda::CDataTemplateModuleFuelTank*>(moduleTemplate);
	ASSERT_OR_EXECUTE(moduleTemplate, return);

	auto fuelType = moduleTemplateFuelTank->GetFuelType();

	{
		const auto& fuelTypeString = hvda::CModuleHelper::ConvertFuelTypeToString(fuelType);

		constexpr Vector2 fuelCapacityLabelPos{ 1109.0f, 477.0f };
		constexpr Vector2 fuelCapacityPos{ 1481.0f, 477.0f };
		CRenderManager::GetMutable().DrawTextUI(fuelCapacityLabelPos, "Fuel Type:", Alignment::TopLeft, FontName::FiraSans_Regular, FontSize(25), sf::Color::Black);
		CRenderManager::GetMutable().DrawTextUI(fuelCapacityPos, fuelTypeString, Alignment::TopRight, FontName::FiraSans_Regular, FontSize(25), sf::Color::Black);
	}

	//////////////////////////////////////////////////////////////////////////

	FuelAmount fuelCapacity = moduleTemplateFuelTank->GetCapacity();

	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(0) << fuelCapacity.get() << " L";
		auto fuelCapacityString = ss.str();

		constexpr Vector2 fuelCapacityLabelPos{ 1109.0f, 514.0f };
		constexpr Vector2 fuelCapacityPos{ 1481.0f, 514.0f };
		CRenderManager::GetMutable().DrawTextUI(fuelCapacityLabelPos, "Capacity:", Alignment::TopLeft, FontName::FiraSans_Regular, FontSize(25), sf::Color::Black);
		CRenderManager::GetMutable().DrawTextUI(fuelCapacityPos, fuelCapacityString, Alignment::TopRight, FontName::FiraSans_Regular, FontSize(25), sf::Color::Black);
	}

	//////////////////////////////////////////////////////////////////////////

	//FuelConsumption fuelConsumption = moduleTemplateFuelTank->GetConsumption();
	FuelConsumption fuelConsumption = FuelConsumption(20);

	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(0) << fuelConsumption.get() << " L/s";
		auto fuelConsumptionString = ss.str();

		constexpr Vector2 fuelConsumptionLabelPos{ 1109.0f, 551.0f };
		constexpr Vector2 fuelConsumptionPos{ 1481.0f, 551.0f };
		CRenderManager::GetMutable().DrawTextUI(fuelConsumptionLabelPos, "Consumption:", Alignment::TopLeft, FontName::FiraSans_Regular, FontSize(25), sf::Color::Black);
		CRenderManager::GetMutable().DrawTextUI(fuelConsumptionPos, fuelConsumptionString, Alignment::TopRight, FontName::FiraSans_Regular, FontSize(25), sf::Color::Black);
	}
}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui::BuildingWorkshop
