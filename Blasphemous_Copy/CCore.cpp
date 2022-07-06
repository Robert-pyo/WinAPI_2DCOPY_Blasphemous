#include "framework.h"
#include "CCore.h"
#include "CGameObject.h"
#include "CScene.h"
#include "CTexture.h"

CCore::CCore()
{
	m_hDC = {};
}

CCore::~CCore()
{
}

void CCore::update()
{
	CEventManager::GetInst()->update();		// 가장 먼저 이벤트에 관한 내용 처리

	CTimeManager::GetInst()->update();
	CKeyManager::GetInst()->update();
	CSoundManager::GetInst()->update();
	CSceneManager::GetInst()->update();
	CCameraManager::GetInst()->update();
	CGameManager::GetInst()->update();
	CUIManager::GetInst()->update();
	CCollisionManager::GetInst()->update();
}

void CCore::render()
{
	CRenderManager::GetInst()->GetRenderTarget()->BeginDraw();

	CRenderManager::GetInst()->RenderFillRectangle(
		-1, -1, WINSIZE_X, WINSIZE_Y,
		D2D1::ColorF(255.f, 255.f, 255.f, 1.f)
	);

	CSceneManager::GetInst()->render();
	CCameraManager::GetInst()->render();

#ifdef _DEBUG
	// fps 표현
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::GetInst()->GetFPS());
	CRenderManager::GetInst()->RenderText(strFPS, WINSIZE_X - 50, 10, WINSIZE_X, 50, 12, RGB(0, 0, 0));
#endif

	CRenderManager::GetInst()->GetRenderTarget()->EndDraw();
}

void CCore::init()
{
	m_hDC = GetDC(hWnd);	// 윈도우에 그릴 수 있으려면 DC가 필요

	// Core의 초기화 과정
	CPathManager::GetInst()->init();
	CTimeManager::GetInst()->init();
	CKeyManager::GetInst()->init();
	CRenderManager::GetInst()->init();
	CCameraManager::GetInst()->init();
	CSoundManager::GetInst()->init();
	CCollisionManager::GetInst()->init(); 
	CSceneManager::GetInst()->init();
	CGameManager::GetInst()->init();
}

HDC CCore::GetMainDC()
{
	return m_hDC;
}
