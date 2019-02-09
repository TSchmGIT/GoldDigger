#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{
enum class EventType : hvuint8;
}

namespace hvgs::ui
{

/////////////////////////////////////////////////////////////////////////////

class CEvent
{

public:
	CEvent();
	virtual ~CEvent();

	EventType GetType() const;

protected:
	EventType	m_Type;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui