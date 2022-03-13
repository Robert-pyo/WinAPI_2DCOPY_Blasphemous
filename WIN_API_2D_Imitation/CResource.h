#pragma once
class CResource
{
private:
	wstring m_strKey;	// �ش� ���ҽ��� �����ϱ� ���� key��
	wstring m_strPath;	// �ش� ���ҽ��� ���

public:
	CResource();
	virtual ~CResource();

	void SetKey(const wstring& strKey);
	void SetPath(const wstring& strPath);

	const wstring& GetKey();
	const wstring& GetPath();
};

