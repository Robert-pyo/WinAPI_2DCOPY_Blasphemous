#pragma once
class CPathManager
{
	SINGLETON(CPathManager);

public:
	const static int MAXSIZE_PATH = 255;

private:
	WCHAR m_szContentPath[255];		// 리소스 경로 (255 -> 윈도우에서 경로의 최대 길이)

public:
	void init();

	const WCHAR* GetContentPath();
	const WCHAR* GetRelativeContentPath();
};

