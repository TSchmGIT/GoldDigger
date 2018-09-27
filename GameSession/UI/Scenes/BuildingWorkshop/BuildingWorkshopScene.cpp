#include "stdafx.h"
#include "BuildingWorkshopScene.h"

#include "GameSession/Actor/Equipment/Modules/EnumsModules.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopScene::Draw() const
{
	CBuildingWorkshopSceneBase::Draw();
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopScene::Enter()
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
			break;
		case hvgs::ModuleType::Motor:
			moduleTypeText = "Motor";
			break;
		case hvgs::ModuleType::Drill:
			moduleTypeText = "Drill";
			break;
		case hvgs::ModuleType::Cargo:
			moduleTypeText = "Cargo";
			break;
		case hvgs::ModuleType::FuelTank:
			moduleTypeText = "Fuel Tank";
			break;
		}

		button.SetText(moduleTypeText);
		button.SetTextSize(FontSize(30));
		button.SetTextFont(FontName::FiraSans_Regular);
	}
}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui
