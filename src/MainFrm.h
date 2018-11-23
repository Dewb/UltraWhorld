// Copyleft 2006 Chris Korda
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.
/*
        chris korda
 
		revision history:
		rev		date	comments
        00      19apr06	initial version
		01		25apr06	add RotateHue
        02      30dec06	support 16-bit mode
        03      25jul07	add more parameters
		04		31jan08	add shear, and global parameters

		whorld freeframe server
 
*/

#ifndef CMAINFRAME_INCLUDED
#define CMAINFRAME_INCLUDED

//#include "FreeFrame.h"
#include "Patch.h"
#include "WhorldView.h"
//#include "SortStringArray.h"
#include "NormVal.h"
//#include "RealTimer.h"
#include "Win32Shim.h"

#include <vector>


struct VideoInfoStructTag;

class CMainFrame {
public:
// Construction
	CMainFrame();
	~CMainFrame();
	bool	Init(const VideoInfoStructTag& videoInfo);

// Constants
	enum {	// origin motion types
		OM_PARK,	// no motion
		OM_DRAG,	// cursor drag mode
		OM_RANDOM	// random jump mode
	};
	enum {	// patch change modes
		PM_FULL,	// affects all settings
		PM_GEOMETRY	// affects geometry only
	};

// Types
	typedef struct tagINFO {	// persistent information including components
		CCrossDlg::INFO		XFader;		// crossfader dialog info
		CPlaylistDlg::INFO	Playlist;	// playlist dialog info
		CVideoList::INFO	VideoList;	// video list info
		//CPatch	Patch;		// master patch
		CParmInfo	GlobParm;	// global parameters
		int		ViewSel;	// view selection: document or mix
		int		EditSel;	// edit selection: document, A, B, mix, master offsets
		int		PatchMode;	// patch change mode; see enum above
	} INFO;

// Attributes
	int		GetWidth() const;
	int		GetHeight() const;
	int		GetPatchCount() const;
	int		GetCurPatch() const;
	bool	SetCurPatch(int PatchIdx);
	bool	SetCurPatchNorm(double Val);
	int		GetCurBank() const;
	bool	SetCurBank(int BankIdx);
	bool	SetCurBankNorm(double Val);
	void	SetSpeed(double Speed);
	double	GetSpeed() const;
	void	SetSpeedNorm(double Speed);
	double	GetSpeedNorm() const;
	void	SetZoom(double Zoom);
	double	GetZoom() const;
	void	SetZoomNorm(double Zoom);
	double	GetZoomNorm() const;
	void	SetTargetZoomNorm(double Zoom);
	double	GetTargetZoomNorm() const;
	void	SetDamping(double Damping);
	double	GetDamping() const;
	void	SetDampingNorm(double Damping);
	double	GetDampingNorm() const;
	void	SetTrail(double Trail);
	double	GetTrail() const;
	void	SetTrailNorm(double Trail);
	double	GetTrailNorm() const;
	void	SetRings(double Rings);
	double	GetRings() const;
	void	SetRingsNorm(double Rings);
	double	GetRingsNorm() const;
	void	SetTempo(double Tempo);
	double	GetTempo() const;
	void	SetTempoNorm(double Tempo);
	double	GetTempoNorm() const;
	void	SetHueLoopLength(double HueLoopLength);
	double	GetHueLoopLength() const;
	void	SetHueLoopLengthNorm(double HueLoopLength);
	double	GetHueLoopLengthNorm() const;
	void	SetCanvasScale(double CanvasScale);
	double	GetCanvasScale() const;
	void	SetCanvasScaleNorm(double CanvasScale);
	double	GetCanvasScaleNorm() const;
	void	SetCopies(int Copies);
	int		GetCopies() const;
	void	SetCopiesNorm(double Copies);
	double	GetCopiesNorm() const;
	void	SetSpread(int Spread);
	int		GetSpread() const;
	void	SetSpreadNorm(double Spread);
	double	GetSpreadNorm() const;
	void	SetHue(double Hue);
	double	GetHue() const;
	void	SetHueNorm(double Hue);
	double	GetHueNorm() const;
	void	SetGlobalHue(double Hue);
	void	SetGlobalHueNorm(double Hue);
	void	RotateHue(double Rot);
	void	RotateHueNorm(double Rot);
	void	SetDrawMode(int Mode);
	void	SetDrawMode(int Mask, bool Value);
	int		GetDrawMode() const;
	void	SetOrgMotion(int Motion);
	int		GetOrgMotion() const;
	void	Mirror(bool Enable);
	bool	IsMirrored() const;
	void	LoopHue(bool Enable);
	bool	IsHueLooped() const;
	void	InvertColor(bool Enable);
	bool	IsColorInverted() const;
	void	SetReverse(bool Enable);
	bool	GetReverse() const;
	void	SetConvex(bool Enable);
	bool	GetConvex() const;
	void	SetZoomCenter(bool Enable);
	bool	GetZoomCenter() const;
	void	SetOriginNorm(const DPOINT& Origin);
	void	GetOriginNorm(DPOINT& Origin) const;
	void	SetTargetOriginNorm(const DPOINT& Origin);
	void	GetTargetOriginNorm(DPOINT& Origin) const;
	double	GetMasterOffset(int ParmIdx) const;
	void	SetMasterOffset(int ParmIdx, double Val);
	void	SetMasterOffsetNorm(int ParmIdx, double Val, double MaxVal);
	void	SetPatchMode(int Mode);
	static	int		ParmToEnum(double Val, int Enums);
	static	double	EnumToParm(int Val, int Enums);
	void	SetGlobalParm(int ParmIdx, double Val);
	void	SetGlobalParmNorm(int ParmIdx, double Val);

// Operations
	DWORD	processFrame(LPVOID pFrame);
	void	ClearScreen();
	void	RandomPhase();
	void	SetPatch(const CPatch& Patch);
    void	GetPatch(CPatch& Patch) const;
	//bool	SavePatch() const;
	//bool	SavePatch(LPCSTR Path) const;

protected:
// Types
	enum {
		BANKS = 20
	};
//	typedef	CArray<CPatch, CPatch&>	PATCH_LIST[BANKS];
    typedef std::vector<CPatch> PATCH_LIST[BANKS];
    
//	typedef struct tagMYBITMAPINFO : BITMAPINFO {
//		// The bmiColors array allocates a single DWORD, but in 16-bit mode,
//		// bmiColors needs to contain three DWORDs: one DWORD each for the red,
//		// green and blue color masks.  So we inherit from BITMAPINFO and add 
//		// space for the green and blue masks; the red mask is bmiColors[0].
//		DWORD	GreenMask;
//		DWORD	BlueMask;
//	} MYBITMAPINFO;

// Constants
	static const CNormVal		m_NormZoom;
	static const CNormVal		m_NormSpeed;
	static const CPosNormVal	m_NormDamping;
	static const CPosNormVal	m_NormTrail;
	static const CPosNormVal	m_NormRings;
	static const CNormVal		m_NormTempo;
	static const CNormVal		m_NormHueLoop;
	static const CNormVal		m_NormCanvas;
	static const CNormVal		m_NormHue;
	static const CNormVal		m_NormSpread;
	enum {
		PARM_ROWS = CParmInfo::ROWS,
		GLOBAL_PARMS = CParmInfo::GLOBAL_PARMS
	};

// Member data
	//VideoInfoStruct	m_VideoInfo;	// copy of video info passed to Init
	CWhorldView	m_View;			// our view instance
	PATCH_LIST	m_Patch;		// array of patches, in same order as m_PatchPath
	CParmInfo	m_ParmInfo;		// current view parameters
	CParmInfo	m_MastInfo;		// oscillator overrides
	//CRealTimer	m_TempoTimer;	// self-correcting timer based on performance counter
	//MYBITMAPINFO	m_bmi;		// frame DIB info
	//HDC		m_hDC;				// frame DIB device context
	//HBITMAP	m_hDib;				// frame DIB handle
	//void	*m_DibBits;			// frame DIB data
	//HGDIOBJ	m_PrevBm;			// DC's previous bitmap
	LONG	m_FrameBytes;		// size of frame in bytes
	LONG	m_BytesPerPixel;	// number of bytes per pixel
	int		m_FrameRate;		// frame rate in frames per second
	int		m_BankIdx;			// index of currently selected bank
	int		m_PatchIdx;			// index of currently selected patch
	int		m_Banks;			// number of banks in use; excludes trailing empties
	double	m_Speed;			// normalized speed: 0 = nominal, 1 = max, -1 = min
	double	m_Zoom;				// normalized zoom: 0 = nominal, 1 = max, -1 = min
	double	m_TargetZoom;		// zoom target value; may differ from m_Zoom when damped
	double	m_Damping;			// damping for origin motion and zoom; 1 = none, 0 = max
	double	m_Rings;			// maximum number of rings
	double	m_Tempo;			// tempo in beats per minute
	DPoint	m_TargetOrg;		// target origin, in normalized coordinates
	int		m_GrowDir;			// ring growth direction: 1 = outward, -1 = inward
	int		m_OrgMotion;		// origin motion; see enum above
	volatile UINT	m_Clock;	// CRealTimer thread's callback increments this
	UINT	m_PrevClock;		// previous value of m_Clock, for detecting change
	double	m_PrevHue;			// previous hue: 360 degrees mapped to 0..1
	double	m_MastOfs[PARM_ROWS];	// master offsets for geometry parameters
	int		m_PatchMode;		// patch change mode; see enum above
	//CString	m_DocFolder;		// path to folder containing playlist/patches
	CParmInfo	m_GlobParm;		// global parameter info
	COscillator	m_GlobOsc[PARM_ROWS];	// global oscillators
	double	m_GlobParmTarg[PARM_ROWS];	// global parameter targets

// Helpers
//	bool	LoadPatches();
//	bool	LoadPlaylist();
//	bool	LoadPlaylist(LPCSTR Path);
//	bool	ReadIniFile();
//	static	bool	GetDocFolder(CString& Folder);
//	static	void	TimerCallback(LPVOID Cookie);
//	static	void	Mirror24(LPVOID pFrame, int w, int h);
//	static	void	Mirror32(LPVOID pFrame, int w, int h);
//	static	void	Mirror16(LPVOID pFrame, int w, int h);
//	static	bool	MakeUniquePath(LPCSTR Folder, LPCSTR Prefix, LPCSTR Extension, CString& Path);
};

