#include "framework.h"
#include "CSoundManager.h"
#include "CSound.h"

CSoundManager::CSoundManager()
{
	m_pSystem = nullptr;
}

CSoundManager::~CSoundManager()
{
	m_pSystem->release();
	m_pSystem->close();
}

void CSoundManager::init()
{
	FMOD_RESULT result;

	// �ý��� �����
	result = System_Create(&m_pSystem);
	assert(!result);

	// �ý����� �ʱ�ȭ ���� ����
	result = m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr);
	assert(!result);
}

void CSoundManager::update()
{
	FMOD_RESULT result;
	
	// IMPORTANT! UPDATE PER FRAME!
	result = m_pSystem->update();		// ������� �ʴ� ä���� �ڵ����� ��ȯ����
	assert(!result);
}

System* CSoundManager::GetSystem()
{
	return m_pSystem;
}

void CSoundManager::AddSound(wstring keyName, wstring filePath, bool isLoop)
{
	if (m_mapSound.end() != m_mapSound.find(keyName)) return;
	CSound* pSound = CResourceManager::GetInst()->LoadSound(keyName, filePath);
	pSound->SetLoop(isLoop);
	m_mapSound.insert(make_pair(keyName, pSound));
}

void CSoundManager::Play(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	// ���尡 ���ٸ� ����
	if (iter == m_mapSound.end()) return;

	iter->second->Play();
	m_mapChannel.insert(make_pair(keyName, iter->second->GetChannel()));
}

void CSoundManager::Stop(wstring keyName)
{
	map<wstring, Channel*>::iterator chIter = m_mapChannel.find(keyName);
	if (chIter == m_mapChannel.end()) return;

	chIter->second->stop();
	m_mapChannel.erase(keyName);
}

void CSoundManager::Pause(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter == m_mapSound.end()) return;

	iter->second->Pause();
}

void CSoundManager::Resume(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter == m_mapSound.end()) return;

	iter->second->Resume();
}

bool CSoundManager::IsPlaySound(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	assert(iter != m_mapSound.end());

	return iter->second->IsPlaying();
}

bool CSoundManager::IsPauseSound(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	assert(iter != m_mapSound.end());

	return iter->second->IsPaused();
}
