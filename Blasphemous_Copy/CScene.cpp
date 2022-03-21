#include "framework.h"
#include "CScene.h"
#include "CGameObject.h"
#include "CTile.h"
#include "CTexture.h"
#include "CUI.h"

CScene::CScene()
{
	this->m_sceneName = L"";
	m_iTileX = 0;
	m_iTileY = 0;

	m_vecUI = {};
}

CScene::CScene(const wstring& sceneName)
{
	this->m_sceneName = sceneName;
}

CScene::~CScene()
{
	// 씬이 끝났을 때 씬에 속하는 오브젝트들 모두 삭제
	for (int i = 0; i < (int)GROUP_GAMEOBJ::SIZE; ++i)
	{
		for (int j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (nullptr != m_arrObj[i][j])
				delete m_arrObj[i][j];
		}
	}
}

void CScene::update()
{
	// 씬에 속한 모든 오브젝트들의 업데이트를 수행
	for (int i = 0; i < (int)GROUP_GAMEOBJ::SIZE; ++i)
	{
		for (int j = 0; j < m_arrObj[i].size(); ++j)
		{
			// 비활성화 되지 않은 오브젝트만 업데이트
			if (!m_arrObj[i][j]->IsDisabled())
			{
 	 			m_arrObj[i][j]->update();
			}
		}
	}
}

void CScene::finalUpdate()
{
	// 씬에 속한 모든 오브젝트들의 finalUpdate를 수행
	for (int i = 0; i < (int)GROUP_GAMEOBJ::SIZE; ++i)
	{
		for (int j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finalUpdate();
		}
	}
}

void CScene::render()
{
	// 씬에 속한 모든 오브젝트들의 렌더링을 수행
	for (int i = 0; i < (int)GROUP_GAMEOBJ::SIZE; ++i)
	{
		if ((UINT)GROUP_GAMEOBJ::TILE == i)
		{
			// 보이는 영역 타일만 그려주기
			render_tile();
			continue;
		}
		for (vector<CGameObject*>::iterator iter = m_arrObj[i].begin(); iter != m_arrObj[i].end();)
		{
			if (!(*iter)->IsDisabled())
			{
				(*iter)->render();
				iter++;
			}
			else
				iter = m_arrObj[i].erase(iter);
		}
	}
}

void CScene::render_tile()
{
	const vector<CGameObject*>& vecTile = GetObjGroup(GROUP_GAMEOBJ::TILE);

	// 보이는 타일 영역만 그려주기

	fPoint fptCamLook = CCameraManager::GetInst()->GetLookAt();
	fPoint fptLeftTop = fptCamLook - fPoint(WINSIZE_X, WINSIZE_Y) / 2.f;

	int iLeftTopX = (int)fptLeftTop.x / CTile::SIZE_TILE;
	int iLeftTopY = (int)fptLeftTop.y / CTile::SIZE_TILE;

	int iClientWidth = (int)WINSIZE_X / CTile::SIZE_TILE;
	int iClientHeight = (int)WINSIZE_Y / CTile::SIZE_TILE;

	for (int row = iLeftTopY; row <= (iLeftTopY + iClientHeight); ++row)
	{
		for (int col = iLeftTopX; col <= (iLeftTopX + iClientWidth); ++col)
		{
			// 타일이 없는경우 무시
			// 가로 타일 전체 갯수와 세로 타일 전체 갯수가 row와 col보다 적을 때
			if (row < 0 || m_iTileY <= (UINT)row || col < 0 || m_iTileX <= (UINT)col) continue;

			int iIndex = col + row * m_iTileX;
			vecTile[iIndex]->render();
		}
	}
}

void CScene::SetName(const wstring& strName)
{
	this->m_sceneName = strName;
}

wstring CScene::GetName()
{
	return m_sceneName;
}

UINT CScene::GetTileX()
{
	return m_iTileX;
}

UINT CScene::GetTileY()
{
	return m_iTileY;
}

void CScene::RegisterUI(CUI* pUI)
{
	m_vecUI.push_back(pUI);
}

CUI* CScene::GetUI(const CUI* pUI)
{
	for (UINT i = 0; i < m_vecUI.size(); ++i)
	{
		if (m_vecUI[i] == pUI)
		{
			return m_vecUI[i];
		}
	}

	return nullptr;
}

