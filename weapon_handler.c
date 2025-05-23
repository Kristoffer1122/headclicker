// Weapon handling

#include "weapon_handler.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h> 

struct Weapon weapon;
struct offset offset;

Weapon load_Weapon() {

  weapon.position = (Vector3){0.0f, 1.0f, 0.0f};
  weapon.model = LoadModel("../resources/weapons/Gun _obj/Gun.obj");
  weapon.texture = LoadTexture("../resources/weapons/WesternPistol.png");
  weapon.bounds = GetModelBoundingBox(weapon.model);

  return weapon;
};

Weapon weapon_handling(Camera3D *camera) {

  weapon.position.x = camera->position.x + 10;
  weapon.position.y = camera->position.y - 10;
  weapon.position.z = camera->position.z + 10;

  return weapon;
}

// WARNING: DO NOT TOUCH
void draw_Weapon(Camera3D *camera, Weapon *weapon) {
  // model offset
    Vector3 offset = {0.3f, -0.2f, 0.5f};
    
  // camera and relative vectors
    Vector3 forward = Vector3Normalize(Vector3Subtract(camera->target, camera->position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera->up));
    Vector3 up = Vector3Normalize(camera->up);
    
  // weapon position in the world
    Vector3 weaponPos = {
        camera->position.x + right.x * offset.x + up.x * offset.y + forward.x * offset.z,
        camera->position.y + right.y * offset.x + up.y * offset.y + forward.y * offset.z,
        camera->position.z + right.z * offset.x + up.z * offset.y + forward.z * offset.z
    };
    
  // yaw and pitch for gun, trig
  //  NOTE: why do i have to learn Trig for this game??????
  //  get point for yaw, where we are looking based on x and z axis
    float yaw = atan2f(forward.x, forward.z);
  // get pitch, how far up we are looking, used to move model when looking up and down  NOTE: negative because of raylib y up is positive
    float pitch = asinf(-forward.y);
    
    // Save current transform matrix
    rlDrawRenderBatchActive();
    rlPushMatrix();
    
  // move model position
    rlTranslatef(weaponPos.x, weaponPos.y, weaponPos.z);
    
 // NOTE: This is where the magic happens
  // rotate model right pitch and yaw 
  // yaw
    rlRotatef(yaw * RAD2DEG, 0, 1, 0);
  // pitch
    rlRotatef(pitch * RAD2DEG, 1, 0, 0);
    
  // put model in right position
    rlRotatef(90.0f, 0, 1, 0);
    
    DrawModel(weapon->model, (Vector3){0, 0, 0}, 1.0f, WHITE);
  // show forward direction  NOTE: doesnt follow player movement
    // DrawLine3D(weaponPos, Vector3Add(weaponPos, Vector3Scale(forward, 1.0f)), GREEN);
    
    // restart matrix
    rlPopMatrix();
    
}
