#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include "gl_includes.h"


class ShaderProgram {

	private:
		GLuint  vertex_shader_id;
		GLuint  geometry_shader_id;
		GLuint  fragment_shader_id;
		GLuint  program;
	
	public:
		ShaderProgram(const char* vertexSourceFile, const char* geometrySourceFile, const char* fragmentSourceFile); //pass NULL or 0 where you want the fixed funtion pipeline
		inline void enable(void)  { glUseProgram(program);  };
		inline void disable(void) { glUseProgram(0);        };
		inline void setUniform1f(const char* name, float val){  glUniform1f(glGetUniformLocation(this->program, name), val);  };
		virtual ~ShaderProgram();
		
};


#endif //SHADERPROGRAM_H_
