#pragma once
class CResource
{
private:
	wstring m_strKey;	// 해당 리소스를 관리하기 위한 key값
	wstring m_strPath;	// 해당 리소스의 경로

public:
	CResource();
	virtual ~CResource();

	void SetKey(const wstring& strKey);
	void SetPath(const wstring& strPath);

	const wstring& GetKey();
	const wstring& GetPath();
};

