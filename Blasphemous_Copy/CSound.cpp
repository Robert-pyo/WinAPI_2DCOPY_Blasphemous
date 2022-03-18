#include "framework.h"
#include "CSound.h"

CSound::CSound()
{
	m_pChannel = nullptr;
	m_pSound = nullptr;
}

CSound::~CSound()
{
	Stop();

	if (nullptr != m_pSound)
	{
		m_pSound->release();
	}
}

void CSound::Play()
{
	FMOD_RESULT result;

	result = CSoundManager::GetInst()->GetSystem()->playSound(m_pSound, nullptr, false, &m_pChannel);
	assert(!result);
}

void CSound::Stop()
{
	if (nullptr != m_pChannel)
	{
		m_pChannel->stop();
	}
}

void CSound::Pause()
{
	FMOD_RESULT result;

	if (nullptr != m_pChannel)
	{
		result = m_pChannel->setPaused(true);
		assert(!result);
	}
}

void CSound::Resume()
{
	FMOD_RESULT result;
	result = m_pChannel->setPaused(false);
	assert(!result);
}

bool CSound::IsPlaying()
{
	bool isPlaying = false;
	if (nullptr != m_pChannel)
	{
		m_pChannel->isPlaying(&isPlaying);
		return isPlaying;
	}
	assert(nullptr);

	return isPlaying;
}

bool CSound::IsPaused()
{
	bool isPaused = false;
	if (nullptr != m_pChannel)
	{
		m_pChannel->getPaused(&isPaused);
		return isPaused;
	}
	assert(nullptr);

	return isPaused;
}

void CSound::Load(const wstring& strFilePath)
{
	// createSound 할때 문자열을 char형식으로 받기 때문에
	// strFilePath.c_str()을 w_char 형식에서 char형식으로 변환해줌
	char str[255];
	// wchar string to multybite string
	wcstombs_s(nullptr, str, strFilePath.c_str(), 255);

	CSoundManager::GetInst()->GetSystem()->createSound(str, FMOD_DEFAULT, nullptr, &m_pSound);
}

void CSound::SetLoop(bool loop)
{
	if (loop)
	{
		m_pSound->setMode(FMOD_LOOP_NORMAL);
	}
	else
	{
		m_pSound->setMode(FMOD_LOOP_OFF);
	}
}

Sound* CSound::GetSound()
{
	return m_pSound;
}

Channel* CSound::GetChannel()
{
	return m_pChannel;
}
