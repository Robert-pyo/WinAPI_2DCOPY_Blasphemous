#include "framework.h"
#include "CScene.h"
#include "CGameObject.h"
#include "CTile.h"
#include "CTexture.h"
#include "CUI.h"
#include "CCollider.h"

#include <fstream>
#include "json/json.h"

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
			{
				delete m_arrObj[i][j];
			}
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
	for (UINT i = 0; i < vecTile.size(); i++)
	{
		vecTile[i]->render();
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

void CScene::LoadTile(const wstring& strPath)
{
	ClearGroup(GROUP_GAMEOBJ::TILE);

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"rb");      // w : write, b : binary
	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;
	UINT tileCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);
	fread(&tileCount, sizeof(UINT), 1, pFile);

	CD2DImage* pImg = CResourceManager::GetInst()->LoadD2DImage(L"Tile", L"texture\\Map\\Tileset\\tilemap.bmp");

	for (UINT i = 0; i < tileCount; i++)
	{
		CTile* newTile = new CTile;
		newTile->Load(pFile);
		newTile->SetD2DImage(pImg);
		newTile->SetPos(fPoint((float)(newTile->GetX() * CTile::SIZE_TILE), (float)(newTile->GetY() * CTile::SIZE_TILE)));

		if (GROUP_TILE::SLOPE == newTile->GetGroup())
		{
			// TODO : OBB 충돌체 추가
		}
		else if (GROUP_TILE::WALL == newTile->GetGroup() || GROUP_TILE::GROUND == newTile->GetGroup())
		{
			newTile->CreateCollider();
			newTile->GetCollider()->SetScale(fPoint(CTile::SIZE_TILE, CTile::SIZE_TILE));
			newTile->GetCollider()->SetOffsetPos(fPoint(CTile::SIZE_TILE / 2.f, CTile::SIZE_TILE / 2.f));
		}

		AddObject(newTile, GROUP_GAMEOBJ::TILE);
	}

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
