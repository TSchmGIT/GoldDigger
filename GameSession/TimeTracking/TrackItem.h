#pragma once

/////////////////////////////////////////////////////////////////////////////
namespace hvgs
{
class CTrackItem;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CTrackItem
{

public:
	CTrackItem(TimePoint timePoint, CTrackItem* parent);
	virtual ~CTrackItem();

public:
	const 
	const CTrackItem* AddChild(String key);

protected:
	TimePoint m_StartTime;

	CTrackItem*						m_Parent;
	Vector<UniquePtr<CTrackItem>>	m_ChildItems;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
