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

Weapon load_weapon_Revolver();

Weapon weapon_handling(Camera3D camera);

void draw_Weapon_Hitbox2(Camera3D* p_Camera, Weapon weapon);
void draw_Weapon_Hitbox(Camera3D* camera, Weapon weapon);

void draw_Weapon(Camera3D camera, Weapon weapon);
