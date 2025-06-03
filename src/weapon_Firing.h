#ifndef BULLETS_H
#define BULLETS_H

#include "raylib.h"
#include "raymath.h"
#include <stdbool.h>

// Define the Bullet structure
typedef struct Bullet {
    Vector3 position;      // Current position
    Vector3 direction;     // Normalized direction vector
    BoundingBox bulletRect;
    float speed;           // Speed in units per second
    float lifetime;        // How long the bullet exists (in seconds)
    float radius;          // Collision radius
    bool active;           // Whether the bullet is active or not
    Color color;           // Bullet color
} Bullet;

// Define bullet pool to avoid constant allocation/deallocation
#define MAX_BULLETS 100    // Maximum number of bullets active at once

typedef struct BulletPool {
    Bullet bullets[MAX_BULLETS];
    int count;             // Number of active bullets
} BulletPool;

// Function declarations (prototypes)
void InitBulletPool(BulletPool *pool);
void SpawnBullet(BulletPool *pool, Vector3 position, Vector3 direction, float speed);
void UpdateBullets(BulletPool *pool, float deltaTime);
void DrawBullets(BulletPool *pool);
void FireWeapon(Camera3D *camera, BulletPool *bulletPool);
bool CheckBulletCollision(Bullet *bullet, Vector3 targetPos, float targetRadius);

// You can also declare a global bullet pool here if you want
extern BulletPool g_bulletPool;  // extern means it's defined elsewhere

#endif // BULLETS_H
