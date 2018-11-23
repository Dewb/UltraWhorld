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
		02		02oct06	add Copies and Spread
        03      30dec06	support 16-bit mode
		04		30dec06	make top-down DIB conditional
        05      25jul07	add more parameters
		06		31jan08	add shear, and global parameters

		whorld freeframe server
 
*/

#include "stdafx.h"
#include "FFGLPluginSDK.h"
//#include "FreeFrame.h"
#include "MainFrm.h"
//#include "PathStr.h"
#include <math.h>
//#include "Playlist.h"

//												Offset	Scale	LogBase
const CNormVal		CMainFrame::m_NormSpeed(	.5,		2,		20);
const CNormVal		CMainFrame::m_NormZoom(		.5,		2,		10);
const CPosNormVal	CMainFrame::m_NormDamping(	0,		1.01,	20);
const CPosNormVal	CMainFrame::m_NormTrail(	0,		1,		10);
const CPosNormVal	CMainFrame::m_NormRings(	0,		1,		30);
const CNormVal		CMainFrame::m_NormTempo(	0,		250,	0);
const CNormVal		CMainFrame::m_NormHueLoop(	0,		360,	0);
const CNormVal		CMainFrame::m_NormCanvas(	0,		2,		0);
const CNormVal		CMainFrame::m_NormHue(		0,		360,	0);
const CNormVal		CMainFrame::m_NormSpread(	0,		600,	0);

static const double DAMP_TOLER = 1e-3;

CMainFrame::CMainFrame()
{
	//ZeroMemory(&m_VideoInfo, sizeof(m_VideoInfo));
	m_ParmInfo.SetDefaults();
	m_MastInfo.SetDefaults();
	//ZeroMemory(&m_bmi, sizeof(m_bmi));
	//m_hDC = NULL;
	//m_hDib = NULL;
	//m_DibBits = NULL;
	//m_PrevBm = NULL;
	m_FrameBytes = 0;
	m_BytesPerPixel = 0;
	m_FrameRate = 25;	// how do we know our frame rate?
	m_BankIdx = 0;
	m_PatchIdx = -1;
	m_Banks = 0;
	m_Speed = 1;
	m_Zoom = 0;
	m_TargetZoom = 0;
	m_Damping = 1;
	m_Rings = CPatch::MAX_RINGS;
	m_Tempo = 100;
	m_TargetOrg = DPoint(.5, .5);
	m_GrowDir = 1;
	m_OrgMotion = 0;
	m_Clock = 0;
	m_PrevClock = 0;
	m_PrevHue = 0;
	//m_TempoTimer.Launch(TimerCallback, this, THREAD_PRIORITY_TIME_CRITICAL);
	//m_TempoTimer.Run(TRUE);
	ZeroMemory(m_MastOfs, sizeof(m_MastOfs));
	m_PatchMode = PM_FULL;
	//GetDocFolder(m_DocFolder);
	ZeroMemory(&m_GlobParm, sizeof(m_GlobParm));
	ZeroMemory(&m_GlobParmTarg, sizeof(m_GlobParmTarg));
}

CMainFrame::~CMainFrame()
{
//	if (m_PrevBm != NULL)
//		SelectObject(m_hDC, m_PrevBm);	// restore DC's previous bitmap
//	DeleteObject(m_hDib);
//	DeleteObject(m_hDC);
}

void CMainFrame::SetZoom(double Zoom)
{
	m_View.SetZoom(Zoom);
	m_Zoom = m_NormZoom.Norm(Zoom);
	m_TargetZoom = m_Zoom;
}

void CMainFrame::SetZoomNorm(double Zoom)
{
	m_View.SetZoom(m_NormZoom.Denorm(Zoom));
	m_Zoom = Zoom;
	m_TargetZoom = Zoom;
}

void CMainFrame::SetRings(double Rings)
{
	m_Rings = Rings;
	int	Limit = round(Rings);
	if (Limit >= CPatch::MAX_RINGS)
		Limit = INT_MAX;	// no limit
	m_View.SetMaxRings(Limit);
}

void CMainFrame::SetTempo(double Tempo)
{
	//m_TempoTimer.SetFreq(float(Tempo / 60.0), TRUE);
	m_Tempo = Tempo;
}

void CMainFrame::SetReverse(bool Enable)
{
	int	Dir = Enable ? -1 : 1;
	if (Dir == m_GrowDir)
		return;	// nothing to do
	m_GrowDir = Dir;
}

