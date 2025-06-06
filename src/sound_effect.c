
#include "sound_effects.h"
#include <raylib.h>

void play_Sound_Effect(void) {
  Sound sound =
      LoadSound("../resources/soundeffects/Realistic Gunshot Sound Effect.mp3");
  SetSoundVolume(sound, 20.0f);
  PlaySound(sound);
  if (!IsSoundPlaying(sound)) {
    StopSound(sound);
    PlaySound(sound);
  } else {
    PlaySound(sound);
  }
}

void play_Ambient_Sounds(void) {
  InitAudioDevice();
  Sound sound = LoadSound("../resources/soundeffects/ambientSounds.mp3");
  SetSoundVolume(sound, 10.0f);
  PlaySound(sound);
}
