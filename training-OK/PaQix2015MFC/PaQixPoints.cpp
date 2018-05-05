// PaQixPoints.cpp: implementation of the CPaQixPoints class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PaQix2015MFC.h"
#include "PaQixPoints.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPaQixPoints::CPaQixPoints()
{

}

CPaQixPoints::~CPaQixPoints()
{

}

void CPaQixPoints::Init(INT nMaxX, INT nMaxY, INT nMinD, INT nRangeD)
{
	x1 = rand() % nMaxX;
	y1 = rand() % nMaxY;
	dx1 = nMinD + rand() % nRangeD;
	dy1 = nMinD + rand() % nRangeD;

	x2 = rand() % nMaxX;
	y2 = rand() % nMaxY;
	dx2 = nMinD + rand() % nRangeD;
	dy2 = nMinD + rand() % nRangeD;
}

void CPaQixPoints::SetNextPoints()
{
	INT nx, ny;
	nx = x1 + dx1;
	ny = y1 + dy1;
	if(nx>m_nRight || nx<m_nLeft){
		dx1 = -dx1;
	}else{
		x1 = nx;
	}
	if(ny>m_nBottom || ny<m_nTop){
		dy1 = -dy1;
	}else{
		y1 = ny;
	}
	nx = x2 + dx2;
	ny = y2 + dy2;
	if(nx>m_nRight || nx<m_nLeft){
		dx2 = -dx2;
	}else{
		x2 = nx;
	}
	if(ny>m_nBottom || ny<m_nTop){
		dy2 = -dy2;
	}else{
		y2 = ny;
	}
}

void CPaQixPoints::SetViewport(INT nLeft, INT nTop, INT nRight, INT nBottom)
{
	m_nLeft = nLeft;
	m_nTop = nTop;
	m_nRight = nRight;
	m_nBottom = nBottom;
}

void CPaQixPoints::Backup()
{
	nData[0]=x1; nDataD[0]=dx1;
	nData[1]=y1; nDataD[1]=dy1;
	nData[2]=x2; nDataD[2]=dx2;
	nData[3]=y2; nDataD[3]=dy2;
}

void CPaQixPoints::Restore()
{
	x1=nData[0]; dx1=nDataD[0];
	y1=nData[1]; dy1=nDataD[1];
	x2=nData[2]; dx2=nDataD[2];
	y2=nData[3]; dy2=nDataD[3];
}
