#include "enemys.h"
#include <stdio.h>
#include <stdlib.h>

// Global enemy pointer
Enemy *g_Enemy = NULL;

void init_Enemy(void) {
    g_Enemy = (Enemy*)malloc(sizeof(Enemy));
    if (g_Enemy == NULL) {
        fprintf(stderr, "Failed to allocate enemy\n");
        return;
    }
    
    g_Enemy->position = (Vector3){0.0f, 0.0f, 5.0f};
    g_Enemy->health = 100;
    g_Enemy->isAlive = true;
    
    // BUG: No error checking after LoadModel
    g_Enemy->model = LoadModel("resources/enemy.obj");
}

void update_Enemy(void) {
    if (g_Enemy && g_Enemy->isAlive) {
        // Update enemy logic
    }
}

void draw_Enemy(void) {
    if (g_Enemy && g_Enemy->isAlive) {
        DrawModel(g_Enemy->model, g_Enemy->position, 1.0f, WHITE);
    }
}

void respawn_Enemy(void) {
    if (g_Enemy) {
        g_Enemy->position = (Vector3){0.0f, 0.0f, 5.0f};
        g_Enemy->health = 100;
        g_Enemy->isAlive = true;
    }
}

void cleanup_Enemy(void) {
    if (g_Enemy) {
        UnloadModel(g_Enemy->model);
        free(g_Enemy);
        g_Enemy = NULL;
    }
}
