#pragma once

#pragma comment(lib, "Msimg32")

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <math.h>
#include <assert.h>


// STL
#include <vector>
#include <map>
#include <queue>
#include <list>

using namespace std;

//========================================
//##			게임 그룹				##
//========================================
enum class GROUP_GAMEOBJ
{
	BACKGROUND,
	FLOOR,
	TILE,
	DEFAULT,
	ENEMY,
	PLAYER,

	UI,
	SIZE,
};

enum class GROUP_SCENE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	SIZE,
};

//========================================
//##			이벤트 타입 그룹			##
//========================================

enum class TYPE_EVENT
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	CHANGE_SCENE,

	SIZE,
};

#include "Logger.h"
#include "CSingleton.h"
#include "struct.h"

//========================================
//##		Core DC의 GDI 그룹			##
//========================================
enum class TYPE_BRUSH
{
	HOLLOW,

	SIZE,
};

enum class TYPE_PEN
{
	RED,
	GREEN,
	BLUE,

	SIZE
};

#include "CCore.h"
#include "CPathManager.h"
#include "CEventManager.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CResourceManager.h"	// Required CPathManager
#include "CSceneManager.h"		// Required CResourceManager
#include "CCollisionManager.h"
#include "CCameraManager.h"
#include "CSoundManager.h"
#include "CUIManager.h"

//========================================
//##			  디파인문				##
//========================================

#define WINSIZE_X		1280
#define	WINSIZE_Y		720
#define WINSTART_X		100
#define WINSTART_Y		100
#define WINSTYLE		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

#define fDeltaTime		(float)CTimeManager::getInst()->GetDeltaTime()

#define PRESS_KEY(VK_KEY)			CKeyManager::getInst()->GetButton(VK_KEY)
#define PRESS_KEY_DOWN(VK_KEY)		CKeyManager::getInst()->GetButtonDown(VK_KEY)
#define PRESS_KEY_UP(VK_KEY)		CKeyManager::getInst()->GetButtonUp(VK_KEY)

#define MOUSE_POS()					CKeyManager::getInst()->GetMousePos()

#define CREATE_OBJ(OBJ, GROUP)		CEventManager::getInst()->EventCreateObj(OBJ, GROUP)
#define DELETE_OBJ(OBJ)				CEventManager::getInst()->EventDeleteObj(OBJ)
#define CHANGE_SCENE(SCENE)			CEventManager::getInst()->EventChangeScene(SCENE)

#define GRAVITY						(1500.f)

//========================================
//## 전역변수(인스턴스, 윈도우 핸들)	##
//========================================

extern HINSTANCE hInst;
extern HWND hWnd;

// 1. 지역변수
// 2. 전역변수
// 3. 정적변수
// 4. 외부변수

// 5. 멤버변수