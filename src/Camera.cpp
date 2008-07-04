#include <stdio.h>
#include "Camera.h"



#define IsBGR(s) ((s[0] == 'B') && (s[1] == 'G') && (s[2] == 'R'))



Camera::Camera(CameraType camType){
   this->capture = cvCaptureFromCAM(0);
   if( !this->capture ){
      printf("Error: Could not initialize Camera.\n");
   	  exit(1);
   }
   
   this->frame = cvQueryFrame( this->capture );
}


void Camera::grabFrameToGlTexture (GLuint texture){
   this->frame = cvQueryFrame( this->capture );
   GLenum format = IsBGR(frame->channelSeq) ? GL_BGR_EXT : GL_RGBA;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, frame->width, frame->height, 0, format, GL_UNSIGNED_BYTE, frame->imageData);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glBindTexture(GL_TEXTURE_2D,0);
}


void Camera::setCamera(int index){
   cvReleaseCapture( &this->capture );

   this->capture = cvCaptureFromCAM(index);
   if( !this->capture ){
      fprintf(stderr,"Error: Could not initialize Camera.");
   }
}

Camera::~Camera(){
   cvReleaseCapture( &this->capture );
}
