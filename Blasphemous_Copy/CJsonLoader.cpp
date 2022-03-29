#include "framework.h"
#include "CJsonLoader.h"
#include "CScene.h"
#include "json/json.h"
#include <fstream>

CJsonLoader::CJsonLoader()
{
}

CJsonLoader::~CJsonLoader()
{
}

multimap<string, fPoint> CJsonLoader::LoadSpawnPoint(CScene* targetScene)
{
	multimap<string, fPoint> mapSpawnPoint = {};

	wstring path = CPathManager::GetInst()->GetContentPath();
	path += L"data\\";
	path += targetScene->GetName();
	path += L"_SpawnPoint.json";

	ifstream stream;
	stream.open(path);

	if (stream)
	{
		Json::Value root;

		stream >> root;

		Json::Value objName = root["ObjectName"];
		Json::Value objPosX = root["PositionX"];
		Json::Value objPosY = root["PositionY"];

		for (UINT i = 0; i < objName.size(); ++i)
		{
			fPoint pos = fPoint(objPosX[i].asFloat(), objPosY[i].asFloat());

			mapSpawnPoint.insert(make_pair(objName[i].asString(), pos));
		}
	}

	return mapSpawnPoint;
}

multimap<string, fPoint> CJsonLoader::LoadSpawnPoint(const wstring& sceneName)
{
	multimap<string, fPoint> mapSpawnPoint = {};

	wstring path = CPathManager::GetInst()->GetContentPath();
	path += L"data\\";
	path += sceneName;
	path += L"_SpawnPoint.json";

	ifstream stream;
	stream.open(path);

	if (stream)
	{
		Json::Value root;

		stream >> root;

		Json::Value objName = root["ObjectName"];
		Json::Value objPosX = root["PositionX"];
		Json::Value objPosY = root["PositionY"];

		for (UINT i = 0; i < objName.size(); ++i)
		{
			fPoint pos = fPoint(objPosX[i].asFloat(), objPosY[i].asFloat());

			mapSpawnPoint.insert(make_pair(objName[i].asString(), pos));
		}
	}

	return mapSpawnPoint;
}
