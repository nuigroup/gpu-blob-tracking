#include "FilterChain.h"

FilterChain::FilterChain()
{

}



void FilterChain::attachFilter(ImageFilter* f)
{
	filters.push_back(f);

}


void FilterChain::attachNewFilter(const char* fname, int sx, int sy)
{
	filters.push_back ( new ImageFilter(fname, sx,sy ) );

}


GLuint FilterChain::apply(GLuint inputTexture)
{
	GLuint tex = inputTexture;
	for(int i=0; i< filters.size()  ; i++ ){
			tex = filters[i]->apply(tex);
	}
	return tex;
	
}


FilterChain::~FilterChain()
{
}


