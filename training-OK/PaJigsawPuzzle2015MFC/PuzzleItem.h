// PuzzleItem.h: interface for the CPuzzleItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUZZLEITEM_H__AA12FBDF_46F2_4F64_9476_9FF6A8D9E0A4__INCLUDED_)
#define AFX_PUZZLEITEM_H__AA12FBDF_46F2_4F64_9476_9FF6A8D9E0A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPuzzleItem  
{
public:
	INT m_nImageStartX;
	INT m_nImageStartY;
	INT m_nPosition;
	INT m_nStartX;
	INT m_nStartY;
	CPuzzleItem();
	virtual ~CPuzzleItem();

};

#endif // !defined(AFX_PUZZLEITEM_H__AA12FBDF_46F2_4F64_9476_9FF6A8D9E0A4__INCLUDED_)
