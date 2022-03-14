#pragma once
class CPathManager
{
	SINGLETON(CPathManager);

public:
	const static int MAXSIZE_PATH = 255;

private:
	WCHAR m_szContentPath[255];		// ���ҽ� ��� (255 -> �����쿡�� ����� �ִ� ����)

public:
	void init();

	const WCHAR* GetContentPath();
	const WCHAR* GetRelativeContentPath();
};

