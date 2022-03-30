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

	// 플레이어 체력
	float m_fMaxHP;
	float m_fCurHP;

	// 플레이어 마나(a.k.a 열정)
	float m_fMaxMP;
	float m_fCurMP;

	// 체력 포션 담즙 플라스크) 현재 갯수
	USHORT m_sPotionCount;
	USHORT m_sMaxPotionCount;

	// mp로 쓸 수 있는 스킬이 있을 것

public:
	virtual void update() final;
	virtual void render() final;
};

