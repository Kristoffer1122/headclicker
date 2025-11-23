#ifndef SOUND_EFFECTS_H
#define SOUND_EFFECTS_H

// Sound effect identifiers
typedef enum {
    SOUND_GUNSHOT = 0,
    SOUND_HIT,
    SOUND_DEATH,
    SOUND_COUNT
} SoundEffect;

// Initialize sound system and pre-load all sounds
void init_Sound_System(void);

// Play a pre-loaded sound effect by ID
void play_Sound_Effect(SoundEffect effect);

// Cleanup sound system and unload all sounds
void cleanup_Sound_System(void);

#endif // SOUND_EFFECTS_H
