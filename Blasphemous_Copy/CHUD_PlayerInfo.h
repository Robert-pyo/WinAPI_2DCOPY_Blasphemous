#pragma once
#include "CHUD.h"
class CHUD_PlayerInfo : public CHUD
{
private:
	// �÷��̾� ü��
	float m_fMaxHP;
	float m_fCurHP;

	// �÷��̾� ����(a.k.a ����)
	float m_fMaxMP;
	float m_fCurMP;

	// ü�� ���� ���� �ö�ũ) ���� ����
	USHORT m_sPotionCount;
	USHORT m_sMaxPotionCount;

	// mp�� �� �� �ִ� ��ų�� ���� ��

public:
	CHUD_PlayerInfo();
	~CHUD_PlayerInfo();

	virtual CHUD_PlayerInfo* Clone();

public:
	virtual void update() final;
	virtual void render() final;
};

