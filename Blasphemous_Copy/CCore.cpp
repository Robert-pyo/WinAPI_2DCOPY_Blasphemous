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
	// ���� ���� �����찡 ���õ� �����찡 �ƴ� ���
	//if (hWnd != GetFocus()) return;

	CEventManager::getInst()->update();		// ���� ���� �̺�Ʈ�� ���� ���� ó��

	CTimeManager::getInst()->update();
	CKeyManager::getInst()->update();
	CSoundManager::getInst()->update();
	CSceneManager::getInst()->update();
	CCameraManager::getInst()->update();
	CUIManager::getInst()->update();
	CCollisionManager::getInst()->update();
}

void CCore::render()
{
	// ���� ���� �����찡 ���õ� �����찡 �ƴ� ���
	//if (hWnd != GetFocus()) return;

	CRenderManager::getInst()->GetRenderTarget()->BeginDraw();

	CRenderManager::getInst()->RenderFillRectangle(-1, -1, WINSIZE_X + 1, WINSIZE_Y + 1, D2D1::ColorF(255.f, 255.f, 255.f, 1.f));

	CSceneManager::getInst()->render();
	CCameraManager::getInst()->render();

	// fps ǥ��
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::getInst()->GetFPS());
	CRenderManager::getInst()->RenderText(strFPS, WINSIZE_X - 50, 10, WINSIZE_X, 50, 12, RGB(0, 0, 0));

	CRenderManager::getInst()->GetRenderTarget()->EndDraw();
}

void CCore::init()
{
	m_hDC = GetDC(hWnd);	// �����쿡 �׸� �� �������� DC�� �ʿ�

	// Core�� �ʱ�ȭ ����
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
