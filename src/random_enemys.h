// random_enemys header file
#include "raylib.h"

typedef struct Enemy {
	Vector3 position;
	int health;
	bool alive;
	Model model;
	Texture texture;
} Enemy;

Enemy spawn_Enemy(Camera3D* camera);
