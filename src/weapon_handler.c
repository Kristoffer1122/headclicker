// Weapon handling

#include "weapon_handler.h"
#include <raylib.h>
#include <raymath.h>

struct Weapon weapon;
struct offset offset;

Weapon load_weapon_Revolver() {

  weapon.position = (Vector3){0.0f, 1.0f, 0.0f};
  weapon.model = LoadModel("../resources/weapons/Gun _obj/Gun.obj");
  weapon.texture = LoadTexture("../resources/weapons/WesternPistol.png");
  weapon.bounds = GetModelBoundingBox(weapon.model);

  return weapon;
};

Weapon weapon_handling(Camera3D camera) {

  weapon.position.x = camera.position.x + 10;
  weapon.position.y = camera.position.y - 10;
  weapon.position.z = camera.position.z + 10;

  return weapon;
}

void draw_Weapon(Camera3D camera, Weapon weapon) {
  offset.x = 1.0f;
  offset.y = 0.5f;
  offset.z = -0.4f;
  Vector3 forward =
      Vector3Normalize(Vector3Subtract(camera.target, camera.position));
  Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));

  Vector3 modelPosition = {
      camera.position.x + forward.x * offset.x + right.x * offset.y,
      camera.position.y + offset.z,
      camera.position.z + forward.z * offset.x + right.z * offset.y};
  float angle = atan2f(forward.x, forward.z);
  angle += PI / 2;

  DrawModelEx(weapon.model, modelPosition, (Vector3){0.0f, 1.0f, 0.0f},
              angle * RAD2DEG, (Vector3){1.0f, 1.0f, 1.0f}, BLACK);
}
