#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include "../engine/world_definition/gameWorld.h"
#include "../engine/world_definition/character.h"


class Event {

public:
	int start_time, duration;
	std::string name;
	bool persist;

	Event(int duration, bool persist=false, std::string name="none"); // duration is in seconds
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

class CharHitEvent : public Event {
public:
	CharHitEvent(int duration, Character *c);
	Character *c;
	void execute();

};

class AnonEvent : public Event {
public:
	AnonEvent(int duration, std::function<void()> f, bool persist=false);
	std::function<void()> f;
	void execute();
};


/*
**  This class defines a Clock object whose purpose is to keep track of 
**  total running time as well as event timing.
*/

class Clock {

private:

	// events
	

	Uint32 start_time;  // all time measured in milliseconds
	Uint32 now;
	Uint32 last_time;   // time during previous frame

	int fps;		    // set the desired frames per second
	Uint32 ms_per_frame;   // time / frame, ms per frame
	Uint32 counted_frames; // number of frames that have passed 

public:
	std::vector<Event*> events;
	Clock(Uint32 fps=60);
	void tick();
	float avgFPS();
	Uint32 time();
	void add_event(Event* e, std::string name="none");
	bool has_event(std::string name);

};