void CMainFrame::SetZoomCenter(bool Enable)
{
	m_View.SetZoomType(Enable ? 
		CWhorldView::ZT_WND_CENTER : CWhorldView::ZT_RING_ORIGIN);
}

void CMainFrame::SetOriginNorm(const DPOINT& Origin)
{
	m_View.SetNormOrigin(Origin);
	m_TargetOrg = Origin;
}

void CMainFrame::SetGlobalHue(double Hue)
{
    if (Hue == m_PrevHue)
        return;
    
	m_View.RotateHue(Hue - m_PrevHue);
	m_PrevHue = Hue;
}

void CMainFrame::RandomPhase() 
{
	for (int i = 0; i < PARM_ROWS; i++)
		m_View.SetPhase(i, double(rand()) / RAND_MAX);
}

/*
bool CMainFrame::Init(const VideoInfoStruct& videoInfo)
{
	m_VideoInfo = videoInfo;
	m_hDC = CreateCompatibleDC(NULL);
	if (m_hDC == NULL)
		return(FALSE);
	ZeroMemory(&m_bmi, sizeof(m_bmi));
	m_bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_bmi.bmiHeader.biWidth = m_VideoInfo.frameWidth;
	m_bmi.bmiHeader.biHeight = LONG(m_VideoInfo.frameHeight);
	if (videoInfo.orientation != FF_ORIGIN_BOTTOM_LEFT)
		m_bmi.bmiHeader.biHeight = -m_bmi.bmiHeader.biHeight;	// top-down DIB
	m_bmi.bmiHeader.biPlanes = 1;
	switch (m_VideoInfo.bitDepth) {
	case FF_CAP_16BITVIDEO:
		m_bmi.bmiHeader.biBitCount = 16;
		m_bmi.bmiHeader.biCompression = BI_BITFIELDS;	// must be 5-6-5
		*(DWORD *)m_bmi.bmiColors = 0xF800;	// red color mask
		m_bmi.GreenMask = 0x07E0;	// green color mask
		m_bmi.BlueMask = 0x001F;	// blue color mask
		m_BytesPerPixel = 2;
		break;
	case FF_CAP_24BITVIDEO:
		m_bmi.bmiHeader.biBitCount = 24;
		m_BytesPerPixel = 3;
		break;
	case FF_CAP_32BITVIDEO:
		m_bmi.bmiHeader.biBitCount = 32;
		m_BytesPerPixel = 4;
		break;
	default:
		return(FALSE);
	}
	m_hDib = CreateDIBSection(GetDC(NULL), &m_bmi, DIB_RGB_COLORS, &m_DibBits, NULL, 0);
	if (m_hDib == NULL)
		return(FALSE);
	BITMAP	bm;	// check bitmap's actual size in bytes, just in case
	if (!GetObject(m_hDib, sizeof(bm), &bm))
		return(FALSE);
	if (bm.bmWidthBytes != LONG(m_VideoInfo.frameWidth) * m_BytesPerPixel)
		return(FALSE);
	m_PrevBm = SelectObject(m_hDC, m_hDib);
	if (m_PrevBm == NULL)
		return(FALSE);
	m_FrameBytes = m_VideoInfo.frameWidth * m_VideoInfo.frameHeight * m_BytesPerPixel;
	m_View.SetWndSize(CSize(m_VideoInfo.frameWidth, m_VideoInfo.frameHeight));
	m_View.SetTimerFreq(m_FrameRate);
	for (int i = 0; i < GLOBAL_PARMS; i++) {
		int	gpi = CParmInfo::m_GlobParm[i];
		m_GlobOsc[gpi].SetTimerFreq(m_FrameRate);
	}
	if (!ReadIniFile() && !LoadPlaylist()) {
		LoadPatches();
		SetCurPatch(0);	// select first patch
	}
	return(TRUE);
}
*/

