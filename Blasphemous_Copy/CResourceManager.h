#pragma once
class CTexture;
class CSound;

class CResourceManager
{
	SINGLETON(CResourceManager);
	
private:
	// 빨리 탐색해서 빨리 넣어줘야하기에 탐색에 빠른 이진트리구조를 선택
	map<wstring, CTexture*> m_mapTex;
	map<wstring, CSound*> m_mapSound;

public:
	CTexture* FindTexture(const wstring& strKey);
	CTexture* LoadTexture(const wstring& strKey, const wstring& strPath);
	CTexture* CreateTexture(const wstring& strKey, UINT width, UINT height);

	CSound* FindSound(const wstring& strKey);
	CSound* LoadSound(const wstring& strKey, const wstring& strPath);
};

