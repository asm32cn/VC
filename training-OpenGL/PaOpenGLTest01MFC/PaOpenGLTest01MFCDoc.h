// PaOpenGLTest01MFCDoc.h : interface of the CPaOpenGLTest01MFCDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAOPENGLTEST01MFCDOC_H__88DE4A76_1CFF_4BA8_94E7_35245A49AABD__INCLUDED_)
#define AFX_PAOPENGLTEST01MFCDOC_H__88DE4A76_1CFF_4BA8_94E7_35245A49AABD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPaOpenGLTest01MFCDoc : public CDocument
{
protected: // create from serialization only
	CPaOpenGLTest01MFCDoc();
	DECLARE_DYNCREATE(CPaOpenGLTest01MFCDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaOpenGLTest01MFCDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void RenderScene();
	virtual ~CPaOpenGLTest01MFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPaOpenGLTest01MFCDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAOPENGLTEST01MFCDOC_H__88DE4A76_1CFF_4BA8_94E7_35245A49AABD__INCLUDED_)
