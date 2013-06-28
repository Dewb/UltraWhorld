//
//  GDIShim.cpp
//  UltraWhorldFFGL
//
//  Created by Michael Dewberry on 3/15/13.
//
//

#include "GDIShim.h"
#include <FFGL.h>
#include <functional>

// keep these in sync with MainFrm.h definitions (or pull out into proper header)
#define CANVAS_WIDTH 2048
#define CANVAS_HEIGHT 2048

#define CanvasX2GL(x) x/(1.0*CANVAS_WIDTH) - 0.5
#define CanvasY2GL(y) y/(1.0*CANVAS_HEIGHT) - 0.5
#define CanvasPenWidth2GL(p) p/(1.0*CANVAS_WIDTH) * 400.0

#define MAX_GDI_HANDLES 256

typedef std::function<void(void)> SelectionFunc;

class GdiImpl {
public:
    static COLORREF bkColor;
    static COLORREF dcPenColor;
    static COLORREF dcBrushColor;

    GdiImpl() {
        handles.resize(MAX_GDI_HANDLES, nullptr);
        
        // DC_PEN
        createNewObject([]{
            glLineWidth(CanvasPenWidth2GL(1.0));
            glColor3ub(GetRValue(GdiImpl::dcPenColor),
                       GetGValue(GdiImpl::dcPenColor),
                       GetBValue(GdiImpl::dcPenColor));
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
            handles[((int)obj)-1] = nullptr;
        }
    }
    
    void selectObject(HGDIOBJ obj) {
        if (obj != nullptr) {
            SelectionFunc fn = handles[((int)obj)-1];
            if (fn) {
                fn();
            }
        }
    }
        
protected:
    std::vector<SelectionFunc> handles;
};

COLORREF GdiImpl::bkColor = 0;
COLORREF GdiImpl::dcPenColor = 0;
COLORREF GdiImpl::dcBrushColor = 0;

GdiImpl gdi;

int SetROP2(HDC hdc, int fnDrawMode) {
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
    } else {
        return nullptr;
    }
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

#define BEZIER_SUBDIVISIONS 40

BOOL PolyBezier(HDC hdc, const POINT* lppt, DWORD cPoints) {
    GLfloat bezierBuffer[4*3];
    glEnable(GL_MAP1_VERTEX_3);
    for (int i = 0; i < cPoints-2; i += 3) {
        for (int p = 0; p < 4; p++) {
            bezierBuffer[3 * p + 0] = CanvasX2GL(lppt[i + p].x);
            bezierBuffer[3 * p + 1] = CanvasY2GL(lppt[i + p].y);
            bezierBuffer[3 * p + 2] = 0.0;
        }
        
        glMap1f(GL_MAP1_VERTEX_3, 0.0, BEZIER_SUBDIVISIONS, 3, 4, bezierBuffer);
        glBegin(GL_LINE_STRIP);
        for (int t = 0; t <= BEZIER_SUBDIVISIONS; t++) {
            glEvalCoord1f((GLfloat)t);
        }
        glEnd();
    }
    return TRUE;
}

BOOL Polyline(HDC hdc, const POINT* lppt, DWORD cPoints) {
    glBegin(GL_LINE_STRIP);
    for(int ii = 0; ii < cPoints; ii++) {
        glVertex3f(CanvasX2GL(lppt[ii].x),
                   CanvasY2GL(lppt[ii].y),
                   0);
    }
    glEnd();
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
        glLineWidth(CanvasPenWidth2GL(nWidth));
        glColor3ub(GetRValue(crColor),
                   GetGValue(crColor),
                   GetBValue(crColor));
    });
    return _handle;
}


