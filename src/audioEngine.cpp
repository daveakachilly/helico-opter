#include "fmod.hpp"

FMOD::System     *system;
FMOD::Sound      *sound1;
FMOD::Sound      *song1;
FMOD::Channel    *songChannel = 0, *fxChannel = 0;
FMOD_RESULT       result;
unsigned int      version;
void             *extradriverdata = 0;

void openAudio() {
	result = FMOD::System_Create(&system);

    result = system->getVersion(&version);

    result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);

    result = system->createSound("/resources/audio/goosehonk.mp3", FMOD_DEFAULT, 0, &sound1);

    result = system->createSound("/resources/audio/colorspace.wav", FMOD_DEFAULT, 0, &song1);
}

void playSound() {
    result = system->playSound(sound1, 0, false, &fxChannel);
}

void loopSong() {
  result = system->playSound(song1, 0, false, &songChannel);
  result = song1->setMode(FMOD_LOOP_OFF);
}

void closeAudio() {
	result = sound1->release();
    result = system->close();
    result = system->release();
}
