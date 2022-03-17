#pragma once
#include "CGameObject.h"
class CSword : public CGameObject
{
private:
	CGameObject* m_pOwner;

public:
	CSword();
	~CSword();

	virtual CSword* Clone();

	virtual void update();
	virtual void render();

	void SetOwner(CGameObject* pOwner);

	void Attack();
};

