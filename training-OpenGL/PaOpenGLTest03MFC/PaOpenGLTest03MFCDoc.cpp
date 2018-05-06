// PaOpenGLTest03MFCDoc.cpp : implementation of the CPaOpenGLTest03MFCDoc class
//

#include "stdafx.h"
#include "PaOpenGLTest03MFC.h"

#include "PaOpenGLTest03MFCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest03MFCDoc

IMPLEMENT_DYNCREATE(CPaOpenGLTest03MFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CPaOpenGLTest03MFCDoc, CDocument)
	//{{AFX_MSG_MAP(CPaOpenGLTest03MFCDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest03MFCDoc construction/destruction

CPaOpenGLTest03MFCDoc::CPaOpenGLTest03MFCDoc()
{
	// TODO: add one-time construction code here
	m_transY=100;
	m_transX=100;
	m_angle2=15;
	m_angle1=15;
}

CPaOpenGLTest03MFCDoc::~CPaOpenGLTest03MFCDoc()
{
}

BOOL CPaOpenGLTest03MFCDoc::OnNewDocument()
{
	//if (!CDocument::OnNewDocument())
	//	return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	//return TRUE;
	if (!CDocument::OnNewDocument())
		return FALSE;
	glNewList(ArmPart, GL_COMPILE);
		glBegin(GL_POLYGON);
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glVertex2f(-10.0f, 10.0f);
			glVertex2f(-10.0f, -10.0f);
			glVertex2f(100.0f, -10.0f);
			glVertex2f(100.0f, 10.0f);
		glEnd();
	glEndList();
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest03MFCDoc serialization

void CPaOpenGLTest03MFCDoc::Serialize(CArchive& ar)
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
// CPaOpenGLTest03MFCDoc diagnostics

#ifdef _DEBUG
void CPaOpenGLTest03MFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPaOpenGLTest03MFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest03MFCDoc commands

void CPaOpenGLTest03MFCDoc::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	/*
	*/
	glPushMatrix();
	glTranslated( m_transX, m_transY, 0);
	glRotated( m_angle1, 0, 0, 1);
	glPushMatrix();
	glTranslated( 90, 0, 0);
	glRotated( m_angle2, 0, 0, 1);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glCallList(ArmPart);
	glPopMatrix();
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glCallList(ArmPart);
	glPopMatrix();


	glFlush();
	
}
