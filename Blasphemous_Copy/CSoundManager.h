#pragma once
#include "FMOD/inc/fmod.hpp"
#pragma comment(lib, "FMOD/lib/fmod_vc.lib")

class CSound;

using namespace FMOD;

class CSoundManager
{
	SINGLETON(CSoundManager);

private:
	System* m_pSystem;						// ���� �ý���

	map<wstring, CSound*> m_mapSound;		// ������� �����ϱ� ���� �ڷᱸ��

	map<wstring, Channel*> m_mapChannel;	// ������� ä���� �����ϱ� ���� �ڷᱸ��

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

