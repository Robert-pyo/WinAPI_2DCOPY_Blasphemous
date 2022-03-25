#include "framework.h"
#include "CSpawnPoint.h"

CSpawnPoint::CSpawnPoint()
{
}

CSpawnPoint::~CSpawnPoint()
{
}

CSpawnPoint* CSpawnPoint::Clone()
{
	return new CSpawnPoint(*this);
}

void CSpawnPoint::update()
{
}

void CSpawnPoint::render()
{
}