/*
 bool CMainFrame::GetDocFolder(CString& Folder)
{
	CPathStr	Path;
	char	*p = Path.GetBuffer(MAX_PATH);
	bool	retc = SUCCEEDED(SHGetSpecialFolderPath(NULL, p, CSIDL_PERSONAL, 0));
	Path.ReleaseBuffer();
	if (!retc)
		return(FALSE);
	Path.Append("WhorldFF");
	Folder = Path;
	return(TRUE);
}

bool CMainFrame::LoadPatches()
{
	CPathStr	Path(m_DocFolder);
	Path.Append("*.*");
	CFileFind	ff;
	BOOL bWorking = ff.FindFile(Path);
	CSortStringArray	PatchPath;	// sorted array of patch paths
	while (bWorking) {
		bWorking = ff.FindNextFile();
		if (!ff.IsDirectory())
			PatchPath.Add(ff.GetFilePath());
	}
	PatchPath.Sort();
	CPatch	Patch;
	for (int i = 0; i < PatchPath.GetSize(); i++) {
		CStdioFile	fp;	// new object each time so dtor releases lock
		if (fp.Open(PatchPath[i], CFile::modeRead | CFile::shareDenyWrite)
		&& Patch.Read(fp))	// this overload doesn't display any messages
			m_Patch[0].Add(Patch);	// add to bank zero
	}
	m_Banks = 1;	// all patches are in first bank
	return(TRUE);
}

bool CMainFrame::ReadIniFile()
{
	CPathStr	Path(m_DocFolder);
	Path.Append("UltraWhorld.ini");
	bool	GotPlaylist = FALSE;
	CStdioFile	fp;
	if (fp.Open(Path, CFile::modeRead | CFile::shareDenyWrite)) {
		CString	Line;
		while (fp.ReadString(Line)) {
			char	*p = Line.GetBuffer(0);
			char	*Token = strtok(p, "=");
			char	*Value = strtok(NULL, "");
			if (!stricmp(Token, "playlist"))
				GotPlaylist = LoadPlaylist(Value);
			Line.ReleaseBuffer(0);
		}
	}
	return(GotPlaylist);
}

bool CMainFrame::LoadPlaylist()
{
	CPathStr	Path(m_DocFolder);
	Path.Append("UltraWhorld.whl");
	return(LoadPlaylist(Path));
}

bool CMainFrame::LoadPlaylist(LPCSTR Path)
{
	CPathStr	ListFolder(Path);	// for resolving relative patch paths
	ListFolder.RemoveFileSpec();
	CPlaylist	Playlist;
	ZeroMemory(&Playlist.m_Main, sizeof(Playlist.m_Main));
	Playlist.m_Main.Patch.m_Main = CPatch::m_MainDefaults;
	Playlist.m_Main.Patch.m_Master = CPatch::m_MasterDefaults;
	CStdioFile	fp;
	if (fp.Open(Path, CFile::modeRead | CFile::shareDenyWrite)
	&& Playlist.Read(fp)) {	// this overload doesn't display any messages
		SetPatch(Playlist.m_Main.Patch);
		SetPatchMode(Playlist.m_Main.PatchMode);	// order matters
		int	Patches = Playlist.m_Patch.GetSize();
		CPatch	Patch;
		int	i;
		for (i = 0; i < Patches; i++) {
			CPatchLink& pl = Playlist.m_Patch[i];
			if (pl.m_Bank < BANKS) {	// range check bank
				CStdioFile	fp;	// new object each time so dtor releases lock
				if (PathIsFileSpec(pl.m_Path)) {	// if filename only
					CPathStr	Path(ListFolder);	// assume patch is in playlist folder
					Path.Append(pl.m_Path);
					pl.m_Path = Path;
				}
				if (fp.Open(pl.m_Path, CFile::modeRead | CFile::shareDenyWrite)
				&& Patch.Read(fp)) {	// this overload doesn't display any messages
					m_Patch[pl.m_Bank].Add(Patch);
					if (pl.m_Bank >= m_Banks)	// track number of banks in use
						m_Banks = pl.m_Bank + 1;
				}
			}
		}
		m_MastInfo = Playlist.m_Main.Patch;
		for (i = 0; i < PARM_ROWS; i++)	// set initial master offsets
			m_MastOfs[i] = m_MastInfo.m_Row[i].Val;
		for (i = 0; i < GLOBAL_PARMS; i++) {
			int	gpi = CParmInfo::m_GlobParm[i];
			const	CParmInfo::ROW& GlobInfo = Playlist.m_Main.GlobParm.m_Row[gpi];
			m_GlobParmTarg[gpi] = GlobInfo.Val;	// update global parameter target
			m_GlobOsc[gpi].SetWaveform(GlobInfo.Wave);
			m_GlobOsc[gpi].SetPulseWidth(GlobInfo.PW);
			m_GlobOsc[gpi].SetFreq(GlobInfo.Freq);
		}
		m_GlobParm = Playlist.m_Main.GlobParm;
		SetCurBank(Playlist.m_Main.Playlist.CurBank);
		SetCurPatch(Playlist.m_Main.Playlist.CurPatch);
		return(TRUE);
	}
	return(FALSE);
}
*/

