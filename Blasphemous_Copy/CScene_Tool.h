#pragma once
#include "CScene.h"
class CD2DImage;
class CButtonUI;
class CTileButton;

class CScene_Tool : public CScene
{
private:
	CD2DImage* m_pMap;

	HWND m_hWnd;
	UINT m_iIdx;
	HWND m_hTileInfoWnd;
	UINT m_iInfoWndCount;
	GROUP_TILE m_gTile;
	float m_velocity;

	UINT m_iTileX;
	UINT m_iTileY;

	fPoint m_fptSelectedPos;

	wstring m_strCurEdit;

public:
	CScene_Tool();
	~CScene_Tool();

	virtual void update();
	virtual void render();

	virtual void Enter();
	virtual void Exit();

public:
	const UINT  GetInfoWndCount() { return m_iInfoWndCount; }
	void		SetInfoWndCount(const UINT iCount) { m_iInfoWndCount = iCount; }

public:
	void SetIdx(UINT idx);
	void SetTileIdx();		// 마우스와 상호작용해서 타일을 바꿈.
	void SetGroup(GROUP_TILE group);
	void SetTileGroup();

public:
	void CreateTile(UINT xSize, UINT ySize);
	void SaveTile(const wstring& strPath);
	void LoadTile(const wstring& strPath);
	void SaveTileData();
	void LoadTileData();
	void LoadMap();

	void ClickTileGroup(CButtonUI* button);
	void ClickTile(CTileButton* button);

	const fPoint& GetSelectedPos() { return m_fptSelectedPos; }

	void SetCurEditName(const wstring& curEdit);
	const wstring& GetCurEditName() { return m_strCurEdit; }

//public:
//	void CreateObjPanel();

private:
	void CreateTilePanel();

	void PrintMap(const fPoint& ratio = {2, 2});
	void PrintTileLine();
	void PrintTileGroup();


};