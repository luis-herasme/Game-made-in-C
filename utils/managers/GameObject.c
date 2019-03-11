
// Prototipado.
Texture2D getImage (char* src);
void render(struct GameObject gameObject);
//struct GameObject createGameObject(Vector2 position, Vector2 size, char* img, struct GameObject (*update)(struct GameObject), struct GameObject (*collision)(struct GameObject, struct GameObject));
//struct GameObject updateGameObject(struct GameObject gameObject);
struct GameObject simpleGameObject(Vector2 position, Vector2 size, char* img);

// Carga imagen.
Texture2D getImage (char* src) {
    Image image = LoadImage(src);
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    return texture;
}

// Dibuja objeto de juego.
void render(struct GameObject this)
{
    DrawTexturePro(this.sprite, (Rectangle) {
        0.0f,
        0.0f,
        this.sprite.width,
        this.sprite.height
    }, (Rectangle) {
        this.position.x + this.size.x / 2,
        this.position.y + this.size.y / 2,
        this.size.x,
        this.size.y,
    }, 
    (Vector2)
    {
        this.size.x / 2,
        this.size.y / 2
    }
    , this.rotation , WHITE);
    
    // IF TEST MODE:
   if (TEST_MODE)
   {
       DrawText("GameObject", this.position.x, this.position.y, 12, GREEN);
       DrawRectangleLines(this.position.x, this.position.y, this.size.x, this.size.y, GREEN);
   }
}

struct GameObject createSprite(Vector2 position, Vector2 size, char* img)
{
    struct GameObject gameObject;
    gameObject.size = size;
    gameObject.position = position;
    gameObject.sprite = getImage(img);
    return gameObject;
}

struct GameObject createGameObject(Vector2 position, Vector2 size, char* img, struct GameObject (*update)(struct GameObject, struct GameObject*), struct GameObject (*collision)(struct GameObject, struct GameObject))
{
    struct GameObject this;
    this.deleted = 0;
    this.vida = 1;
    this.rotation = 0;
    this.size = size;
    this.position = position;
    this.sprite = getImage(img);
    this.update = update;
    this.collision = collision;
    this.type = 2;
    return this;
}

struct GameObject simpleGameObject(Vector2 position, Vector2 size, char* img)
{
    struct GameObject this;
    this.deleted = 0;
    this.type = 1;
    this.rotation = 0;
    this.size = size;
    this.position = position;
    this.sprite = getImage(img);
    return this;
}

struct GameObject updateGameObject(struct GameObject this, struct GameObject GameObjects[])
{   
    this.rect = (Rectangle) {
        this.position.x,
        this.position.y,
        this.size.x,
        this.size.y,
    };
 
    render(this);
    
    if (this.type == 2) {
        this = this.update(this, GameObjects);
    }
 
    return this;
}

struct GameObject empty (struct GameObject this, struct GameObject gameObject[]) {
    return this;    
}
struct GameObject emptyCollision (struct GameObject this, struct GameObject other) {
    return this;    
}
