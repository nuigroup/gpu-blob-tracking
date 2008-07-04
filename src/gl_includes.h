#ifdef __APPLE_CC__
	#include <OpenGL/gl.h>
	#include <GLUT/glut.h>
#else
	#include <stdlib.h> //needed to avoid redefinition of exit
	#include <GL/glew.h>
	#include <GL/gl.h>
	#include <GL/glut.h>
#endif
