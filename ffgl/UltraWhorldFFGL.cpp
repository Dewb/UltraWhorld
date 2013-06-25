#include <FFGL.h>
#include <FFGLLib.h>
#include <GLUT/GLUT.h>
#include "UltraWhorldFFGL.h"


static CFFGLPluginInfo PluginInfo(
	UltraWhorldFFGL::CreateInstance,	// Create method
	"UWHG",								// Plugin unique ID
	"UltraWhorldFFGL",			// Plugin name											
	1,						   			// API major version number 										
	500,								  // API minor version number
	1,										// Plugin major version number
	000,									// Plugin minor version number
	FF_SOURCE,						// Plugin type
	"Visualizer for sacred geometry",	// Plugin description
	"by Chris Korda; experimental FFGL port by Dewb" // About
);


UltraWhorldFFGL::UltraWhorldFFGL()
: CFreeFrameGLPlugin()
{
	SetMinInputs(0);
	SetMaxInputs(0);
      
#undef FFPARM
#define FFPARM(tag, defval, name) SetParamInfo(PARAM_##tag, name, FF_TYPE_STANDARD, (float) defval );
#include "FFParmDef.h"
    
}


DWORD UltraWhorldFFGL::InitGL(const FFGLViewportStruct *vp)
{
    m_View.SetWndSize(CSize(CANVAS_WIDTH, CANVAS_HEIGHT));

    return FF_SUCCESS;
}

DWORD UltraWhorldFFGL::DeInitGL()
{
    return FF_SUCCESS;
}

DWORD UltraWhorldFFGL::ProcessOpenGL(ProcessOpenGLStruct *pGL)
{
    glPushMatrix();
    
    CWhorldView::PARMS	GlobParm;
    processFrame(NULL);
    glFlush();
    glPopMatrix();
 
    m_Clock++;
    return FF_SUCCESS;
}

DWORD UltraWhorldFFGL::GetParameter(DWORD dwIndex)
{
	if (dwIndex < NUM_PARAMS)
		return m_Param[dwIndex].value;
	return 0;
}

bool UltraWhorldFFGL::IsBang(int ParamIdx, double Value)
{
	bool	b = Value == 1.0;
	bool	retc = b && !m_Bang[ParamIdx];
	m_Bang[ParamIdx] = b;
	return(retc);
}

#undef PARMDEF
#define PARMDEF(Name, Tag, MinVal, MaxVal, Steps, Scale) \
{ \
case PARAM_##Tag: \
SetMasterOffsetNorm(CParmInfo::Tag, val, MaxVal); \
break; \
}

DWORD UltraWhorldFFGL::SetParameter(const SetParameterStruct* pParam)
{
	if (pParam != NULL) {
        int	index = pParam->ParameterNumber;
        if (index >= 0 && index < NUM_PARAMS) {
            float	val = *(float*)(&(pParam->NewParameterValue));
            
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
                        //SavePatch();
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
	}

	return FF_FAIL;
}
