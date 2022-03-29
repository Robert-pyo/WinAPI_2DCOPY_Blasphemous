#pragma once
class CScene;

class CJsonLoader
{
public:
	CJsonLoader();
	~CJsonLoader();

public:
	static multimap<string, fPoint> LoadSpawnPoint(CScene* mapName);
	static multimap<string, fPoint> LoadSpawnPoint(const wstring& sceneName);
};

