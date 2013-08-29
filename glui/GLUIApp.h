/*
 *  GLUIApp.h
 *  OpenGL
 *
 *  Created by Nelson El-Hage on Fri Sep 20 2002.
 *  The GLUIApp class is the core of every GLUI App. It's run() method is a GLUI
 *  program's main loop
 */

#ifndef __GLUIAPP_H__
#define __GLUIAPP_H__

//#include "GLUI.h"

class GLUIApp
{
	private:
		static std::list<GLUIObject *> Objects;
		static int Width,Height;
		
	public:
		GLUIApp(int w, int h);		//create a GLUIApp with the specifed screen size
		~GLUIApp();

		void Add(GLUIObject & obj);	//Add a window to the app
		void Delete(GLUIObject & obj);	//remove an object

		int Run();					//The main event loop

		void HandleEvent(SDL_Event & evt);

		static void Exit();				//safely shutdown the app

		static GLUIRect getSize() {return GLUIRect(0,0,Width,Height);}

		static GLUIApp * GlobalApp;
};

#endif
