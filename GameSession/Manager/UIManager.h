#pragma once
#include "SingletonBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{
class IUIEventHandler;
}

namespace hvgs::ui
{

/////////////////////////////////////////////////////////////////////////////

class CUIManager : public CSingletonBase<CUIManager>
{

public:
	CUIManager();
	virtual ~CUIManager();

protected:
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
