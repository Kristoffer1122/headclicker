#include "luaintegration.h"
#include <stdio.h>
#include <stdlib.h>

// Global Lua state pointer
static lua_State *L = NULL;

// Initialize Lua state and update global pointer
void start_lua(void) {
    lua_State *new_L = luaL_newstate();
    if (new_L == NULL) {
        fprintf(stderr, "Failed to create Lua state\n");
        return;
    }
    
    luaL_openlibs(new_L);
    
    // Load init script
    if (luaL_dofile(new_L, "scripts/init.lua") != LUA_OK) {
        fprintf(stderr, "Error loading init.lua: %s\n", lua_tostring(new_L, -1));
        lua_pop(new_L, 1);
    }
    
    // FIX: Update global pointer to the new Lua state
    L = new_L;
}

// Reload Lua state safely
void reload_Lua(void) {
    if (L != NULL) {
        lua_close(L);
        // FIX: Set to NULL before creating new state
        L = NULL;
    }
    start_lua();
    // FIX: start_lua() now properly updates L with the new state
}

void cleanup_lua(void) {
    if (L != NULL) {
        lua_close(L);
        L = NULL;
    }
}
