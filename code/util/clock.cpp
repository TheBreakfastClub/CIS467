#include "clock.h"
#include <iostream>


// C L O C K //

Clock::Clock(Uint32 fps) : events()
{
	start_time = SDL_GetTicks();
	now = SDL_GetTicks() - start_time;
	last_time = start_time;

	counted_frames = 0;

	this->fps = fps;
	ms_per_frame = 1000 / fps; // how long (ms) we should spend in each frame
}

/* Add an event to the event queue */
void Clock::add_event(Event* e, std::string name)
{
	e->name = name;
	e->set_start(time());
	events.push_back(e);
}

Uint32 Clock::time() { return SDL_GetTicks() - start_time; }

void Clock::tick()
{
	// first check to see if it's time to execute any events
	if (!events.empty()) {
		Uint32 t = time();
		std::vector<Event*>::iterator it = events.begin();
		while (it != events.end()) { 
			if ((*it)->time_to_exec(t)) {
				(*it)->execute();
				if (!(*it)->persist) { // remove non-persistent events
					Event* e = *it;
					it = events.erase(it);
					delete e;
				}
				else {
					(*it)->start_time = time();
				}
			}
			// a deletion that causes the collection to be empty will point to end(). check before indenting
			if (it == events.end()) break;
			it++;
		}
	}
	
	// set new times and increment frame count
	now = time();
	counted_frames++;

	/*
	// limit frame rate if frame ended early
	int frame_time = now - last_time;
	std::cout << "Frame time was: " << std::to_string(frame_time) << "(supposed to be " << std::to_string(ms_per_frame) << ")" << std::endl;
	if (frame_time < ms_per_frame) {
		std::cout << "   Delaying for " << std::to_string(ms_per_frame - frame_time) << "ms\n";
		SDL_Delay(ms_per_frame - frame_time);
	}
	//else std::cout << "\nWE WENT OVER FRAME TIME\n" << std::endl;
	std::cout << "   Total time in frame: " << std::to_string(frame_time + (ms_per_frame - frame_time)) << std::endl;
	last_time = now;
	*/
	SDL_Delay(16);
}

float Clock::avgFPS()
{
	float avg = counted_frames / (time() / 1000.0f);
	return (avg > 2000000 ? 0.0f : avg); // initial avg might be super high, cap it
}

bool Clock::has_event(std::string name)
{
	for (Event *e : events) {
		if (e->name == name) return true;
	}
	return false;
}


// E V E N T S

// Define the base Event class. Completely takes care of timing. Child classes only exist
// in order to define the data stored and the execute() function.
Event::Event(int duration, bool persist, std::string name) 
 : duration(duration*1000), persist(persist) {}

/* Each event must know when it was started (to compare against duration) */
void Event::set_start(int start_time)
{
	this->start_time = start_time;
}

/* Return true if it is time to execute this event */
bool Event::time_to_exec(int current_time)
{
	return (start_time + duration) <= current_time;
}


// Here we define an example Event child class. Just for testing the system.
SampleEvent::SampleEvent(int duration, std::string data, bool persist) 
 : Event(duration, persist), data(data) {}

void SampleEvent::execute()
{
	std::cout << data << std::endl;
}

// Auto Pixelation Event: Another sample Event subclass that shows dealing with some real game data
AutoPixEvent::AutoPixEvent(GameWorld *gw) : Event(1, true) 
{ this->gw = gw; }

void AutoPixEvent::execute()
{
//	if (rand() % 2) {
//		gw->next_resolution();
//	}
//	else {
//		gw->prev_resolution();
//	}
}


// Use this to control the duration of when a Character is "hit" for (incomplete: probably going to just use AnonEvent)
CharHitEvent::CharHitEvent(int duration, Character *c) : c(c), Event(duration, false) {}
void CharHitEvent::execute() {}


// For small events that can can quickly be implemented with a lambda, define a generic event type
AnonEvent::AnonEvent(int duration, std::function<void()> f, bool persist)
 : f(f), Event(duration, persist) {}

void AnonEvent::execute() 
{ 
	f();
}
