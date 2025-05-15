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

  struct World world_Map;

  // load weapon and add texture
  Weapon weapon_Revolver = load_weapon_Revolver();
  struct Enemy enemy_Test;

  DisableCursor();
  SetTargetFPS(60);
  // game loop
  while (!WindowShouldClose()) {
    UpdateCamera(&camera, cameraMode);

    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode3D(camera);
    // start 3d drawing
    loadmap();
    // raymap();

    draw_Weapon(camera, weapon_Revolver);
    // shooting mechanic
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      bullet_Fired(camera);
    } else
      reload(camera);

    // reload mechanic
    if (IsKeyDown(KEY_R)) {
      reload(camera);
    }

    spawn_Enemy(camera);

    EndMode3D();

    DrawFPS(40, 20);
    DrawText("+", screenWidth / 2, screenHeight / 2, 40, BLACK);
    EndDrawing();
  }

  UnloadTexture(world_Map.texture); // Unload cubicmap texture
  UnloadTexture(world_Map.texture);  // Unload map texture
  UnloadModel(world_Map.model);

  UnloadModel(weapon_Revolver.model);
  UnloadModel(enemy_Test.model);

  CloseWindow();
}
