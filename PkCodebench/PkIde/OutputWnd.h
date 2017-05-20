
#pragma once

#include <vector>
#include <map>

#include "OutTable.h"

#include "../PkLangDefs/PkLang.h"

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
	COutputList m_wndOutErrors;
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
	void SetBuildData(const PkLang::TmErrors& buildData, bool isClear = true);
	void ClearErrors();

	void SetLexemsData(const PkLang::TmPkOutLexems& lexems);
	
	void SetTrmData(const PkLang::TmPkOutLexems& data, bool isClear = true);
	void SetConstData(const PkLang::TmPkOutConsts& data, bool isClear = true);
	void SetVarData(const PkLang::TvPkOutIdnts& data, bool isClear = true);	

	COutputList* GetBuildOutWnd() { return &m_wndOutputBuild; }

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

