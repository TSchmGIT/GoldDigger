#pragma once
#include "GameSession/Manager/SingletonBase.h"
#include "GameSession/Rendering/Fonts/EnumsFont.h"
#include "GameSession/Rendering/RenderDefines.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CFontManager : public CSingletonBase<CFontManager>
{

public:
	CFontManager();
	virtual ~CFontManager();

	void Init();

public:
	sf::Text* PopText(String content, const FontName& fontName = FontName::FiraSans_Regular, FontSize fontSize = FontSize(30), const sf::Color& textColor = sf::Color::White);
	void PushText(sf::Text* text);

protected:
	Map<FontName, sf::Font> m_FontTable;

	hvsdk::CObjectPool<sf::Text> m_PoolText;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
