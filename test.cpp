#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <ncurses.h>

void ncDraw( int yPos, int xPos, int lr ) {
	
	const char* rightPressed = "                       /\\__\n                   .--^    ^^^^--__/\\\n---...          .-^  .               |\n      ^^^---...^       -^-  .  .-.   \\\n         -    t_.--^...       | @ `   \\\n         -^             ^^^---.\\..     \\\n            /   |  `              ^^^^--|..\n                                            ^^^---...";
	const char* leftPressed = "                        /\\__\n               .-.  .--^    ^^^^--__/\\\n---...        | @  ` .                |\n      ^^^---...\\       -^-  .         \\\n               ^^^---...               \\\n                        ^^^---./        \\\n                         --   t_..-*^^--|..\n                            /   |   \\       ^^^---...";
	
	move( yPos, xPos );
	if( lr ) {
		printw( leftPressed );
	} else {
		printw( rightPressed );
	}
}

const char* unPressed = "                        /\\__\n               .-.  .--^    ^^^^--__/\\\n---...        | @  ` .                |\n      ^^^---...\\       -^-  .  .-.    \\\n               ^^^---...      | @ `    \\\n                        ^^^---.\\..      \\\n                                  ^^^^--|..\n                                            ^^^---...";

int main( int argc, char **argv ) {

	Display *display;
	XEvent xevent;
	Window root;
	Window curFocus;
	int revert;
	int alt = 1;

	if( ( display = XOpenDisplay( NULL ) ) == NULL )
		return -1;


	// Get the focussed window, get inputs for that selected window
	XGetInputFocus ( display, &curFocus, &revert );
	XSelectInput( display, 
			curFocus, 
			KeyPressMask | KeyReleaseMask | FocusChangeMask );
	
	int yMax, xMax;
	getmaxyx( stdscr, yMax, xMax );

	while( 1 ) {
		XNextEvent( display, &xevent );										// Listen for events
		switch( xevent.type ) {
			case FocusOut :
				XGetInputFocus ( display, &curFocus, &revert );	// Get new focus
				if ( curFocus == PointerRoot )
					curFocus = root;														// Change focus to root
				XSelectInput( display, 
						curFocus, 
						KeyPressMask | KeyReleaseMask | FocusChangeMask );
				break;
			case KeyPress :
				std::cout << "key pressed is " << xevent.xkey.keycode << "\n";
				break;
			case KeyRelease :
				std::cout << "key unpressed in " << curFocus << "\n";
				break;
		}
	}
	
	return 0;
}
