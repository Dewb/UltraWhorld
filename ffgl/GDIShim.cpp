//
//  GDIShim.cpp
//  UltraWhorldFFGL
//
//  Created by Michael Dewberry on 3/15/13.
//
//

#include "GDIShim.h"
#include <FFGL.h>

// keep these in sync with MainFrm.h definitions (or pull out into proper header)
#define CANVAS_WIDTH 2048
#define CANVAS_HEIGHT 2048

#define CanvasX2GL(x) x/(1.0*CANVAS_WIDTH) - 0.5
#define CanvasY2GL(y) y/(1.0*CANVAS_HEIGHT) - 0.5


int SetROP2(HDC hdc, int fnDrawMode) {
    return 0;
}

COLORREF SetBkColor(HDC hdc, COLORREF color) {
    glClearColor(GetRValue(color) / 255.0, GetGValue(color) / 255.0, GetBValue(color) / 255.0, 1.0);
    return color;
}

COLORREF SetDCPenColor(HDC hdc, COLORREF color) {
    glColor3ub(GetRValue(color), GetGValue(color), GetBValue(color));
    return color;
}

COLORREF SetDCBrushColor(HDC hdc, COLORREF color) {
    glColor3ub(GetRValue(color), GetGValue(color), GetBValue(color));
    return color;
}

HGDIOBJ SelectObject(HDC hdc, HGDIOBJ object) {
    return NULL;
}

HGDIOBJ GetStockObject(int fnObject) {
    return NULL;
}

BOOL BeginPath(HDC hdc) {
    return TRUE;
}

BOOL EndPath(HDC hdc) {
    return TRUE;
}

BOOL StrokeAndFillPath(HDC hdc) {
    return TRUE;
}

BOOL PolyPolygon(HDC hdc, const POINT* lpPoints, const int* lpPolyCounts, int nCount) {
    BOOL bRet = TRUE;
    int pointCount = 0;
    for(int ii=0; ii < nCount; ii++) {
        int c = lpPolyCounts[ii];
        bRet &= Polygon(hdc, lpPoints+pointCount, c);
        pointCount += c;
    }
}

BOOL Polygon(HDC hdc, const POINT* lpPoints, int nCount) {
    glBegin(GL_LINE_LOOP);
    for(int ii=0; ii < nCount; ii++) {
        glVertex2i(lpPoints[ii].x, lpPoints[ii].y);
    }
    glVertex2i(lpPoints[0].x, lpPoints[0].y);
    glEnd();
    return TRUE;
}

BOOL PolyBezier(HDC hdc, const POINT* lppt, DWORD cPoints) {
    return Polyline(hdc, lppt, cPoints);
}

BOOL Polyline(HDC hdc, const POINT* lppt, DWORD cPoints) {
    glBegin(GL_LINES);
    for(int ii=0; ii < cPoints; ii++) {
        glVertex2f(CanvasX2GL(lppt[ii].x),
                   CanvasY2GL(lppt[ii].y));
    }
    glEnd();
    return TRUE;
}

BOOL ExtTextOut(HDC hdc, int X, int Y, UINT fuOptions, const RECT *lprc,
                LPCTSTR lpString, UINT cbCount, const INT *lpDx) {
    return TRUE;
}

BOOL CGdiObject::DeleteObject() {
    return TRUE;
}

HGDIOBJ CPen::CreatePen(int nPenStyle, int nWidth, COLORREF crColor) {
    return NULL;
}


