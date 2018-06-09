#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class C{{PropertyName}}
{
public:
	C{{PropertyName}}() = default;
	virtual ~C{{PropertyName}}() = default;

public:
{{SingleAttributeMethodBegin}}
    {{AttributeType}} Get{{AttributeName}}() const;
{{SingleAttributeMethodEnd}}
protected:
{{AttributeListBegin}}
    {{AttributeType}} {{AttributeName}} = {{AttributeDefaultValue}};
{{AttributeListEnd}}
};

/////////////////////////////////////////////////////////////////////////////

    } // hvgs
