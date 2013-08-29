#include "GLUI.h"

#include "SDL.h"
#include "App_Log.h"
#include <stdio.h>
#include <stdlib.h>

CApp_Log Log("GLUI.log");

int main(int argc, char *argv[])
{
	GLUIApp g(800,800);
	GLUIWindow w1("Test window 1",10,10,300,300);
	w1.SetFocus(false);

	GLUIWindow w2("Test Window 2", 250,300,300,150);
	w2.SetFocus(true);

	g.Add(w1);
	g.Add(w2);

	GLUILabel l1(50,250,"Hello world!",w1);
	GLUILabel l2(10,40,"Label 2",w2);
	return g.Run();
}
