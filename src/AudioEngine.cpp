#include "fmod.hpp"

FMOD::System     *system;
FMOD::Sound      *sound1;
FMOD::Sound      *song1;
FMOD::Channel    *channel = 0;
FMOD_RESULT       result;
unsigned int      version;
void             *extradriverdata = 0;

void openAudio() {
    result = FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->getVersion(&version);
    ERRCHECK(result);

    result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
    ERRCHECK(result);

    result = system->createSound("/resources/audio/goosehonk.mp3", FMOD_DEFAULT, 0, &sound1);
    ERRCHECK(result);

    result = system->createSound("/resources/audio/colorspace.wav", FMOD_DEFAULT, 0, &song1);
    ERRCHECK(result);
}

void playSound() {
    result = system->playSound(sound1, 0, false, &channel);
    ERRCHECK(result);
}

void loopSong() {
  result = system->playSound(song1, 0, false, &channel);
  result = song1->setMode(FMOD_LOOP_ON);
}

void closeAudio() {
	result = sound1->release();
    ERRCHECK(result);=
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);
}
