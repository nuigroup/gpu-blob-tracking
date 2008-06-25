#ifndef IMAGEFILTER_H_
#define IMAGEFILTER_H_

#include "ShaderProgram.h"

#include <map>
#include <string>




class FilterParameter{
public:
	const char* name;
	float value;
	float max;
	float min;
	
	inline FilterParameter(const char* name, float val, float minVal, float maxVal) { this->name=name; value=val; min=minVal; max=maxVal;  };

};

//TODO: make constructor that reads filter description (shader sources, input parameters etc.) from file
//      add parameters
class ImageFilter		
{
	private:
		//should maybe go wih image..bu for now we are onlt passing gl texture handles...
		int res_x, res_y;
	
		ShaderProgram* shader;
		GLuint output_buffer;
		//GLuint output_texture;
		
		const char* name;
		
		
		void parseXML(const char* fname);
	
	
	public:
		GLuint output_texture;
		std::map<std::string, FilterParameter*> parameters;
		
		ImageFilter(const char* fname, int outputWidth, int outputHeight);
		
		GLuint apply(GLuint inputTexture);
		
		virtual ~ImageFilter();
};




#endif /*IMAGEFILTER_H_*/
