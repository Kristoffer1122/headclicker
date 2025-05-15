// World Map Headerfile
#include <raylib.h>

typedef struct World {
	Vector3 position;
	Model model;
	Texture2D texture;
	Image image;
	Mesh mesh;

} World;




void loadmap();

World raymap();
