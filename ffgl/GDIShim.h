//
//  GDIShim.h
//  UltraWhorldFFGL
//
//  Created by Michael Dewberry on 3/15/13.
//
//

#ifndef __UltraWhorldFFGL__GDIShim__
#define __UltraWhorldFFGL__GDIShim__

#include "Win32Shim.h"

typedef uint32_t HDC;
typedef void* HGDIOBJ;

enum {
    DC_BRUSH,
    NULL_PEN,
    R2_XORPEN,
    R2_COPYPEN,
    PS_SOLID,
    DC_PEN,
    ETO_OPAQUE,
};

int SetROP2(HDC hdc, int fnDrawMode);

COLORREF SetBkColor(HDC hdc, COLORREF color);
COLORREF SetDCPenColor(HDC hdc, COLORREF color);
COLORREF SetDCBrushColor(HDC hdc, COLORREF color);
HGDIOBJ SelectObject(HDC hdc, HGDIOBJ object);
HGDIOBJ GetStockObject(int fnObject);

BOOL BeginPath(HDC hdc);
BOOL EndPath(HDC hdc);
BOOL StrokePath(HDC dc);
BOOL StrokeAndFillPath(HDC hdc);
BOOL PolyPolygon(HDC hdc, const POINT* lpPoints, const int* lpPolyCounts, int nCount);
BOOL Polygon(HDC hdc, const POINT* lpPoints, int nCount);
BOOL PolyBezier(HDC hdc, const POINT* lppt, DWORD cPoints);
BOOL Polyline(HDC hdc, const POINT* lppt, DWORD cPoints);
BOOL ExtTextOut(HDC hdc, int X, int Y, UINT fuOptions, const RECT *lprc,
                LPCTSTR lpString, UINT cbCount, const INT *lpDx);

class CGdiObject {
public:
    CGdiObject() : _handle(0) {}
    BOOL DeleteObject();
    operator HGDIOBJ() { return _handle; }
protected:
    HGDIOBJ _handle;
};

class CPen : public CGdiObject {
public:
    HGDIOBJ CreatePen(int nPenStyle, int nWidth, COLORREF crColor);
};

void GDIShim_BeginFrame(int renderHeight, int renderWidth);
void GDIShim_EndFrame();

#endif /* defined(__UltraWhorldFFGL__GDIShim__) */
