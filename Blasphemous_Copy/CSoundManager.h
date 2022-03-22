#pragma once
#include "FMOD/inc/fmod.hpp"
#pragma comment(lib, "FMOD/lib/fmod_vc.lib")

class CSound;

using namespace FMOD;

class CSoundManager
{
	SINGLETON(CSoundManager);

private:
	System* m_pSystem;						// 사운드 시스템

	map<wstring, CSound*> m_mapSound;		// 사운드들을 관리하기 위한 자료구조

	map<wstring, Channel*> m_mapChannel;	// 사운드들의 채널을 관리하기 위한 자료구조

public:
	void init();
	void update();

	System* GetSystem();

	void AddSound(wstring keyName, wstring filePath, bool isLoop);
	void Play(wstring keyName);
	void Stop(wstring keyName);
	void Pause(wstring keyName);
	void Resume(wstring keyName);
	void SetVolume(wstring keyName, float fVolume);
	float GetVolume(wstring keyName);


	bool IsPlaySound(wstring keyName);
	bool IsPauseSound(wstring keyName);
};

