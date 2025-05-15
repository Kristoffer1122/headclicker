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

struct Enemy enemy = {
    (Vector3){10.0f, 0.0f, 10.0f},
    100,
    true,
};

void spawn_Enemy(Camera3D camera) {

   enemy.model = LoadModel("../resources/enemy_models/greenman.glb");

    DrawModel(enemy.model, (Vector3){1.0f, 0.0f, 1.0f}, 1.0f, WHITE);
	
};

