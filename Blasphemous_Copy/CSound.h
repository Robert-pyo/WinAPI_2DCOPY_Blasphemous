#pragma once
#include "FMOD/inc/fmod.hpp"
#pragma comment(lib, "FMOD/lib/fmod_vc.lib")
#include "CResource.h"

using namespace FMOD;

class CSound : public CResource
{
private:
	Channel*	m_pChannel;
	Sound*		m_pSound;

	float*		m_pVolume;

public:
	CSound();
	~CSound();

	void Play();
	void Stop();
	void Pause();
	void Resume();
	void SetVolume(float fVolume);
	float GetVolume();

	bool IsPlaying();
	bool IsPaused();

	void Load(const wstring& strFilePath);

	void SetLoop(bool loop);

	Sound*		GetSound();
	Channel*	GetChannel();
};

