
#pragma once

#include <vector>
#include <map>

#include "OutTable.h"

#include "cbtypes.h"

/////////////////////////////////////////////////////////////////////////////
// COutputList window

class COutputList : public CListBox
{
// Construction
public:
	COutputList();

// Implementation
public:
	virtual ~COutputList();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};

class COutputWnd : public CDockablePane
{
// Construction
public:
	COutputWnd();

	void UpdateFonts();

// Attributes
protected:
	CMFCTabCtrl	m_wndTabs;

	COutputList m_wndOutputBuild;
	COutputList m_wndOutLexems;
	//COutputList m_wndOutputDebug;
	//COutputList m_wndOutputFind;

	COutTable m_wndOutTrm;
	COutTable m_wndOutCon;
	COutTable m_wndOutVar;

protected:
	void FillBuildWindow();
	void FillDebugWindow();
	void FillFindWindow();

	void FillOutTable();

	void AdjustHorzScroll(CListBox& wndListBox);

// Implementation
public:
	virtual ~COutputWnd();

	void SetBuildData(const std::vector<std::wstring>& buildData, bool isClear = true);
	void SetBuildData(const std::map<size_t, std::wstring>& buildData, bool isClear = true);
	void SetLexemsData(const TvLnLexems& lexems);
	void SetTrmData(bool isClear = true);
	void SetConData(bool isClear = true);
	void SetVarData(bool isClear = true);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

