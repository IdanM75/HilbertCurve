
// OOPTask4MFCDoc.cpp : implementation of the COOPTask4MFCDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OOPTask4MFC.h"
#endif

#include "OOPTask4MFCDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COOPTask4MFCDoc

IMPLEMENT_DYNCREATE(COOPTask4MFCDoc, CDocument)

BEGIN_MESSAGE_MAP(COOPTask4MFCDoc, CDocument)
END_MESSAGE_MAP()


// COOPTask4MFCDoc construction/destruction

COOPTask4MFCDoc::COOPTask4MFCDoc() noexcept
{
	// TODO: add one-time construction code here

}

COOPTask4MFCDoc::~COOPTask4MFCDoc()
{
}

BOOL COOPTask4MFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// COOPTask4MFCDoc serialization

void COOPTask4MFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void COOPTask4MFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void COOPTask4MFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void COOPTask4MFCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// COOPTask4MFCDoc diagnostics

#ifdef _DEBUG
void COOPTask4MFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COOPTask4MFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COOPTask4MFCDoc commands
