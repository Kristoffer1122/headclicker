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
#include "sound_effects.h"
#include "player_movement.h"
#include "enemys.h"
#include "weapon_Firing.h"
#include "weapon_handler.h"
#include "world_map.h"
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

// resolution numbers
#define GAME_WIDTH 640
#define GAME_HEIGHT 400
// upscale multi
#define WINDOW_SCALE 3

Enemy *g_Enemy;

int lua_drawCube(lua_State *L) {
  int vec1 = luaL_checkinteger(L, 1);
  int vec2 = luaL_checkinteger(L, 2);
  int vec3 = luaL_checkinteger(L, 3);
  int width = luaL_checkinteger(L, 4);
  int height = luaL_checkinteger(L, 5);
  int length = luaL_checkinteger(L, 6);
  Color color = ORANGE;

  Vector3 pos = (Vector3){vec1, vec2, vec3};

  DrawCube(pos, width, height, length, color);
  return 0;
}

int lua_drawModel(lua_State *L) {
  Enemy enemy;
  // x
  float vec1 = luaL_checknumber(L, 1);
  // y
  float vec2 = luaL_checknumber(L, 2);
  // z
  float vec3 = luaL_checknumber(L, 3);
  g_Enemy->position = (Vector3){vec1, vec2, vec3};
  return 0;
}

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

  // Initialize Lua
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  // let lua know these functions work
  // make a lua name that points to a c function
  lua_register(L, "drawCube", lua_drawCube);
  lua_register(L, "drawEnemy", lua_drawModel);
  lua_register(L, "drawHealthBar", lua_drawHealthBar);

  printf("Loading init.lua...\n");
  // Register your C functions for Lua to cal

  // Load initial scripts
  // luaL_dofile(L, "../scripts/init.lua");
  // Load the init script
  int result = luaL_dofile(L, "../scripts/init.lua");
  if (result != LUA_OK) {
    printf("Error loading init.lua: %s\n", lua_tostring(L, -1));
    lua_close(L);
    return 1;
  }

  struct World world_Map;
  struct Game game;

  // init bullets
  InitBulletPool(&g_bulletPool);

  // load weapon and add texture
  Weapon weapon = load_Weapon();
  Weapon *p_Weapon = &weapon;

  // enemy
  // we can change the enemy position with lua scripts now
  Enemy enemy = spawn_Enemy();
  g_Enemy = &enemy;

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

    // Hot-reload script when R key is pressed
    if (IsKeyPressed(KEY_R)) {
      printf("Reloading Lua script...\n");
      int result = luaL_dofile(L, "../scripts/init.lua");
      if (result != LUA_OK) {
        printf("Error reloading: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
      }
    }
    lua_getglobal(L, "update");
    if (lua_isfunction(L, -1)) {
      lua_pushnumber(L, delta_Time);
      lua_call(L, 1, 0); // ← CORRECT: expecting 0 return values
    } else {
      lua_pop(L, 1); // Pop the non-function value
    }
    // Test reading variables from Lua
    lua_getglobal(L, "draw");
    if (lua_isfunction(L, -1)) {
      lua_call(L, 0, 0); // ← CORRECT: expecting 0 return values
    } else {
      lua_pop(L, 1); // Pop the non-function value
    }

    lua_getglobal(L, "draw_Enemy");
    if (lua_isfunction(L, -1)) {
      lua_call(L, 0, 0); // ← CORRECT: expecting 0 return values
    } else {
      lua_pop(L, 1); // Pop the non-function value
    }

    lua_getglobal(L, "draw_EnemyHealthBar");
    if (lua_isfunction(L, -1)) {
      lua_call(L, 0, 0); // ← CORRECT: expecting 0 return values
    } else {
      lua_pop(L, 1); // Pop the non-function value
    }

    // enemy and weapon models
    // enemy
    DrawModel(g_Enemy->model, g_Enemy->position, 1.0f, WHITE);
    // weapon
    draw_Weapon(p_Camera, p_Weapon);

    // shooting mechanic
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      FireWeapon(&camera, &g_bulletPool);
      // play_Sound_Effect();
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
    DrawText("+", screenWidth / 2 + 10, screenHeight / 2 - 10, 40,
             Fade(BLACK, 0.8));
    DrawFPS(40, 20);
    EndDrawing();
  }

  lua_close(L);
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
