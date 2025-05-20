// Weapon handling

#include "weapon_handler.h"
#include <math.h>
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

void draw_Weapon_Hitbox2(Camera3D *camera, Weapon weapon) {
  // 1. Offset in camera-local space (+X = right, +Y = up, -Z = forward in
  // raylib)
  Vector3 offset = {0.30f, -0.20f, 0.60f}; // Slightly right, down, and in front

  // 2. Build camera-local basis vectors
  Vector3 forward =
      Vector3Normalize(Vector3Subtract(camera->target, camera->position));
  Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera->up));
  Vector3 up = camera->up;

  // 3. Compute gun position in world space
  Vector3 gunPos = {camera->position.x + right.x * offset.x + up.x * offset.y +
                        forward.x * offset.z,
                    camera->position.y + right.y * offset.x + up.y * offset.y +
                        forward.y * offset.z,
                    camera->position.z + right.z * offset.x + up.z * offset.y +
                        forward.z * offset.z};

  // 4. Calculate direction from weapon to camera.target (aim direction)
  Vector3 aimDir = Vector3Normalize(Vector3Subtract(camera->target, gunPos));

  float yaw = atan2f(aimDir.x, aimDir.z); // left/right rotation
  float pitch = asinf(-aimDir.y);         // up/down tilt

  // ---- FIX: wrap yaw to [0, 2π) to prevent quadrant flipping
  if (yaw < 0.0f)
    pitch = -pitch;

  // One-time mesh fix: if your model faces +X, rotate -90° so it faces +Z
  const Matrix meshFix = MatrixRotateY(PI / 2.0f); // flip direction

  // Rotation matrices
  Matrix rotYaw = MatrixRotateY(yaw);
  Matrix rotPitch = MatrixRotateX(pitch);
  Matrix rotView = MatrixMultiply(rotYaw, rotPitch); // <- new order
  Matrix rotFinal = MatrixMultiply(rotView, meshFix);

  // 5. Combine final transform matrix
  Matrix trs = MatrixTranslate(gunPos.x, gunPos.y, gunPos.z);
  weapon.model.transform = MatrixMultiply(rotFinal, trs);

  // Draw the weapon
  DrawModel(weapon.model, (Vector3){0}, 1.0f, WHITE);
}

void draw_Weapon_Hitbox(Camera3D *camera, Weapon weapon) {

  offset.x = 1.0f;
  offset.y = 0.6f;
  offset.z = -0.4f;

  float max_distance = 2.0f;

  // Compute basis once
  Vector3 forward =
      Vector3Normalize(Vector3Subtract(camera->target, camera->position));
  Vector3 up = camera->up;
  Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, up));

  Vector3 modelPosition = {
      camera->position.x + forward.x * offset.x + right.x * offset.y,
      camera->position.y + offset.z,
      camera->position.z + forward.z * offset.x + right.z * offset.y};

  Vector3 direction = Vector3Subtract(forward, right);

  // float test = atan2f(forward.y, right.x);
  // test += PI / 2;

  float angle = atan2f(-forward.y, right.x);
  angle += PI / 2;

  DrawModelEx(weapon.model, modelPosition, (Vector3){0.0f, 0.0f, 1.0f},
              angle * RAD2DEG, (Vector3){1.0f, 1.0f, 1.0f}, BLACK);
}

void draw_Weapon(Camera3D camera, Weapon weapon) {

  offset.x = 1.0f;
  offset.y = 0.6f;
  offset.z = -0.4f;

  // Compute basis once
  Vector3 forward =
      Vector3Normalize(Vector3Subtract(camera.target, camera.position));
  Vector3 up = camera.up;
  Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, up));

  // Compute muzzle world position
  Vector3 barrelOffset = {0.7f, 0.5f, -0.30f};
  Vector3 worldOffset =
      Vector3Add(Vector3Add(Vector3Scale(right, barrelOffset.x),
                            Vector3Scale(up, barrelOffset.y)),
                 Vector3Scale(forward, barrelOffset.z));

  Vector3 modelPosition = {
      camera.position.x + forward.x * offset.x + right.x * offset.y,
      camera.position.y + offset.z,
      camera.position.z + forward.z * offset.x + right.z * offset.y};

  Vector3 direction = Vector3Subtract(camera.target, modelPosition);

  float angle = atan2f(direction.x, direction.z);
  angle += PI / 2;

  DrawModelEx(weapon.model, modelPosition, (Vector3){0.0f, 1.0f, 0.0f},
              angle * RAD2DEG, (Vector3){1.0f, 1.0f, 1.0f}, BLACK);
}
