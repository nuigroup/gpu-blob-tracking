#include "ImageFilter.h"
#include <stdio.h>
#include "tinyxml.h"


//helper functon, should go somewhere else
void getFrameBufferForTexture(GLuint* fbo, GLuint* tex, int sizeX, int sizeY){
    GLenum status;
    
    //allocate ouput buffer on GPU using FBO
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, tex);
    glBindTexture(GL_TEXTURE_2D, *tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8,  sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmapEXT(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    //generate fbo
    glGenFramebuffersEXT(1, fbo);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, *fbo);
    
    //attach texture to fbo
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, *tex, 0);
    
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    
    status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    printf("Frame buffer status: %d\n", status);
}









//constructor
//
//reads the filter description file and creates a filter based on the shaders and parameters given in that file
//allocates output buffer/texture
ImageFilter::ImageFilter(const char* fname, int sx, int sy){
	res_x = sx; res_y = sy;
	//this->shader = shaderProg;
	glGenTextures(1, &output_texture );
	getFrameBufferForTexture(&output_buffer, &output_texture, res_x, res_y);
	
	this->parseXML(fname);

	

}


void ImageFilter::parseXML(const char* fname){
	//load filter description file
	printf("Loading Filter...\n");
	
	
	//load and parse xml filter description file
	TiXmlDocument doc(fname);
	if (!doc.LoadFile()) printf("error loading filter description file");
	
	
	//get the name of the filter
	TiXmlElement* root_node = doc.RootElement();
	
	this->name = root_node->Attribute("name");
	printf("Filter Name:%s\n", this->name);
	
	
	//get the  shader source file names
	TiXmlElement* node = root_node;
	
	node = root_node->FirstChildElement("VertexShader");
	const char* vertSrc = node ? node->GetText() : NULL;
	
	node = root_node->FirstChildElement("GeometryShader");
	const char* geomSrc = node ? node->GetText() : NULL;
	
	node = root_node->FirstChildElement("FragmentShader");
	const char* fragSrc = node ? node->GetText() : NULL;
	
	this->shader = new ShaderProgram(vertSrc, geomSrc, fragSrc);
	
	
	//get parameters
	//TODO: add type handling
	while( (node = (TiXmlElement*)node->NextSibling("Parameter")) ){
		const char* name = node->Attribute("name");
		float min = atof(node->Attribute("min"));
		float max = atof(node->Attribute("max"));
		float val = atof(node->GetText());
		parameters[std::string(name)] = new FilterParameter(name, val, min, max);
	}
}


//applies the filter to a GL texture.
//
//saves opengl states, and binds this filter's output buffer (render to texture) 
//sets up ortho projection for drawing just the texture using teh filters shaders
//parameters are set as uniforms for the shaders 
GLuint ImageFilter::apply(GLuint inputTexture){
	
	glPushAttrib(GL_VIEWPORT_BIT);
    glPushAttrib(GL_ENABLE_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
	
    //render to the fbo using the shader
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, output_buffer);

        glClearColor(0.0,1.0,0.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0,0,res_x, res_y);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1, 1.0, -1, 1.0, -1, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
		glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, inputTexture);
        
        
        //glUseProgram(f->program);
        
        this->shader->enable();

        
        for(std::map<std::string, FilterParameter*>::const_iterator it = parameters.begin(); it != parameters.end(); ++it)
    		this->shader->setUniform1f(it->first.c_str(), it->second->value);

        
        //glUniform1i(glGetUniformLocation(f->program, "tex"), 0);
        //glUniform1i(glGetUniformLocation(f->program, "tex1"), 1);
        
        glBegin(GL_QUADS);
        glColor3d(1.0, 1.0, 1.0);
        glTexCoord2f(0, 0); glVertex3f(-1, -1, 0); 
        glTexCoord2f(1, 0); glVertex3f(1, -1, 0);  
        glTexCoord2f(1, 1); glVertex3f(1, 1, 0);   
        glTexCoord2f(0, 1); glVertex3f(-1, 1, 0);  
        glEnd();
    
        this->shader->disable();
        
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPopAttrib();
		glPopAttrib();
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);  //should maybe have a stack
			
	return output_texture;	
		
		
};




//destructor
ImageFilter::~ImageFilter()
{
}
