#pragma once


// COutTable

class COutTable : public CListCtrl
{
public:
	COutTable();

public:
	virtual ~COutTable();

public:
	void AddData(int row, int col, const wchar_t *str);
	void AddData(int col, const wchar_t *str);
	void Clear();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};


