#include "stdafx.h"
#include "ModuleList.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui::BuildingWorkshop
{

//////////////////////////////////////////////////////////////////////////

CModuleList::CModuleList(const CBaseScene& baseScene)
	: m_BaseScene(baseScene)
{
}

//////////////////////////////////////////////////////////////////////////

void CModuleList::Draw() const
{
	for (const auto& moduleElement : m_ElementList)
	{
		moduleElement.Draw();
	}
}

//////////////////////////////////////////////////////////////////////////

constexpr hvgs::ScreenPos CModuleList::GetElementMargin()
{
	return { 20.0f, 20.0f };
}

//////////////////////////////////////////////////////////////////////////

CModuleElement& CModuleList::PushElement()
{
	auto& moduleElement = m_ElementList.emplace_back(m_BaseScene);

	UpdateSingleElement(moduleElement, m_ElementList.size() - 1);

	return moduleElement;
}

//////////////////////////////////////////////////////////////////////////

int CModuleList::GetMaximumElementsHorizontal() const
{
	return m_MaxElementsHor;
}

//////////////////////////////////////////////////////////////////////////

void CModuleList::SetMaximumElementsHorizontal(int maxElementsHor)
{
	m_MaxElementsHor = maxElementsHor;
}

//////////////////////////////////////////////////////////////////////////

constexpr hvgs::ScreenPos CModuleList::GetFirstElementOffset()
{
	return { 394.0f, 194.0f }; // relative: { 50.0f, 31.0f };
}

//////////////////////////////////////////////////////////////////////////

constexpr hvgs::ScreenPos CModuleList::GetElementSize()
{
	return { 124.0f, 154.0f };
}

//////////////////////////////////////////////////////////////////////////

const hvgs::Vector<hvgs::ui::BuildingWorkshop::CModuleElement>& CModuleList::GetElementList() const
{
	return m_ElementList;
}

//////////////////////////////////////////////////////////////////////////

hvgs::ui::BuildingWorkshop::CModuleElement& CModuleList::GetElement(size_t index)
{
	return m_ElementList.at(index);
}

//////////////////////////////////////////////////////////////////////////

const hvgs::Vector2& CModuleList::GetPosition() const
{
	return m_Position;
}

//////////////////////////////////////////////////////////////////////////

void CModuleList::SetPosition(const Vector2& position)
{
	m_Position = position;
}

//////////////////////////////////////////////////////////////////////////

void CModuleList::Resize(size_t newSize)
{
	if (m_ElementList.size() == newSize)
	{
		return;
	}

	m_ElementList.resize(newSize, CModuleElement(m_BaseScene));
	UpdateElements();
}

//////////////////////////////////////////////////////////////////////////

void CModuleList::UpdateElements()
{
	for (size_t i = 0; i < m_ElementList.size(); ++i)
	{
		auto& moduleElement = m_ElementList[i];
		UpdateSingleElement(moduleElement, i);
	}
}

//////////////////////////////////////////////////////////////////////////

void CModuleList::UpdateSingleElement(CModuleElement& moduleElement, size_t moduleIndex)
{
	auto xOffset = GetFirstElementOffset().x;
	xOffset += (moduleIndex % m_MaxElementsHor) * (GetElementSize().x + GetElementMargin().x);

	auto yOffset = GetFirstElementOffset().y;
	yOffset += (moduleIndex / m_MaxElementsHor) * (GetElementSize().y + GetElementMargin().y);

	ScreenPos pos{ xOffset, yOffset };
	moduleElement.SetPosition(pos);

	auto& buttonIcon = moduleElement.GetIconButton();
	buttonIcon.SetSelectionOverlayTexture(ButtonState::Default, TextureName::BUILDING_WORKSHOP_UI_SELECTION_FRAME);
	buttonIcon.SetSelectionOverlayTexture(ButtonState::Hover, TextureName::BUILDING_WORKSHOP_UI_SELECTION_FRAME_HOVER);
	buttonIcon.SetSelectionOverlayTexture(ButtonState::Pressed, TextureName::BUILDING_WORKSHOP_UI_SELECTION_FRAME_PRESSED);

}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui::BuildingWorkshop
