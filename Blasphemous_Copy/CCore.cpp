#include "framework.h"
#include "CCore.h"
#include "CGameObject.h"
#include "CScene.h"
#include "CTexture.h"

CCore::CCore()
{
	m_hDC			= {};
}

CCore::~CCore()
{
}

void CCore::update()
{
	CEventManager::getInst()->update();		// 가장 먼저 이벤트에 관한 내용 처리

	CTimeManager::getInst()->update();
	CKeyManager::getInst()->update();
	CSoundManager::getInst()->update();
	CSceneManager::getInst()->update();
	CCameraManager::getInst()->update();
	CCollisionManager::getInst()->update();
	CUIManager::getInst()->update();
}

void CCore::render()
{
	CRenderManager::getInst()->GetRenderTarget()->BeginDraw();

	CRenderManager::getInst()->RenderFillRectangle(-1, -1, WINSIZE_X + 1, WINSIZE_Y + 1, RGB(255, 255, 255));

	CSceneManager::getInst()->render();
	//CCameraManager::getInst()->render(m_pMemTex->GetDC());

	// fps 표현
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::getInst()->GetFPS());
	CRenderManager::getInst()->RenderText(strFPS, WINSIZE_X - 50, 10, WINSIZE_X, 50, 12, RGB(0, 0, 0));

	CRenderManager::getInst()->GetRenderTarget()->EndDraw();
}

void CCore::init()
{
	m_hDC = GetDC(hWnd);	// 윈도우에 그릴 수 있으려면 DC가 필요

	// Core의 초기화 과정
	CPathManager::getInst()->init();
	CTimeManager::getInst()->init();
	CKeyManager::getInst()->init();
	CSoundManager::getInst()->init();
	CRenderManager::getInst()->init();
	CCameraManager::getInst()->init();
	CSceneManager::getInst()->init();
	CCollisionManager::getInst()->init();
}

HDC CCore::GetMainDC()
{
	return m_hDC;
}
