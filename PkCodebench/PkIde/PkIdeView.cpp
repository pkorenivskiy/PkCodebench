
// PkIdeView.cpp : implementation of the CPkIdeView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PkIde.h"
#endif

#include "PkIdeDoc.h"
#include "PkIdeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPkIdeView

IMPLEMENT_DYNCREATE(CPkIdeView, CEditView)

BEGIN_MESSAGE_MAP(CPkIdeView, CEditView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPkIdeView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CPkIdeView construction/destruction

CPkIdeView::CPkIdeView()
{
	// TODO: add construction code here

}

CPkIdeView::~CPkIdeView()
{
}

BOOL CPkIdeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}


// CPkIdeView printing


void CPkIdeView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPkIdeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CPkIdeView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CPkIdeView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

void CPkIdeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPkIdeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPkIdeView diagnostics

#ifdef _DEBUG
void CPkIdeView::AssertValid() const
{
	CEditView::AssertValid();
}

void CPkIdeView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CPkIdeDoc* CPkIdeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPkIdeDoc)));
	return (CPkIdeDoc*)m_pDocument;
}
#endif //_DEBUG


// CPkIdeView message handlers
