// ----------------------------------------------------------------------------------
// to build use: gcc *.c -o headclicker -lraylib -lGL -lm -lpthread -ldl -lrt
// -lX11
//
//		HEADCLICKER
//
//
// ----------------------------------------------------------------------------------

#include "camera.h"
#include "collision_handler.h"
#include "physics.h"
#include "player_movement.h"
#include "random_enemys.h"
#include "weapon_Firing.h"
#include "weapon_handler.h"
#include "world_map.h"
#include <raylib.h>
#include <raymath.h>

int main(void) {
  int screenWidth = 1920;
  int screenHeight = 1199;
  InitWindow(screenWidth, screenHeight, "Headclicker");

  Camera3D camera;
  camera.position = (Vector3){0.0f, 2.0f, 4.0f}; // Camera position
  camera.target = (Vector3){0.0f, 2.0f, 0.0f};   // Camera looking at point
  camera.up =
      (Vector3){0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
  camera.fovy = 60.0f;             // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE; // Camera projection type
  int cameraMode = CAMERA_FIRST_PERSON;
  Camera3D *p_Camera = &camera;

  struct World world_Map;
  struct Bullet bullet;
  struct Game game;

  // load weapon and add texture
  Weapon weapon = load_Weapon();
  Weapon *p_Weapon = &weapon;
  struct Enemy enemy_Test;

  DisableCursor();
  SetTargetFPS(60);
  // game loop
  while (!WindowShouldClose()) {
    UpdateCamera(&camera, cameraMode);
    // time since last frame
    float delta_Time = GetFrameTime();
    game.delta_Time = &delta_Time;

    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode3D(camera);
    // start 3d drawing
    loadmap();
    // raymap();

    // draw_Weapon(camera, weapon_Revolver);
    // draw_Weapon_Hitbox(p_Camera, weapon_Revolver);
    draw_Weapon(p_Camera, p_Weapon);

    // shooting mechanic
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      shoot(p_Camera);
    }

    spawn_Enemy(p_Camera);
    DrawGrid(10, 1); // Grid helps with orientation

    EndMode3D();

    DrawFPS(40, 20);
    DrawText("+", screenWidth / 2, screenHeight / 2, 40, BLACK);
    EndDrawing();
  }

  UnloadTexture(world_Map.texture); // Unload cubicmap texture
  UnloadModel(world_Map.model);
  UnloadMesh(world_Map.mesh);
  UnloadImage(world_Map.image);

  UnloadModel(weapon.model);
  UnloadModel(enemy_Test.model);

  CloseWindow();
}
