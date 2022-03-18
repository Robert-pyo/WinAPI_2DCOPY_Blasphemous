#pragma once
#include "CEnemyFactory.h"

// 전방 선언 : 해당 클래스의 포인터 변수를 사용할 수 있게 해줌
// 1. 헤더파일이 여러번 호출되어 #pragma once 선언부를 확인 불가한 문제 해결
// 2. 컴파일 시간을 단축시킬 수 있음
class CGameObject;

class CScene
{
private:
	// 현재 Scene에 어떤 오브젝트들이 속해있는지 vector로 저장
	vector<CGameObject*> m_arrObj[(int)GROUP_GAMEOBJ::SIZE];
	// 현재 Scene의 이름
	wstring m_sceneName;

	UINT m_iTileX;
	UINT m_iTileY;

public:
	CScene();
	CScene(const wstring& sceneName);
	virtual ~CScene();

	virtual void update();
	virtual void finalUpdate();
	virtual void render();
	void render_tile();

	virtual void Enter() = 0;	// 씬 진입 시 행동 -> 씬 마다 행동이 다를 수 있으므로 순수가상함수로 처리
	virtual void Exit() = 0;	// 씬 아웃 시 행동 -> 씬 마다 행동이 다를 수 있으므로 순수가상함수로 처리

	void SetName(const wstring& strName);

	wstring GetName();
	UINT	GetTileX();
	UINT	GetTileY();

	vector<CGameObject*>& GetObjGroup(GROUP_GAMEOBJ group);
	vector<CGameObject*>& GetUIGroup();

	// 현재 씬에 게임 오브젝트 추가
	void AddObject(CGameObject* pGameObj, GROUP_GAMEOBJ type);

	void CreateTile(UINT xSize, UINT ySize);
	void LoadTile(const wstring& strPath);

	void ClearGroup(GROUP_GAMEOBJ group);
	void ClearAll();
};

