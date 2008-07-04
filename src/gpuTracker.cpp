#include "gl_includes.h"
#include <stdio.h>

#include "Camera.h"
#include "FilterChain.h"
#include "FilterController.h"


//we will need a pointer to the camera and a texture to upload the frames to
//the filter chain is used to process the image on the gpu
Camera* cam;
GLuint videoTexture;
FilterChain* filterChain;
int currentFilter;

FilterController* fController;




void renderScene(void) {
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//grab a frame from the camera
	cam->grabFrameToGlTexture(videoTexture);
	
	//apply the image filters
	GLuint tex = filterChain->apply(videoTexture);
	tex = fController->filterOutput();
	
	//draw processed video
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glBegin(GL_QUADS);
		glColor3d(1.0,1.0,1.0);
		glTexCoord2i(0,0); glVertex3i(-1,-1,0);
		glTexCoord2i(1,0); glVertex3i( 1,-1,0);
		glTexCoord2i(1,1); glVertex3i( 1, 1,0);
		glTexCoord2i(0,1); glVertex3i(-1, 1,0);
	glEnd();
	
	
	//drawFilterController
	fController->draw();
		
	//done drawing
	glFlush();
	glutSwapBuffers();
	
	glutPostRedisplay();
}


void specialKeyPress(int key, int x, int y){
	switch (key) {
		case GLUT_KEY_LEFT:
			fController->decreaseCurrentParameter();
			break;
		case GLUT_KEY_RIGHT:
			fController->increaseCurrentParameter();
			break;
		case GLUT_KEY_UP:
			fController->selectNextParameter();
			break;
		case GLUT_KEY_DOWN:
			fController->selectPreviousParameter();
			break;
		case  GLUT_KEY_PAGE_UP:
			if (currentFilter < filterChain->numFilters()-1)
				currentFilter++;
				fController->setFilter(filterChain->getFilter(currentFilter));
			break;
		case  GLUT_KEY_PAGE_DOWN:
			if (currentFilter > 0)
				currentFilter--;
				fController->setFilter(filterChain->getFilter(currentFilter));
			break;
		default:
			break;
	}
	
	
}


int main(int argc, char **argv) {
	
	//initialize camera
	cam = new Camera(USB_CAMERA);


	//initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("gpuTracker");
	glutDisplayFunc(renderScene);
	glutSpecialFunc(specialKeyPress);
	
	
#ifndef __APPLE_CC__ //on osx we dont need glew
	//initalize GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
  		/* Problem: glewInit failed, something is seriously wrong. */
  		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif
	
	
	//initialize tracking stuff
	glGenTextures(1, &videoTexture);
	filterChain = new FilterChain();
	

	filterChain->attachNewFilter("filters/contrast.xml", 640,480);
	filterChain->attachNewFilter("filters/gauss.xml", 640,480);
	filterChain->attachNewFilter("filters/gaussV.xml", 640,480);
	filterChain->attachNewFilter("filters/threshold.xml", 640,480);

	
	int currentFilter = 0;
	fController = new FilterController(filterChain->getFilter(currentFilter));
		
	
	//go
	glutMainLoop();
	
	return 0;
}



