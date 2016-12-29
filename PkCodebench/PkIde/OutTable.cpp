// OutTable.cpp : implementation file
//

#include "stdafx.h"
#include "PkIde.h"
#include "OutTable.h"


// COutTable

COutTable::COutTable()
{

}

COutTable::~COutTable()
{
}

BEGIN_MESSAGE_MAP(COutTable, CListCtrl)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


void COutTable::AddData(int row, int col, const wchar_t *str)
{
	LVITEM lv;
	lv.iItem = row;
	lv.iSubItem = col;
	lv.pszText = (LPTSTR)str;
	lv.mask = LVIF_TEXT;
	if (col == 0)
		InsertItem(&lv);
	else
		SetItem(&lv);
}

void COutTable::AddData(int col, const wchar_t *str)
{
	LVITEM lv;
	lv.iItem = GetItemCount();
	lv.iSubItem = col;
	lv.pszText = (LPTSTR)str;
	lv.mask = LVIF_TEXT;
	if (col == 0)
		InsertItem(&lv);
	else
		SetItem(&lv);
}

void COutTable::Clear()
{
	DeleteAllItems();
}

// COutTable message handlers

void COutTable::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
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

void COutTable::OnEditCopy()
{
	//MessageBox(_T("Copy output"));
}

void COutTable::OnEditClear()
{
	Clear();
}

void COutTable::OnViewOutput()
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