inline int CMainFrame::ParmToEnum(double Val, int Enums)
{
	int ival = trunc(Val * Enums);
	return(min(ival, Enums - 1));
}

inline double CMainFrame::EnumToParm(int Val, int Enums)
{
	return((Val + .5) / Enums);
}

inline int CMainFrame::GetWidth() const
{
	//return(m_VideoInfo.frameWidth);
    return CANVAS_WIDTH;
}

inline int CMainFrame::GetHeight() const
{
	//return(m_VideoInfo.frameHeight);
    return CANVAS_HEIGHT;
}

inline int CMainFrame::GetPatchCount() const
{
	return(m_Patch[m_BankIdx].size());
}

inline int CMainFrame::GetCurPatch() const
{
	return(m_PatchIdx);
}

inline bool CMainFrame::SetCurPatchNorm(double Val)
{
	return(SetCurPatch(ParmToEnum(Val, GetPatchCount())));
}

inline int CMainFrame::GetCurBank() const
{
	return(m_BankIdx);
}

inline bool CMainFrame::SetCurBankNorm(double Val)
{
	return(SetCurBank(ParmToEnum(Val, m_Banks)));
}

inline void CMainFrame::SetSpeed(double Speed)
{
	m_Speed = Speed;
}

inline double CMainFrame::GetSpeed() const
{
	return(m_Speed);
}

