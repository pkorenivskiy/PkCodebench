
#include "stdafx.h"

#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputWnd::COutputWnd()
{
}

COutputWnd::~COutputWnd()
{
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create tabs window:
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;      // fail to create
	}

	// Create output panes:
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

	if (!m_wndOutputBuild.Create(dwStyle, rectDummy, &m_wndTabs, 2) ||
		!m_wndOutLexems.Create(dwStyle, rectDummy, &m_wndTabs, 3) ||
		!m_wndOutErrors.Create(dwStyle, rectDummy, &m_wndTabs, 4)/* ||
		!m_wndOutputFind.Create(dwStyle, rectDummy, &m_wndTabs, 4)*/)
	{
		TRACE0("Failed to create output windows\n");
		return -1;      // fail to create
	}

	//create out table
	const DWORD dwOutStyle = WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_ALIGNLEFT | WS_BORDER | WS_TABSTOP;
	m_wndOutTrm.Create(dwOutStyle, rectDummy, &m_wndTabs, IDC_OUTTRMTBL);
	m_wndOutCon.Create(dwOutStyle, rectDummy, &m_wndTabs, IDC_OUTTRMTBL);
	m_wndOutVar.Create(dwOutStyle, rectDummy, &m_wndTabs, IDC_OUTTRMTBL);

	UpdateFonts();

	CString strTabName;
	BOOL bNameValid;

	// Attach list windows to tab:
	bNameValid = strTabName.LoadString(IDS_BUILD_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputBuild, strTabName, (UINT)0);
	bNameValid = strTabName.LoadString(IDS_LEXEMS_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutLexems, strTabName, (UINT)0);

	/*bNameValid = strTabName.LoadString(IDS_DEBUG_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputDebug, strTabName, (UINT)1);
	bNameValid = strTabName.LoadString(IDS_FIND_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputFind, strTabName, (UINT)2);*/


	bNameValid = strTabName.LoadString(IDS_OUTTERM);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutTrm, strTabName, (UINT)2);

	bNameValid = strTabName.LoadString(IDS_OUTCON);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutCon, strTabName, (UINT)3);

	bNameValid = strTabName.LoadString(IDS_OUTIDN);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutVar, strTabName, (UINT)4);

	bNameValid = strTabName.LoadString(IDS_OUTERRS);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutErrors, strTabName, (UINT)4);

	// Fill output tabs with some dummy text (nothing magic here)
	FillBuildWindow();
	/*FillDebugWindow();
	FillFindWindow();*/

	FillOutTable();

	return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// Tab control should cover the whole client area:
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void COutputWnd::AdjustHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);

	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount(); i ++)
	{
		CString strItem;
		wndListBox.GetText(i, strItem);

		cxExtentMax = max(cxExtentMax, (int)dc.GetTextExtent(strItem).cx);
	}

	wndListBox.SetHorizontalExtent(cxExtentMax);
	dc.SelectObject(pOldFont);
}

void COutputWnd::FillBuildWindow()
{
	//m_wndOutputBuild.AddString(_T("Build output is being displayed here."));
	//m_wndOutputBuild.AddString(_T("The output is being displayed in rows of a list view"));
	//m_wndOutputBuild.AddString(_T("but you can change the way it is displayed as you wish..."));
}

void COutputWnd::FillDebugWindow()
{
	/*m_wndOutputDebug.AddString(_T("Debug output is being displayed here."));
	m_wndOutputDebug.AddString(_T("The output is being displayed in rows of a list view"));
	m_wndOutputDebug.AddString(_T("but you can change the way it is displayed as you wish..."));*/
}

void COutputWnd::FillFindWindow()
{
	/*m_wndOutputFind.AddString(_T("Find output is being displayed here."));
	m_wndOutputFind.AddString(_T("The output is being displayed in rows of a list view"));
	m_wndOutputFind.AddString(_T("but you can change the way it is displayed as you wish..."));*/
}

void COutputWnd::FillOutTable()
{
	m_wndOutTrm.InsertColumn(0, L"Ln");
	m_wndOutTrm.SetColumnWidth(0, 60);

	m_wndOutTrm.InsertColumn(1, L"Name");
	m_wndOutTrm.SetColumnWidth(1, 100);

	m_wndOutTrm.InsertColumn(2, L"Code");
	m_wndOutTrm.SetColumnWidth(2, 50);

	m_wndOutTrm.InsertColumn(3, L"Index");
	m_wndOutTrm.SetColumnWidth(3, 50);

	m_wndOutTrm.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

	m_wndOutCon.InsertColumn(0, L"Index");
	m_wndOutCon.SetColumnWidth(0, 60);

	m_wndOutCon.InsertColumn(1, L"Value");
	m_wndOutCon.SetColumnWidth(1, 60);

	m_wndOutCon.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

	m_wndOutVar.InsertColumn(0, L"Index");
	m_wndOutVar.SetColumnWidth(0, 60);

	m_wndOutVar.InsertColumn(1, L"Name");
	m_wndOutVar.SetColumnWidth(1, 60);

	m_wndOutVar.InsertColumn(2, L"Type");
	m_wndOutVar.SetColumnWidth(2, 50);

	m_wndOutVar.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
}

