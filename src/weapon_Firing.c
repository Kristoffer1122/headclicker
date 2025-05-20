// ----------------------------------------------------------------------------------
// to build use: gcc *.c -o headclicker -lraylib -lGL -lm -lpthread -ldl -lrt
// -lX11
//
//		HEADCLICKER
//
//
// ----------------------------------------------------------------------------------

#include "weapon_Firing.h"
#include "physics.h"
#include <raylib.h>
#include <raymath.h>

struct Weapon_info weapon_Info;
struct Bullet bullet;
struct Game game;

void shoot(Camera3D *camera) {

      bullet.active = true;

      // Compute basis once
      Vector3 forward =
          Vector3Normalize(Vector3Subtract(camera->target, camera->position));
      Vector3 up = camera->up;
      Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, up));

      // Compute muzzle world position
      Vector3 barrelOffset = {0.7f, 0.5f, -0.30f};
      Vector3 worldOffset =
          Vector3Add(Vector3Add(Vector3Scale(right, barrelOffset.x),
                                Vector3Scale(up, barrelOffset.y)),
                     Vector3Scale(forward, barrelOffset.z));
      bullet.position =
          Vector3Add(camera->position, Vector3Scale(forward, 1.5f));

      // test bullet
      // DrawCube(bullet.position, 0.2f, 0.2f, 0.2f, RED);
      bullet_Fired(camera);

      // Set the bullet’s fixed direction
      bullet.direction = forward;
      bullet.speed = 20.0f;

}

void bullet_Fired(Camera3D *camera) {

    

    DrawCube(bullet.position, 0.2f, 0.2f, 0.2f, RED);

};

void reload(Camera3D *camera) {
  bullet.offset.x = 0.7f;
  bullet.offset.y = 0.5f;
  bullet.offset.z = -0.30f;
}
