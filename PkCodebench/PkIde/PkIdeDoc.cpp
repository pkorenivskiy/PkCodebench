
// PkIdeDoc.cpp : implementation of the CPkIdeDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PkIde.h"
#endif

#include "PkIdeDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPkIdeDoc

IMPLEMENT_DYNCREATE(CPkIdeDoc, CDocument)

BEGIN_MESSAGE_MAP(CPkIdeDoc, CDocument)
	ON_COMMAND(ID_BUILD_LEXICALANALYZE, &CPkIdeDoc::OnBuildLexicalanalyze)
	ON_COMMAND(ID_BUILD_SYNTAXANALYZE, &CPkIdeDoc::OnBuildLexicalanalyze)
END_MESSAGE_MAP()


// CPkIdeDoc construction/destruction

CPkIdeDoc::CPkIdeDoc()
{
	// TODO: add one-time construction code here
}

CPkIdeDoc::~CPkIdeDoc()
{
	
}

BOOL CPkIdeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CPkIdeDoc serialization

void CPkIdeDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	if (!m_viewList.IsEmpty())
	{
		auto pView = reinterpret_cast<CEditView*>(m_viewList.GetHead()); //->SerializeRaw(ar);
		//reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);

		if (ar.IsLoading())
		{
			CFile* pFile = ar.GetFile();
			pFile->Seek(0, FILE_BEGIN);
			int nFileSizeBytes = (int)pFile->GetLength();
			int nFileSizeChars = nFileSizeBytes / sizeof(TCHAR);
			LPSTR lpszBuf = (LPSTR)malloc((size_t)nFileSizeBytes + 2);
			if (lpszBuf != NULL)
			{
				pFile->Read(lpszBuf, (UINT)nFileSizeBytes);
				lpszBuf[nFileSizeBytes] = '\0';
				lpszBuf[nFileSizeBytes+1] = '\0';
				if (!IsTextUnicode(lpszBuf, nFileSizeBytes, nullptr))
				{					
					CA2CT lptszText(lpszBuf + 3);
					pView->SetWindowText(lptszText);
				}
				else
				{					
					//pView->SetWindowText((wchar_t*)lpszBuf);
					pFile->Seek(0, FILE_BEGIN);
					pView->SerializeRaw(ar);
				}
				this->UpdateAllViews(pView);
				free(lpszBuf);
			}
		}
	}
#ifdef SHARED_HANDLERS

	if (m_viewList.IsEmpty() && ar.IsLoading())
	{
		CFile* pFile = ar.GetFile();
		pFile->Seek(0, FILE_BEGIN);
		ULONGLONG nFileSizeBytes = pFile->GetLength();
		ULONGLONG nFileSizeChars = nFileSizeBytes/sizeof(TCHAR);
		LPTSTR lpszText = (LPTSTR)malloc(((size_t)nFileSizeChars + 1) * sizeof(TCHAR));
		if (lpszText != NULL)
		{
			ar.Read(lpszText, (UINT)nFileSizeBytes);
			lpszText[nFileSizeChars] = '\0';
			m_strThumbnailContent = lpszText;
			m_strSearchContent = lpszText;
		}
	}
#endif
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPkIdeDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(m_strThumbnailContent, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPkIdeDoc::InitializeSearchContent()
{
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// Use the entire text file content as the search content.
	SetSearchContent(m_strSearchContent);
}

void CPkIdeDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPkIdeDoc diagnostics

#ifdef _DEBUG
void CPkIdeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPkIdeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPkIdeDoc commands


void CPkIdeDoc::OnBuildLexicalanalyze()
{
	CSyntalizer syntalyzer;

	const auto& errors = syntalyzer.GetErrors();

	auto view = reinterpret_cast<CEditView*>(m_viewList.GetHead());
	
	view->SetWindowText(syntalyzer.GetErrorText().c_str());
}
