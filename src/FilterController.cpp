#include "FilterController.h"
#include <sstream>



void renderBitmapString(
		float x, 
		float y, 
		float z, 
		void *font, 
		const char *string) {  
  const char *c;
  glRasterPos3f(x, y,z);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}




void drawSlider(const char* name, float val, float min, float max, bool highlight){
	
	if (highlight)
		glColor3d(1.0,1.0,0.0);
	else
		glColor3d(.5,.5,0.7);
		
    
    //draw name
    renderBitmapString(-.98 ,-0.01,0,GLUT_BITMAP_HELVETICA_12, name);
    
    //draw bar
    glBegin(GL_LINES);
    	glVertex2d(-.7, 0.0);
    	glVertex2d(.9, 0.0);
    glEnd();
    
    //draw handle
    float pos = -.7 + (1.7 * (val - min)/max);
    glBegin(GL_QUADS);
       	glVertex2d(pos, -.05);
    	glVertex2d(pos+.01, -.05);
    	glVertex2d(pos+.01, .05);
    	glVertex2d(pos, .05);	
    glEnd();
    
    

	
}





FilterController::FilterController(ImageFilter* filter)
{
	this->myFilter = filter;
	currentParameter = myFilter->parameters.begin();
}



void FilterController::draw(){
	glPushAttrib(GL_ENABLE_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
	
        
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1.0, -1, 1.0, -1, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glDisable(GL_TEXTURE_2D);
   	glColor3d(0.0, 0.0, 0.8);
	

	
	for(std::map<std::string, FilterParameter*>::iterator it = myFilter->parameters.begin(); it != myFilter->parameters.end(); ++it){
		std::stringstream label;		
		label << it->first << ": " << it->second->value;
		bool highlight = (it == currentParameter);
		drawSlider(label.str().c_str(),
	    	       it->second->value,
	    	       it->second->min,
	    	       it->second->max,
	    	       highlight );
		
		glTranslated(0.0,0.2,0.0);
	
	}
	           
    glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();		           
}


//currentParameter is a iterator to a map<str, FilterParameter*>  FilterParameter is defined in ImageFilter.h
void FilterController::increaseCurrentParameter(){
	const char* n = currentParameter->first.c_str();
	int t = currentParameter->second->type;
	if (t==0){//int
		currentParameter->second->value += 1.0;
	}
	if (t==1){//float
		if(currentParameter->second->value < currentParameter->second->max) 
			currentParameter->second->value += 0.05;
	}
}


void FilterController::decreaseCurrentParameter(){
		int t = currentParameter->second->type;
	if (t==0){//int
		currentParameter->second->value -= 1.0;
	}
	if (t==1){//float
		if(currentParameter->second->value < currentParameter->second->max) 
			currentParameter->second->value -= 0.05;
	}
}


void FilterController::setFilter(ImageFilter* filter){
		this->myFilter = filter;
		currentParameter = myFilter->parameters.begin();
}


FilterController::~FilterController()
{
}
