

// Estructura objeto de juego.
struct GameObject
{
    int type;
    int tag;
    int id;
    struct Sound sounds[10];
    float vida;
    int deleted;
    Texture2D sprite;
    Vector2 position;
    Vector2 velocity;
    Vector2 size;
    Rectangle rect;
    struct GameObject (*update)(struct GameObject, struct GameObject*);
    struct GameObject (*collision)(struct GameObject, struct GameObject);
    float rotation;
};

struct GameObject sceneGameObjects[1024];

// Estructura de una escena
struct Scene
{
    Camera2D camera;
    int target;
    int size;
};