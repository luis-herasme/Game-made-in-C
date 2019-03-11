
int zombies_alive = 1;

struct Scene setTarget(struct Scene this, int index) {
    this.target = index;
    return this;
}

struct Scene createScene()
{
    struct Scene this;
    this.size = 0;
    return this;
}

struct Scene addObject(struct Scene scene, struct GameObject gameObject)
{
    sceneGameObjects[scene.size] = gameObject;
    scene.size = scene.size + 1;
    return scene;
}


struct GameObject move (struct GameObject this, struct GameObject GameObjects[]) {
    this.position.x += this.velocity.x;
    this.position.y += this.velocity.y;
    return this;    
}

struct GameObject ballCol (struct GameObject this, struct GameObject other) {
    this.vida -= 0.1;
    if (this.vida < 0) {
        this.deleted = 1;
    }
    return this;    
}

struct Scene updateScene(struct Scene scene)
{
    zombies_alive = 0;
    if ((rand() % 1000) == 10) {

    scene = addObject(scene, createGameObject(
        (Vector2) {rand() % 2400, rand() % 2400},
        (Vector2) {30.0f, 30.0f},
        "./assets/sprites/box.png",
        boxUpdate,
        boxCollision
    ));    

    }

    if (IsKeyPressed(KEY_E))
    
{
    
        if (sceneGameObjects[1].tag > 0) {
            struct GameObject ball = createGameObject(
                (Vector2) {sceneGameObjects[scene.target].position.x, sceneGameObjects[1].position.y},
                (Vector2) {10, 10},
                "./assets/sprites/ball.png",
                move,
                ballCol
            );
            
            ball.velocity.x = -1 * 2 * sceneGameObjects[1].velocity.x;
            ball.velocity.y = -1 * 2 * sceneGameObjects[1].velocity.y;
            
            ball.position.x += 3 * ball.velocity.x;
            ball.position.y += 3 * ball.velocity.y;
            
            ball.tag = 3;
            ball.deleted = 0;
            scene = addObject(scene, ball);
            sceneGameObjects[1].tag -= 1;
        }

   }
    
    for (int i = 0; i < scene.size; i++)
    {
        
        
        
        if (!sceneGameObjects[i].deleted) {
        if (sceneGameObjects[i].tag == 5) {
            zombies_alive++;
        }
        sceneGameObjects[i] = updateGameObject(sceneGameObjects[i], sceneGameObjects);
            
            if (sceneGameObjects[i].type == 2) // PHYSICS_TYPE
            {
                for (int y = 0; y < scene.size; y++)
                {
                    if (!sceneGameObjects[y].deleted) {
                        if (i != y)
                        {
                            if (sceneGameObjects[y].type == 2)
                            {
                                sceneGameObjects[i] = checkCollision(sceneGameObjects[i], sceneGameObjects[y]);
                            }
                        }
                    }
                }
            }
        }
    }
    

    
    return scene;
}

void startScene (struct Scene this) {
    
    this.camera.target = (Vector2) {sceneGameObjects[this.target].position.x + 35, sceneGameObjects[this.target].position.y + 35};
    this.camera.offset = (Vector2) {0, 0};
    this.camera.rotation = 0.0f;
    this.camera.zoom = 0.75f;
    
    Music music = LoadMusicStream("./assets/sound/zombie.ogg");
    PlayMusicStream(music);
    
    // Game loop.
    while (!WindowShouldClose()) {
        
        this.camera.target = (Vector2) {sceneGameObjects[this.target].position.x + 35, sceneGameObjects[this.target].position.y + 35};

        Vector2 desplazamiento = (Vector2) {0, 0};
        desplazamiento.x += sceneGameObjects[this.target].position.x;
        desplazamiento.y += sceneGameObjects[this.target].position.y;

        BeginDrawing();
            BeginMode2D(this.camera);
                
                ClearBackground(BLACK);
                
                this = updateScene(this);
                
                
            EndMode2D();
        // UI
  
        char result[50]; 
        int balas = sceneGameObjects[this.target].tag;
        sprintf(result, "Balas %i", balas); 
        
        DrawText(result, 50, 50, 25, WHITE);
        
        if (sceneGameObjects[this.target].vida < 0) {
            DrawRectangle(0, 0, 1200, 700, GRAY);
            DrawText("GAME OVER", 600 - MeasureText("GAME OVER", 100) / 2, 300, 100, WHITE);
            DrawText("Cierra la ventana para volver a jugar", 600 - MeasureText("Cierra la ventana para volver a jugar", 25) / 2, 450, 25, WHITE);
        }
        if (!zombies_alive) {
            DrawRectangle(0, 0, 1200, 700, GRAY);
            DrawText("Ganaste!", 600 - MeasureText("Ganaste!", 100) / 2, 300, 100, WHITE);   
        }
   
        EndDrawing();

        desplazamiento.x -= sceneGameObjects[this.target].position.x;
        desplazamiento.y -= sceneGameObjects[this.target].position.y;
        
        this.camera.offset.x += desplazamiento.x;
        this.camera.offset.y += desplazamiento.y;
    
        UpdateMusicStream(music);
    }

    CloseWindow();
}
