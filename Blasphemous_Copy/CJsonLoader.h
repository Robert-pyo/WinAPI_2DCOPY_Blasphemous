#pragma once
class CScene;

class CJsonLoader
{
public:
	CJsonLoader();
	~CJsonLoader();

public:
	static multimap<string, fPoint> LoadSpawnPoint(CScene* mapName);
};

