#pragma once

class CJsonLoader
{
public:
	CJsonLoader();
	~CJsonLoader();

public:
	static map<string, fPoint> LoadSpawnPoint();
};

