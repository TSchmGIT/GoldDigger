#include "stdafx.h"
#include "FontManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CFontManager::CFontManager()
{

}

//////////////////////////////////////////////////////////////////////////

CFontManager::~CFontManager()
{

}

//////////////////////////////////////////////////////////////////////////

void CFontManager::Init()
{
	for (size_t i = 0; i < size_t(FontName::FontCount); i++)
	{
		FontName fontName = FontName(i);

		std::string fileName;

		switch (fontName)
		{
		case hvgs::FontName::Arial:
			fileName = "Arial.ttf";
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

} // hvgs
