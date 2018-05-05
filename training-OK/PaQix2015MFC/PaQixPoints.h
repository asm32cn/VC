// PaQixPoints.h: interface for the CPaQixPoints class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAQIXPOINTS_H__61254A56_7A89_46FF_9B16_0311F85AE117__INCLUDED_)
#define AFX_PAQIXPOINTS_H__61254A56_7A89_46FF_9B16_0311F85AE117__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPaQixPoints  
{
public:
	void Restore();
	void Backup();
	void SetViewport(INT nLeft, INT nTop, INT nRight, INT nBottom);
	void SetNextPoints();
	void Init(INT nMaxX, INT nMaxY, INT nMinD, INT nRangeD);
	INT nData[4], nDataD[4];
	INT x1, x2;
	INT y1, y2;
	INT dx1, dx2;
	INT dy1, dy2;
	INT m_nLeft, m_nRight, m_nTop, m_nBottom;
	CPaQixPoints();
	virtual ~CPaQixPoints();

};

#endif // !defined(AFX_PAQIXPOINTS_H__61254A56_7A89_46FF_9B16_0311F85AE117__INCLUDED_)
