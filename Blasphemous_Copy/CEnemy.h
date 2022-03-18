#pragma once
#include "CGameObject.h"

class AI;

struct tEnemyInfo
{
	float fVelocity;
	float fHP;
	float fRecogRange;
	float fAttRange;
	float fAtt;
	float fAttDelayTime;
	float fInvTime;		// ���� �ð�
};

class CEnemy : public CGameObject
{
private:
	AI* m_pAI;
	tEnemyInfo m_tEnmInfo;

	float	m_fAccelGravity;

	fVector2D m_fvCurDir;
	fVector2D m_fvPrevDir;

	bool	m_bIsGrounded;

public:
	friend class CEnemyFactory;

	CEnemy();
	virtual ~CEnemy();
	virtual CEnemy* Clone();

public:
	virtual void update();
	virtual void render();

public:
	float GetVelocity() { return m_tEnmInfo.fVelocity; }
	void  SetVelocity(float fSpeed) { m_tEnmInfo.fVelocity = fSpeed; }

	void SetAI(AI* pAI);

private:
	// Enemy�� info�� enemy������ ���� ����
	// ��, factory������ ��� ���� -> ���� �����ؾ��ϱ� ����
	void SetEnemyInfo(const tEnemyInfo& info) { m_tEnmInfo = info; }

public:
	const tEnemyInfo& GetEnemyInfo() { return m_tEnmInfo; }

public:
	void Hit(CGameObject* pPlayer);

public:
	virtual void OnCollision(CCollider* target) override;
	virtual void OnCollisionEnter(CCollider* target) override;
};

