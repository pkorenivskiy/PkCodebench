#pragma once


// CPkGridView view

class CPkGridView : public CListView
{
	DECLARE_DYNCREATE(CPkGridView)

protected:
	CPkGridView();           // protected constructor used by dynamic creation
	virtual ~CPkGridView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	void SetData();
};


