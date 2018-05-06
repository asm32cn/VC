// PaOpenGLTest02MFCDoc.h : interface of the CPaOpenGLTest02MFCDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAOPENGLTEST02MFCDOC_H__27006ACF_6C78_46DE_B55B_849E60B8FB47__INCLUDED_)
#define AFX_PAOPENGLTEST02MFCDOC_H__27006ACF_6C78_46DE_B55B_849E60B8FB47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPaOpenGLTest02MFCDoc : public CDocument
{
protected: // create from serialization only
	CPaOpenGLTest02MFCDoc();
	DECLARE_DYNCREATE(CPaOpenGLTest02MFCDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaOpenGLTest02MFCDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPaOpenGLTest02MFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPaOpenGLTest02MFCDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAOPENGLTEST02MFCDOC_H__27006ACF_6C78_46DE_B55B_849E60B8FB47__INCLUDED_)
