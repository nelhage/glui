/*
 *  GLUIWindow.cpp
 *  OpenGL
 *
 *  Created by Nelson El-Hage on Fri Sep 20 2002.
 *  Copyright (c) 2002 __MyCompanyName__. All rights reserved.
 *
 */

#include "GLUI.h"

Texture GLUIWindow::Titlebar;
Texture GLUIWindow::Close;
Texture GLUIWindow::Maximize;
Texture GLUIWindow::Minimize;
Texture GLUIWindow::UnMaximize;
Texture GLUIWindow::UnMinimize;

bool GLUIWindow::TexturesLoaded = false;

void GLUIWindow::SetState(WindowState s)
{
	State = s;
}

void GLUIWindow::SetFocus(bool Focus)
{
	HasInputFocus = Focus;
	if(!Focus)
	{
		for(std::list<GLUIControl *>::iterator itr = Controls.begin();
			itr != Controls.end();itr++)
		(*itr)->SetFocus(false);		
	}
}

void GLUIWindow::DrawContents(int w, int h)
{
	for(std::list<GLUIControl *>::iterator itr = Controls.begin();
		itr != Controls.end();itr++)
	{
		(*itr)->Draw();
	}
}

GLUIWindow::GLUIWindow(std::string caption, int x, int y, int w, int h) :
	Caption(caption), X(x), Y(y), Width(w), Height(h), State(GLUI_NORMAL), Dragging(false)
{
		if(!TexturesLoaded)
		{
			Titlebar.Load("titlebar.png");
			Close.Load("Close.png");
			Maximize.Load("Maximize.png");
			Minimize.Load("Minimize.png");
			UnMaximize.Load("UnMaximize.png");
			UnMinimize.Load("UnMinimize.png");
			TexturesLoaded = true;
		}
}

GLUIWindow::~GLUIWindow() {}

void GLUIWindow::Draw()
{
	int x,y,w,h;
	float alpha = HasInputFocus ? 1. : .75;
	
	if(State == GLUI_MAXIMIZED)
	{
		x=y=0;
		GLUIRect dim = GLUIApp::getSize();
		w = dim.w;
		h = dim.h;
	}
	else
	{
		x = X;
		y = Y;
		w = Width;
		h = Height;
	}
	
	if(State != GLUI_MINIMIZED)
	{
		glBindTexture(GL_TEXTURE_2D,0);

		if(HasInputFocus)
		{
			glColor4f(0.0,0.0,0.0,1./6.);
			for(int i=1;i<=6;i++)
				GLUI2D::Rect(x+6,y-i,w-6+i,h-6+i);		//Drop Shadow
		}
		
		glColor4f(0.5,0.0,0.0,alpha);
		GLUI2D::Rect(x,y,w,h-20);
	}

	glColor4f(1.0,1.0,1.0,alpha);
	Titlebar.Bind();
	GLUI2D::Rect(x,y+h-20,w,20);

	GLUI2D::Text(x+4,y+h-18,Caption.c_str());
	
	Close.Bind();
	GLUI2D::Rect(x+w-18,y+h-18,16,16);

	if(State != GLUI_MAXIMIZED)
		Maximize.Bind();
	else
		UnMaximize.Bind();
	GLUI2D::Rect(x+w-36,y+h-18,16,16);

	if(State != GLUI_MINIMIZED)
		Minimize.Bind();
	else
		UnMinimize.Bind();
	GLUI2D::Rect(x+w-54,y+h-18,16,16);

	if(State != GLUI_MINIMIZED)
	{
		glViewport(x,y,w,h-20);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,w,0,h-20,-1,1);
		glMatrixMode(GL_MODELVIEW);
		DrawContents(w,h);
	}
}

void GLUIWindow::ProcessEvent(SDL_Event & evt)
{
	int x,y,w,h,xrel,yrel;
	int ScreenW = GLUIApp::getSize().w,
		ScreenH = GLUIApp::getSize().h;
	if(State == GLUI_MAXIMIZED)
	{
		x = y = 0;
		w = ScreenW;
		h = ScreenH;
	}
	else
	{
		x = X;
		y = Y;
		w = Width;
		h = Height;
	}
	
	switch(evt.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			xrel = evt.button.x - x;
			yrel = ScreenH - evt.button.y - y;
			//Log.Write("Click (%d,%d)",xrel,yrel);
			//close button
			if(GLUIRect(w-18,h-18,16,16).Contains(xrel,yrel))
			{
				//Log.Write("Close button clicked.");
				GLUIApp::GlobalApp->Delete(*this);
			}
			//Maximize
			else if(GLUIRect(w-36,h-18,16,16).Contains(xrel,yrel))
			{
				if(State == GLUI_MAXIMIZED)
					State = GLUI_NORMAL;
				else
					State = GLUI_MAXIMIZED;
			}
			//Minimize
			else if(GLUIRect(w-54,h-18,16,16).Contains(xrel,yrel))
			{
				if(State == GLUI_MINIMIZED)
					State = GLUI_NORMAL;
				else
					State = GLUI_MINIMIZED;
			}
			//other click in the titlebar - drag
			else if(GLUIRect(0,h-20,w,20).Contains(xrel,yrel) && State != GLUI_MAXIMIZED)
				Dragging=true;					
			break;
		case SDL_MOUSEBUTTONUP:
			Dragging=false;
			break;
		case SDL_MOUSEMOTION:
			if(Dragging)
			{
				X += evt.motion.xrel;
				Y -= evt.motion.yrel;
				if(X > ScreenW) X = ScreenW;
				if(Y > ScreenH) Y = ScreenH;
			}
			break;				
	}
}

GLUIRect GLUIWindow::GetBounds()
{
	switch(State)
	{
		case GLUI_NORMAL:
			return GLUIRect(X,Y,Width,Height);
		case GLUI_MINIMIZED:
			return GLUIRect(X,Y+Height-20,Width,20);
		case GLUI_MAXIMIZED:
			return GLUIApp::getSize();
		default:
			Log.Write("Invalid state in window %s: %d",Caption.c_str(),State);
			return GLUIRect(0,0,0,0);
	}
}

