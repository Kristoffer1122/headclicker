// playermovement header file
#include "raylib.h"
#include <raymath.h>

typedef struct Player {
	Vector3 position;
	Vector3 velocity;
	float speed;
	float jumpForce;
	bool isGrounded;
} Player;

void jumping(Player);
void killTracker();
