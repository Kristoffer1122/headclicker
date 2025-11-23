#include "sound_effects.h"
#include <raylib.h>
#include <stdio.h>

// BUG: No sound manager - sounds are loaded every time
void play_Sound_Effect(const char *filename) {
    // BUG: LoadSound is called every time without unloading
    // This causes memory leaks
    Sound sound = LoadSound(filename);
    
    // BUG: No null check after LoadSound
    PlaySound(sound);
    
    // BUG: Sound is never unloaded - memory leak!
    // Should call UnloadSound(sound) but we can't do it here
    // because the sound needs to finish playing
}

void init_Sound_System(void) {
    InitAudioDevice();
}

void cleanup_Sound_System(void) {
    CloseAudioDevice();
}
