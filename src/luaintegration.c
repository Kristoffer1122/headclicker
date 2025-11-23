#include "luaintegration.h"
#include <stdio.h>
#include <stdlib.h>

// Global Lua state pointer - BUG: This doesn't get updated properly
static lua_State *L = NULL;

// BUG: This function doesn't return the new state or update the global pointer
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
    
    // BUG: Local variable new_L is not assigned to global L
    // This causes L to remain NULL or point to old state
}

// BUG: Closes Lua state but start_lua doesn't update the pointer
void reload_Lua(void) {
    if (L != NULL) {
        lua_close(L);
        // BUG: L is now dangling pointer
    }
    start_lua();
    // BUG: L still points to old/closed state, causes crash
}

void cleanup_lua(void) {
    if (L != NULL) {
        lua_close(L);
        L = NULL;
    }
}
