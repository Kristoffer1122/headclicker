// random_enemys header file
#include <raylib.h>
#include <lua.h>

typedef struct Enemy {
	Vector3 position;
	Vector3 healthbar_Position;
	BoundingBox enemyRect;
	int health;
	bool alive;
	Model model;
	Texture texture;
} Enemy;

int lua_drawHealthBar(lua_State *L);

Model load_Enemy_Model();
