// PaQixColor.h: interface for the CPaQixColor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAQIXCOLOR_H__090EB072_E52B_42F4_B4B4_3F5D4FC19D63__INCLUDED_)
#define AFX_PAQIXCOLOR_H__090EB072_E52B_42F4_B4B4_3F5D4FC19D63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPaQixColor  
{
public:
	COLORREF GetColorEx(INT nMax, INT nPos);
	void Restore();
	void Backup();
	void SetNextColor();
	COLORREF GetColor();
	BYTE m_bColorR;
	BYTE m_bColorG;
	BYTE m_bColorB;
	CHAR Dr;
	CHAR Dg;
	CHAR Db;
	CHAR cDataD[3];
	BYTE bData[3];
	CPaQixColor();
	virtual ~CPaQixColor();

};

#endif // !defined(AFX_PAQIXCOLOR_H__090EB072_E52B_42F4_B4B4_3F5D4FC19D63__INCLUDED_)
