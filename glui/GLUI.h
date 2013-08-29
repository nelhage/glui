/*
 *  GLUI.h
 *  GLUI
 *
 *  Created by Nelson El-Hage on Sat Sep 21 2002.
 *  This is the main header file for GLUI. It includes
 *	all the GLUI class headers, and defines the GLUIRect
 *	utility class
 *
 */

#ifndef __GLUI_H__
#define __GLUI_H__

#include <string>
#include <list>

#include "SDL.h"
#include "SDL_opengl.h"

#include "App_Log.h"
#include "Vector.h"
#include "Texture.h"

extern CApp_Log Log;

#define ABS(x) ((x)<0 ? (-(x)) : (x))
//returns a random float 0 <= RAND <= 1
#define RAND ABS((float)(rand() - rand())/RAND_MAX)
//returns a random float x <= f <= y
#define RANDFLOAT(x,y) (RAND * ABS((y)-(x)) + x)

#define SDL_ASSERT(x) if(!(x)) \
{ \
				Log.Write("%s: %s",#x,SDL_GetError()); \
					exit(1);\
}

#define CASE(c,a) case c: a; break;

struct GLUIRect
{
	int x,y,w,h;

	GLUIRect(int nx, int ny, int nw, int nh) : x(nx), y(ny), w(nw), h(nh) {}

	bool Intersects(GLUIRect & r)
	{
		return (ABS((x+w/2)-(r.x+r.w)/2) <= (w/2 + r.w/2)) &&
		(ABS((y+h/2)-(r.y+r.h)/2) <= (h/2 + r.h/2));
	}

	bool Contains(int px, int py)
	{
		return (px > x) && (px < (x+w)) && (py > y) && (py < (y+h));
	}
};

#include "GLUI2D.h"
#include "GLUIObject.h"
#include "GLUIControl.h"
#include "GLUIApp.h"
#include "GLUIWindow.h"
#include "GLUIScrollWindow.h"
#include "GLUILabel.h"


#endif
