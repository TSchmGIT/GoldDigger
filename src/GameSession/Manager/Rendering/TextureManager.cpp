//////////////////////////////////////////////////////////////////////////
// Generated by Dockyard, do not edit, manual changes will be overwritten

#include "stdafx.h"
#include "TextureManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

void CTextureManager::Init()
{
	for (size_t i = 0; i < size_t(TextureName::COUNT); i++)
	{
		auto textureName = TextureName(i);

		std::string fileName;

		switch (textureName)
		{
		case TextureName::BACKGROUND:
			fileName = R"(..\..\Resources\Textures\background.png)";
			break;
		case TextureName::ACTOR:
			fileName = R"(..\..\Resources\Textures\Actor.png)";
			break;
		case TextureName::BUTTON_DEFAULT:
			fileName = R"(..\..\Resources\Textures\Button\Default.png)";
			break;
		case TextureName::BUTTON_HOVER:
			fileName = R"(..\..\Resources\Textures\Button\Hover.png)";
			break;
		case TextureName::BUTTON_DEACTIVATED:
			fileName = R"(..\..\Resources\Textures\Button\Deactivated.png)";
			break;
		case TextureName::BUTTON_PRESSED:
			fileName = R"(..\..\Resources\Textures\Button\Pressed.png)";
			break;
		case TextureName::TILEATLAS:
			fileName = R"(..\..\Resources\Textures\TileAtlas\Final_Atlas.png)";
			break;
		case TextureName::INVENTORYMAINSPRITE:
			fileName = R"(..\..\Resources\Textures\Scenes\InventoryMainSprite.png)";
			break;
		case TextureName::ITEM_DIRT:
			fileName = R"(..\..\Resources\Textures\TileAtlas\Dirt.png)";
			break;
		case TextureName::ITEM_STONE:
			fileName = R"(..\..\Resources\Textures\TileAtlas\Stone.png)";
			break;
		case TextureName::ITEM_IRON:
			fileName = R"(..\..\Resources\Textures\TileAtlas\Iron.png)";
			break;
		case TextureName::WHITE:
			fileName = R"(..\..\Resources\Textures\TileAtlas\White.png)";
			break;
		case TextureName::BLACK:
			fileName = R"(..\..\Resources\Textures\TileAtlas\Black.png)";
			break;
		case TextureName::BUILDING_BROKER:
			fileName = R"(..\..\Resources\Textures\Buildings\Broker.png)";
			break;
		case TextureName::SCENEBUILDINGBROKER:
			fileName = R"(..\..\Resources\Textures\Scenes\BrokerUI.png)";
			break;
		case TextureName::ACTOR_THRUSTER:
			fileName = R"(..\..\Resources\Textures\Actor_Thruster.png)";
			break;
		case TextureName::BUTTONICON_XBOX_ONE_A:
			fileName = R"(..\..\Resources\Textures\Button\Platform Buttons\Xelu_FREE_keyboard&controller_prompts_pack\Xbox One\XboxOne_A.png)";
			break;
		case TextureName::BUTTONICON_XBOX_ONE_B:
			fileName = R"(..\..\Resources\Textures\Button\Platform Buttons\Xelu_FREE_keyboard&controller_prompts_pack\Xbox One\XboxOne_B.png)";
			break;
		case TextureName::BUTTONICON_XBOX_ONE_X:
			fileName = R"(..\..\Resources\Textures\Button\Platform Buttons\Xelu_FREE_keyboard&controller_prompts_pack\Xbox One\XboxOne_X.png)";
			break;
		case TextureName::BUTTONICON_XBOX_ONE_Y:
			fileName = R"(..\..\Resources\Textures\Button\Platform Buttons\Xelu_FREE_keyboard&controller_prompts_pack\Xbox One\XboxOne_Y.png)";
			break;
		case TextureName::KEYBOARDICON_E:
			fileName = R"(..\..\Resources\Textures\Button\Platform Buttons\Xelu_FREE_keyboard&controller_prompts_pack\Keyboard & Mouse\Light\Keyboard_White_E.png)";
			break;
		case TextureName::BUTTON_SPECIAL_INTERACTION:
			fileName = R"(..\..\Resources\Textures\Special Button Sprites\Interaction.png)";
			break;
		case TextureName::BACKGROUND_SPACE:
			fileName = R"(..\..\Resources\Textures\background_space.png)";
			break;
		case TextureName::COAL:
			fileName = R"(..\..\Resources\Textures\TileAtlas\Coal.png)";
			break;
		case TextureName::FUELTANK:
			fileName = R"(..\..\Resources\Textures\UI\FuelTank.png)";
			break;
		case TextureName::BUILDING_WORKSHOP:
			fileName = R"(..\..\Resources\Textures\Scenes\Building_Workshop.png)";
			break;
		case TextureName::MODULE_TANK_1:
			fileName = R"(..\..\Resources\UI\AdobeXD\Tank 1.png)";
			break;
		case TextureName::MODULE_TANK_2:
			fileName = R"(..\..\Resources\UI\AdobeXD\Tank 2.png)";
			break;
		case TextureName::MODULE_TANK_3:
			fileName = R"(..\..\Resources\UI\AdobeXD\Tank 3.png)";
			break;
		case TextureName::MODULE_TANK_4:
			fileName = R"(..\..\Resources\UI\AdobeXD\Tank 4.png)";
			break;
		case TextureName::MODULE_TANK_5:
			fileName = R"(..\..\Resources\UI\AdobeXD\Tank 5.png)";
			break;
		case TextureName::MODULE_TANK_6:
			fileName = R"(..\..\Resources\UI\AdobeXD\Tank 6.png)";
			break;
		case TextureName::MODULE_TANK_7:
			fileName = R"(..\..\Resources\UI\AdobeXD\Tank 7.png)";
			break;
		case TextureName::MODULE_TANK_8:
			fileName = R"(..\..\Resources\UI\AdobeXD\Tank 8.png)";
			break;
		case TextureName::MODULE_MOTOR_1:
			fileName = R"(..\..\Resources\UI\AdobeXD\Motor 1.png)";
			break;
		case TextureName::MODULE_MOTOR_2:
			fileName = R"(..\..\Resources\UI\AdobeXD\Motor 2.png)";
			break;
		case TextureName::MODULE_MOTOR_3:
			fileName = R"(..\..\Resources\UI\AdobeXD\Motor 3.png)";
			break;
		case TextureName::MODULE_MOTOR_4:
			fileName = R"(..\..\Resources\UI\AdobeXD\Motor 4.png)";
			break;
		case TextureName::MODULE_MOTOR_5:
			fileName = R"(..\..\Resources\UI\AdobeXD\Motor 5.png)";
			break;
		case TextureName::MODULE_MOTOR_6:
			fileName = R"(..\..\Resources\UI\AdobeXD\Motor 6.png)";
			break;
		case TextureName::MODULE_MOTOR_7:
			fileName = R"(..\..\Resources\UI\AdobeXD\Motor 7.png)";
			break;
		case TextureName::MODULE_MOTOR_8:
			fileName = R"(..\..\Resources\UI\AdobeXD\Motor 8.png)";
			break;
		case TextureName::BUILDING_WORKSHOP_UI_SELECTION_FRAME:
			fileName = R"(..\..\Resources\UI\AdobeXD\Selectionframe.png)";
			break;
		case TextureName::BUILDING_WORKSHOP_UI_SELECTION_FRAME_HOVER:
			fileName = R"(..\..\Resources\UI\AdobeXD\Selectionframe_hover.png)";
			break;
		case TextureName::BUILDING_WORKSHOP_UI_SELECTION_FRAME_PRESSED:
			fileName = R"(..\..\Resources\UI\AdobeXD\Selectionframe_pressed.png)";
			break;
		case TextureName::BUILDING_WORKSHOP_UI_CLOSE_BUTTON:
			fileName = R"(..\..\Resources\UI\AdobeXD\Button_Close.png)";
			break;

		default:
			break;
		}

		auto texture = std::make_unique<sf::Texture>();
		if (!texture->loadFromFile(fileName))
		{
			LOG_ERROR("Could not load texture with filename " << fileName);
			continue;
		}

		m_TextureTable.emplace(std::move(textureName), std::move(texture));
	}

}

//////////////////////////////////////////////////////////////////////////

const sf::Texture* CTextureManager::GetTexture(TextureName textureName) const
{
	auto it = m_TextureTable.find(textureName);
	ASSERT_OR_EXECUTE(it != m_TextureTable.end(), return nullptr);
	return it->second.get();
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
