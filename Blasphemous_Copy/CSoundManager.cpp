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

	// 시스템 만들기
	result = System_Create(&m_pSystem);
	assert(!result);

	// 시스템의 초기화 과정 실행
	result = m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr);
	assert(!result);
}

void CSoundManager::update()
{
	FMOD_RESULT result;
	
	// IMPORTANT! UPDATE PER FRAME!
	result = m_pSystem->update();		// 사용하지 않는 채널은 자동으로 반환해줌
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
	// 사운드가 없다면 무시
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
