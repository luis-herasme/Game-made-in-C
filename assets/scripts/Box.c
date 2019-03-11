
struct GameObject boxUpdate(struct GameObject this, struct GameObject GameObjects[]) {
    // DrawText("Balas", this.position.x, this.position.y, 12, WHITE);
    return this;
}

struct GameObject boxCollision (struct GameObject this, struct GameObject other) {
 
   if (other.id == 1) {
        this.deleted = 1;
        sceneGameObjects[1].tag += 10;
        PlaySound(sceneGameObjects[1].sounds[1]);
    }
    
    return this;
}
