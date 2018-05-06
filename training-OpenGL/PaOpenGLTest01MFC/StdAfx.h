// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__4B70770D_CAB8_499D_924F_79B8A6E0DA7D__INCLUDED_)
#define AFX_STDAFX_H__4B70770D_CAB8_499D_924F_79B8A6E0DA7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>

#pragma comment( lib, "opengl32.lib")    // OpenGL32连接库
#pragma comment( lib, "glu32.lib")        // GLu32连接库
#pragma comment( lib, "glaux.lib")        // GLaux连接库
//#pragma comment( lib, "glut.lib")        // Glut链接库

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__4B70770D_CAB8_499D_924F_79B8A6E0DA7D__INCLUDED_)
