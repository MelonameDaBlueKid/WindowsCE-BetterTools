//
// How to do Bezier splines (another way) on CE
//
#include "stdafx.h"

#include "CEPolyBezier.h"

typedef struct tagFPOINT
{
	float  x;
	float  y;
} FPOINT, far *LPFPOINT;

// FUNCTION:  GetPointOnCurve(LPFPOINT, float, float, WORD);          
// PARAMS:    LPFPOINT - contains a list of end points and control    
//                 points                                             
//		      float - weighting toward start of points                
//		      float - weighting toward end of points                  
//            WORD - degree of curve								  
// PURPOSE:   Given a list of control points defining a curve of a    
//            specified degree and a weighting, this function will    
//            find the point sits on the curve.                       
void GetPointOnCurve(LPFPOINT lpfptControl, float fStart, float fDest, WORD wDegree)
{
	UINT i;
	
	// Get new points as a function of curent points 
	for (i=0; i<wDegree; i++) {
		lpfptControl[i].x = ((fStart * lpfptControl[i].x) + (fDest * lpfptControl[i+1].x)) / (float)SEGMENTS;
		lpfptControl[i].y = ((fStart * lpfptControl[i].y) + (fDest * lpfptControl[i+1].y)) / (float)SEGMENTS;
	}
  
	if (wDegree == 1) 
		// If we have found the point that sits on the curve 
		return;
	else            
		// Otherwise, recurse for next lower degree with our new curve points 
		GetPointOnCurve(lpfptControl, fStart, fDest, (WORD)(wDegree-1));
}

//  FUNCTION:  CEPolyBezierDegree(HDC, LPPOINT, DWORD, WORD);            
//  PARAMS:    HDC     - handle of device context                	  
// 			  LPPOINT - address of endpoints and control points       	
//             DWORD   - count of endpoints and control points         
//             WORD    - degree of the curve                           
//  PURPOSE:   Calculates a Bezier curve with the specified degree     
BOOL CEPolyBezierDegree(HDC  hdc,LPPOINT lpptControl,DWORD  cPoints,WORD wDegree){
	LPFPOINT lpfptNewControl;
	WORD i, j, iCurves;
	POINT pt[2];
	
	// Check to see if we have enough points for the specified degree 
	if (cPoints > (WORD)(wDegree+2)) {
		if ((cPoints+1) % (wDegree+1)) 
			return FALSE;
	} else
		if (cPoints % (wDegree+1)) 
			return FALSE;
		
		// Allocate floating point (minimize error) array to hold points 
		lpfptNewControl = (LPFPOINT)malloc(sizeof(FPOINT) * (wDegree + 1));
		//Simulates a MoveTo
				pt[0].x = lpptControl[0].x; pt[0].y = lpptControl[0].y;
				// Parse the individual curves out of the array of points 
				for (iCurves=0; iCurves<(cPoints / wDegree); iCurves++) {
					
					// Divide the curve up into segments 
					for (i=0; i<=SEGMENTS; i++) {
						
						// Convert points to floats in order to minimize round-off error 
						for (j=0; j<=wDegree; j++) {
							lpfptNewControl[j].x = (float)lpptControl[iCurves * wDegree + j].x;
							lpfptNewControl[j].y = (float)lpptControl[iCurves * wDegree + j].y;
						}
						
						// Get the point on the curve that cooresponds to this segment 
						GetPointOnCurve(lpfptNewControl, (float)(SEGMENTS-i), (float)i, wDegree);       
						
						// Draw the segment 
						pt[1].x = (long)lpfptNewControl[0].x; pt[1].y = (long)lpfptNewControl[0].y;
						Polyline(hdc, pt, 2);
						pt[0].x = pt[1].x; pt[0].y = pt[1].y; //New MoveTo location
					}     
				}
				free(lpfptNewControl);
				return TRUE;
}

// FUNCTION:  CEPolyBezier(HDC, LPPOINT, DWORD);                     
// PARAMS:    HDC     - handle of device context                	  
// 			  LPPOINT - address of endpoints and control points       	
//             DWORD   - count of endpoints and control points         
//  PURPOSE:   Calculates a Bezier curve of degree 3   
BOOL CEPolyBezier(HDC  hdc,LPPOINT lpptControl,DWORD  cPoints){
	return CEPolyBezierDegree(hdc, lpptControl, cPoints, 3);
}

//  FUNCTION:  CEPolyDraw(HDC, LPPOINT, LPBYTE, int)                   
//  NOTES:     This function is similar to the Windows NT PolyDraw     
//             function, which draws a set of line segments and Bezier 
//             curves.              
BOOL CEPolyDraw(HDC  hdc, CONST LPPOINT lppt,CONST LPBYTE lpbTypes,int  cCount){
	int i;
	static POINT m_ptStart[2];
	POINT m_ptBezier[4];
	memset (m_ptBezier, 0, sizeof(m_ptBezier));
	m_ptBezier[0].x = m_ptStart[0].x; 
	m_ptBezier[0].y = m_ptStart[0].y;
	
	for (i=0; i<cCount; i++){
		switch (lpbTypes[i]) 
		{
		case PT_MOVETO :
			//MoveToEx(hdc, lppt[i].x, lppt[i].y, NULL); //replace
			m_ptStart[0].x = lppt[i].x;
			m_ptStart[0].y = lppt[i].y;
			break;
			
		case PT_LINETO | PT_CLOSEFIGURE:
		case PT_LINETO :
			//LineTo(hdc, lppt[i].x, lppt[i].y); //replace
			m_ptStart[1].x = lppt[i].x;
			m_ptStart[1].y = lppt[i].y;
			Polyline(hdc, m_ptStart, 2);		
			m_ptStart[0].x = m_ptStart[1].x;
			m_ptStart[0].y = m_ptStart[1].y;
			break;
			
		case PT_BEZIERTO | PT_CLOSEFIGURE:
		case PT_BEZIERTO :
			if (cCount < 3)break;
			m_ptStart[0].x = m_ptBezier[1].x = lppt[i].x; // next go round start points
			m_ptStart[0].y = m_ptBezier[1].y = lppt[i].y;
			m_ptBezier[2].x = lppt[i + 1].x; 
			m_ptBezier[2].y = lppt[i + 1].y;
			m_ptBezier[3].x = lppt[i + 2].x; 
			m_ptBezier[3].y = lppt[i + 2].y;
			CEPolyBezier(hdc, m_ptBezier, 4);
			i+=2;
			break;
		}
	}
	return TRUE;	 
} 
