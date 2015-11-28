// This is based on sdl-jstest
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.

#include <SDL.h>
#include <assert.h>
#include <curses.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_READS 50
#define PI 3.14159265

typedef double v[3];

v _i = {1.0,   0  , 0};
v _j = {  0, 1.0,   0};
v _k = {  0,   0, 1.0};

double mag(v x) {
	double d = 0;
	d += x[0]*x[0];
	d += x[1]*x[1];
	d += x[2]*x[2];

	return sqrt(d);
}

double gradATan2(double y, double x) {
	return atan2(y, x) * 180 / PI;
}

int main(int argc, char** argv)
{
	// FIXME: We don't need video, but without it SDL will fail to work in SDL_WaitEvent()
	if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}


	atexit(SDL_Quit);
	int joyID = 0;  // TODO: use atoi(argv[1])
	SDL_Joystick* joy = SDL_JoystickOpen(joyID);
	if (!joy) {
		fprintf(stderr, "Unable to open joystick %d\n", joyID);
		exit(2);
	}


	int quit = 0;
	SDL_Event event;
	v motion;
	char axes=0;

	for(int i=0; i<MAX_READS && (axes&7)!=7 && SDL_WaitEvent(&event); i++)
		switch(event.type)
		{
			// Button
			case SDL_JOYBUTTONDOWN:
				//printf("SDL_JOYBUTTONDOWN: joystick: %d button: %d state: %d\n",
				//       event.jbutton.which, event.jbutton.button, event.jbutton.state);
				break;
			case SDL_JOYBUTTONUP:
				//printf("SDL_JOYBUTTONUP: joystick: %d button: %d state: %d\n",
				//       event.jbutton.which, event.jbutton.button, event.jbutton.state);
				break;

			// Motion
			case SDL_JOYAXISMOTION:
				//printf("SDL_JOYAXISMOTION: joystick:%d axis:%d value:%d\n",
				//       event.jaxis.which, event.jaxis.axis, event.jaxis.value);
				if(joyID == event.jaxis.which) {
					motion[event.jaxis.axis] = ((double)event.jaxis.value)/32768.0;
					axes |= 1<<event.jaxis.axis;
				}
				break;
			case SDL_JOYHATMOTION:
				//printf("SDL_JOYHATMOTION: joystick:%d hat:%d value:%d\n",
				//       event.jhat.which, event.jhat.hat, event.jhat.value);
				break;
			case SDL_JOYBALLMOTION:
				//printf("SDL_JOYBALLMOTION: joystick:%d ball:%d x:%d y:%d\n",
				//       event.jball.which, event.jball.ball, event.jball.xrel, event.jball.yrel);
				break;
			case SDL_QUIT:
				i = MAX_READS;
				printf("Recieved interrupt, exiting\n");
				break;
			default:
				fprintf(stderr, "Error: Unhandled event type: %d\n", event.type);
				break;
		}
	double x = -motion[0];
	double y =  motion[1];
	double z = -motion[2];
	printf("Force: (%.4f,%.4f,%.4f)\n", x, y, z);

	double xr = -90 - gradATan2(z, x);
	double yr =  90 + gradATan2(z, y);
	printf("Angle: (%.4f,%.4f)\n", xr, yr);

	SDL_JoystickClose(joy);
}

