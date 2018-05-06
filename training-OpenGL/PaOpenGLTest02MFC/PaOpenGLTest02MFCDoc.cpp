// PaOpenGLTest02MFCDoc.cpp : implementation of the CPaOpenGLTest02MFCDoc class
//

#include "stdafx.h"
#include "PaOpenGLTest02MFC.h"

#include "PaOpenGLTest02MFCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest02MFCDoc

IMPLEMENT_DYNCREATE(CPaOpenGLTest02MFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CPaOpenGLTest02MFCDoc, CDocument)
	//{{AFX_MSG_MAP(CPaOpenGLTest02MFCDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest02MFCDoc construction/destruction

CPaOpenGLTest02MFCDoc::CPaOpenGLTest02MFCDoc()
{
	// TODO: add one-time construction code here

}

CPaOpenGLTest02MFCDoc::~CPaOpenGLTest02MFCDoc()
{
}

BOOL CPaOpenGLTest02MFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest02MFCDoc serialization

void CPaOpenGLTest02MFCDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest02MFCDoc diagnostics

#ifdef _DEBUG
void CPaOpenGLTest02MFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPaOpenGLTest02MFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest02MFCDoc commands
