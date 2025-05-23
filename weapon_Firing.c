// ----------------------------------------------------------------------------------
// to build use: gcc *.c -o headclicker -lraylib -lGL -lm -lpthread -ldl -lrt
// -lX11
//
//		HEADCLICKER
//
//
// ----------------------------------------------------------------------------------
#include "weapon_Firing.h"
#include <raylib.h>

// global bullet pool  NOTE: if i want enemys to be able to shoot too.
BulletPool g_bulletPool;

// Initialize the bullet pool
void InitBulletPool(BulletPool *pool) {
  pool->count = 0;
  for (int i = 0; i < MAX_BULLETS; i++) {
    pool->bullets[i].active = false;
  }
}

// spawn bullet
void SpawnBullet(BulletPool *pool, Vector3 position, Vector3 direction,
                 float speed) {
  int index = -1;
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (!pool->bullets[i].active) {
      index = i;
      break;
    }
  }

  // start from beginning if no bullets left
  if (index == -1) {
    index = 0;
  }

  // Initialize the bullet
  Bullet *bullet = &pool->bullets[index];
  bullet->position = position;
  bullet->direction = Vector3Normalize(direction);
  bullet->speed = speed;
  bullet->lifetime = 1.0f;
  bullet->radius = 0.04f;
  bullet->active = true;
  bullet->color = BLACK;

  // count ++ if new bullet
  if (index >= pool->count) {
    pool->count = index + 1;
  }
}

// bullet update
void UpdateBullets(BulletPool *pool, float deltaTime) {
  for (int i = 0; i < pool->count; i++) {
    Bullet *bullet = &pool->bullets[i];

    if (!bullet->active)
      continue;

    // lifetime update
    bullet->lifetime -= deltaTime;
    if (bullet->lifetime <= 0) {
      bullet->active = false;
      continue;
    }

    // position update
    Vector3 movement =
        Vector3Scale(bullet->direction, bullet->speed * deltaTime);
    bullet->position = Vector3Add(bullet->position, movement);

    // NOTE: collision with world check here probably
    // and just bullet.active = false if collision?
  }

  // keep bullet pool compact, keep order
  while (pool->count > 0 && !pool->bullets[pool->count - 1].active) {
    pool->count--;
  }
}

// draw active bullets
void DrawBullets(BulletPool *pool) {
  for (int i = 0; i < pool->count; i++) {
    if (pool->bullets[i].active) {
      // bullet shape
      DrawSphere(pool->bullets[i].position, pool->bullets[i].radius,
                 pool->bullets[i].color);
      // bullet hitbox
      DrawSphereWires(pool->bullets[i].position, 0.2f, 10, 10, GREEN);

      // bullet trail
      Vector3 trailEnd =
          Vector3Subtract(pool->bullets[i].position,
                          Vector3Scale(pool->bullets[i].direction, 0.5f));
      DrawLine3D(pool->bullets[i].position, trailEnd, pool->bullets[i].color);
    }
  }
}

// shooting
void FireWeapon(Camera3D *camera, BulletPool *bulletPool) {
  // directions in world
  Vector3 forward =
      Vector3Normalize(Vector3Subtract(camera->target, camera->position));
  Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera->up));
  Vector3 up = Vector3Normalize(camera->up);

  // position bullet NOTE: change if wrong
  Vector3 offset = {0.5f, -0.1f, -0.5f};
  Vector3 spawnPos = {camera->position.x + right.x * offset.x +
                          up.x * offset.y + forward.x * offset.z,
                      camera->position.y + right.y * offset.x +
                          up.y * offset.y + forward.y * offset.z,
                      camera->position.z + right.z * offset.x +
                          up.z * offset.y + forward.z * offset.z};

  Vector3 direction = forward;

  // spawn hte bullet
  SpawnBullet(bulletPool, spawnPos, direction, 200.0f);
}

// bullet to enemy collision
bool CheckBulletCollision(Bullet *bullet, Vector3 targetPos,
                          float targetRadius) {
  if (!bullet->active)
    return false;

  return CheckCollisionSpheres(bullet->position, bullet->radius, targetPos,
                               targetRadius);
}
