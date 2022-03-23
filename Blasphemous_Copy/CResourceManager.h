#pragma once
class CTexture;
class CSound;
class CD2DImage;

class CResourceManager
{
	SINGLETON(CResourceManager);
	
private:
	// 빨리 탐색해서 빨리 넣어줘야하기에 탐색에 빠른 이진트리구조를 선택
	map<wstring, CTexture*> m_mapTex;// Texture 리소스의 저장 자료구조
	map<wstring, CSound*> m_mapSound;// Sound 리소스의 저장 자료구조
									 // BGM 리소스의 저장 변수
	map<wstring, CD2DImage*> m_mapD2DImg; // D2D Image 리소스의 저장 자료구조
	CD2DImage* m_pToolImage;

public:
	CTexture* FindTexture(const wstring& strKey);
	CTexture* LoadTexture(const wstring& strKey, const wstring& strPath);
	CTexture* CreateTexture(const wstring& strKey, UINT width, UINT height);

	CSound* FindSound(const wstring& strKey);
	CSound* LoadSound(const wstring& strKey, const wstring& strPath);

	CD2DImage* FindD2DImage(const wstring& strKey);
	CD2DImage* LoadD2DImage(const wstring& strKey, const wstring& strRelativePath);	// D2DImage 불러오기 이미 있는 경우 있던 D2DImage 반환

	CD2DImage* LoadToolD2DImage(const wstring& strPath);
};

