#pragma once

class CPlayer;
class CD2DImage;

class CHUD
{
private:
	fPoint m_fptPos;
	fPoint m_fptScale;

protected:
	CPlayer* m_pPlayer;		// 플레이어 정보

	CD2DImage* m_pImg;		// 해당 HUD가 가지고있는 이미지 정보

public:
	CHUD();
	virtual ~CHUD();

public:
	virtual void update() = 0;
	virtual void render() = 0;

public:
	void SetPos(const fPoint& fptPos) { m_fptPos = fptPos; }
	const fPoint& GetPos() { return m_fptPos; }

	void SetScale(const fPoint& fptScale) { m_fptScale = fptScale; }
	const fPoint& GetScale() { return m_fptScale; }

public:
	void SetImage(CD2DImage* pImg) { m_pImg = pImg; }
};

