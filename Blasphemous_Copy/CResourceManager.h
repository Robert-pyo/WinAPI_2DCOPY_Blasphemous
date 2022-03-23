#pragma once
class CTexture;
class CSound;
class CD2DImage;

class CResourceManager
{
	SINGLETON(CResourceManager);
	
private:
	// ���� Ž���ؼ� ���� �־�����ϱ⿡ Ž���� ���� ����Ʈ�������� ����
	map<wstring, CTexture*> m_mapTex;// Texture ���ҽ��� ���� �ڷᱸ��
	map<wstring, CSound*> m_mapSound;// Sound ���ҽ��� ���� �ڷᱸ��
									 // BGM ���ҽ��� ���� ����
	map<wstring, CD2DImage*> m_mapD2DImg; // D2D Image ���ҽ��� ���� �ڷᱸ��
	CD2DImage* m_pToolImage;

public:
	CTexture* FindTexture(const wstring& strKey);
	CTexture* LoadTexture(const wstring& strKey, const wstring& strPath);
	CTexture* CreateTexture(const wstring& strKey, UINT width, UINT height);

	CSound* FindSound(const wstring& strKey);
	CSound* LoadSound(const wstring& strKey, const wstring& strPath);

	CD2DImage* FindD2DImage(const wstring& strKey);
	CD2DImage* LoadD2DImage(const wstring& strKey, const wstring& strRelativePath);	// D2DImage �ҷ����� �̹� �ִ� ��� �ִ� D2DImage ��ȯ

	CD2DImage* LoadToolD2DImage(const wstring& strPath);
};

