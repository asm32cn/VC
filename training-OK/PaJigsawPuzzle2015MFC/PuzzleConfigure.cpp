// PuzzleConfigure.cpp: implementation of the CPuzzleConfigure class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PaJigsawPuzzle2015MFC.h"
#include "PuzzleConfigure.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPuzzleConfigure::CPuzzleConfigure()
{

}

CPuzzleConfigure::~CPuzzleConfigure()
{

}

void CPuzzleConfigure::Init(INT nGameResID, INT nGameResWidth, INT nGameResHeight, INT nItemWidth, INT nItemHeight)
{
	m_nGameResID     = nGameResID;
	m_nGameResWidth  = nGameResWidth;
	m_nGameResHeight = nGameResHeight;
	m_nItemWidth     = nItemWidth;
	m_nItemHeight    = nItemHeight;
	m_nCountX = nGameResWidth / nItemWidth;
	m_nCountY = nGameResHeight / nItemHeight;
	m_nItemCount = m_nCountX * m_nCountY;
}
