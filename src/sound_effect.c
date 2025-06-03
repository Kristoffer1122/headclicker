
#include "sound_effects.h"
#include <raylib.h>

void play_Sound_Effect(void) {
  InitAudioDevice();
 Sound sound = LoadSound("../resources/soundeffects/Realistic Gunshot Sound Effect.mp3");
  PlaySound(sound);
  if (IsSoundPlaying(sound)){
  ResumeSound(sound);
  } else {
  StopSound(sound);
  UnloadSound(sound);
  }
  CloseAudioDevice();
}
