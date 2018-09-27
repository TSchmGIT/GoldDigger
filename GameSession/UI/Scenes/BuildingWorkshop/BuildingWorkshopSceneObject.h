#pragma once
#include "GameSession/UI/Elements/UIButton.h"
#include "GameSession/UI/Elements/UIWidget.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////

namespace BuildingWorkshop
{

//////////////////////////////////////////////////////////////////////////

class CCategorySelectionList : public IUIWidget
{
public:
	CCategorySelectionList(const CBaseScene& baseScene);
	~CCategorySelectionList() = default;

	void Draw() const;

public:
	Vector<CUIButton>& GetButtonList();

	void PushElement();
	void Resize(size_t newSize);

//protected:
//	void OnPivotUpdate() override;

private:
	void UpdateButtonPositions();

private:
	const CBaseScene& m_BaseScene;

	Vector<CUIButton> m_ButtonList;

	Vector2 m_PivotPos = Vector2{ 0.0f, 0.0f };
};

//////////////////////////////////////////////////////////////////////////

class CModuleElement
{
	enum class ModulePurchaseState
	{
		Free,
		Owned,
		ForSale
	};

public:
	void Draw() const;

private:
	CUIButton m_IconButton;
	ModulePurchaseState m_ModuleState;
};

class CModuleList
{
public:
	void Draw() const;

private:
	Vector<CModuleElement> m_ElementList;

};

//////////////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui
