
// PkIdeView.h : interface of the CPkIdeView class
//

#pragma once


class CPkIdeView : public CEditView
{
protected: // create from serialization only
	CPkIdeView();
	DECLARE_DYNCREATE(CPkIdeView)

// Attributes
public:
	CPkIdeDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPkIdeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PkIdeView.cpp
inline CPkIdeDoc* CPkIdeView::GetDocument() const
   { return reinterpret_cast<CPkIdeDoc*>(m_pDocument); }
#endif

