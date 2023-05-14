#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <cmath>

class Xwindow {
	Display *d;
	Window w;
	int s;
	GC gc;
	unsigned long colours[10];
	int width, height;

	public:
	Xwindow(int width=500, int height=500);  // Constructor; displays the window.
	~Xwindow();                              // Destructor; destroys the window.

	enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown, Pink};


	// Draws a string
	void drawString(int x, int y, std::string msg);

	// Draws a rectangle
	void fillRectangle(int x, int y, int width, int height, int colour=Black);

	void drawLine(int x1, int y1, int x2, int y2);


};

#endif
