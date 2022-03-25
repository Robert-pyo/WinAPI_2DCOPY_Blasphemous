#include "framework.h"
#include "CJsonLoader.h"
#include "json/json.h"
#include <fstream>

CJsonLoader::CJsonLoader()
{
}

CJsonLoader::~CJsonLoader()
{
}

map<string, fPoint> CJsonLoader::LoadSpawnPoint()
{
	map<string, fPoint> mapSpawnPoint = {};

	wstring path = CPathManager::GetInst()->GetContentPath();
	path += L"data\\SpawnPoint.json";

	ifstream stream;
	stream.open(path);

	if (stream)
	{
		Json::Value root;

		stream >> root;

		Json::Value objName = root["ObjectName"];
		Json::Value objPosX = root["PositionX"];
		Json::Value objPosY = root["PositionY"];

		for (int i = 0; i < objName.size(); ++i)
		{
			fPoint pos = fPoint(objPosX[i].asFloat(), objPosY[i].asFloat());

			mapSpawnPoint.insert(make_pair(objName[i].asString(), pos));
		}
	}

	return mapSpawnPoint;
}
