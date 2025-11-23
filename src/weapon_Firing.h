#ifndef WEAPON_FIRING_H
#define WEAPON_FIRING_H

#include <raylib.h>
#include "enemys.h"

void init_Weapon_System(void);
void fire_Weapon(Vector3 origin, Vector3 direction);
void update_Bullets(void);
void draw_Bullets(void);

#endif // WEAPON_FIRING_H
