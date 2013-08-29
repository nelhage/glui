/*
 *  GLUIScrollWindow.h
 *  OpenGL
 *
 *  Created by Nelson El-Hage on Fri Sep 20 2002.
 *  This subclass of GLUIWindow is a scrollable window
 */

#ifndef __GLUISCROLLWINDOW_H__
#define __GLUISCROLLWINDOW_H__

//#include "GLUI.h"

class GLUIScrollWindow : public GLUIWindow
{
	public:
		GLUIScrollWindow(std::string caption, int x, int y, int w, int h);
		virtual ~GLUIScrollWindow();

		virtual void Draw();
		virtual void ProcessEvent(SDL_Event &e);	
};

#endif
