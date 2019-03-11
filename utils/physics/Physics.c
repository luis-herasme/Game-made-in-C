
struct GameObject checkCollision(struct GameObject rect1, struct GameObject rect2)
{
    float dx            = (rect1.position.x + rect1.size.x / 2) - (rect2.position.x + rect2.size.x / 2);
    float dy            = (rect1.position.y + rect1.size.y / 2) - (rect2.position.y + rect2.size.y / 2);

    float width         = (rect1.size.x + rect2.size.x) / 2;
    float height        = (rect1.size.y + rect2.size.y) / 2;

    float crossWidth    = width * dy;
    float crossHeight   = height * dx;

    if (fabs(dx) <= width && fabs(dy) <= height)
    {
        if (crossWidth > crossHeight)
        {
            if ((crossWidth >= (-crossHeight)))
            {
                rect1 = rect1.collision(rect1, rect2);
                rect1.position.y += (height - dy);
            }
            else
            {
                rect1 = rect1.collision(rect1, rect2);
                rect1.position.x -= (dx + width);
            }
        }
        else
        {
            if ((crossWidth >= -(crossHeight)))
            {
                rect1 = rect1.collision(rect1, rect2);
                rect1.position.x += (width - dx);
            }
            else
            {
                rect1 = rect1.collision(rect1, rect2);
                rect1.position.y -= (dy + height);
            }
        }
    }
    return rect1;
}

struct GameObject checkInsideBounds(struct GameObject this, int boundXMax, int boundXMin, int boundYMax, int boundYMin)
{
    if (this.position.x < boundXMin)
    {
        this.position.x = boundXMin;
    }
    else if (this.position.x + this.size.x > boundXMax)
    {
        this.position.x = boundXMax - this.size.x;
    }

    if (this.position.y < boundYMin)
    {
        this.position.y = boundYMin;  
    }
    else if (this.position.y + this.size.y > boundYMax)
    {
        this.position.y = boundYMax - this.size.y;
    }

    return this;
}
