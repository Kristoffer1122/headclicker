#include <raylib.h>
#include <stdint.h>

// max bullets
#define MAX_BULLETS 100

typedef struct Bullet {
  Vector3 position;
  Vector3 direction;
  float speed;
  float lifetime;
  bool active;
  float radius;
  Color color;
} Bullet;

typedef struct BulletPool {
    Bullet bullets[MAX_BULLETS];
    int count;
} BulletPool;


void shoot(Camera3D* camera);

void bullet_Fired(Camera3D* camera);

void bullet_Update(Camera3D* camera);

void reload(Camera3D* camera);