bool CMainFrame::SetCurBank(int BankIdx)
{
	if (BankIdx < 0 || BankIdx >= m_Banks)
		return(FALSE);
	if (BankIdx == m_BankIdx)	// if bank is already selected
		return(TRUE);	// nothing to do
	m_BankIdx = BankIdx;
	m_PatchIdx = -1;	// invalidate current patch selection
	return(TRUE);
}

bool CMainFrame::SetCurPatch(int PatchIdx)
{
	if (PatchIdx < 0 || PatchIdx >= m_Patch[m_BankIdx].size())
		return(FALSE);
	if (PatchIdx == m_PatchIdx)	// if patch is already selected
		return(TRUE);	// nothing to do
	const CPatch& p = m_Patch[m_BankIdx][PatchIdx];
	m_ParmInfo = p;	// set geometry parameters
	if (m_PatchMode == PM_FULL) {	// if full mode
		ZeroMemory(m_MastOfs, sizeof(m_MastOfs));	// zero master offsets
		SetPatch(p);	// set master and main attributes
	}
	m_View.FlushHistory();	// prevent glitching
	m_PatchIdx = PatchIdx;
	return(TRUE);
}

void CMainFrame::SetPatch(const CPatch& Patch)
{
	// set master attributes
	SetSpeed(Patch.m_Master.Speed);
	SetZoom(Patch.m_Master.Zoom);
	SetDamping(Patch.m_Master.Damping);
	SetTrail(Patch.m_Master.Trail);
	SetRings(Patch.m_Master.Rings);
	SetTempo(Patch.m_Master.Tempo);
	SetHueLoopLength(Patch.m_Master.HueLoopLength);
	SetCanvasScale(Patch.m_Master.CanvasScale);
	SetCopies(round(Patch.m_Master.Copies));
	SetSpread(round(Patch.m_Master.Spread));
	// set main attributes
	SetOriginNorm(Patch.m_Main.Origin);
	SetDrawMode(Patch.m_Main.DrawMode);
	SetOrgMotion(Patch.m_Main.OrgMotion);
	SetHue(Patch.m_Main.Hue);
	Mirror(Patch.m_Main.Mirror);
	SetReverse(Patch.m_Main.Reverse);
	SetConvex(Patch.m_Main.Convex);
	InvertColor(Patch.m_Main.InvertColor);
	LoopHue(Patch.m_Main.LoopHue);
	// pause is not supported
	SetZoomCenter(Patch.m_Main.ZoomCenter);
}

void CMainFrame::GetPatch(CPatch& Patch) const
{
	// set master attributes
	Patch.m_Master.Speed = GetSpeed();
	Patch.m_Master.Zoom = GetZoom();
	Patch.m_Master.Damping = GetDamping();
	Patch.m_Master.Trail = GetTrail();
	Patch.m_Master.Rings = GetRings();
	Patch.m_Master.Tempo = GetTempo();
	Patch.m_Master.HueLoopLength = GetHueLoopLength();
	Patch.m_Master.CanvasScale = GetCanvasScale();
	Patch.m_Master.Copies = GetCopies();
	Patch.m_Master.Spread = GetSpread();
	// set main attributes
	GetOriginNorm(Patch.m_Main.Origin);
	Patch.m_Main.DrawMode = GetDrawMode();
	Patch.m_Main.OrgMotion = GetOrgMotion();
	Patch.m_Main.Hue = GetHue();
	Patch.m_Main.Mirror = IsMirrored();
	Patch.m_Main.Reverse = GetReverse();
	Patch.m_Main.Convex = GetConvex();
	Patch.m_Main.InvertColor = IsColorInverted();
	Patch.m_Main.LoopHue = IsHueLooped();
	Patch.m_Main.Pause = FALSE;	// pause is not supported
	Patch.m_Main.ZoomCenter = GetZoomCenter();
}