inline void CMainFrame::SetSpeedNorm(double Speed)
{
	SetSpeed(m_NormSpeed.Denorm(Speed));
}

inline double CMainFrame::GetSpeedNorm() const
{
	return(m_NormSpeed.Norm(GetSpeed()));
}

inline double CMainFrame::GetZoom() const
{
	return(m_NormZoom.Denorm(m_Zoom));
}

inline double CMainFrame::GetZoomNorm() const
{
	return(m_Zoom);
}

inline void CMainFrame::SetTargetZoomNorm(double Zoom)
{
	m_TargetZoom = Zoom;
}

inline double CMainFrame::GetTargetZoomNorm() const
{
	return(m_TargetZoom);
}

inline void CMainFrame::SetDamping(double Damping)
{
	m_Damping = Damping;
}

inline double CMainFrame::GetDamping() const
{
	return(m_Damping);
}

inline void CMainFrame::SetDampingNorm(double Damping)
{
	SetDamping(m_NormDamping.Denorm(m_NormDamping.GetScale() - Damping));
}

inline double CMainFrame::GetDampingNorm() const
{
	return(m_NormDamping.GetScale() - m_NormDamping.Norm(GetDamping()));
}

inline void CMainFrame::SetTrail(double Trail)
{
	m_View.SetTrail(Trail);
}