void CScene::UIOptionSelector()
{
	if (PRESS_KEY_DOWN(VK_UP) || PRESS_KEY_DOWN('W'))
	{
		CSoundManager::GetInst()->Play(L"ChangeSelection");
		for (UINT i = 0; i < m_vecUI.size(); ++i)
		{
			if (m_vecUI[i]->IsMouseOn())
			{
				m_vecUI[i]->DeselectUI();
				m_vecUI[i]->MouseLBtnUp();

				if (i > 0)
				{
					m_vecUI[i - 1]->SelectUI();
					CUIManager::GetInst()->SetFocusedUI(m_vecUI[i - 1]);
				}
				else
				{
					m_vecUI[m_vecUI.size() - 1]->SelectUI();
					CUIManager::GetInst()->SetFocusedUI(m_vecUI[m_vecUI.size() - 1]);
				}
				break;
			}
		}
	}

	if (PRESS_KEY_DOWN(VK_DOWN) || PRESS_KEY_DOWN('S'))
	{
		CSoundManager::GetInst()->Play(L"ChangeSelection");
		for (UINT i = 0; i < m_vecUI.size(); ++i)
		{
			if (m_vecUI[i]->IsMouseOn())
			{
				m_vecUI[i]->DeselectUI();
				m_vecUI[i]->MouseLBtnUp();

				if (i < m_vecUI.size() - 1)
				{
					m_vecUI[i + 1]->SelectUI();
					CUIManager::GetInst()->SetFocusedUI(m_vecUI[i + 1]);
				}
				else
				{
					m_vecUI[0]->SelectUI();
					CUIManager::GetInst()->SetFocusedUI(m_vecUI[0]);
				}
				break;
			}
		}
	}

	if (PRESS_KEY_DOWN(VK_RETURN))
	{
		for (UINT i = 0; i < m_vecUI.size(); ++i)
		{
			if (m_vecUI[i]->IsMouseOn())
			{
				m_vecUI[i]->MouseLBtnClicked();
				break;
			}
		}
	}
}

void CScene::AddObject(CGameObject* pGameObj, GROUP_GAMEOBJ type)
{
	m_arrObj[(int)type].push_back(pGameObj);
	pGameObj->SetObjGroup(type);
}

vector<CGameObject*>& CScene::GetObjGroup(GROUP_GAMEOBJ group)
{
	return m_arrObj[(int)group];
}

vector<CGameObject*>& CScene::GetUIGroup()
{
	return m_arrObj[(int)GROUP_GAMEOBJ::UI];
}

void CScene::CreateTile(UINT xSize, UINT ySize)
{
	// 이미 생성했던 타일이 있다면 지워주기
	ClearGroup(GROUP_GAMEOBJ::TILE);

	m_iTileX = xSize;
	m_iTileY = ySize;

	CD2DImage* pImg = CResourceManager::GetInst()->LoadD2DImage(L"Tile", L"texture\\tile\\tilemap.bmp");

	// Tile 생성
	for (UINT i = 0; i < m_iTileY; ++i)
	{
		for (UINT j = 0; j < m_iTileX; ++j)
		{
			CTile* pTile = new CTile();
			pTile->SetPos(fPoint((float)(j * CTile::SIZE_TILE), (float)(i * CTile::SIZE_TILE)));
			pTile->SetTexture(pImg);
			AddObject(pTile, GROUP_GAMEOBJ::TILE);
		}
	}
}

void CScene::LoadTile(const wstring& strPath)
{
	wstring strFilePath = strPath;

	FILE* pFile = nullptr;

	// 파일을 여는 함수
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");		// w : write, b : binary
	assert(pFile);	// 파일을 열지 못했다면 assert

	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	// 파일에 쓰는 함수
	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	const vector<CGameObject*>& vecTile = GetObjGroup(GROUP_GAMEOBJ::TILE);

	for (UINT i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	// 파일 닫기
	fclose(pFile);
}

void CScene::ClearGroup(GROUP_GAMEOBJ group)
{
	for (int i = 0; i < m_arrObj[(UINT)group].size(); ++i)
	{
		delete m_arrObj[(UINT)group][i];
	}
	m_arrObj[(UINT)group].clear();
}

void CScene::ClearAll()
{
	for (int i = 0; i < (UINT)GROUP_GAMEOBJ::SIZE; ++i)
	{
		ClearGroup((GROUP_GAMEOBJ)i);
	}
}
