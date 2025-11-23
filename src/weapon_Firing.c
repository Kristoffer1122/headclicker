#include "weapon_Firing.h"
#include "sound_effects.h"
#include <raylib.h>
#include <stdio.h>

// BUG: Conflicting global enemy declarations!
// This file declares enemy differently than enemys.h
extern Enemy enemy;  // BUG: This is a struct, not a pointer
Enemy *b_Enemy = &enemy;  // BUG: Taking address of extern struct

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
            
            // BUG: Sound loaded every shot - memory leak
            play_Sound_Effect("resources/gunshot.wav");
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
            // BUG: Using b_Enemy which points to wrong enemy structure
            if (b_Enemy && CheckCollisionSpheres(bullets[i].position, 0.1f, 
                                                  b_Enemy->position, 1.0f)) {
                b_Enemy->health -= 10;
                if (b_Enemy->health <= 0) {
                    b_Enemy->isAlive = false;
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
