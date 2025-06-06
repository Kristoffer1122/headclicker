// ----------------------------------------------------------------------------------
// to build use: gcc main.c -o mygame -lraylib -lGL -lm -lpthread -ldl -lrt
// -lX11
//
//		HEADCLICKER
//
//
// ----------------------------------------------------------------------------------

#include "enemys.h"
#include "world_map.h"
#include <lauxlib.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Enemy enemy = {
    .health = 100,
    .alive = true,
};

Model load_Enemy_Model() {

  Model model = LoadModel("../resources/enemy_models/greenman.glb");

  return model;
};

int lua_drawHealthBar(lua_State *L) {
  enemy.healthbar_Position.x = luaL_checknumber(L, 1);
  enemy.healthbar_Position.y = luaL_checknumber(L, 2);
  enemy.healthbar_Position.z = luaL_checknumber(L, 3);
  if (enemy.health > 0) {
    // makeshift healthbar
    DrawCube(enemy.healthbar_Position, 1.5f, 0.4f, 0.001f, WHITE);
    DrawCube((Vector3){enemy.healthbar_Position.x - 0.12f,
                       enemy.healthbar_Position.y,
                       enemy.healthbar_Position.z + 0.01f},
             0.012f * enemy.health, 0.3f, 0.001f, RED);
    DrawCube((Vector3){enemy.healthbar_Position.x - 0.12f,
                       enemy.healthbar_Position.y,
                       enemy.healthbar_Position.z - 0.01f},
             1.2f, 0.3f, 0.001f, RED);

  } else if (enemy.health <= 0) {
    enemy.alive = false;
  }

  return 0;
}

float random_Spawn(World *world) {
  // Seed the random number generator
  srand(time(NULL));
  // Generate a random number between 1 and 6
  float random_number = (rand() % 4) - 4;

  printf("random Number = %f \n", random_number);
  return random_number;
}
