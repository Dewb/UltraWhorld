// Copyleft 2006 Chris Korda
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.
/*
        chris korda
 
		revision history:
		rev		date	comments
        00      19apr06	initial version
		01		25apr06	map Hue to RotateHue instead of SetHue
		02		01may06	change patch default to zero
		03		07jul06	deInstantiate wasn't deleting instance
		04		02oct06	bump plugin version number
        05      30dec06	support 16-bit mode
        06      25jul07	add more parameters
		07		31jan08	add shear and global parameters

		whorld freeframe plugin
 
*/

#include <stdafx.h>
#include "WhorldPlug.h"
#include <math.h>

const PlugInfoStruct PlugInfo = {
	1,	// API major version
	0,	// API minor version
	{'U', 'W', 'H', 'O'},	// plugin identifier
	{'U', 'l', 't', 'r', 'a', 'W', 'h', 'o',
	 'r', 'l', 'd', ' ', ' ', ' ', ' ', ' ',},  // plugin title
	0	// effect plugin
};

const PlugExtendedInfoStruct PlugExtInfo = {
	1,		// plugin major version
	1,		// plugin minor version
	"Whorld Freeframe plugin",	// description
	"Copyleft 2006 Chris Korda",	// about text
	0,		// extended data size
	NULL	// extended data block
};

#undef FFPARM
#define FFPARM(tag, defval, name) {float(defval), name},
const WhorldPlug::ParamConstantsStruct paramConstants[WhorldPlug::NUM_PARAMS] = {
#include "FFParmDef.h"
};

PlugInfoStruct* getInfo() 
{
	return const_cast<PlugInfoStruct *>(&PlugInfo);
}

DWORD initialise()
{
	return FF_SUCCESS;
}

DWORD deInitialise()
{
	return FF_SUCCESS;
}

DWORD getNumParameters()
{
	return WhorldPlug::NUM_PARAMS;  
}

char* getParameterName(DWORD index)
{
	if (index >= 0 && index < WhorldPlug::NUM_PARAMS)
		return const_cast<char *>(paramConstants[index].name);
	return "                ";
}

float getParameterDefault(DWORD index)
{
	if (index >= 0 && index < WhorldPlug::NUM_PARAMS)
		return paramConstants[index].defaultValue;
	return 0;
}

WhorldPlug::WhorldPlug()
{
	for (int i = 0; i < NUM_PARAMS; i++) {
		m_Param[i].value = paramConstants[i].defaultValue;
		memset(m_Param[i].displayValue, ' ', MAX_STRING);
	}
	ZeroMemory(m_Bang, sizeof(m_Bang));
}

WhorldPlug::~WhorldPlug()
{
}

char* WhorldPlug::getParameterDisplay(DWORD index)
{
	memset(m_Param[index].displayValue, ' ', MAX_STRING);
	if (index >= 0 && index < NUM_PARAMS) {
		CString	s;
		switch (index) {
		case PARAM_PATCH:
			s.Format("%d", GetCurPatch());
			break;
		default:
			s.Format("%g", m_Param[index].value);
			break;
		}
		memcpy(m_Param[index].displayValue, s, min(s.GetLength(), MAX_STRING));
	}
	return m_Param[index].displayValue;
}

#undef PARMDEF
#define PARMDEF(Name, Tag, MinVal, MaxVal, Steps, Scale) \
{ \
case PARAM_##Tag: \
	SetMasterOffsetNorm(CParmInfo::Tag, val, MaxVal); \
	break; \
}

bool WhorldPlug::IsBang(int ParamIdx, double Value)
{
	bool	b = Value == 1.0;
	bool	retc = b && !m_Bang[ParamIdx];
	m_Bang[ParamIdx] = b;
	return(retc);
}

