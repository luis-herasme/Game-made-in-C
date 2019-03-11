
float rotation = 0;

struct GameObject updateObject (struct GameObject this, struct GameObject GameObjects[]) {
   
    DrawRectangle(this.position.x, this.position.y, this.size.x, 3, BLACK);
    DrawRectangle(this.position.x, this.position.y, this.size.x * this.vida, 3, RED);
    
    if (IsKeyDown(KEY_W))
    {
        this.position.x -= this.velocity.x;
        this.position.y -= this.velocity.y;
    }
   
    if (IsKeyDown(KEY_S))
    {
        this.position.x += this.velocity.x;
        this.position.y += this.velocity.y;
    }
    
    if (IsKeyDown(KEY_A))
    {
        this.velocity = rotateVector(this.velocity, -0.05);
        rotation -= 0.05;
    }
    
    if (IsKeyDown(KEY_D))
    {
        this.velocity = rotateVector(this.velocity, 0.05);
        rotation += 0.05;
    }
    
    if (IsKeyPressed(KEY_E))
    {
        if (this.tag > 0) {
            PlaySound(this.sounds[0]);
        }
    }
    
    this.rotation = rotation;
    this.rotation *= 57.2958;
    this = checkInsideBounds(this, 2 * 1200, 0, 2400, 0);

    return this;
}

struct GameObject collisionPlayer (struct GameObject this, struct GameObject other) {
   // DrawText("Collision!", this.position.x, this.position.y, 20, RED);
   if (other.tag == 5) {
        this.vida -= 0.0001;
    }
    
    return this;
}
