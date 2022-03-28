#pragma once
#include "CGameObject.h"
#include "AI.h"
#include "CState.h"

class AI;
class CWeapon;
class CD2DImage;

struct tEnemyInfo
{
	float fVelocity;
	float fMaxVelocity;
	float fHP;
	float fRecogRange;
	float fAttRange;
	float fAtt;
	float fAttDelayTime;
	UINT  iAttCount = 0;
	float fInvTime;		// ���� �ð�
	bool  bIsInvincible;
	UINT  iMoney;
	CWeapon* pWeapon;
};

class CEnemy : public CGameObject
{
private:
	CD2DImage* m_pImg;

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

public:
	virtual void update();
	virtual void render();

	virtual void component_render();
	virtual void debug_render();

	virtual void Update_Animation() = 0;
	virtual void Init_Animation() = 0;

public:
	void SetImage(const wstring& strKey, const wstring& strPath);
	CD2DImage* GetImage();

	float GetVelocity() { return m_tEnmInfo.fVelocity; }
	void  SetVelocity(float fSpeed) { m_tEnmInfo.fVelocity = fSpeed; }

	fVector2D GetDir() { return m_fvCurDir; }
	void SetDir(fVector2D dir) { m_fvCurDir = dir; }

	AI*  GetAI();
	void SetAI(AI* pAI);

protected:
	// Enemy�� info�� enemy������ ���� ����
	// ��, factory������ ��� ���� -> ���� �����ؾ��ϱ� ����
	void SetEnemyInfo(const tEnemyInfo& info) { m_tEnmInfo = info; }

public:
	const tEnemyInfo& GetEnemyInfo() { return m_tEnmInfo; }

	const UINT GetAttCount() { return m_tEnmInfo.iAttCount; }
	void SetAttCount(const UINT count) { m_tEnmInfo.iAttCount = count; }

public:
	virtual void Attack() = 0;
	
	void SetInvincible(const bool bIsInv) { m_tEnmInfo.bIsInvincible = bIsInv; }

	virtual void Hit(CGameObject* pPlayer);
	virtual void Die();

public:
	virtual void OnCollision(CCollider* target) override;
	virtual void OnCollisionEnter(CCollider* target) override;
};

