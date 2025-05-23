// ----------------------------------------------------------------------------------
// to build use: gcc *.c -o headclicker -lraylib -lGL -lm -lpthread -ldl -lrt
// -lX11
//
//		HEADCLICKER
//
//
// ----------------------------------------------------------------------------------

#include "world_map.h"
#include <raylib.h>

struct World world;

void loadmap() {

  // roof
  // DrawCube((Vector3){0.0f, 10.0f, 0.0f}, 32.0f, 10.0f, 32.0f, WHITE);
  // walls
  DrawCube((Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 10.0f, 32.0f, BLUE);
  DrawCube((Vector3){16.0f, 2.5f, 0.0f}, 1.0f, 10.0f, 32.0f, LIME);
  DrawCube((Vector3){0.0f, 2.5f, 16.0f}, 32.0f, 10.0f, 1.0f, GOLD);
  DrawCube((Vector3){0.0f, 2.5f, -16.0f}, 32.0f, 10.0f, 1.0f, RED);
  // ground
  DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f}, LIGHTGRAY);
};


World raymap() {

  world.model = LoadModel("../resources/maps/obj/Space Station Scene.obj");

  // NOTE: By default each cube is mapped to one part of texture atlas
  Texture2D texture =
      LoadTexture("../resources/maps/obj/t1_UVMap_nmap.jpg"); // Load map texture

  world.position = (Vector3){-16.0f, 0.0f, -8.0f}; // Set model position


    DrawModel(world.model, world.position, 10.0f, WHITE);

  return world;

}
