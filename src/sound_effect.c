#include "sound_effects.h"
#include <raylib.h>
#include <stdio.h>
#include <stdbool.h>

// FIX: Sound manager with pre-loaded sounds
static Sound sounds[SOUND_COUNT];
static bool sounds_loaded = false;

// Sound file paths
static const char* sound_files[SOUND_COUNT] = {
    "resources/gunshot.wav",
    "resources/hit.wav",
    "resources/death.wav"
};

void init_Sound_System(void) {
    InitAudioDevice();
    
    // FIX: Pre-load all sounds at initialization
    for (int i = 0; i < SOUND_COUNT; i++) {
        sounds[i] = LoadSound(sound_files[i]);
        
        // FIX: Add error handling for failed loads
        if (!IsSoundValid(sounds[i])) {
            fprintf(stderr, "Warning: Failed to load sound: %s\n", sound_files[i]);
        }
    }
    
    sounds_loaded = true;
}

// FIX: Play pre-loaded sound by ID instead of loading each time
void play_Sound_Effect(SoundEffect effect) {
    // FIX: Validate sound effect ID
    if (effect < 0 || effect >= SOUND_COUNT) {
        fprintf(stderr, "Error: Invalid sound effect ID: %d\n", effect);
        return;
    }
    
    // FIX: Check if sounds are loaded
    if (!sounds_loaded) {
        fprintf(stderr, "Error: Sound system not initialized\n");
        return;
    }
    
    // FIX: Check if sound is valid before playing
    if (IsSoundValid(sounds[effect])) {
        PlaySound(sounds[effect]);
    } else {
        fprintf(stderr, "Error: Sound %d is not valid\n", effect);
    }
}

void cleanup_Sound_System(void) {
    // FIX: Unload all pre-loaded sounds
    if (sounds_loaded) {
        for (int i = 0; i < SOUND_COUNT; i++) {
            if (IsSoundValid(sounds[i])) {
                UnloadSound(sounds[i]);
            }
        }
        sounds_loaded = false;
    }
    
    CloseAudioDevice();
}
