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

// resolution numbers
#define GAME_WIDTH 640
#define GAME_HEIGHT 400
// upscale multi
#define WINDOW_SCALE 3

int main(void) {
  const int screenWidth = GAME_WIDTH * WINDOW_SCALE;
  const int screenHeight = GAME_HEIGHT * WINDOW_SCALE;
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Headclicker");
  Camera3D camera;
  camera.position = (Vector3){0.0f, 2.0f, 4.0f}; // Camera position
  camera.target = (Vector3){0.0f, 2.0f, 0.0f};   // Camera looking at point
  camera.up =
      (Vector3){0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
  camera.fovy = 60.0f;             // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE; // Camera projection type
  int cameraMode = CAMERA_FIRST_PERSON;
  Camera3D *p_Camera = &camera;

  RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

  SetTextureFilter(target.texture,
                   TEXTURE_FILTER_POINT); // Nearest-neighbor filtering

  struct World world_Map;
  struct Game game;

  // init bullets
  InitBulletPool(&g_bulletPool);

  // load weapon and add texture
  Weapon weapon = load_Weapon();
  weapon.texture = LoadTexture("../resources/weapons/Gun _obj/Gun.png");
  Weapon *p_Weapon = &weapon;

  // enemy
  Enemy enemy = spawn_Enemy(p_Camera);

  DisableCursor();
  SetTargetFPS(60);
  // game loop
  while (!WindowShouldClose()) {
    UpdateCamera(&camera, cameraMode);
    // time since last frame
    float delta_Time = GetFrameTime();
    game.delta_Time = &delta_Time;

    // start drawing
    BeginDrawing();

    BeginTextureMode(target);
    BeginMode3D(camera);
    ClearBackground(WHITE);
    // start 3d drawing
    loadmap();
    // raymap();

    // enemy and weapon models
    // enemy
    DrawModel(enemy.model, (Vector3){1.0f, 0.0f, 1.0f}, 1.0f, WHITE);
    // weapon
    draw_Weapon(p_Camera, p_Weapon);

    // shooting mechanic
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      FireWeapon(&camera, &g_bulletPool);
    }

    // update and draw bullets every frame
    UpdateBullets(&g_bulletPool, GetFrameTime());
    DrawBullets(&g_bulletPool);

    EndMode3D();
    EndTextureMode();

    // pixelated effect on screen
    DrawTexturePro(
        target.texture,
        (Rectangle){0, 0, (float)target.texture.width,
                    -((float)target.texture.height)}, // flipped vertically
        (Rectangle){0, 0, (float)screenWidth,
                    (float)screenHeight}, // scale up to screen
        (Vector2){0, 0}, 0.0f, WHITE);

    // pixelated crosshair
    // DrawText("+", GAME_WIDTH / 2 - 5, GAME_HEIGHT / 2 - 5, 10, BLACK);
    // normal crosshair
    DrawText("+", screenWidth / 2 + 10, screenHeight / 2 - 10, 40, BLACK);
    DrawFPS(40, 20);
    EndDrawing();
  }

  // pixelated effect
  UnloadRenderTexture(target);

  UnloadTexture(world_Map.texture);
  UnloadModel(world_Map.model);
  UnloadMesh(world_Map.mesh);
  UnloadImage(world_Map.image);

  UnloadTexture(weapon.texture);
  UnloadModel(weapon.model);
  UnloadModel(enemy.model);

  CloseWindow();
}
