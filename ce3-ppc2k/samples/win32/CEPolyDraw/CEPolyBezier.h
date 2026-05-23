//
// How to do Bezier splines (another way) on CE
//

#define SEGMENTS 64 //number of segments in line to compute

#ifndef PT_CLOSEFIGURE
#define PT_CLOSEFIGURE      0x01
#define PT_LINETO           0x02
#define PT_BEZIERTO         0x04
#define PT_MOVETO           0x06
#endif

BOOL CEPolyBezierDegree(HDC, LPPOINT, DWORD, WORD);
BOOL CEPolyBezier(HDC, LPPOINT, DWORD);
BOOL CEPolyDraw(HDC, CONST LPPOINT, CONST LPBYTE, int);
