// ----------------------------------------------------------------------------------
// to build use: gcc main.c -o mygame -lraylib -lGL -lm -lpthread -ldl -lrt
// -lX11
//
//		HEADCLICKER
//
//
// ----------------------------------------------------------------------------------

#include "random_enemys.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "world_map.h"

struct Enemy enemy = {
    (Vector3){10.0f, 0.0f, 10.0f},
    100,
    true,
};

void spawn_Enemy(Camera3D* camera) {

   enemy.model = LoadModel("../resources/enemy_models/greenman.glb");

    DrawModel(enemy.model, (Vector3){1.0f, 0.0f, 1.0f}, 1.0f, WHITE);
	
};

float random_Spawn(World *world) {
  // Seed the random number generator
    srand(time(NULL));
    // Generate a random number between 1 and 6
    float random_number = (rand() % 4)  -4;

   printf("random Number = %f \n", random_number);
   return random_number;
};

