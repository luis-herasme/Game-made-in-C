#define TEST_MODE 0

// Library import.
#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Framework import.
#include "./utils/vector.c"
#include "./utils/managers/Estructuras.c"
#include "./utils/physics/Physics.c"
#include "./utils/managers/GameObject.c"

// Cambiar
#include "./assets/scripts/Box.c"
#include "./utils/managers/Scene.c"

// Game imports.
#include "./assets/scripts/Player.c"
#include "./assets/scripts/Zombie.c"

int main()
{
    struct Scene scene = createScene();

    // Constantes del juego.
    const int WINDOW_WIDTH = 1600;
    const int WINDOW_HEIGHT = 900;
    const char *GAME_NAME = "ZOMBI";

    // Setup.
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);
    //ToggleFullscreen();
    InitAudioDevice();

    SetTargetFPS(60);

    scene = addObject(scene, simpleGameObject(
                                 (Vector2){0, 0},
                                 (Vector2){2 * 1200.0f, 2400},
                                 "./assets/sprites/grass.png"));

    Sound sound1 = LoadSound("./assets/sound/shot.wav");
    Sound sound2 = LoadSound("./assets/sound/load.wav");

    struct GameObject player = createGameObject(
        (Vector2){1200 / 2, 700 / 2},
        (Vector2){30.0f, 30.0f},
        "./assets/sprites/top.png",
        updateObject,
        collisionPlayer);

    player.velocity = (Vector2){0, 5};

    player.sounds[0] = sound1;
    player.sounds[1] = sound2;

    player.tag = 100;
    player.id = 1;
    scene = addObject(scene, player);

    /*
    scene = addObject(scene, createGameObject(
        (Vector2) {1200, 700},  
        (Vector2) {100.0f, 50.0f},
        "./assets/sprites/truck.png", 
        empty,
        emptyCollision
    ));
*/

    Texture2D treeSprite = getImage("./assets/sprites/palmtree1.png");
    Texture2D zombieSprite = getImage("./assets/sprites/Zombie2.png");

    for (int i = 0; i < 200; i++)
    {
        struct GameObject zombie;
        zombie.position = (Vector2){rand() % 2400, rand() % 2400};
        zombie.size = (Vector2){40.0f, 40.0f},
        zombie.vida = 1;
        zombie.sprite = zombieSprite;
        zombie.type = 2;
        zombie.update = zombiUpdate,
        zombie.collision = zombiCollision;
        zombie.tag = 5;
        zombie.deleted = 0;
        scene = addObject(scene, zombie);
    }

    for (int i = 0; i < 25; i++)
    {
        struct GameObject tree;
        tree.type = 2;
        tree.tag = 0;
        tree.vida = 1;
        tree.deleted = 0;
        tree.sprite = treeSprite;
        tree.position = (Vector2){rand() % 2300, rand() % 2300};
        tree.size = (Vector2){75, 75};
        tree.update = empty,
        tree.collision = emptyCollision;
        scene = addObject(scene, tree);
    }

    scene = addObject(scene, createGameObject(
                                 (Vector2){400.0f, 300.0f},
                                 (Vector2){30.0f, 30.0f},
                                 "./assets/sprites/box.png",
                                 boxUpdate,
                                 boxCollision));

    struct GameObject truck = createGameObject(
        (Vector2){400.0f, 450.0f},
        (Vector2){150.0f, 75.0f},
        "./assets/sprites/truck.png",
        empty,
        emptyCollision);
    truck.rotation = 15;
    scene = addObject(scene, truck);

    scene = setTarget(scene, 1);
    startScene(scene);

    return 0;
}