inline double CMainFrame::GetTrail() const
{
	return(m_View.GetTrail());
}

inline void CMainFrame::SetTrailNorm(double Trail)
{
	SetTrail(m_NormTrail.Denorm(Trail));
}

inline double CMainFrame::GetTrailNorm() const
{
	return(m_NormTrail.Norm(GetTrail()));
}

inline double CMainFrame::GetRings() const
{
	return(m_Rings);
}

inline void CMainFrame::SetRingsNorm(double Rings)
{
	SetRings(m_NormRings.Denorm(Rings) * CPatch::MAX_RINGS);
}

inline double CMainFrame::GetRingsNorm() const
{
	return(m_NormRings.Norm(GetRings() / CPatch::MAX_RINGS));
}

inline double CMainFrame::GetTempo() const
{
	return(m_Tempo);
}

inline void CMainFrame::SetTempoNorm(double Tempo)
{
	SetTempo(m_NormTempo.Denorm(Tempo));
}

inline double CMainFrame::GetTempoNorm() const
{
	return(m_NormTempo.Norm(GetTempo()));
}

inline void CMainFrame::SetHueLoopLength(double HueLoopLength)
{
	m_View.SetHueLoopLength(HueLoopLength);
}

inline double CMainFrame::GetHueLoopLength() const
{
	return(m_View.GetHueLoopLength());
}

inline void CMainFrame::SetHueLoopLengthNorm(double HueLoopLength)
{
	SetHueLoopLength(m_NormHueLoop.Denorm(HueLoopLength));
}

inline double CMainFrame::GetHueLoopLengthNorm() const
{
	return(m_NormHueLoop.Norm(GetHueLoopLength()));
}

inline void CMainFrame::SetCanvasScale(double CanvasScale)
{
	m_View.SetCanvasScale(CanvasScale);
}

inline double CMainFrame::GetCanvasScale() const
{
	return(m_View.GetCanvasScale());
}

inline void CMainFrame::SetCanvasScaleNorm(double CanvasScale)
{
	SetCanvasScale(m_NormCanvas.Denorm(CanvasScale) + 1);
}

inline double CMainFrame::GetCanvasScaleNorm() const
{
	return(m_NormCanvas.Norm(GetCanvasScale() - 1));
}

inline void CMainFrame::SetCopies(int Copies)
{
	m_View.SetCopyCount(Copies);
}

inline int CMainFrame::GetCopies() const
{
	return(m_View.GetCopyCount());
}

inline void CMainFrame::SetCopiesNorm(double Copies)
{
	SetCopies(ParmToEnum(Copies, 20) + 1);
}

inline double CMainFrame::GetCopiesNorm() const
{
	return(EnumToParm(GetCopies() - 1, 20));
}

inline void CMainFrame::SetSpread(int Spread)
{
	m_View.SetCopySpread(Spread);
}

inline int CMainFrame::GetSpread() const
{
	return(m_View.GetCopySpread());
}

inline void CMainFrame::SetSpreadNorm(double Spread)
{
	SetSpread(round(m_NormSpread.Denorm(Spread)));
}

