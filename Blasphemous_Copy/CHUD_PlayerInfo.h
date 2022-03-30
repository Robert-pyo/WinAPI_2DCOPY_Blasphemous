#pragma once
#include "CHUD.h"

class CD2DImage;

class CHUD_PlayerInfo : public CHUD
{
	SINGLETON(CHUD_PlayerInfo);
private:
	CD2DImage* m_pPortraitImg;
	CD2DImage* m_pHealthImg;
	CD2DImage* m_pMpImg;

	fPoint m_fHpPos;
	fPoint m_fMpPos;

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
	virtual void update() final;
	virtual void render() final;
};

