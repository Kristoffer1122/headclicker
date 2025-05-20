#include <raylib.h>

struct Weapon_info {
  int ammo;
  int damage;
  float bullet_speed;
};

struct Bullet {
  Vector3 position;
  Vector3 direction;
  float speed;
  bool active;
  float height;
  float width;
  float length;
  Vector3 offset;
};

void shoot(Camera3D* camera);

void bullet_Fired(Camera3D* camera);

void reload(Camera3D* camera);