DWORD WhorldPlug::setParameter(SetParameterStruct* pParam)
{
	int	index = pParam->index;
	if (index >= 0 && index < NUM_PARAMS) {
		float	val = pParam->value;
		m_Param[index].value = val;
		switch (index) {
		case PARAM_BANK:
			SetCurBankNorm(val);
			break;
		case PARAM_PATCH:
			SetCurPatchNorm(val);
			break;
		case PARAM_SPEED:
			SetSpeedNorm(val);
			break;
		case PARAM_ZOOM:
			SetTargetZoomNorm(val);
			break;
		case PARAM_HUE:
			SetGlobalHueNorm(val);
			break;
		case PARAM_DAMPING:
			SetDampingNorm(val);
			break;
		case PARAM_TRAIL:
			SetTrailNorm(val);
			break;
		case PARAM_RINGS:
			SetRingsNorm(val);
			break;
		case PARAM_TEMPO:
			SetTempoNorm(val);
			break;
		case PARAM_HUE_LOOP_LEN:
			SetHueLoopLengthNorm(val);
			break;
		case PARAM_CANVAS_SCALE:
			SetCanvasScaleNorm(val);
			break;
		case PARAM_COPIES:
			SetCopiesNorm(val);
			break;
		case PARAM_SPREAD:
			SetSpreadNorm(val);
			break;
		case PARAM_XPOS:
			if (GetOrgMotion() == CMainFrame::OM_DRAG) {
				DPOINT	p;
				GetTargetOriginNorm(p);
				p.x = val;
				SetTargetOriginNorm(p);
			}
			break;
		case PARAM_YPOS:
			if (GetOrgMotion() == CMainFrame::OM_DRAG) {
				DPOINT	p;
				GetTargetOriginNorm(p);
				p.y = val;
				SetTargetOriginNorm(p);
			}
			break;
		#include "ParmDef.h"
		case PARAM_PATCH_MODE:
			SetPatchMode(val ? PM_GEOMETRY : PM_FULL);
			break;
		case PARAM_CENTER_ORIGIN:
			if (IsBang(index, val))
				SetOriginNorm(DPoint(.5, .5));
			break;
		case PARAM_ORIGIN_MOTION:
			SetOrgMotion(ParmToEnum(val, 3));
			break;
		case PARAM_LOOP_HUE:
			LoopHue(val != 0);
			break;
		case PARAM_ROTATE_HUE:
			if (IsBang(index, val))
				RotateHue(90.0);
			break;
		case PARAM_INVERT_COLOR:
			InvertColor(val != 0);
			break;
		case PARAM_MIRROR:
			Mirror(val != 0);
			break;
		case PARAM_FILL:
			SetDrawMode(CWhorldView::DM_FILL, val != 0);
			break;
		case PARAM_OUTLINE:
			SetDrawMode(CWhorldView::DM_OUTLINE, val != 0);
			break;
		case PARAM_XRAY:
			SetDrawMode(CWhorldView::DM_XRAY, val != 0);
			break;
		case PARAM_RANDOM_PHASE:
			if (IsBang(index, val))
				RandomPhase();
			break;
		case PARAM_REVERSE:
			SetReverse(val != 0);
			break;
		case PARAM_CONVEX:
			SetConvex(val != 0);
			break;
		case PARAM_CLEAR:
			if (IsBang(index, val))
				ClearScreen();
			break;
		case PARAM_ZOOM_CENTER:
			SetZoomCenter(val != 0);
			break;
		case PARAM_SAVE_PATCH:
			if (IsBang(index, val))
				SavePatch();
			break;
		case PARAM_GLOB_LINE_WIDTH:
			SetGlobalParmNorm(CParmInfo::LINE_WIDTH, val);
			break;
		case PARAM_GLOB_POLY_SIDES:
			SetGlobalParmNorm(CParmInfo::POLY_SIDES, val);
			break;
		case PARAM_GLOB_ROTATION:
			SetGlobalParmNorm(CParmInfo::ROTATE_SPEED, val);
			break;
		case PARAM_GLOB_ASPECT_RATIO:
			SetGlobalParmNorm(CParmInfo::ASPECT_RATIO, val);
			break;
		case PARAM_GLOB_SKEW_RADIUS:
			SetGlobalParmNorm(CParmInfo::SKEW_RADIUS, val);
			break;
		case PARAM_GLOB_SKEW_ANGLE:
			SetGlobalParmNorm(CParmInfo::SKEW_ANGLE, val);
			break;
		case PARAM_GLOB_STAR_FACTOR:
			SetGlobalParmNorm(CParmInfo::STAR_FACTOR, val);
			break;
		case PARAM_GLOB_PINWHEEL:
			SetGlobalParmNorm(CParmInfo::PINWHEEL, val);
			break;
		case PARAM_GLOB_EVEN_CURVE:
			SetGlobalParmNorm(CParmInfo::EVEN_CURVE, val);
			break;
		case PARAM_GLOB_ODD_CURVE:
			SetGlobalParmNorm(CParmInfo::ODD_CURVE, val);
			break;
		case PARAM_GLOB_EVEN_SHEAR:
			SetGlobalParmNorm(CParmInfo::EVEN_SHEAR, val);
			break;
		case PARAM_GLOB_ODD_SHEAR:
			SetGlobalParmNorm(CParmInfo::ODD_SHEAR, val);
			break;
		}
		return FF_SUCCESS;
	}
	return FF_FAIL;
}

float WhorldPlug::getParameter(DWORD index)
{
	if (index >= 0 && index < NUM_PARAMS)
		return m_Param[index].value;
	return 0;
}

DWORD WhorldPlug::processFrameCopy(ProcessFrameCopyStruct* pFrameData)
{
	return FF_FAIL;
}

DWORD getPluginCaps(DWORD index)
{
	switch (index) {

	case FF_CAP_16BITVIDEO:
		return FF_TRUE;

	case FF_CAP_24BITVIDEO:
		return FF_TRUE;

	case FF_CAP_32BITVIDEO:
		return FF_TRUE;

	case FF_CAP_PROCESSFRAMECOPY:
		return FF_FALSE;

	case FF_CAP_MINIMUMINPUTFRAMES:
		return WhorldPlug::NUM_INPUTS;

	case FF_CAP_MAXIMUMINPUTFRAMES:
		return WhorldPlug::NUM_INPUTS;

	case FF_CAP_COPYORINPLACE:
		return FF_FALSE;

	default:
		return FF_FALSE;
	}
}

LPVOID instantiate(VideoInfoStruct* pVideoInfo)
{
	// this shouldn't happen if the host is checking the capabilities properly
	if (pVideoInfo->bitDepth < 0 || pVideoInfo->bitDepth > 2)
		return (LPVOID) FF_FAIL;

	WhorldPlug *pPlugObj = new WhorldPlug;

	if (!pPlugObj->Init(*pVideoInfo)) {
		delete pPlugObj;
		return NULL;
	}

	return (LPVOID) pPlugObj;
}

DWORD deInstantiate(LPVOID instanceID)
{
	WhorldPlug *pPlugObj = (WhorldPlug*) instanceID;
	delete pPlugObj;	// delete first, THEN set to null (duh!)
	pPlugObj = NULL;	// mark instance deleted
	return FF_SUCCESS;
}

LPVOID getExtendedInfo()
{
	return (LPVOID) &PlugExtInfo;
}
