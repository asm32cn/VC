// PuzzleConfigure.h: interface for the CPuzzleConfigure class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUZZLECONFIGURE_H__40348EBD_EF62_4E7D_9482_673F2826DBC6__INCLUDED_)
#define AFX_PUZZLECONFIGURE_H__40348EBD_EF62_4E7D_9482_673F2826DBC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPuzzleConfigure  
{
public:
	void Init(INT nGameResID, INT nGameResWidth, INT nGameResHeight, INT nItemWidth, INT nItemHeight);
	INT m_nGameResWidth;
	INT m_nGameResHeight;
	INT m_nCountX;
	INT m_nCountY;
	INT m_nItemCount;
	INT m_nItemWidth;
	INT m_nItemHeight;
	INT m_nGameResID;
	CPuzzleConfigure();
	virtual ~CPuzzleConfigure();

};

#endif // !defined(AFX_PUZZLECONFIGURE_H__40348EBD_EF62_4E7D_9482_673F2826DBC6__INCLUDED_)
