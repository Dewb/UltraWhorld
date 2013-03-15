#include <FFGL.h>
#include <FFGLLib.h>
#include <GLUT/GLUT.h>
#include "UltraWhorldFFGL.h"


static CFFGLPluginInfo PluginInfo(
	UltraWhorldFFGL::CreateInstance,	// Create method
	"WHRL",								// Plugin unique ID
	"UltraWhorldFFGL",			// Plugin name											
	1,						   			// API major version number 													
	000,								  // API minor version number
	1,										// Plugin major version number
	000,									// Plugin minor version number
	FF_SOURCE,						// Plugin type
	"Visualizer for sacred geometry",	// Plugin description
	"by Chris Korda; experimental FFGL port by Dewb" // About
);

#define FFPARAM_Clip  (0)

/*
char *vertexShaderCode =
"void main()"
"{"
"  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
"  gl_TexCoord[0] = gl_MultiTexCoord0;"
"  gl_FrontColor = gl_Color;"
"}";


char *fragmentShaderCode =
"uniform sampler2D inputTexture;"
"uniform vec2 maxCoords;"
"uniform float clipDistance;"
"void main()"
"{"
"  vec2 texCoord = gl_TexCoord[0].xy;"
"  gl_FragColor.r = 0.0;"
"  gl_FragColor.g = 0.0;"
"  gl_FragColor.a = 1.0;"
"  gl_FragColor.b = texture2D(inputTexture, texCoord).b;"
"}";
 */

char* vertexShaderCode =
"uniform sampler2D inputTexture;"
"varying vec4 vVertex;"
"varying float depth;"
"uniform float clipDistance;"
"void main()"
"{"
"	gl_TexCoord[0]		= gl_MultiTexCoord0;"
"	vVertex				= vec4( gl_Vertex );"
"	depth				= texture2D( inputTexture, gl_TexCoord[0].st ).a;"
//"	vVertex.z			+= (depth - clipDistance) * 2.0;"
"	gl_Position			= gl_ModelViewProjectionMatrix * vVertex;"
"}";

char* fragmentShaderCode =
"varying float depth;"
"uniform float clipDistance;"
"void main()"
"{"
//"	if( depth < clipDistance ) discard;"
"	gl_FragColor.rgb	= vec3( depth );"
"	gl_FragColor.a		= 1.0;"
"}";

UltraWhorldFFGL::UltraWhorldFFGL()
:CFreeFrameGLPlugin(),
m_initResources(1),
m_inputTextureLocation(-1),
m_maxCoordsLocation(-1),
m_clipDistanceLocation(-1)
{
	SetMinInputs(0);
	SetMaxInputs(0);
  
	m_fClip = 0.5f;
	SetParamInfo(FFPARAM_Clip, "Clip", FF_TYPE_STANDARD, m_fClip);
}


DWORD UltraWhorldFFGL::InitGL(const FFGLViewportStruct *vp)
{
    m_extensions.Initialize();
    if (m_extensions.multitexture==0 || m_extensions.ARB_shader_objects==0)
        return FF_FAIL;
    
    m_shader.SetExtensions(&m_extensions);
    m_shader.Compile(vertexShaderCode,fragmentShaderCode);
    m_shader.BindShader();
    
    m_inputTextureLocation = m_shader.FindUniform("inputTexture");
    m_maxCoordsLocation = m_shader.FindUniform("maxCoords");
    m_clipDistanceLocation = m_shader.FindUniform("clipDistance");
  
    m_extensions.glUniform1iARB(m_inputTextureLocation, 0);
  
    m_shader.UnbindShader();
  /*
    float data[3][3] = {
        {  0.0, 1.0, 0.0   },
        { -1.0, -1.0, 0.5  },
        {  1.0, -1.0, 1.0  }
    };
    
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 3*3*sizeof(float), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    */
    
    return FF_SUCCESS;
}

DWORD UltraWhorldFFGL::DeInitGL()
{
    m_shader.FreeGLResources();
    return FF_SUCCESS;
}

DWORD UltraWhorldFFGL::ProcessOpenGL(ProcessOpenGLStruct *pGL)
{
    if (pGL->numInputTextures<1) return FF_FAIL;
    if (pGL->inputTextures[0]==NULL) return FF_FAIL;
  
    m_shader.BindShader();
    
	FFGLTextureStruct &Texture = *(pGL->inputTextures[0]);
  
	FFGLTexCoords maxCoords = GetMaxGLTexCoords(Texture);
    m_extensions.glUniform2fARB(m_maxCoordsLocation, maxCoords.s, maxCoords.t);
    m_extensions.glUniform1fARB(m_clipDistanceLocation, 2.0 * m_fClip);
  
    m_extensions.glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture.Handle);

    //glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    
    //glFrustum(-2.0, 2.0, -2.0, 2.0, -3.0, 10.0);
    //gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(m_fClip*360.0, 0.0, 0.0, 1.0);
    
	
    glBegin(GL_QUADS);

	m_extensions.glMultiTexCoord2f(GL_TEXTURE0, 0,0);
	glVertex2f(-1,-1);
	m_extensions.glMultiTexCoord2f(GL_TEXTURE0, 0, maxCoords.t);
	glVertex2f(-1,1);
	m_extensions.glMultiTexCoord2f(GL_TEXTURE0, maxCoords.s, maxCoords.t);
	glVertex2f(1,1);
	m_extensions.glMultiTexCoord2f(GL_TEXTURE0, maxCoords.s, 0);
	glVertex2f(1,-1);
	glEnd();
    
/*
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexPointer(3, GL_FLOAT, 0, NULL);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
*/

    glBindTexture(GL_TEXTURE_2D, 0);
  
    m_shader.UnbindShader();
  
    glFlush();
    glPopMatrix();
    
    return FF_SUCCESS;
}

DWORD UltraWhorldFFGL::GetParameter(DWORD dwIndex)
{
	DWORD dwRet;
  
	switch (dwIndex)
    {
        case FFPARAM_Clip:
            *((float *)(unsigned)&dwRet) = m_fClip;
            return dwRet;
        default:
            return FF_FAIL;
	}
}

DWORD UltraWhorldFFGL::SetParameter(const SetParameterStruct* pParam)
{
	if (pParam != NULL)
    {
		switch (pParam->ParameterNumber)
        {
            case FFPARAM_Clip:
                m_fClip = *((float *)(unsigned)&(pParam->NewParameterValue));
                break;
        
            default:
                return FF_FAIL;
		}
    
		return FF_SUCCESS;
	}
  
	return FF_FAIL;
}
