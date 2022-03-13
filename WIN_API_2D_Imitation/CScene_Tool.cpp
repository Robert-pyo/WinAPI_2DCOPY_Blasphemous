#include "framework.h"
#include "resource.h"
#include "CScene_Tool.h"
#include "CTile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CUI.h"
#include "CButtonUI.h"
#include "CPanelUI.h"

#include <commdlg.h>

INT_PTR CALLBACK TileWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

CScene_Tool::CScene_Tool()
{
	m_hWnd = 0;
	m_iIndex = 0;
}

CScene_Tool::~CScene_Tool()
{
}
CPanelUI* pUI2;
void CScene_Tool::update()
{
	CScene::update();

	if (PRESS_KEY_DOWN(VK_ESCAPE))
	{
		CHANGE_SCENE(GROUP_SCENE::STAGE_01);
	}

	if (PRESS_KEY('A'))
	{
		CCameraManager::getInst()->Scroll(fVector2D(-1, 0), 500.f);
	}
	if (PRESS_KEY('D'))
	{
		CCameraManager::getInst()->Scroll(fVector2D(1, 0), 500.f);
	}
	if (PRESS_KEY('W'))
	{
		CCameraManager::getInst()->Scroll(fVector2D(0, -1), 500.f);
	}
	if (PRESS_KEY('S'))
	{
		CCameraManager::getInst()->Scroll(fVector2D(0, 1), 500.f);
	}

	if (PRESS_KEY_DOWN('1'))
	{
		CUIManager::getInst()->SetFocusedUI(pUI2);
	}

	SetTileDrawIndex();
}

void ButtonItemClicked(DWORD_PTR param1, DWORD_PTR param2)
{
	int a = 0;
}

void ButtonMapClicked(DWORD_PTR param1, DWORD_PTR param2)
{
	CHANGE_SCENE(GROUP_SCENE::STAGE_01);
}

void CScene_Tool::Enter()
{
	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZE_X / 2.f, WINSIZE_Y / 2.f));

	m_hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TILEBOX), hWnd, TileWndProc);

	ShowWindow(m_hWnd, SW_SHOW);

	// UI����
	CPanelUI* pUI = new CPanelUI;
	pUI->SetScale(fPoint(200.f, 200.f));
	// UI�� ī�޶��� ��ġ�� ������� ���� ��ǥ�� ���� ����
	pUI->SetPos(fPoint(WINSIZE_X / 2.f, WINSIZE_Y / 2.f));
	pUI->SetCamAffected(true);
	AddObject(pUI, GROUP_GAMEOBJ::UI);

	CButtonUI* pChildUI = new CButtonUI;
	pChildUI->SetScale(fPoint(50.f, 50.f));
	pChildUI->SetPos(fPoint(50.f, 50.f));
	pChildUI->SetClickCallBack(ButtonItemClicked, 0, 0);
	pUI->AddChild(pChildUI);

	// UI����
	pUI2 = pUI->Clone();
	pUI2->SetScale(fPoint(200.f, 200.f));
	// UI�� ī�޶��� ��ġ�� ������� ���� ��ǥ�� ���� ����
	pUI2->SetPos(fPoint(WINSIZE_X / 2.f - 100.f, WINSIZE_Y / 2.f));
	pUI2->SetCamAffected(true);
	AddObject(pUI2, GROUP_GAMEOBJ::UI);

	CButtonUI* pChildUI2 = pChildUI->Clone();
	pChildUI2->SetScale(fPoint(50.f, 50.f));
	pChildUI2->SetPos(fPoint(50.f, 50.f));
	pChildUI2->SetClickCallBack(ButtonItemClicked, 0, 0);
	pUI2->AddChild(pChildUI2);

	CButtonUI* pMapButton = new CButtonUI;
	pMapButton->SetScale(fPoint(50.f, 50.f));
	pMapButton->SetPos(fPoint(50.f, 50.f));
	pMapButton->SetClickCallBack(ButtonMapClicked, 0, 0);
	AddObject(pMapButton, GROUP_GAMEOBJ::UI);
}

void CScene_Tool::Exit()
{
	ClearAll();

	// Tool Scene���� ���� �� ���̾�α� â�� �������� ����
	EndDialog(m_hWnd, IDOK);
}

void CScene_Tool::SelectIndex(UINT index)
{
	m_iIndex = index;
}

