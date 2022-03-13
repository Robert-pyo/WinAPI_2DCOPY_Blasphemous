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
	ReleaseDC(hWnd, m_hDC); // ������ �������� DC ��ȯ

	// ���� �� ������
	for (int i = 0; i < (int)TYPE_PEN::SIZE; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}

void CCore::update()
{
	CEventManager::getInst()->update();		// ���� ���� �̺�Ʈ�� ���� ���� ó��

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
	// ������ ���� �׷��ִ� �۾�
	// �׸��� �۾��� ��� ���纻�� �׷���
	Rectangle(m_pMemTex->GetDC(), -1, -1, WINSIZE_X + 1, WINSIZE_Y + 1);

	// fps ǥ��
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::getInst()->GetFPS());
	TextOutW(m_pMemTex->GetDC(), WINSIZE_X - 100, 10, strFPS, 5);

	CSceneManager::getInst()->render(m_pMemTex->GetDC());
	CCameraManager::getInst()->render(m_pMemTex->GetDC());

	// hMemDC�� �׸� ���纻�� ���� DC�� �׷���
	BitBlt(m_hDC, 0, 0, WINSIZE_X, WINSIZE_Y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);
}

void CCore::init()
{
	m_hDC = GetDC(hWnd);	// �����쿡 �׸� �� �������� DC�� �ʿ�

	// Core�� �ʱ�ȭ ����
	CPathManager::getInst()->init();
	CTimeManager::getInst()->init();
	CKeyManager::getInst()->init();
	CCameraManager::getInst()->init();
	CSoundManager::getInst()->init();
	CSceneManager::getInst()->init();
	CCollisionManager::getInst()->init();

	// �ھ� �ʱ�ȭ ���� �� �ھ�� �׸��µ� �ʿ��� �귯���� �� ����
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
