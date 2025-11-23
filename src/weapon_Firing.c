#include "weapon_Firing.h"
#include "sound_effects.h"
#include <raylib.h>
#include <stdio.h>

// FIX: Use consistent global enemy pointer from enemys.h
// Removed conflicting declarations

typedef struct Bullet {
    Vector3 position;
    Vector3 velocity;
    bool active;
} Bullet;

#define MAX_BULLETS 100
static Bullet bullets[MAX_BULLETS];

void init_Weapon_System(void) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = false;
    }
}

void fire_Weapon(Vector3 origin, Vector3 direction) {
    // Find inactive bullet
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) {
            bullets[i].position = origin;
            bullets[i].velocity = (Vector3){
                direction.x * 50.0f,
                direction.y * 50.0f,
                direction.z * 50.0f
            };
            bullets[i].active = true;
            
            // FIX: Use pre-loaded sound from sound manager
            play_Sound_Effect(SOUND_GUNSHOT);
            break;
        }
    }
}

void update_Bullets(void) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].position.x += bullets[i].velocity.x * GetFrameTime();
            bullets[i].position.y += bullets[i].velocity.y * GetFrameTime();
            bullets[i].position.z += bullets[i].velocity.z * GetFrameTime();
            
            // Check collision with enemy
            // FIX: Use consistent g_Enemy pointer from enemys.h
            if (g_Enemy && g_Enemy->isAlive && 
                CheckCollisionSpheres(bullets[i].position, 0.1f, 
                                     g_Enemy->position, 1.0f)) {
                g_Enemy->health -= 10;
                
                // FIX: Play hit sound
                play_Sound_Effect(SOUND_HIT);
                
                if (g_Enemy->health <= 0) {
                    g_Enemy->isAlive = false;
                    // FIX: Play death sound
                    play_Sound_Effect(SOUND_DEATH);
                }
                bullets[i].active = false;
            }
            
            // Deactivate bullets that go too far
            if (Vector3Distance(bullets[i].position, (Vector3){0,0,0}) > 100.0f) {
                bullets[i].active = false;
            }
        }
    }
}

void draw_Bullets(void) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            DrawSphere(bullets[i].position, 0.1f, YELLOW);
        }
    }
}
