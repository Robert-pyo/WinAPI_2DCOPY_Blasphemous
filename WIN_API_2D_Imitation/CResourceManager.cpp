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
	// �ε�� �ؽ��� �����ֱ�
	for (map<wstring, CTexture*>::iterator iter = m_mapTex.begin(); iter != m_mapTex.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}

	m_mapTex.clear();

	// �ε�� ���� ��� �����ֱ�
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

	if (m_mapTex.end() == iter)	// ������ ���Ҵµ� ��ã������
		return nullptr;
	else
		return iter->second;
}

CTexture* CResourceManager::LoadTexture(const wstring& strKey, const wstring& strPath)
{
	// �̹� ��ϵ� �ؽ����� ��� �� ��ϵ� �ؽ��ķ� ��ȯ������
	CTexture* pTex = FindTexture(strKey);
	if (nullptr != pTex)
		return pTex;

	// ���� ���ο� �ؽ����� ��� �߰�������

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

	if (m_mapSound.end() == iter)	// ������ ���Ҵµ� ��ã������
		return nullptr;
	else
		return iter->second;
}

CSound* CResourceManager::LoadSound(const wstring& strKey, const wstring& strPath)
{
	// �̹� ��ϵ� �ؽ����� ��� �� ��ϵ� �ؽ��ķ� ��ȯ������
	CSound* pSound = FindSound(strKey);
	if (nullptr != pSound)
		return pSound;

	// ���� ���ο� �ؽ����� ��� �߰�������

	wstring strFilePath = CPathManager::getInst()->GetContentRelativePath();
	strFilePath += strPath;

	pSound = new CSound();
	pSound->Load(strFilePath);
	pSound->SetKey(strKey);
	pSound->SetPath(strPath);

	m_mapSound.insert(make_pair(strKey, pSound));

	return pSound;
}
