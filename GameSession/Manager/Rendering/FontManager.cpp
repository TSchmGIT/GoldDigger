#include "stdafx.h"
#include "FontManager.h"

#include <SFML\Graphics\Text.hpp>

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

static const String RESOURCES_PATH_FONTS("..\\Resources\\Fonts\\");

//////////////////////////////////////////////////////////////////////////

CFontManager::CFontManager()
	: m_PoolText(32, 1000)
{

}

//////////////////////////////////////////////////////////////////////////

CFontManager::~CFontManager()
{

}

//////////////////////////////////////////////////////////////////////////

void CFontManager::Init()
{
	for (size_t i = 0; i < size_t(FontName::Count); i++)
	{
		FontName fontName = FontName(i);

		std::string fileName = RESOURCES_PATH_FONTS;

		switch (fontName)
		{
		case hvgs::FontName::Arial:
			fileName += "arial.ttf";
			break;
		case hvgs::FontName::Courier_New:
			fileName += "cour.ttf";
			break;
		default:
			break;
		}

		sf::Font font;
		if (!font.loadFromFile(fileName))
		{
			LOG_ERROR("Could not load font with filename " << fileName);
			continue;
		}

		m_FontTable.emplace(std::move(fontName), std::move(font));
	}
}

//////////////////////////////////////////////////////////////////////////

sf::Text* CFontManager::PopText(String content, const FontName& fontName /*= FontName::Arial*/, unsigned int charSize /*= 30*/, const sf::Color& textColor /*= sf::Color::White*/)
{
	auto itFont = m_FontTable.find(fontName);
	ASSERT_OR_EXECUTE(itFont != m_FontTable.end(), return nullptr);

	sf::Text* text = m_PoolText.New();
	text->setFont(itFont->second);
	text->setCharacterSize(charSize);
	text->setFillColor(textColor);
	text->setStyle(sf::Text::Style::Regular);
	text->setString(content);

	return text;
}

//////////////////////////////////////////////////////////////////////////

void CFontManager::PushText(sf::Text* text)
{
	ASSERT_OR_EXECUTE(text, return);
	m_PoolText.Delete(text);
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
