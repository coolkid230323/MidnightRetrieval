#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>
#include <SDL_mixer.h>


class Audio
{
public:
    Audio();
    ~Audio();

    void load(const char* filename);
    void play();
    void stop();
    void pause();
    void resume();

private:
    Mix_Chunk* wavChunk;
};

#endif
