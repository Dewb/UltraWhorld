//
//  Win32Shim.h
//  UltraWhorldFFGL
//
//  Created by Michael Dewberry on 3/15/13.
//
//

#ifndef __UltraWhorldFFGL__Win32Shim__
#define __UltraWhorldFFGL__Win32Shim__

#include <vector>
#include <list>
#include <algorithm>

class CView {
    
};

#if defined(_UNICODE)
#define _T(x) wchar_t ##x
typedef wchar_t* LPCTSTR;
#else
#define _T(x) x
typedef char* LPCTSTR;
#endif

typedef int32_t LONG;
typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int BOOL;
typedef int INT;
typedef unsigned int UINT;

typedef DWORD COLORREF;
typedef DWORD* LPCOLORREF;

#define RGB(r, g ,b)  ((DWORD) (((BYTE) (r) | \
((WORD) (g) << 8)) | \
(((DWORD) (BYTE) (b)) << 16)))

#define GetRValue(rgb)   ((BYTE) (rgb)) 
#define GetGValue(rgb)   ((BYTE) (((WORD) (rgb)) >> 8))
#define GetBValue(rgb)   ((BYTE) ((rgb) >> 16))

#define TRUE 1
#define FALSE 0

#define ASSERT(x)
#define MAX_PATH 255

typedef struct tagPOINT {
    LONG x;
    LONG y;
} POINT, *PPOINT;

typedef struct tagRECT {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECT, *LPRECT;

class CPoint : public tagPOINT {
public:
    CPoint() { x = 0; y = 0; }
    CPoint(LONG a, LONG b) { x = a; y = b; }
    
};

struct CRect : public tagRECT {
    CRect() { left = top = right = bottom = 0; }
    CRect(int l, int t, int r, int b) { left = l; top = t; right = r; bottom = b; };
    BOOL SetRectEmpty() { left = 0; top = 0; right = 0; bottom = 0; }
    void OffsetRect(int x, int y) { left += x; right +=x; bottom += y; top += y; }
    int Width() { return right - left; }
    int Height() { return bottom - top; }
    operator LPRECT() { return this; }
};

struct CSize {
    CSize() : cx(0), cy(0) {}
    CSize(LONG x, LONG y) : cx(x), cy(y) {}
    LONG cx;
    LONG cy;
};

#define max fmax
#define min fmin
#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))

/*

#define CLIST_POSITION(T) CList<T,T&>::POSITION
#define CARRAY_POSITON(T) CArray<T,T&>::POSITION
#define NULL_POSITON(CONTAINER) CONTAINER.end()


template<class T, class R>
class CList
{
public:
    typedef typename std::list<T>::iterator POSITION;
    
    int GetCount() const { return _impl.size(); }
    int GetSize() const { return _impl.size(); }
    void RemoveAll() { _impl.clear(); }
    POSITION GetHeadPosition() const { return _impl.begin(); }
    POSITION GetTailPosition() const { return _impl.size() > 0 ? _impl.size() : NULL; }
    R GetNext(POSITION& p) const { ASSERT(p > 0); R ret = _impl[p-1]; p = p < _impl.size() ? p++ : NULL; return ret; }
    R GetPrev(POSITION& p) const { ASSERT(p > 0); R ret = _impl[p-2]; --p; return ret; }
    POSITION AddTail(R arg) { _impl.push_back(arg); return _impl.size(); }
    POSITION AddHead(R arg) { _impl.push_front(arg); return 1; }
    T RemoveTail() { T ret = *(_impl.rbegin()); _impl.pop_back(); return ret; }
    T RemoveHead() { return _impl.pop_front(); }
    void RemoveAt(POSITION p) { auto iter = _impl.begin(); for (int i=1; i<p; i++) { ++iter; } _impl.erase(iter); }
protected:
    std::list<T> _impl;
};

template<class T, class R>
class CArray
{
public:
    typedef typename std::vector<T>::iterator POSITION;
    
    int GetSize() const { return _impl.size(); }
    void RemoveAll() const { _impl.clear(); }
    POSITION GetHeadPosition() const { return _impl.begin(); }
    POSITION GetTailPosition() const { return _impl.rbegin(); }
    R GetNext(POSITION& p) const { ASSERT(p > 0); R ret = _impl[p-1]; p = p < _impl.size() ? p++ : NULL; return ret; }
    R GetPrev(POSITION& p) const { ASSERT(p > 0); R ret = _impl[p-2]; --p; return ret; }
    POSITION Add(R arg) { _impl.push_back(arg); return _impl.size(); }
    void RemoveAt(POSITION p) { auto iter = _impl.begin(); for (int i=1; i<p; i++) { ++iter; } _impl.erase(iter); }
    void SetSize(int newSize, int grow = -1) { _impl.resize(newSize); }
    R operator[] (int n) const { return _impl[n]; }
    void Copy(const CArray<T, R>& src) { std::copy(src._impl.begin(), src._impl.end(), _impl.begin()); }
protected:
    std::vector<T> _impl;
};


class CDWordArray : public CArray<DWORD, DWORD&> {
    
};

*/


#endif /* defined(__UltraWhorldFFGL__Win32Shim__) */
