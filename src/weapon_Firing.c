// ----------------------------------------------------------------------------------
// to build use: gcc *.c -o headclicker -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
//
//		HEADCLICKER
//
//
// ----------------------------------------------------------------------------------



#include "weapon_Firing.h"
#include <raylib.h>
#include <raymath.h>

struct Weapon_info weapon_Info;
struct Bullet bullet;

void bullet_Fired(Camera3D camera) {

  bullet.height = 0.5f;
  bullet.width = 0.5f;
  bullet.length = 1.0f;

  bullet.offset.x += 2.0f;

  Vector3 forward =
      Vector3Normalize(Vector3Subtract(camera.target, camera.position));
  Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));
  //
  // Vector3 bullet_Position = {camera.position.x + forward.x * bullet.offset.x +
  //                                right.x * bullet.offset.y,
  //                            camera.position.y + bullet.offset.z,
  //                            camera.position.z + forward.z * bullet.offset.x +
  //                                right.z * bullet.offset.y};
  //

  Vector3 bullet_Position = {camera.position.x + forward.x * bullet.offset.x +
                                 right.x * bullet.offset.y,
                             camera.position.y + bullet.offset.z,
                             camera.position.z + forward.z * bullet.offset.x +
                                 right.z * bullet.offset.y};


  DrawCube(bullet_Position, 0.1f, 0.1f, 0.1f, BLACK);
};

void reload(Camera3D camera) {
  bullet.offset.x = 0.7f;
  bullet.offset.y = 0.5f;
  bullet.offset.z = -0.30f;
}
