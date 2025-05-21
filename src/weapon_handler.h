// weapon_handler header file

#include <raylib.h>

struct offset {
	float x;
	float y;
	float z;
};

typedef struct Weapon {
	Vector3 position;
	Texture texture;
	Model model;
	BoundingBox bounds;
} Weapon;

Weapon load_Weapon();

Weapon weapon_handling(Camera3D* camera);

void draw_Weapon(Camera3D* camera, Weapon* weapon);