void COutputWnd::SetBuildData(const std::vector<std::wstring>& buildData, bool isClear)
{
	if (isClear)
		m_wndOutputBuild.ResetContent();

	for (auto& it : buildData)
		m_wndOutputBuild.AddString(it.c_str());
}

void COutputWnd::SetLexemsData(const PkLang::TmPkOutLexems& lexems)
{
	m_wndOutLexems.ResetContent();
	for (auto it : lexems)
	{
		std::wstring sOut = L"";
		for (auto itLex : it.second)
		{
			sOut += L"\"" + itLex.Name + L"\"...";
		}
		m_wndOutLexems.AddString(sOut.c_str());
	}
}

void COutputWnd::SetBuildData(const PkLang::TmErrors& buildData, bool isClear)
{
	if (isClear)
	{
		m_wndOutputBuild.ResetContent();
		m_wndOutErrors.ResetContent();
	}

	for (auto& it : buildData)
	{
		for (auto& itErr : it.second)
		{
			//swprintf_s(lpwszErr, 512, L"Line %d: %s", it.first, itErr.c_str());
			m_wndOutputBuild.AddString(itErr.c_str());

			m_wndOutErrors.AddString(itErr.c_str());
		}
	}

	if (m_wndOutputBuild.GetCount() > 0)
		m_wndOutputBuild.SetTopIndex(m_wndOutputBuild.GetCount() - 1);
}

void COutputWnd::SetTrmData(const PkLang::TmPkOutLexems& data, bool isClear)
{
	if (isClear)
		m_wndOutTrm.Clear();

	wchar_t lptszBuf[10];
	int nRow = 0;
	for (const auto& itRow : data)
	{
		for (const auto& it : itRow.second)
		{
			_itow_s(it.Line, lptszBuf, 10, 10);
			m_wndOutTrm.AddData(nRow, 0, lptszBuf);
			m_wndOutTrm.AddData(nRow, 1, it.Name.c_str());
			_itow_s(it.Id, lptszBuf, 10, 10);
			m_wndOutTrm.AddData(nRow, 2, lptszBuf);
			_itow_s(it.Index, lptszBuf, 10, 10);
			m_wndOutTrm.AddData(nRow++, 3, lptszBuf);
		}
	}	
}

void COutputWnd::SetConstData(const PkLang::TmPkOutConsts& data, bool isClear)
{
	if (isClear)
		m_wndOutCon.Clear();

	wchar_t lptszBuf[10];
	int nRow = 0;
	for (const auto& it : data)
	{
		_itow_s(it.first, lptszBuf,  10, 10);
		m_wndOutCon.AddData(0, lptszBuf);

		_itow_s(it.second.Value, lptszBuf, 10, 10);
		m_wndOutCon.AddData(nRow++, 1, lptszBuf);
	}
}

void COutputWnd::SetVarData(const PkLang::TvPkOutIdnts& data, bool isClear)
{
	if (isClear)
		m_wndOutVar.Clear();

	wchar_t lptszBuf[10];
	int nRow = 0;
	for (auto it : data)
	{
		_itow_s(it.Index, lptszBuf, 10, 10);
		m_wndOutVar.AddData(nRow, 0, lptszBuf);

		m_wndOutVar.AddData(nRow, 1, it.Name.c_str());

		_itow_s(it.Type, lptszBuf, 10, 10);
		m_wndOutVar.AddData(nRow++, 2, lptszBuf);
	}
}

void COutputWnd::UpdateFonts()
{
	m_wndOutputBuild.SetFont(&afxGlobalData.fontRegular);
	/*m_wndOutputDebug.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputFind.SetFont(&afxGlobalData.fontRegular);*/
}

/////////////////////////////////////////////////////////////////////////////
// COutputList1

COutputList::COutputList()
{
}

COutputList::~COutputList()
{
}

BEGIN_MESSAGE_MAP(COutputList, CListBox)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList message handlers

void COutputList::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_OUTPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}

	SetFocus();
}

void COutputList::OnEditCopy()
{
	//MessageBox(_T("Copy output"));
}

void COutputList::OnEditClear()
{
	//MessageBox(_T("Clear output"));
}

void COutputList::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();

	}
}
