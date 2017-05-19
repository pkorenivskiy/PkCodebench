
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "../PkLangDefs/PkLang.h"

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CFileView         m_wndFileView;
	CClassView        m_wndClassView;
	COutputWnd        m_wndOutput;
	CPropertiesWnd    m_wndProperties;

public:	
	void SetBuildData(const std::vector<std::wstring>& buildData, bool isClear = true) { m_wndOutput.SetBuildData(buildData, isClear); };
	void SetBuildData(const PkLang::TmErrors& buildData, bool isClear = true) { m_wndOutput.SetBuildData(buildData, isClear); };
	void SetLexemsData(const PkLang::TmPkOutLexems& lexems) { m_wndOutput.SetLexemsData(lexems); }
	void SetTrmData(const PkLang::TmPkOutLexems& data, bool isClear = true) { m_wndOutput.SetTrmData(data, isClear); };
	void SetConstData(const PkLang::TmPkOutConsts& data, bool isClear = true) { m_wndOutput.SetConstData(data, isClear); };
	void SetVarData(const PkLang::TvPkOutIdnts& data, bool isClear = true) { m_wndOutput.SetVarData(data, isClear); };

	COutputList* GetBuildOutWnd() { return m_wndOutput.GetBuildOutWnd(); }

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
//	afx_msg void OnBuildLexicalanalyze();
};


