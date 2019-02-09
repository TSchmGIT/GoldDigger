#pragma once
#include "GameSessionNew/Manager/RenderManager.h"
#include "GameSessionNew/Meta/Defines.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CUIScope
{

public:
	CUIScope(const ScreenPos& pivotPosition)
		: m_PivotPosition(pivotPosition)
	{
		m_LastUIScope = CRenderManager::Get().GetCurrentUIScope();

		if (m_LastUIScope)
		{
			m_PivotPosition += m_LastUIScope->m_PivotPosition;
		}

		CRenderManager::GetMutable().SetCurrentUIScope(this);
	}

	~CUIScope()
	{
		CRenderManager::GetMutable().SetCurrentUIScope(m_LastUIScope);
	}

public:
	constexpr const ScreenPos& GetPivotPosition() const
	{
		return m_PivotPosition;
	}

protected:
	const CUIScope* m_LastUIScope = nullptr;

	ScreenPos m_PivotPosition = Vector2(0.0f, 0.0f);
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
