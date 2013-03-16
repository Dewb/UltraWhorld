#include <FFGLShader.h>
#include <FFGLPluginSDK.h>

#include <stdafx.h>
#include <WhorldView.h>

class UltraWhorldFFGL : public CFreeFrameGLPlugin
{
public:
	UltraWhorldFFGL();
    virtual ~UltraWhorldFFGL() {}
    
#define FFPARM(tag, defval, name) PARAM_##tag,
	enum {
#include "FFParmDef.h"
		NUM_PARAMS
	};
	enum {
		NUM_INPUTS = 1,
		MAX_STRING = 16
	};
    
	///////////////////////////////////////////////////
	// FreeFrameGL plugin methods
	///////////////////////////////////////////////////
	
	DWORD	SetParameter(const SetParameterStruct* pParam);
	DWORD	GetParameter(DWORD dwIndex);
	DWORD	ProcessOpenGL(ProcessOpenGLStruct* pGL);
    DWORD InitGL(const FFGLViewportStruct *vp);
    DWORD DeInitGL();
    
	///////////////////////////////////////////////////
	// Factory method
	///////////////////////////////////////////////////
    
	static DWORD __stdcall CreateInstance(CFreeFrameGLPlugin **ppOutInstance)
    {
        *ppOutInstance = new UltraWhorldFFGL();
        if (*ppOutInstance != NULL)
            return FF_SUCCESS;
        return FF_FAIL;
    }
    
protected:	
    
    CWhorldView m_View;
    CParmInfo m_ParmInfo;
};


