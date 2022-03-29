#pragma once
class CGameManager
{
private:
	SINGLETON(CGameManager);

private:
	bool m_bDisableControl;

public:
	void update();
	void init();

public:
	void SetDisableControl(bool bRemote) { m_bDisableControl = bRemote; }
	bool IsDisableControl() { return m_bDisableControl; }
};

