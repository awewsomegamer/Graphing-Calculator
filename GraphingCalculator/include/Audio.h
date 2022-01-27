#ifndef AUDIO_H
#define AUDIO_H

#include <audio/AL/al.h>
#include <audio/AL/alc.h>
#include <audio/AudioFile.h>
#include <string>
#include <vector>

void* play_sound(void*);

class Audio{
public:
	Audio();

	void update();
	void cleanup();

	double find_pitch(std::vector<double>);
};

#endif
