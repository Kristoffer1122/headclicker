#include <raylib.h>
#include <stdio.h>
#include <stdbool.h>
#include "luaintegration.h"
#include "sound_effects.h"
#include "enemys.h"
#include "weapon_Firing.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "HeadClicker");
    SetTargetFPS(60);
    
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, -10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    
    // Initialize systems
    init_Sound_System();
    start_lua();
    init_Enemy();
    init_Weapon_System();
    
    // Main game loop
    while (!WindowShouldClose()) {
        // Input handling
        if (IsKeyPressed(KEY_O)) {
            printf("Reloading Lua...\n");
            reload_Lua();
        }
        
        if (IsKeyPressed(KEY_R)) {
            printf("Respawning enemy...\n");
            respawn_Enemy();
        }
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector3 origin = camera.position;
            Vector3 direction = Vector3Normalize(
                Vector3Subtract(camera.target, camera.position)
            );
            fire_Weapon(origin, direction);
        }
        
        // Update
        update_Enemy();
        update_Bullets();
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        BeginMode3D(camera);
        DrawGrid(10, 1.0f);
        draw_Enemy();
        draw_Bullets();
        EndMode3D();
        
        DrawText("Press O to reload Lua", 10, 10, 20, DARKGRAY);
        DrawText("Press R to respawn enemy", 10, 40, 20, DARKGRAY);
        DrawText("Click to fire", 10, 70, 20, DARKGRAY);
        
        DrawFPS(10, SCREEN_HEIGHT - 30);
        EndDrawing();
    }
    
    // Cleanup
    cleanup_Enemy();
    cleanup_Sound_System();
    cleanup_lua();
    CloseWindow();
    
    return 0;
}
