// PaOpenGLTest03MFCDoc.h : interface of the CPaOpenGLTest03MFCDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAOPENGLTEST03MFCDOC_H__1100ADD5_D19A_4107_B82A_8217AF587453__INCLUDED_)
#define AFX_PAOPENGLTEST03MFCDOC_H__1100ADD5_D19A_4107_B82A_8217AF587453__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPaOpenGLTest03MFCDoc : public CDocument
{
protected: // create from serialization only
	CPaOpenGLTest03MFCDoc();
	DECLARE_DYNCREATE(CPaOpenGLTest03MFCDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaOpenGLTest03MFCDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	enum GLDisplayListNames
	{
		ArmPart=1
	};

	double m_transY;
	double m_transX;
	double m_angle2;
	double m_angle1;
	void RenderScene(void);
	virtual ~CPaOpenGLTest03MFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPaOpenGLTest03MFCDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAOPENGLTEST03MFCDOC_H__1100ADD5_D19A_4107_B82A_8217AF587453__INCLUDED_)
