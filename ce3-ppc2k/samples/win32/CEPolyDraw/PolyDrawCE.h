
#if !defined(AFX_POLYDRAWCE_H__26A9E7B5_0E0F_11D3_8E70_00C04F72E693__INCLUDED_)
#define AFX_POLYDRAWCE_H__26A9E7B5_0E0F_11D3_8E70_00C04F72E693__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

//
//Colors : Standard colors for QcQp
#define BLACK           0
#define WHITE           1
#define RED             2
#define GREEN           3
#define BLUE            4
#define YELLOW          5
#define MAGENTA         6
#define CYAN            7
#define GRAY            8
#define LIGHTGRAY       9
#define DARKRED         10
#define DARKGREEN       11
#define DARKBLUE        12
#define LIGHTBROWN      13
#define DARKMAGENTA     14
#define DARKCYAN        15
#define NBUTTONS				16

enum fAction {
	LINE_TO, MOVE_TO, POLY_TO
};

enum fAction eDrawAction = POLY_TO;

#endif // !defined(AFX_POLYDRAWCE_H__26A9E7B5_0E0F_11D3_8E70_00C04F72E693__INCLUDED_)
