//
//  AudioEngine.hpp
//  Helico-opter
//
//  Created by David McIntyre on 2/1/18.
//

#ifndef AudioEngine_hpp
#define AudioEngine_hpp

#include <stdio.h>

#include "fmod.hpp"

class AudioEngine 
{   
public :
    void openAudio();
    void playSound();
    void loopSong();
    void closeAudio();
};


#endif /* AudioEngine_hpp */
