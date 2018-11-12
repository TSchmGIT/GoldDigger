#pragma once
#include "ModuleElement.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs::ui::BuildingWorkshop
{

/////////////////////////////////////////////////////////////////////////////

class CModuleList
{

public:
	CModuleList(const CBaseScene& baseScene);
	virtual ~CModuleList() = default;

public:
	void Draw() const;

	const Vector2& GetPosition() const;
	void SetPosition(const Vector2& position);

	CModuleElement& GetElement(size_t index);

	const Vector<CModuleElement>& GetElementList() const;
	CModuleElement& PushElement();
	void Resize(size_t newSize);

public:
	int GetMaximumElementsHorizontal() const;
	void SetMaximumElementsHorizontal(int maxElementsHor);

	constexpr static ScreenPos	GetElementMargin();
	constexpr static ScreenPos	GetFirstElementOffset();
	constexpr static ScreenPos	GetElementSize();

private:
	void UpdateElements();
	void UpdateSingleElement(CModuleElement& moduleElement, size_t moduleIndex);


private:
	const CBaseScene&	m_BaseScene;
	ScreenPos			m_Position;

	Vector<CModuleElement> m_ElementList;

	int					m_MaxElementsHor = 0;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui::BuildingWorkshop
