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

public:
	CSound();
	~CSound();

	void Play();
	void Stop();
	void Pause();
	void Resume();

	bool IsPlaying();
	bool IsPaused();

	void Load(const wstring& strFilePath);

	void SetLoop(bool loop);

	Sound*		GetSound();
	Channel*	GetChannel();
};

