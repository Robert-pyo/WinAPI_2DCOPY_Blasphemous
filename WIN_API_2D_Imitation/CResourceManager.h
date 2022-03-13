#pragma once
class CTexture;
class CSound;

class CResourceManager
{
	SINGLETON(CResourceManager);
	
private:
	// ���� Ž���ؼ� ���� �־�����ϱ⿡ Ž���� ���� ����Ʈ�������� ����
	map<wstring, CTexture*> m_mapTex;
	map<wstring, CSound*> m_mapSound;

public:
	CTexture* FindTexture(const wstring& strKey);
	CTexture* LoadTexture(const wstring& strKey, const wstring& strPath);
	CTexture* CreateTexture(const wstring& strKey, UINT width, UINT height);

	CSound* FindSound(const wstring& strKey);
	CSound* LoadSound(const wstring& strKey, const wstring& strPath);
};

