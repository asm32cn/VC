// PaQixColor.cpp: implementation of the CPaQixColor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PaQix2015MFC.h"
#include "PaQixColor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPaQixColor::CPaQixColor()
{
	m_bColorR = 10;
	m_bColorG = 10;
	m_bColorB = 10;
	Dr = 5;
	Dg = 5;
	Db = 5;
}

CPaQixColor::~CPaQixColor()
{

}

COLORREF CPaQixColor::GetColor()
{
	return RGB(m_bColorR, m_bColorG, m_bColorB);
}

void CPaQixColor::SetNextColor()
{
	INT nr, ng, nb;
	nb = m_bColorB+Db;
	if( (nb>255 && Db>0) || (nb<0 && Db<0) ){
		Db = -Db;
		ng = m_bColorG+Dg;
		if( (ng>255 && Dg>0) || (ng<0 && Dg<0) ){
			Dg = -Dg;
			nr = m_bColorR+Dr;
			if( (nr>255 && Dr>0) || (nr<0 && Dr<0) ){
				Dr = -Dr;
			}else{
				m_bColorR = nr;
			}
		}else{
			m_bColorG = ng;
		}
	}else{
		m_bColorB = nb;
	}
}

void CPaQixColor::Backup()
{
	bData[0]=m_bColorR; cDataD[0]=Dr;
	bData[1]=m_bColorG; cDataD[1]=Dg;
	bData[2]=m_bColorB; cDataD[2]=Db;
}

void CPaQixColor::Restore()
{
	m_bColorR=bData[0]; Dr=cDataD[0];
	m_bColorG=bData[1]; Dg=cDataD[1];
	m_bColorB=bData[2]; Db=cDataD[2];
}

COLORREF CPaQixColor::GetColorEx(INT nMax, INT nPos)
{
	INT m_nMax = nMax>0 ? nMax : 1;
	INT m_nPos2 = nPos>nMax ? 0 : nPos;
	return RGB(m_bColorR * m_nPos2 / m_nMax, m_bColorG * m_nPos2 / m_nMax, m_bColorB * m_nPos2 / m_nMax);
}
