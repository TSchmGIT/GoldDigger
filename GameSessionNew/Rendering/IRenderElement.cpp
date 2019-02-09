#include "stdafx.h"
#include "IRenderElement.h"

#include "GameSessionNew/Manager\RenderManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

IRenderElement::IRenderElement()
{
	CRenderManager::GetMutable().RegisterRenderElement(this);
}

//////////////////////////////////////////////////////////////////////////

IRenderElement::IRenderElement(const IRenderElement&)
{
	CRenderManager::GetMutable().RegisterRenderElement(this);
}

//////////////////////////////////////////////////////////////////////////

IRenderElement::IRenderElement(IRenderElement&&)
{
	CRenderManager::GetMutable().RegisterRenderElement(this);
}

//////////////////////////////////////////////////////////////////////////

IRenderElement& IRenderElement::operator=(const IRenderElement&)
{
	ASSERT_TEXT(false, "No implementation for method IRenderElement::operator=(const IRenderElement& other)");
	return *this;
}

//////////////////////////////////////////////////////////////////////////

IRenderElement& IRenderElement::operator=(IRenderElement&&)
{
	ASSERT_TEXT(false, "No implementation for method IRenderElement::operator=(IRenderElement&& other)");
	return *this;
}

//////////////////////////////////////////////////////////////////////////

IRenderElement::~IRenderElement()
{
	CRenderManager::GetMutable().UnregisterRenderElement(this);
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
