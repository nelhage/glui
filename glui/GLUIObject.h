/*
 *  GLUIObject.h
 *  OpenGL
 *
 *  Created by Nelson El-Hage on Fri Sep 20 2002.
 *  The GLUIObject class is the abstract base class of all GLUI graphical objects
 */
#ifndef __GLUIOBJECT_H__
#define __GLUIOBJECT_H__


//#include "GLUI.h"

class GLUIObject
{
	protected:
		bool HasInputFocus;			//Does this object have the input focus,
									//i.e. do keyboard events get directed to us?
	public:
		GLUIObject() : HasInputFocus(false){};

		virtual ~GLUIObject() {};
		
		virtual void ProcessEvent(SDL_Event &e)=0;
		virtual void Draw()=0;

		virtual void SetFocus(bool HasFocus) {HasInputFocus = HasFocus;}
		virtual bool HasFocus() {return HasInputFocus;}

		virtual std::string GetText()=0;		//Every GLUIObject has some text string associated
		virtual void SetText(std::string txt)=0;	//with it, like a caption or button label

		virtual GLUIRect GetBounds()=0 ;			//return a rectangle bounding the shape

		virtual void SetPosition(int x, int y)=0;
		
};

#endif
