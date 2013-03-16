#include <FFGL.h>
#include <FFGLLib.h>
#include <GLUT/GLUT.h>
#include "UltraWhorldFFGL.h"


static CFFGLPluginInfo PluginInfo(
	UltraWhorldFFGL::CreateInstance,	// Create method
	"UWHG",								// Plugin unique ID
	"UltraWhorldFFGL",			// Plugin name											
	1,						   			// API major version number 													
	000,								  // API minor version number
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
    m_View.TimerHook(m_ParmInfo, GlobParm, 0.5);
    m_View.Draw(NULL);
 
    glFlush();
    glPopMatrix();
    
    return FF_SUCCESS;
}

DWORD UltraWhorldFFGL::GetParameter(DWORD dwIndex)
{
	DWORD dwRet;
  
	switch (dwIndex)
    {
        case PARAM_BANK:
        default:
            *((float *)(unsigned)&dwRet) = 0;
            return dwRet;

        //default:
        //    return FF_FAIL;
	}
}

DWORD UltraWhorldFFGL::SetParameter(const SetParameterStruct* pParam)
{
	if (pParam != NULL)
    {
		switch (pParam->ParameterNumber)
        {
            case PARAM_BANK:
            default:
                break;
                
            //default:
            //    return FF_FAIL;
		}
    
		return FF_SUCCESS;
	}
  
	return FF_FAIL;
}
