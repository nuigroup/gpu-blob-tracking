#ifndef CAMERA_H_
#define CAMERA_H_


#include "gl_includes.h"
#include <highgui.h>

//i cant find docuimentation for openCV about what number is what camera.
//these numbers corrospond to what happens on my system, i will add
//support for other camera drivers (dc1394, dsVideoLib(Win32) cmu driver etc. later)
//so this will most definatly change
enum CameraType {USB_CAMERA = -1, FW_CAMERA = 0 } ;



class Camera {

	private:
		CvCapture  *capture;
		IplImage* frame;

	
	public:
		Camera(CameraType camType);
		void grabFrameToGlTexture(GLuint texture); 
		void setCamera(int index);
		inline int getFrameWidth() {return this->frame->width;};
		inline int getFrameHeight() {return this->frame->height;};
		
		~Camera();
		
};


#endif //CAMERA_H_
