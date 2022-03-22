#pragma once
#include "CGameObject.h"

class CD2DImage;

class CEffect : public CGameObject
{
private:
	CD2DImage* m_pFxImg;

	CGameObject* m_pOwner;

	float m_fFxDuration;
	bool  m_bIsStart;

public:
	CEffect();
	virtual ~CEffect();

public:
	virtual void update() = 0;
	virtual void render() = 0;

public:
	void LoadEffectImg(const wstring& strKey, const wstring& strRelativePath);
	CD2DImage* GetFxImg() { return m_pFxImg; }

public:
	CGameObject* GetOwnerObj() { return m_pOwner; }
	void		 SetOwnerObj(CGameObject* pObj) { m_pOwner = pObj; }

	void  SetDuration(float fDuration) { m_fFxDuration = fDuration; }
	float GetDuration() { return m_fFxDuration; }

	bool IsFxStart() { return m_bIsStart; }
	void SetFxStart(bool bIsStart) { m_bIsStart = bIsStart; }
};

