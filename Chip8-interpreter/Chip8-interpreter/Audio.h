#pragma once

#include <al.h>
#include <alc.h>
#include <alext.h>

class Audio {
public:
    Audio();
    ~Audio();

    void playBeep() const;
    void stopAudio() const;

private:
    ALuint m_source;
    ALuint m_buffer;
    ALCdevice* m_device;
    ALCcontext* m_context;

    void createBuffer();
};