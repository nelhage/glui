/*
 *  GLUILabel.h
 *  GLUI
 *
 *  Created by Nelson El-Hage on Sun Sep 22 2002.
 *	The GLUILabel is a simple text label inside a GLUIWindow
 */

#ifndef __GLUILABEL_H__
#define __GLUILABEL_H__

class GLUILabel : public GLUIControl
{
	protected:
		int X,Y;
		std::string Caption;

		GLUIWindow * Parent;
	public:
		GLUILabel(int x, int y, std::string text, GLUIWindow & parent);
		virtual ~GLUILabel();
	
		virtual void Draw();
		virtual void ProcessEvent(SDL_Event & e);
	
		virtual std::string GetText() {return Caption;}
		virtual void SetText(std::string txt) {Caption = txt;}

		virtual GLUIRect GetBounds() {return GLUIRect(X,Y,GLUI2D::Length(Caption.c_str()),16);}
	
		virtual void SetPosition(int x, int y) {X = x; Y = y;}	
};

#endif
