#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "../engine/world_definition/gameWorld.h"


class Event {

public:
	int start_time, duration;
	bool persist;

	Event(int duration, bool persist=false); // duration is in seconds
	void set_start(int start_time);
	bool time_to_exec(int current_time);
	virtual void execute() = 0;

};

class SampleEvent : public Event {
private:
	std::string data;
public:
	SampleEvent(int duration, std::string data, bool persist=false);
	void execute();
};

class AutoPixEvent : public Event {

public:
	GameWorld *gw;
	AutoPixEvent(GameWorld *gw);
	void execute();

};

/*
**  This class defines a Clock object whose purpose is to keep track of 
**  total running time as well as event timing.
*/

class Clock {

private:

	// events
	std::vector<Event*> events;

	Uint32 start_time;  // all time measured in milliseconds
	Uint32 now;
	Uint32 last_time;   // time during previous frame

	int fps;		    // set the desired frames per second
	Uint32 ms_per_frame;   // time / frame, ms per frame
	Uint32 counted_frames; // number of frames that have passed 

public:

	Clock(Uint32 fps=60);
	void tick();
	float avgFPS();
	Uint32 time();
	void add_event(Event* e);

};