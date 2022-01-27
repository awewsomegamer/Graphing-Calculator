#include "../include/Audio.h"
#include "../include/Log.h"
#include "../include/AudioFile.h"
#include <vector>

// Implement some sort of clean up mechanism for sound files

// Define mutex to be able to synchronize threads
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

std::vector<ALuint> sources;
ALuint buffer;

void Audio::cleanup(){
	for (unsigned int i = 0; i < sources.size(); i++){
		ALuint source = sources[i];

		ALint playing;
		alGetSourcei(source, AL_SOURCE_STATE, &playing);

		if (playing == AL_STOPPED){
			alSourceStop(source);
			alDeleteSources(1, &source);

			sources.erase(sources.begin()+i);
			i--;
		}
	}
}

// Initialize OpenAL
Audio::Audio(){
	ALCdevice *device;
	ALCcontext *context;

	device = alcOpenDevice(NULL);
	if (device == 0){
		log("OpenAL failed to open device", LERROR);
		exit(1);
	}

	context = alcCreateContext(device, NULL);
	if (context == 0){
		log("OpenAL failed to make context", LERROR);
		exit(1);
	}

	alcMakeContextCurrent(context);

	AudioFile<double> file("res/Noise.wav");

	uint8_t channels = file.getNumChannels();
	int32_t sample = file.getNumSamplesPerChannel();
	uint8_t bits = file.getBitDepth();
	std::vector<uint8_t> data;

	file.writePCMToBuffer(data);

	alGenBuffers(1, &buffer);

	ALenum format;

	if (bits == 8){
		if (channels == 1)
			format = AL_FORMAT_MONO8;
		else if (channels == 2)
			format = AL_FORMAT_STEREO8;
	} else if (bits == 16){
		if (channels == 1)
			format = AL_FORMAT_MONO16;
		else if (channels == 2)
			format = AL_FORMAT_STEREO16;
	}

	alBufferData(buffer, format, data.data(), data.size(), sample);
}

// Find a pitch
double Audio::find_pitch(std::vector<double> values){
	double total = 0;

	// Total up difference
	for (unsigned int i = 0; i < values.size()-1; i++){
		double first = values[i];
		double second = values[i+1];

		double difference = first - second;

		total += difference;
	}

	// Calculate average difference
	double avg_difference = total/values.size();

	return avg_difference;
}

// Play noise on set pitch
void* play_sound(void* arg){
	pthread_mutex_lock(&mutex);

	double pitch = *(double*)arg;

	ALuint source;

	alGenSources(1, &source);

	alListener3f(AL_POSITION, 0,0,0);
	alListener3f(AL_VELOCITY, 0,0,0);

	ALfloat orientation[] = {
			1,0,0,
			0,1,0
	};

	alListenerfv(AL_ORIENTATION, orientation);

	alSourcef(source, AL_PITCH, (int)15+pitch);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0,0,0);
	alSource3f(source, AL_VELOCITY, 0,0,0);
	alSourcei(source, AL_LOOPING, AL_FALSE);
	alSourcei(source, AL_BUFFER, buffer);

	sources.push_back(source);

	alSourcePlay(source);

	pthread_mutex_unlock(&mutex);

	return 0;
}
