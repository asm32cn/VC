// PaOpenGLTest01MFCDoc.cpp : implementation of the CPaOpenGLTest01MFCDoc class
//

#include "stdafx.h"
#include "PaOpenGLTest01MFC.h"

#include "PaOpenGLTest01MFCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum GLDisplayListNames { ArmPart1, ArmPart2 };

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest01MFCDoc

IMPLEMENT_DYNCREATE(CPaOpenGLTest01MFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CPaOpenGLTest01MFCDoc, CDocument)
	//{{AFX_MSG_MAP(CPaOpenGLTest01MFCDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest01MFCDoc construction/destruction

CPaOpenGLTest01MFCDoc::CPaOpenGLTest01MFCDoc()
{
	// TODO: add one-time construction code here

}

CPaOpenGLTest01MFCDoc::~CPaOpenGLTest01MFCDoc()
{
}

BOOL CPaOpenGLTest01MFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
    glNewList(ArmPart1, GL_COMPILE);
    GLfloat RedSurface[]   = { 1.0f, 0.0f, 0.0f, 1.0f};
    GLfloat GreenSurface[] = { 0.0f, 1.0f, 0.0f, 1.0f};
    GLfloat BlueSurface[]  = { 0.0f, 0.0f, 1.0f, 1.0f};
    GLfloat LightAmbient[]  = { 0.1f, 0.1f, 0.1f, 0.1f };
    GLfloat LightDiffuse[]  = { 0.7f, 0.7f, 0.7f, 0.7f };
    GLfloat LightSpecular[] = { 0.0f, 0.0f, 0.0f, 0.1f };
    GLfloat LightPosition[] = { 5.0f, 5.0f, 5.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glEnable(GL_LIGHT0);
    glMaterialfv(GL_FRONT_AND_BACK,
    GL_AMBIENT, RedSurface);
    glBegin(GL_POLYGON);
        glNormal3d( 1.0,  0.0,  0.0);
        glVertex3d( 1.0,  1.0,  1.0);
        glVertex3d( 1.0, -1.0,  1.0);
        glVertex3d( 1.0, -1.0, -1.0);
        glVertex3d( 1.0,  1.0, -1.0); // ����һ����
    glEnd();
    glBegin(GL_POLYGON);
        glNormal3d( -1.0,  0.0,  0.0);
        // �˴�ͬ�ϻ��ڶ����档�����������Ϊ����ԭ�㡣
    glEnd();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GreenSurface);
    // �˴�ͬ�ϻ������� �ĸ��棬ע��ƽ�淨������ꡣ
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, BlueSurface);
    // �˴�ͬ�ϻ����塢 �����档
    glEndList();
    glNewList(ArmPart2, GL_COMPILE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GreenSurface);
    auxSolidTeapot(1.0);// �ø����⺯���������
    glEndList();

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest01MFCDoc serialization

void CPaOpenGLTest01MFCDoc::Serialize(CArchive& ar)
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
// CPaOpenGLTest01MFCDoc diagnostics

#ifdef _DEBUG
void CPaOpenGLTest01MFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPaOpenGLTest01MFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest01MFCDoc commands

void CPaOpenGLTest01MFCDoc::RenderScene()
{
	/*
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
	*/
	double m_angle1=60.0;
    double m_angle2=30.0;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslated(3.0, 0.0, -8.0);
    glRotated( m_angle1, 0, 0, 1);
    glRotated( m_angle2, 0, 1, 0);
    glCallList(ArmPart1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0.0, 0.0, -8.0);
    glCallList(ArmPart2);
    glPopMatrix();
    glFlush();
}
