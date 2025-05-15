// random_enemys header file
#include "raylib.h"

struct Enemy {
	Vector3 position;
	int health;
	bool alive;
	Model model;
	Texture texture;
};

void spawn_Enemy(Camera3D camera);
