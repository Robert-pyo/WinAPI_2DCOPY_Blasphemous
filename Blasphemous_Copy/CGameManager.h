#pragma once
class CGameManager
{
private:
	SINGLETON(CGameManager);

private:
	bool m_bGameStart;
	bool m_bDisableControl;

public:
	void update();
	void init();

public:
	void SetGameStart(bool isStart) { m_bGameStart = isStart; }
	bool GetIsGameStarted() { return m_bGameStart; }

	void SetDisableControl(bool bRemote) { m_bDisableControl = bRemote; }
	bool IsDisableControl() { return m_bDisableControl; }
};

