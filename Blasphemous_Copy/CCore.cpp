#include "framework.h"
#include "CCore.h"
#include "CGameObject.h"
#include "CScene.h"
#include "CTexture.h"

CCore::CCore()
{
	m_hDC			= {};
	m_pMemTex		= nullptr;
	m_arrBrush[0]	= 0;
	m_arrPen[0]		= 0;
}

CCore::~CCore()
{
	ReleaseDC(hWnd, m_hDC); // 게임이 끝났으면 DC 반환

	// 만든 펜 지워줌
	for (int i = 0; i < (int)TYPE_PEN::SIZE; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
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
	// 정보를 토대로 그려주는 작업
	// 그리는 작업은 모두 복사본에 그려줌
	Rectangle(m_pMemTex->GetDC(), -1, -1, WINSIZE_X + 1, WINSIZE_Y + 1);

	// fps 표현
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::getInst()->GetFPS());
	TextOutW(m_pMemTex->GetDC(), WINSIZE_X - 100, 10, strFPS, 5);

	CSceneManager::getInst()->render(m_pMemTex->GetDC());
	CCameraManager::getInst()->render(m_pMemTex->GetDC());

	// hMemDC에 그린 복사본을 원본 DC에 그려줌
	BitBlt(m_hDC, 0, 0, WINSIZE_X, WINSIZE_Y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);
}

void CCore::init()
{
	m_hDC = GetDC(hWnd);	// 윈도우에 그릴 수 있으려면 DC가 필요

	// Core의 초기화 과정
	CPathManager::getInst()->init();
	CTimeManager::getInst()->init();
	CKeyManager::getInst()->init();
	CCameraManager::getInst()->init();
	CSoundManager::getInst()->init();
	CSceneManager::getInst()->init();
	CCollisionManager::getInst()->init();

	// 코어 초기화 진행 시 코어에서 그리는데 필요한 브러쉬와 펜 생성
	CreateBrushNPen();

	m_pMemTex = CResourceManager::getInst()->CreateTexture(L"CoreTex", WINSIZE_X, WINSIZE_Y);
}

HDC CCore::GetMainDC()
{
	return m_hDC;
}

void CCore::CreateBrushNPen()
{
	// Pen
	m_arrPen[(int)TYPE_PEN::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(int)TYPE_PEN::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(int)TYPE_PEN::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	// Brush
	m_arrBrush[(int)TYPE_BRUSH::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
}

HPEN CCore::GetPen(TYPE_PEN pen)
{
	return m_arrPen[(int)pen];
}

HBRUSH CCore::GetBrush(TYPE_BRUSH brush)
{
	return m_arrBrush[(int)brush];
}
