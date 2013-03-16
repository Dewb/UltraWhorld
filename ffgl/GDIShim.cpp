//
//  GDIShim.cpp
//  UltraWhorldFFGL
//
//  Created by Michael Dewberry on 3/15/13.
//
//

#include "GDIShim.h"
#include <FFGL.h>

int SetROP2(HDC hdc, int fnDrawMode) {
    return 0;
}

COLORREF SetBkColor(HDC hdc, COLORREF color) {
    return RGB(0,0,0);
}

COLORREF SetDCPenColor(HDC hdc, COLORREF color) {
    return RGB(0,0,0);
}

COLORREF SetDCBrushColor(HDC hdc, COLORREF color) {
    return RGB(0,0,0);
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
    glBegin(GL_LINES);
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
        glVertex2i(lppt[ii].x, lppt[ii].y);
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


