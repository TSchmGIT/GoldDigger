#include "stdafx.h"
#include "BuildingWorkshopSceneObject.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////

namespace BuildingWorkshop
{

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CCategorySelectionList::CCategorySelectionList(const CBaseScene& baseScene)
	: m_BaseScene(baseScene)
{
}

//////////////////////////////////////////////////////////////////////////

hvgs::Vector<hvgs::ui::CUIButton>& CCategorySelectionList::GetButtonList()
{
	return m_ButtonList;
}

//////////////////////////////////////////////////////////////////////////

void CCategorySelectionList::PushElement()
{
	m_ButtonList.emplace_back(m_BaseScene);
	UpdateButtonPositions();
}

//////////////////////////////////////////////////////////////////////////

void CCategorySelectionList::Resize(size_t newSize)
{
	if (newSize == m_ButtonList.size())
	{
		return;
	}

	m_ButtonList.resize(newSize, CUIButton(m_BaseScene));
	UpdateButtonPositions();
}

//////////////////////////////////////////////////////////////////////////

void CCategorySelectionList::UpdateButtonPositions()
{
	constexpr Vector2 firstButtonPos{ 75.0f, 194.0f };
	constexpr float distanceBetweenButtons = 17.0f;

	constexpr Vector2 buttonSize{ 190.0f, 46.0f };

	for (size_t i = 0; i < m_ButtonList.size(); ++i)
	{
		auto& button = m_ButtonList[i];

		auto pos = firstButtonPos + i * Vector2{ 0.0f, distanceBetweenButtons + buttonSize.y };
		button.SetPosition(pos);
		button.SetSize(buttonSize);
	}
}

//////////////////////////////////////////////////////////////////////////

void CCategorySelectionList::Draw() const
{
	for (const auto& button : m_ButtonList)
	{
		button.Draw();
	}
}

//////////////////////////////////////////////////////////////////////////

}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui
