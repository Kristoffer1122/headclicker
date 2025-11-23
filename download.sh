#!/bin/bash
BASE_URL="https://raw.githubusercontent.com/Kristoffer1122/headclicker/39e648e781686937bde4dd194234d5e8216c6098"

# Download src files
wget -q -O src/headclicker.c "$BASE_URL/src/headclicker.c"
wget -q -O src/enemys.c "$BASE_URL/src/enemys.c"
wget -q -O src/enemys.h "$BASE_URL/src/enemys.h"
wget -q -O src/weapon_Firing.c "$BASE_URL/src/weapon_Firing.c"
wget -q -O src/weapon_Firing.h "$BASE_URL/src/weapon_Firing.h"
wget -q -O src/sound_effect.c "$BASE_URL/src/sound_effect.c"
wget -q -O src/sound_effects.h "$BASE_URL/src/sound_effects.h"
wget -q -O src/camera.h "$BASE_URL/src/camera.h"
wget -q -O src/camera_handler.c "$BASE_URL/src/camera_handler.c"
wget -q -O src/collision_Handler.c "$BASE_URL/src/collision_Handler.c"
wget -q -O src/collision_handler.h "$BASE_URL/src/collision_handler.h"
wget -q -O src/physics.c "$BASE_URL/src/physics.c"
wget -q -O src/physics.h "$BASE_URL/src/physics.h"
wget -q -O src/player_movement.h "$BASE_URL/src/player_movement.h"
wget -q -O src/weapon_handler.c "$BASE_URL/src/weapon_handler.c"
wget -q -O src/weapon_handler.h "$BASE_URL/src/weapon_handler.h"
wget -q -O src/world_map.c "$BASE_URL/src/world_map.c"
wget -q -O src/world_map.h "$BASE_URL/src/world_map.h"

# Download Makefile
wget -q -O Makefile "$BASE_URL/Makefile"

# Download README
wget -q -O README.md "$BASE_URL/README.md"

echo "Download complete"
