#include "stdafx.h"
#include "CameraManager.h"

#include "GameSession/Camera/Camera.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CCameraManager::CCameraManager()
	: m_ActiveCamera(nullptr)
{

}

//////////////////////////////////////////////////////////////////////////

CCameraManager::~CCameraManager()
{

}

//////////////////////////////////////////////////////////////////////////

void CCameraManager::Init()
{
	m_CameraList.emplace_back();
	m_ActiveCamera = &m_CameraList.back();
}

//////////////////////////////////////////////////////////////////////////

void CCameraManager::Tick()
{
	for (CCamera& camera : m_CameraList)
	{
		camera.Tick();
	}
}

//////////////////////////////////////////////////////////////////////////

const hvgs::CCamera* CCameraManager::GetActive() const
{
	return m_ActiveCamera;
}

//////////////////////////////////////////////////////////////////////////

hvgs::CCamera* CCameraManager::GetActive()
{
	return m_ActiveCamera;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
