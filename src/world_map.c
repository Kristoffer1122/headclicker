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
  DrawCube((Vector3){0.0f, 10.0f, 0.0f}, 32.0f, 10.0f, 32.0f, WHITE);
  // walls
  DrawCube((Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 10.0f, 32.0f, BLUE);
  DrawCube((Vector3){16.0f, 2.5f, 0.0f}, 1.0f, 10.0f, 32.0f, LIME);
  DrawCube((Vector3){0.0f, 2.5f, 16.0f}, 32.0f, 10.0f, 1.0f, GOLD);
  DrawCube((Vector3){0.0f, 2.5f, -16.0f}, 32.0f, 10.0f, 1.0f, RED);
  // ground
  DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f}, LIGHTGRAY);
};

World raymap() {

  world.image =
      LoadImage("../resources/maps/cubicmap.png"); // Load cubicmap image (RAM)
  world.texture =
      LoadTextureFromImage(world.image); // Convert image to texture to display (VRAM)

  world.mesh = GenMeshCubicmap(world.image, (Vector3){1.0f, 1.0f, 1.0f});
  world.model = LoadModelFromMesh(world.mesh);

  // NOTE: By default each cube is mapped to one part of texture atlas
  Texture2D texture =
      LoadTexture("../resources/maps/cubicmap_atlas.png"); // Load map texture
 world.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture =
      texture; // Set map diffuse texture

  world.position = (Vector3){-16.0f, 0.0f, -8.0f}; // Set model position

  UnloadImage(
      world.image); // Unload cubesmap image from RAM, already uploaded to VRAM

    DrawModel(world.model, world.position, 10.0f, WHITE);

  return world;

}
