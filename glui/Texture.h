#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "SDL.h"
//#if defined(__APPLE__) && defined(__MACH__)
//#include "SDL_image/SDL_Image.h"
//#else
#include "SDL_image.h"
//#endif
#include "SDL_opengl.h"

class Texture
{
	private:
		GLuint texid;
	
	public:
		Texture();		
		~Texture();
		
		bool Load(const char * file, GLenum MinFilter = GL_NEAREST, 
    				GLenum MagFilter = GL_NEAREST, bool UseMipMaps = false,
   					bool TileS = true, bool TileT = true);
		bool Load(SDL_Surface * data, GLenum MinFilter = GL_NEAREST, 
  					GLenum MagFilter = GL_NEAREST, bool UseMipMaps = false,
       				bool TileS = true, bool TileT = true);
		
		void Bind() {glBindTexture(GL_TEXTURE_2D, texid);}
};


#endif	//__TEXTURE_H__
