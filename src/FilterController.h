#ifndef FILTERCONTROLLER_H_
#define FILTERCONTROLLER_H_

#include "ImageFilter.h"


class FilterController
{
	
	private:
		ImageFilter* myFilter;
		std::map<std::string, FilterParameter*>::iterator currentParameter; // iterator/pointer to current paramtername/value pair
		
	
	public:
		FilterController(ImageFilter* filter);
		void draw();
		void setFilter(ImageFilter* filter);
		inline GLuint filterOutput() { return myFilter->output_texture; };
		void increaseCurrentParameter();
		void decreaseCurrentParameter();
		
		inline void selectNextParameter(){
			currentParameter++;
			if (currentParameter == myFilter->parameters.end())
				currentParameter = myFilter->parameters.begin();
		
		}
		
		
		inline void selectPreviousParameter(){
			if (currentParameter != myFilter->parameters.begin())
				currentParameter--;
			else
				currentParameter = --(myFilter->parameters.end());
		};
		
		
		
		virtual ~FilterController();
};

#endif /*FILTERCONTROLLER_H_*/
