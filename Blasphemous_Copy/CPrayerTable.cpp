#include "framework.h"
#include "CPrayerTable.h"
#include "CAnimator.h"
#include "CCollider.h"

CPrayerTable::CPrayerTable()
{
	m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"PrayerTable", L"texture\\Map\\PrayerTable\\priedieu_stand_and_liton_anim.png");

	InitObject(fPoint(0.f, 0.f), fPoint(132.f, 290.f));

	m_bIsActive = false;

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PrayerTable_Stand", m_pImg, fPoint(0.f, 111.f), fPoint(66.f, 145.f), fPoint(0.f, 0.f), 0, 0.1f, 1, true, false);
	GetAnimator()->CreateAnimation(L"PrayerTable_LitOn", m_pImg, fPoint(66.f, 111.f), fPoint(66.f, 145.f), fPoint(66.f, 0.f), 0, 0.1f, 6, true, false);
	GetAnimator()->Play(L"PrayerTable_Stand");

	CreateCollider();
	GetCollider()->SetFinalPos(GetPos());
	GetCollider()->SetOffsetPos(fPoint(-7.f, 0.f));
	GetCollider()->SetScale(GetScale());
}

CPrayerTable::~CPrayerTable()
{
}

CPrayerTable* CPrayerTable::Clone()
{
	return new CPrayerTable(*this);
}

void CPrayerTable::update()
{
	GetAnimator()->update();
}

void CPrayerTable::render()
{
	component_render();
}
