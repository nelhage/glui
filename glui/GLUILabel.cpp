/*
 *  GLUILabel.cpp
 *  GLUI
 *
 *  Created by Nelson El-Hage on Sun Sep 22 2002.
 *  Copyright (c) 2002 __MyCompanyName__. All rights reserved.
 *
 */

#include "GLUI.h"

GLUILabel::GLUILabel(int x, int y, std::string text, GLUIWindow & parent) :
			X(x), Y(y), Caption(text), Parent(&parent)
{
	Parent->Add(*this);
}

GLUILabel::~GLUILabel(){}

void GLUILabel::ProcessEvent(SDL_Event & e)
{
}

void GLUILabel::Draw()
{
	GLUI2D::Text(X,Y,Caption.c_str());
}