/*
bool CMainFrame::SavePatch(LPCSTR Path) const
{
	if (m_PatchIdx < 0)
		return(FALSE);
	CPatch	Patch;
	Patch = m_ParmInfo;	// save whatever we're viewing; assign to base class
	for (int i = 0; i < PARM_ROWS; i++) {
		Patch.m_Row[i].Val += m_MastOfs[i];	// add master offset to parameter
		if (m_MastInfo.m_Row[i].Freq)		// if master frequency is nonzero
			Patch.SetOscProps(m_MastInfo, i);	// override oscillator settings
	}
	GetPatch(Patch);	// get master and main info
	CStdioFile	fp;
	return(fp.Open(Path, CFile::modeCreate | CFile::modeWrite) && Patch.Write(fp));
}

bool CMainFrame::SavePatch() const
{
	if (!PathIsDirectory(m_DocFolder)) {	// make sure doc folder exists
		if (!CreateDirectory(m_DocFolder, NULL))
			return(FALSE);
	}
	CPathStr	Folder(m_DocFolder);
	Folder.Append("Saved");
	CString	Path;
	if (!MakeUniquePath(Folder, "Patch", ".whp", Path))
		return(FALSE);
	return(SavePatch(Path));
}

bool CMainFrame::MakeUniquePath(LPCSTR Folder, LPCSTR Prefix, LPCSTR Extension, CString& Path)
{
	CTime	t(CTime::GetCurrentTime());
	CString	fname = CString(Prefix) + t.Format("_%y%m%d%H%M%S") + Extension;
	CPathStr	ps(Folder);
	if (!PathIsDirectory(ps)) {
		if (!CreateDirectory(ps, NULL))
			return(FALSE);
	}
	ps.Append(fname);
	if (PathFileExists(ps))	{	// time is wrong, or multiple calls per second
		CString	s;
		s.Format("_%d", clock());
		ps.Insert(ps.ReverseFind('.'), s);	// append milliseconds to filename
		if (PathFileExists(ps))	// shouldn't happen
			return(FALSE);
	}
	Path = ps;
	return(TRUE);
}
*/

DWORD CMainFrame::processFrame(LPVOID pFrame)
{
	double	delta = m_Zoom - m_TargetZoom;
	if (fabs(delta) > 1e-3) {
		m_Zoom -= delta * GetDamping();	// update normalized zoom
		DPoint	p1, p2;
		m_View.GetNormOrigin(p1);
		m_View.SetZoom(m_NormZoom.Denorm(m_Zoom));	// pass zoom to view
		m_View.GetNormOrigin(p2);
		m_TargetOrg -= (p1 - p2);	// zoom can change origin, so compensate target
	}
	switch (m_OrgMotion) {
	case OM_DRAG:
		{
			DPoint	org;
			m_View.GetNormOrigin(org);
			org += (m_TargetOrg - org) * GetDamping();
			m_View.SetNormOrigin(org);
		}
		break;
	case OM_RANDOM:
		{
			if (m_Clock != m_PrevClock) {	// time for a new random target
				m_TargetOrg.x = double(rand()) / RAND_MAX;
				m_TargetOrg.y = double(rand()) / RAND_MAX;
			}
			m_PrevClock = m_Clock;
			DPoint	org;
			m_View.GetNormOrigin(org);
			org += (m_TargetOrg - org) * GetDamping();	// update normalized origin
			m_View.SetNormOrigin(org);	// pass origin to view
		}
		break;
	}
	CParmInfo	Info = m_ParmInfo;
	for (int i = 0; i < PARM_ROWS; i++) {
		Info.m_Row[i].Val += m_MastOfs[i];	// apply master offsets to geometry
		if (m_MastInfo.m_Row[i].Freq)		// if master frequency is nonzero
			Info.SetOscProps(m_MastInfo, i);	// override oscillator settings
		Info.m_Row[i].Freq *= m_Speed;	// compensate frequency for master speed
	}
	CWhorldView::PARMS	GlobParm;		// global parameter values
	for (int i = 0; i < GLOBAL_PARMS; i++) {
		int	gpi = CParmInfo::m_GlobParm[i];
		CParmInfo::ROW& GlobRow = m_GlobParm.m_Row[gpi];
		if (m_GlobParmTarg[gpi] != GlobRow.Val) {	// if target differs from value
			double delta = GlobRow.Val - m_GlobParmTarg[gpi];
			if (fabs(delta) > DAMP_TOLER)
				GlobRow.Val -= delta * m_Damping;
			else	// close enough to target
				GlobRow.Val = m_GlobParmTarg[gpi];	// arrive at target
		}
		if (GlobRow.Freq) {
			COscillator&	Osc = m_GlobOsc[gpi];
			Osc.TimerHook();
			((double *)&GlobParm)[gpi] = GlobRow.Val + Osc.GetVal() * GlobRow.Amp;
		} else
			((double *)&GlobParm)[gpi] = GlobRow.Val;
	}
	m_View.TimerHook(Info, GlobParm, m_Speed * m_GrowDir);
	m_View.Draw(NULL);
	// the following assumes pFrame layout matches DIB layout
//	if (IsMirrored()) {
//		memcpy(pFrame, m_DibBits, m_FrameBytes / 2);	// skip bottom half
//		switch (m_VideoInfo.bitDepth) {
//		case FF_CAP_16BITVIDEO:
//			Mirror16(pFrame, GetWidth(), GetHeight());
//			break;
//		case FF_CAP_24BITVIDEO:
//			Mirror24(pFrame, GetWidth(), GetHeight());
//			break;
//		case FF_CAP_32BITVIDEO:
//			Mirror32(pFrame, GetWidth(), GetHeight());
//			break;
//		}
//	} else
//		memcpy(pFrame, m_DibBits, m_FrameBytes);
	return(FF_SUCCESS);
}

