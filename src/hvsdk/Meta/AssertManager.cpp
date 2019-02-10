#include "stdafx.h"
#include "AssertManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvsdk
{

//////////////////////////////////////////////////////////////////////////

void CAssertManager::CreateErrorAssert(const std::string& errorMessage)
{
	int msgID = MessageBox(
		nullptr,
		std::wstring(errorMessage.begin(), errorMessage.end()).c_str(),
		L"ASSERT",
		MB_ICONERROR | MB_ABORTRETRYIGNORE | MB_DEFBUTTON3);

	switch (msgID)
	{
	case IDABORT:
		break;
	case IDRETRY:
		break;
	case IDIGNORE:
		break;
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////

} // hvsdk
