#ifndef FILTERCHAIN_H_
#define FILTERCHAIN_H_

#include <vector>
#include "ImageFilter.h"

class FilterChain
{
	
private:
	std::vector<ImageFilter*> filters; 
	
	
	
public:
	FilterChain();
	inline int numFilters() {return filters.size();};
	void attachFilter(ImageFilter* f);
	void attachNewFilter(const char*, int sx, int sy);
	GLuint apply(GLuint inputTexture);
	inline ImageFilter* getFilter(unsigned int index) {if (index <  filters.size() ) return filters[index];};
	virtual ~FilterChain();
};

#endif /*FILTERCHAIN_H_*/