void CScene_Tool::SetTileDrawIndex()
{
	if (PRESS_KEY(VK_LBUTTON))
	{
		fPoint fptMousePos = MOUSE_POS();
		fptMousePos = CCameraManager::getInst()->GetRealPos(fptMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iClickPosX = (int)fptMousePos.x / CTile::SIZE_TILE;
		int iClickPosY = (int)fptMousePos.y / CTile::SIZE_TILE;

		// �߸��� ���� Ŭ���Ͽ��� ��� ����
		if (fptMousePos.x < 0.f || iTileX <= iClickPosX ||
			fptMousePos.y < 0.f || iTileY <= iClickPosY) return;

		UINT iIndex = iClickPosX + iClickPosY * iTileX;
		const vector<CGameObject*>& vecTile = GetObjGroup(GROUP_GAMEOBJ::TILE);
		((CTile*)vecTile[iIndex])->SetTileIndex(m_iIndex);
	}
	if (PRESS_KEY(VK_RBUTTON))	// ������ ���콺 ���� �� �����
	{
		fPoint fptMousePos = MOUSE_POS();
		fptMousePos = CCameraManager::getInst()->GetRealPos(fptMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iClickPosX = (int)fptMousePos.x / CTile::SIZE_TILE;
		int iClickPosY = (int)fptMousePos.y / CTile::SIZE_TILE;

		// �߸��� ���� Ŭ���Ͽ��� ��� ����
		if (fptMousePos.x < 0.f || iTileX <= iClickPosX ||
			fptMousePos.y < 0.f || iTileY <= iClickPosY) return;

		UINT iIndex = iClickPosX + iClickPosY * iTileX;
		const vector<CGameObject*>& vecTile = GetObjGroup(GROUP_GAMEOBJ::TILE);
		((CTile*)vecTile[iIndex])->SetTileIndex(0);
	}
}

void CScene_Tool::SaveTile(const wstring& strPath)
{
	wstring strFilePath = strPath;

	FILE* pFile = nullptr;

	// ������ ���� �Լ�
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");		// w : write, b : binary
	assert(pFile);	// ������ ���� ���ߴٸ� assert

	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	// ���Ͽ� ���� �Լ�
	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	const vector<CGameObject*>& vecTile = GetObjGroup(GROUP_GAMEOBJ::TILE);

	for (UINT i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	// ���� �ݱ�
	fclose(pFile);
}

void CScene_Tool::SaveTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName;			// ���߿� �ϼ��� ��ΰ� ä���� ���� ����
	ofn.nMaxFile = sizeof(szName);	// lpstrFile�� ������ ������ ���� ��
	ofn.nFilterIndex = 1;			// �⺻ ���� ����. 0�� all�� �ʱ� ���õ� -> ó��
	ofn.lpstrFileTitle = 0;			// Ÿ��Ʋ �� ���ڿ� ũ�� nullptr�̸� 0
	wstring strTileFolder = CPathManager::getInst()->GetContentPath();
	strTileFolder += L"texture\\Land\\Tileset\\Tilemaps";
	ofn.lpstrInitialDir = strTileFolder.c_str();	// �ʱ� ���
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;	// ��Ÿ��

	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}

void CScene_Tool::LoadTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName;			// ���߿� �ϼ��� ��ΰ� ä���� ���� ����
	ofn.nMaxFile = sizeof(szName);	// lpstrFile�� ������ ������ ���� ��
	ofn.nFilterIndex = 1;			// �⺻ ���� ����. 0�� all�� �ʱ� ���õ� -> ó��
	ofn.lpstrFileTitle = 0;			// Ÿ��Ʋ �� ���ڿ� ũ�� nullptr�̸� 0
	wstring strTileFolder = CPathManager::getInst()->GetContentPath();
	strTileFolder += L"texture\\Land\\Tileset\\Tilemaps";
	ofn.lpstrInitialDir = strTileFolder.c_str();	// �ʱ� ���
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;	// ��Ÿ��

	if (GetOpenFileName(&ofn))
	{
		LoadTile(szName);
	}
}

// Ÿ�� ���̾�α� �ڽ��� �޽��� ó�����Դϴ�.
INT_PTR CALLBACK TileWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			CScene* pCurScene = CSceneManager::getInst()->GetCurrentScene();
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->SaveTileData();
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			CScene* pCurScene = CSceneManager::getInst()->GetCurrentScene();
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->LoadTileData();
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_BUTTON_SIZE)
		{
			int x = GetDlgItemInt(hDlg, IDC_EDIT_SIZEX, nullptr, false);
			int y = GetDlgItemInt(hDlg, IDC_EDIT_SIZEY, nullptr, false);

			CScene* pCurScene = CSceneManager::getInst()->GetCurrentScene();
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->ClearGroup(GROUP_GAMEOBJ::TILE);

			pToolScene->CreateTile(x, y);
		}
		else if (LOWORD(wParam) == IDC_BUTTON_TILEIDX)
		{
			int index = GetDlgItemInt(hDlg, IDC_EDIT_TILE, nullptr, false);

			CScene* pCurScene = CSceneManager::getInst()->GetCurrentScene();
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);		// CScene_Tool �� �ƴ϶�� -> nullptr

			pToolScene->SelectIndex(index);

			// �̸����� �׸���
			CTexture* pTex = CResourceManager::getInst()->LoadTexture(L"Tile", L"texture\\Land\\Tileset\\tilemap.bmp");

			UINT iWidth = pTex->GetBmpWidth();
			UINT iHeight = pTex->GetBmpHeight();

			UINT iMaxCol = iWidth / CTile::SIZE_TILE;
			UINT iMaxRow = iHeight / CTile::SIZE_TILE;

			UINT iCurCol = index % iMaxCol;
			UINT iCurRow = (index / iMaxCol) % iMaxRow;

			BitBlt(GetDC(hDlg),
				150, 150,
				CTile::SIZE_TILE,
				CTile::SIZE_TILE,
				pTex->GetDC(),
				(int)iCurCol * CTile::SIZE_TILE,
				(int)iCurRow * CTile::SIZE_TILE,
				SRCCOPY);
		}
		break;
	}
	return (INT_PTR)FALSE;
}
