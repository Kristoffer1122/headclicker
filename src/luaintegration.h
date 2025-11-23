#ifndef LUAINTEGRATION_H
#define LUAINTEGRATION_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

// Initialize Lua scripting system
void start_lua(void);

// Reload Lua scripts
void reload_Lua(void);

// Clean up Lua resources
void cleanup_lua(void);

#endif // LUAINTEGRATION_H
