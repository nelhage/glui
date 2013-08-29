/*
 *  GLUIWindow.h
 *  OpenGL
 *
 *  Created by Nelson El-Hage on Fri Sep 20 2002.
 *  The GLUIWindow class represents a window in the GLUI windowing system
 */

#ifndef __GLUIWINDOW_H__
#define __GLUIWINDOW_H__

//#include "GLUI.h"

class GLUIWindow : public GLUIObject
{
	public:
		enum WindowState
		{
		GLUI_MAXIMIZED,
		GLUI_MINIMIZED,
		GLUI_NORMAL
		};

		void SetState(WindowState s);
	
	protected:
		std::string Caption;
		int X,Y;
		int Width,Height;
		WindowState State;
		bool Dragging;			//is the window being dragged?

		std::list<GLUIControl*> Controls;

		//These textures are used to draw different parts of the window
		static Texture Titlebar;
		static Texture Close;
		static Texture Maximize;
		static Texture Minimize;
		static Texture UnMaximize;
		static Texture UnMinimize;

		static bool TexturesLoaded;

		virtual void DrawContents(int w, int h);	//Draw the inside of the window
													//override to add custom content
	public:		
		GLUIWindow(std::string caption, int x, int y, int w, int h);
		virtual ~GLUIWindow();

		virtual void SetFocus(bool);

		virtual void Draw();
		virtual void ProcessEvent(SDL_Event & e);

		virtual std::string GetText() {return Caption;}
		virtual void SetText(std::string txt) {Caption = txt;}

		virtual GLUIRect GetBounds();

		virtual void SetPosition(int x, int y) {X = x; Y = y;}

		virtual void Add(GLUIControl &ctrl) {Controls.push_front(&ctrl);}
};

#endif
