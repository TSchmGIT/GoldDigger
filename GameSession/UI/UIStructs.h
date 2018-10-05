#pragma once
#include <SFML/Graphics/Color.hpp>

#include <hvsdk/Meta/DefinesSTL.h>

#include "GameSession/Rendering/Fonts/EnumsFont.h"
#include "GameSession/Rendering/RenderDefines.h"
#include "GameSession/Rendering/RenderEnums.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////

struct TextUIInfo
{
	String		Text = "";
	Alignment	TextAlignment = Alignment::Center;
	FontName	TextFont = FontName::FiraSans_Regular;
	FontSize	TextSize = FontSize(60);
	sf::Color	TextColor = sf::Color::Black;
};


//////////////////////////////////////////////////////////////////////////

}

//////////////////////////////////////////////////////////////////////////