/*
void CMainFrame::TimerCallback(LPVOID Cookie)
{
	((CMainFrame *)Cookie)->m_Clock++;	// trigger random jump
}

void CMainFrame::Mirror32(LPVOID pFrame, int w, int h)
{
	int	hw = w >> 1;	// assume width and height are even
	int	hh = h >> 1;
	int	hspan = hw * 4;
	int	whw = w + hw;
	int	x, y;
	// upper right
	DWORD	*src;
	DWORD	*dst;
	src = (DWORD *)pFrame;
	dst = (DWORD *)pFrame + w;
	for (y = 0; y < hh; y++) {
		for (x = 0; x < hw; x++)
			*--dst = *src++;
		src += hw;
		dst += whw;
	}
	// lower left
	src = (DWORD *)pFrame;
	dst = (DWORD *)pFrame + w * h;
	for (y = 0; y < hh; y++) {
		dst -= w;
		memcpy(dst, src, hspan);
		src += w;
	}
	src = (DWORD *)pFrame;
	dst = (DWORD *)pFrame + w * h;
	// lower right
	for (y = 0; y < hh; y++) {
		for (x = 0; x < hw; x++)
			*--dst = *src++;
		src += hw;
		dst -= hw;
	}
}

void CMainFrame::Mirror24(LPVOID pFrame, int w, int h)
{
	int	hw = w >> 1;	// assume width and height are even
	int	hh = h >> 1;
	int	hspan = hw * 3;
	int	whw = w + hw;
	struct PIX24 {
		char	b[3];
	};
	int	x, y;
	// upper right
	PIX24	*src;
	PIX24	*dst;
	src = (PIX24 *)pFrame;
	dst = (PIX24 *)pFrame + w;
	for (y = 0; y < hh; y++) {
		for (x = 0; x < hw; x++)
			*--dst = *src++;
		src += hw;
		dst += whw;
	}
	// lower left
	src = (PIX24 *)pFrame;
	dst = (PIX24 *)pFrame + w * h;
	for (y = 0; y < hh; y++) {
		dst -= w;
		memcpy(dst, src, hspan);
		src += w;
	}
	src = (PIX24 *)pFrame;
	dst = (PIX24 *)pFrame + w * h;
	// lower right
	for (y = 0; y < hh; y++) {
		for (x = 0; x < hw; x++)
			*--dst = *src++;
		src += hw;
		dst -= hw;
	}
}

void CMainFrame::Mirror16(LPVOID pFrame, int w, int h)
{
	int	hw = w >> 1;	// assume width and height are even
	int	hh = h >> 1;
	int	hspan = hw * 2;
	int	whw = w + hw;
	int	x, y;
	// upper right
	WORD	*src;
	WORD	*dst;
	src = (WORD *)pFrame;
	dst = (WORD *)pFrame + w;
	for (y = 0; y < hh; y++) {
		for (x = 0; x < hw; x++)
			*--dst = *src++;
		src += hw;
		dst += whw;
	}
	// lower left
	src = (WORD *)pFrame;
	dst = (WORD *)pFrame + w * h;
	for (y = 0; y < hh; y++) {
		dst -= w;
		memcpy(dst, src, hspan);
		src += w;
	}
	src = (WORD *)pFrame;
	dst = (WORD *)pFrame + w * h;
	// lower right
	for (y = 0; y < hh; y++) {
		for (x = 0; x < hw; x++)
			*--dst = *src++;
		src += hw;
		dst -= hw;
	}
}
*/
