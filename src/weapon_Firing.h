#include <raylib.h>

struct Weapon_info {
  int ammo;
  int damage;
  float bullet_speed;
};

struct Bullet {
  float height;
  float width;
  float length;
  Vector3 offset;
};

void bullet_Fired(Camera3D camera);

void reload(Camera3D camera);
