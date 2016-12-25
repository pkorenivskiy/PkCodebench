// PkGridView.cpp : implementation file
//

#include "stdafx.h"
#include "PkIde.h"
#include "PkGridView.h"


// CPkGridView

IMPLEMENT_DYNCREATE(CPkGridView, CListView)

CPkGridView::CPkGridView()
{

}

CPkGridView::~CPkGridView()
{
}

BEGIN_MESSAGE_MAP(CPkGridView, CListView)
END_MESSAGE_MAP()


// CPkGridView diagnostics

#ifdef _DEBUG
void CPkGridView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CPkGridView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPkGridView message handlers
void CPkGridView::SetData()
{
	//auto lc = GetListCtrl();
}