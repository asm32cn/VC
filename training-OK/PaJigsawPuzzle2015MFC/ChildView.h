// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__53CBB65A_D958_49FD_8756_8AB2B746EA33__INCLUDED_)
#define AFX_CHILDVIEW_H__53CBB65A_D958_49FD_8756_8AB2B746EA33__INCLUDED_

#include "PuzzleConfigure.h"	// Added by ClassView
#include "PuzzleItem.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	INT m_nCountStep;
	void PA_DoGameAutoStop();
	void PA_DoGameWinFlash();
	void PA_DoGameAutoMove();
	void PA_DoGameAuto();
	CPuzzleConfigure A_objGameConfigure[6];
	void PA_RenderResource(CDC &dc, INT nResourceID, LPCTSTR szType, INT cx, INT cy);
	void PA_DoGameCheckSucceed();
	void PA_DoWindowFinalize();
	void PA_DoWindowInitialize();
	void PA_DoGameMoveItem(INT m_nPosID);
	void ShowStatusString(CString strDisplay);
	void PA_DoGameInit();
	void PA_DoGameDisplay();
	virtual ~CChildView();
	CDC m_cdcGameRes;
	CBitmap m_bmpGameRes;
	CDC m_cdcGameResDark;
	CBitmap m_bmpGameResDark;
	CDC m_cdcMemory;
	CBitmap m_bmpMemory;
	CPen m_penHover;

	CRect m_rectClient;

	CPuzzleItem A_objItems[48];
	BOOL m_bGameSucceed;
	CBrush m_cbBackground;
	INT m_nCountX;
	INT m_nCountY;
	INT m_nItemWidth;
	INT m_nItemHeight;
	INT m_nItemWidth1;
	INT m_nItemHeight1;
	INT m_nItemCount;
	INT m_nCursorX;
	INT m_nCursorY;
	INT m_nHoverID;
	INT m_nGameResWidth;
	INT m_nGameResHeight;
	INT m_nClientWidth;
	INT m_nClientHeight;
	INT m_nDisplayWidth;
	INT m_nDisplayHeight;
	INT m_nTimerID;
	INT m_isAutoMove;
	INT m_nPosID_blank;
	INT m_nSelectedID;
	INT m_nSelected2ID;
	INT m_nGameSelected;
	INT m_nGameSelectedPrevious;
	INT A_nCachedID[48];
	CString m_strDebug;

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg void OnDoGameInit();
	afx_msg void OnDoGameAuto();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void PA_DoSelectNewGame(UINT nID);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__53CBB65A_D958_49FD_8756_8AB2B746EA33__INCLUDED_)
