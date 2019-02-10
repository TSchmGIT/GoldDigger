#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class IInteractionObject
{
public:
	IInteractionObject();
	IInteractionObject(const IInteractionObject& other);
	IInteractionObject(IInteractionObject&& other);

	IInteractionObject& operator=(const IInteractionObject& other);
	IInteractionObject& operator=(IInteractionObject&& other);

	virtual ~IInteractionObject();

public:
	void Tick();
	void Draw() const;

public:
	virtual bool IsInInteractionDistance(const WorldPos& position) const = 0;
	virtual void StartInteraction() = 0;
	virtual void StopInteraction() = 0;

	virtual WorldPos GetInteractionButtonPosition() const = 0;

protected:
	virtual const WorldPos& GetInteractionOriginPosition() const = 0;

protected:
	float m_InteractionDistance = 0.0f;		///< The minimum distance to the object in order to interact with it

private:
	bool m_IsInInteractionRange = false;	///< Indicated whether the actor is currently in interaction range
	bool m_IsInteractionActive = false;		///< Indicates whether an interaction is currently active
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
