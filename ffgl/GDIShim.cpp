//
//  GDIShim.cpp
//  UltraWhorldFFGL
//
//  Created by Michael Dewberry on 3/15/13.
//
//

#include "GDIShim.h"
#include "FFGL.h"

#include "nanovg.h"
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg_gl.h"

#include <functional>

#define CanvasX2GL(x) x/(1.0*CANVAS_WIDTH) - 0.5
#define CanvasY2GL(y) y/(1.0*CANVAS_HEIGHT) - 0.5
#define CanvasPenWidth2GL(p) p * CANVAS_WIDTH

#define MAX_GDI_HANDLES 256

typedef std::function<void(void)> SelectionFunc;

class GdiImpl {
public:
    static COLORREF bkColor;
    static COLORREF dcPenColor;
    static COLORREF dcBrushColor;

    GdiImpl() {
        handles.resize(MAX_GDI_HANDLES, nullptr);

        vg = nullptr;

        // DC_PEN
        createNewObject([this]{

            NVGcolor color = nvgRGB(GetRValue(GdiImpl::dcPenColor),
                                    GetGValue(GdiImpl::dcPenColor),
                                    GetBValue(GdiImpl::dcPenColor));
            nvgStrokeColor(vg, color);
            nvgStrokeWidth(vg, 1.0);
        });

        // DC_BRUSH
        createNewObject([this]{

            NVGcolor color = nvgRGB(GetRValue(GdiImpl::dcBrushColor),
                                    GetGValue(GdiImpl::dcBrushColor),
                                    GetBValue(GdiImpl::dcBrushColor));
            nvgFillColor(vg, color);
        });

        // NULL_PEN
        createNewObject([this]{
            NVGcolor color = nvgRGBA(0, 0, 0, 0);
            nvgStrokeColor(vg, color);
        });


    }
    
    HGDIOBJ createNewObject(SelectionFunc fn) {
        for (int i = 0; i < MAX_GDI_HANDLES; i++) {
            if (handles[i] == nullptr) {
                handles[i] = fn;
                return (HGDIOBJ)(i+1);
            }
        }
        return nullptr;
    }
    
    void deleteObject(HGDIOBJ obj) {
        if (obj != nullptr) {
            handles[((size_t)obj)-1] = nullptr;
        }
    }
    
    void selectObject(HGDIOBJ obj) {
        if (obj != nullptr && (size_t)obj >= 1 && (size_t)obj <= MAX_GDI_HANDLES) {
            SelectionFunc fn = handles[((size_t)obj)-1];
            if (fn) {
                fn();
            }
        }
    }

    struct NVGcontext* vg;
protected:
    std::vector<SelectionFunc> handles;

};

COLORREF GdiImpl::bkColor = 0x000000;
COLORREF GdiImpl::dcPenColor = 0xFFFFFF;
COLORREF GdiImpl::dcBrushColor = 0xC0C0C0;

GdiImpl gdi;


void GDIShim_BeginFrame(int framebufferWidth, int framebufferHeight) {
    if (!gdi.vg) {
        gdi.vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
    }
    nvgBeginFrame(gdi.vg, CANVAS_WIDTH, CANVAS_HEIGHT, framebufferHeight/(1.0*CANVAS_HEIGHT));
}

void GDIShim_EndFrame() {
    nvgEndFrame(gdi.vg);
}

int SetROP2(HDC hdc, int fnDrawMode) {
    if (fnDrawMode == R2_COPYPEN) {
        nvgGlobalCompositeOperation(gdi.vg, NVG_DESTINATION_OVER);
    } else if (fnDrawMode == R2_XORPEN) {
        nvgGlobalCompositeOperation(gdi.vg, NVG_XOR);
    }
    return 0;
}

COLORREF SetBkColor(HDC hdc, COLORREF color) {
    COLORREF oldColor = GdiImpl::bkColor;
    GdiImpl::bkColor = color;
    return oldColor;
}

COLORREF SetDCPenColor(HDC hdc, COLORREF color) {
    COLORREF oldColor = GdiImpl::dcPenColor;
    GdiImpl::dcPenColor = color;
    return oldColor;
}

COLORREF SetDCBrushColor(HDC hdc, COLORREF color) {
    COLORREF oldColor = GdiImpl::dcBrushColor;
    GdiImpl::dcBrushColor = color;
    return oldColor;
}

HGDIOBJ SelectObject(HDC hdc, HGDIOBJ object) {
    gdi.selectObject(object);
    return nullptr; // Should return old selected object of same type, but Whorld never uses this
}

HGDIOBJ GetStockObject(int fnObject) {
    if (fnObject == DC_PEN) {
        return (HGDIOBJ)1;
    } else if (fnObject == DC_BRUSH) {
        return (HGDIOBJ)2;
    } else if (fnObject == NULL_PEN) {
        return (HGDIOBJ)3;
    } else {
        return nullptr;
    }
}

BOOL BeginPath(HDC hdc) {
    nvgBeginPath(gdi.vg);
    return TRUE;
}

BOOL EndPath(HDC hdc) {
    return TRUE;
}

BOOL StrokePath(HDC dc) {
    nvgStroke(gdi.vg);
    return TRUE;
}

BOOL StrokeAndFillPath(HDC hdc) {
    nvgStroke(gdi.vg);
    nvgFill(gdi.vg);
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
    for(int ii=0; ii < nCount; ii++) {
        nvgLineTo(gdi.vg, lpPoints[ii].x, lpPoints[ii].y);
    }
    nvgClosePath(gdi.vg);
    return TRUE;
}

BOOL PolyBezier(HDC hdc, const POINT* lppt, DWORD cPoints) {
    nvgMoveTo(gdi.vg, lppt[0].x, lppt[0].y);
    for (int i = 1; i < cPoints-2; i += 3) {
        nvgBezierTo(gdi.vg, lppt[i].x, lppt[i].y, lppt[i+1].x, lppt[i+1].y, lppt[i+2].x, lppt[i+2].y);
    }
    return TRUE;
}

BOOL Polyline(HDC hdc, const POINT* lppt, DWORD cPoints) {
    nvgMoveTo(gdi.vg, lppt[0].x, lppt[0].y);
    for(int ii = 1; ii < cPoints; ii++) {
        nvgLineTo(gdi.vg, lppt[ii].x, lppt[ii].y);
    }
    return TRUE;
}

BOOL ExtTextOut(HDC hdc, int X, int Y, UINT fuOptions, const RECT *lprc,
                LPCTSTR lpString, UINT cbCount, const INT *lpDx) {
    return TRUE;
}

BOOL CGdiObject::DeleteObject() {
    gdi.deleteObject(_handle);
    return TRUE;
}

HGDIOBJ CPen::CreatePen(int nPenStyle, int nWidth, COLORREF crColor) {
    if (_handle) {
        gdi.deleteObject(_handle);
    }
    _handle = gdi.createNewObject([=] () {
        NVGcolor color = nvgRGB(GetRValue(crColor),
                                GetGValue(crColor),
                                GetBValue(crColor));
        nvgStrokeColor(gdi.vg, color);
        nvgStrokeWidth(gdi.vg, nWidth);
    });
    return _handle;
}


