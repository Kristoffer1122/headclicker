#ifndef ENEMYS_H
#define ENEMYS_H

#include <raylib.h>

typedef struct Enemy {
    Vector3 position;
    Model model;
    bool isAlive;
    int health;
} Enemy;

// BUG: Inconsistent global enemy declarations across files
extern Enemy *g_Enemy;

void init_Enemy(void);
void update_Enemy(void);
void draw_Enemy(void);
void respawn_Enemy(void);
void cleanup_Enemy(void);

#endif // ENEMYS_H
