#pragma once
#include <SFML/Graphics/Color.hpp>

#include <hvsdk/Meta/DefinesSTL.h>

#include "GameSessionNew/Rendering/Fonts/EnumsFont.h"
#include "GameSessionNew/Rendering/RenderDefines.h"
#include "GameSessionNew/Rendering/RenderEnums.h"

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
