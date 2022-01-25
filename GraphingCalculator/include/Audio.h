#ifndef AUDIO_H
#define AUDIO_H

#include <audio/AL/al.h>
#include <audio/AL/alc.h>
#include <audio/AudioFile.h>
#include <string>

class Audio{
public:
	Audio();

	void play(double pitch);
	void update();

	double find_pitch(std::vector<double>);
};

#endif
