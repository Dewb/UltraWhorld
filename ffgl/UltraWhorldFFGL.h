#include <FFGLShader.h>
#include <FFGLPluginSDK.h>

class UltraWhorldFFGL : public CFreeFrameGLPlugin
{
public:
	UltraWhorldFFGL();
    virtual ~UltraWhorldFFGL() {}
    
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
	float m_fClip;
	
	int m_initResources;
        
	FFGLExtensions m_extensions;
    FFGLShader m_shader;
	GLint m_inputTextureLocation;
	GLint m_maxCoordsLocation;
	GLint m_clipDistanceLocation;
    
    GLuint m_vbo;
};


