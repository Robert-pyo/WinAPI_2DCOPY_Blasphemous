#include "framework.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CSound.h"

CResourceManager::CResourceManager()
{
	m_mapTex = {};
	m_mapSound = {};
}

CResourceManager::~CResourceManager()
{
	// 로드된 텍스쳐 지워주기
	for (map<wstring, CTexture*>::iterator iter = m_mapTex.begin(); iter != m_mapTex.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}

	m_mapTex.clear();

	// 로드된 사운드 모두 지워주기
	for (map<wstring, CSound*>::iterator iter = m_mapSound.begin(); iter != m_mapSound.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}

	m_mapSound.clear();
}

CTexture* CResourceManager::FindTexture(const wstring& strKey)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(strKey);

	if (m_mapTex.end() == iter)	// 끝까지 돌았는데 못찾았으면
		return nullptr;
	else
		return iter->second;
}

CTexture* CResourceManager::LoadTexture(const wstring& strKey, const wstring& strPath)
{
	// 이미 등록된 텍스쳐일 경우 그 등록된 텍스쳐로 반환해주자
	CTexture* pTex = FindTexture(strKey);
	if (nullptr != pTex)
		return pTex;

	// 없던 새로운 텍스쳐일 경우 추가해주자

	wstring strFilePath = CPathManager::getInst()->GetContentPath();
	strFilePath += strPath;
	
	pTex = new CTexture();
	pTex->Load(strFilePath);
	pTex->SetKey(strKey);
	pTex->SetPath(strPath);

	m_mapTex.insert(make_pair(strKey, pTex));

	return pTex;
}

CTexture* CResourceManager::CreateTexture(const wstring& strKey, UINT width, UINT height)
{
	CTexture* pTex = FindTexture(strKey);
	if (nullptr != pTex)
		return pTex;

	pTex = new CTexture();
	pTex->Create(width, height);
	pTex->SetKey(strKey);

	m_mapTex.insert(make_pair(strKey, pTex));

	return pTex;
}

CSound* CResourceManager::FindSound(const wstring& strKey)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(strKey);

	if (m_mapSound.end() == iter)	// 끝까지 돌았는데 못찾았으면
		return nullptr;
	else
		return iter->second;
}

CSound* CResourceManager::LoadSound(const wstring& strKey, const wstring& strPath)
{
	// 이미 등록된 텍스쳐일 경우 그 등록된 텍스쳐로 반환해주자
	CSound* pSound = FindSound(strKey);
	if (nullptr != pSound)
		return pSound;

	// 없던 새로운 텍스쳐일 경우 추가해주자

	wstring strFilePath = CPathManager::getInst()->GetContentRelativePath();
	strFilePath += strPath;

	pSound = new CSound();
	pSound->Load(strFilePath);
	pSound->SetKey(strKey);
	pSound->SetPath(strPath);

	m_mapSound.insert(make_pair(strKey, pSound));

	return pSound;
}