inline double CMainFrame::GetSpreadNorm() const
{
	return(m_NormSpread.Norm(GetSpread()));
}

inline void CMainFrame::SetHue(double Hue)
{
	m_View.SetHue(Hue);
}

inline double CMainFrame::GetHue() const
{
	return(m_View.GetHue());
}

inline void CMainFrame::SetHueNorm(double Hue)
{
	SetHue(m_NormHue.Denorm(Hue));
}

inline double CMainFrame::GetHueNorm() const
{
	return(m_NormHue.Norm(GetHue()));
}

inline void CMainFrame::SetGlobalHueNorm(double Hue)
{
	SetGlobalHue(m_NormHue.Denorm(Hue));
}

inline void CMainFrame::RotateHueNorm(double Rot)
{
	RotateHue(m_NormHue.Denorm(Rot));
}

inline void CMainFrame::RotateHue(double Rot)
{
	m_View.RotateHue(Rot);
}

inline void CMainFrame::SetDrawMode(int Mode)
{
	m_View.SetDrawMode(Mode);
}

inline void CMainFrame::SetDrawMode(int Mask, bool Value)
{
	SetDrawMode((GetDrawMode() & ~Mask) | (Value ? Mask : 0));
}

inline int CMainFrame::GetDrawMode() const
{
	return(m_View.GetDrawMode());
}

inline void CMainFrame::SetOrgMotion(int Motion)
{
	m_OrgMotion = Motion;
}

inline int CMainFrame::GetOrgMotion() const
{
	return(m_OrgMotion);
}

inline void CMainFrame::Mirror(bool Enable)
{
	m_View.Mirror(Enable);
}

inline bool CMainFrame::IsMirrored() const
{
	return(m_View.IsMirrored());
}

inline void CMainFrame::LoopHue(bool Enable)
{
	m_View.LoopHue(Enable);
}

inline bool	CMainFrame::IsHueLooped() const
{
	return(m_View.IsHueLooped());
}

inline void CMainFrame::InvertColor(bool Enable)
{
	m_View.InvertColor(Enable);
}

inline bool CMainFrame::IsColorInverted() const
{
	return(m_View.IsColorInverted());
}

inline void CMainFrame::SetConvex(bool Enable)
{
	m_View.SetConvex(Enable);
}

inline bool CMainFrame::GetReverse() const
{
	return(m_GrowDir < 0);
}

inline bool CMainFrame::GetConvex() const
{
	return(m_View.GetConvex());
}

inline bool CMainFrame::GetZoomCenter() const
{
	return(m_View.GetZoomType() == CWhorldView::ZT_WND_CENTER);
}

inline void CMainFrame::GetOriginNorm(DPOINT& Origin) const
{
	m_View.GetNormOrigin(Origin);
}

inline void CMainFrame::SetTargetOriginNorm(const DPOINT& Origin)
{
	m_TargetOrg = Origin;
}

inline void CMainFrame::GetTargetOriginNorm(DPOINT& Origin) const
{
	Origin = m_TargetOrg;
}

inline void CMainFrame::SetPatchMode(int Mode)
{
	m_PatchMode = Mode;
}

inline double CMainFrame::GetMasterOffset(int ParmIdx) const
{
	return(m_MastOfs[ParmIdx]);
}

inline void CMainFrame::SetMasterOffset(int ParmIdx, double Val)
{
	m_MastOfs[ParmIdx] = Val;
}

inline void CMainFrame::SetMasterOffsetNorm(int ParmIdx, double Val, double MaxVal)
{
	SetMasterOffset(ParmIdx, ((Val * 2) - 1) * MaxVal);
}

inline void CMainFrame::ClearScreen()
{
	m_View.ClearScreen();
}

inline void CMainFrame::SetGlobalParm(int ParmIdx, double Val)
{
	m_GlobParmTarg[ParmIdx] = Val;
}

inline void CMainFrame::SetGlobalParmNorm(int ParmIdx, double Val)
{
	SetGlobalParm(ParmIdx, ((Val * 2) - 1) * CParmInfo::m_RowData[ParmIdx].MaxVal);
}

#endif
