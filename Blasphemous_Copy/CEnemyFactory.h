#pragma once
class CEnemy;

enum class ENEMY_TYPE
{
	NORMAL,
	RANGE,
	BOSS,
};

class CEnemyFactory
{
private:
	CEnemyFactory() {}
	~CEnemyFactory() {}

public:
	static CEnemy* CreateEnemy(ENEMY_TYPE eEnmType, fPoint pos);
};

