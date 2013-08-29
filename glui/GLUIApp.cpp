/*
 *  GLUIApp.cpp
 *  OpenGL
 *
 *  Created by Nelson El-Hage on Fri Sep 20 2002.
 *
 */

#include "GLUI.h"

std::list<GLUIObject *> GLUIApp::Objects;
int GLUIApp::Width, GLUIApp::Height;
GLUIApp * GLUIApp::GlobalApp;

GLUIApp::GLUIApp(int width, int height)
{
	GlobalApp = this;
	Width = width;
	Height = height;
	
	SDL_ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0);
	atexit(SDL_Quit);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_ASSERT(SDL_SetVideoMode(width,height,32,SDL_ANYFORMAT | SDL_OPENGL) != NULL);
	SDL_WM_SetCaption("GLUI Application",NULL);

	SDL_ShowCursor(true);
	glShadeModel(GL_SMOOTH);

	glClearColor(0.0,0.0,0.5,0);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0,width,0,height,-1,1);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	if(!GLUI2D::Init())
		exit(-1);
}

GLUIApp::~GLUIApp()
{
}

void GLUIApp::Add(GLUIObject & e)
{
	Objects.push_front(&e);
}

void GLUIApp::Delete(GLUIObject & o)
{
	SDL_Event e;
	e.type = SDL_USEREVENT;
	e.user.data1 = &o;
	SDL_PushEvent(&e);
}

int GLUIApp::Run()
{
	SDL_Event evt;
	bool Done = false;
	while(!Done)
	{
		if(SDL_PollEvent(&evt))
		{
			if(evt.type == SDL_QUIT) Done = true;
			HandleEvent(evt);
		}
		else
		{
			glClear(GL_COLOR_BUFFER_BIT);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glMatrixMode(GL_PROJECTION);

			
			for(std::list<GLUIObject*>::reverse_iterator itr = Objects.rbegin();
				itr != Objects.rend();itr++)
			{
				//Windows alter the projection/viewport, so it is neccessary
				//to reset it for every sub-object
				glPushMatrix();
				glMatrixMode(GL_MODELVIEW);				
				(*itr)->Draw();
				glMatrixMode(GL_PROJECTION);
				glPopMatrix();
				glViewport(0,0,Width,Height);
			}
				
			SDL_GL_SwapBuffers();
		}
	}
	GLUI2D::Shutdown();
	SDL_Quit();
	return 0;
}

void GLUIApp::HandleEvent(SDL_Event & evt)
{
	Uint16 x = evt.button.x,
		   y = Height - evt.button.y;
	
	switch(evt.type)
	{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONUP:
			Objects.front()->ProcessEvent(evt);
			break;
		case SDL_MOUSEBUTTONDOWN:
			//Log.Write("Mouse button down @ (%d,%d)",x,y);
			for(std::list<GLUIObject*>::iterator itr = Objects.begin();
				itr != Objects.end();itr++)
			{
				if((*itr)->GetBounds().Contains(x,y))
				{
					(*itr)->ProcessEvent(evt);
					(*itr)->SetFocus(true);
										
					if(itr != Objects.begin())
					{
						Objects.front()->SetFocus(false);
						GLUIObject * obj = *itr;
						Objects.erase(itr);
						Objects.push_front(obj);
					}
					break;
				}
				else
					(*itr)->SetFocus(false);
			}
			break;
		case SDL_USEREVENT:
			Objects.remove((GLUIObject*)evt.user.data1);
			break;
	}
}

void GLUIApp::Exit()
{
	SDL_Event e;
	e.type = SDL_QUIT;
	SDL_PushEvent(&e);
}

