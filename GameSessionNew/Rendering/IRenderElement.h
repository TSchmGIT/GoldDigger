#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class IRenderElement
{

public:
	IRenderElement();
	IRenderElement(const IRenderElement& other);
	IRenderElement(IRenderElement&& other);

	IRenderElement& operator=(const IRenderElement& other);
	IRenderElement& operator=(IRenderElement&& other);
	virtual ~IRenderElement();

public:
	virtual void Draw() const = 0;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
