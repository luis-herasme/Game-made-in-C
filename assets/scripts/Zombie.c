
struct GameObject zombiUpdate (struct GameObject this, struct GameObject GameObjects[]) {
    DrawRectangle(this.position.x, this.position.y, this.size.x, 3, BLACK);
    DrawRectangle(this.position.x, this.position.y, this.size.x * this.vida, 3, RED);
    
    Vector2 diference;

    diference.x = this.position.x - GameObjects[1].position.x;
    diference.y = this.position.y - GameObjects[1].position.y;

    float difMag = mag(diference);

    diference.x /= difMag;
    diference.y /= difMag;
    
    this.position.x -= diference.x;
    this.position.y -= diference.y;
    
    this.rotation = atan2(diference.y, diference.x);
    this.rotation *= 57.2958;
    this.rotation += 270;
    
    return this;    
}

struct GameObject zombiCollision (struct GameObject this, struct GameObject other) {
    if (other.tag == 3) {
        this.vida -= 0.1;
    }
  
    if (this.vida < 0) {
        this.deleted = 1;
    }
  
    return this;    
}