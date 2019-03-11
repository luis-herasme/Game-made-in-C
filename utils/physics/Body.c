
#include <math.h>
#include "../vector.c"

int MAX_X = 800;
int MAX_Y = 600;

float RESTITUTION = 0.8;
float FRICTION = 0.8;

struct Body
{
    struct vector position;
    struct vector velocity;
    struct vector acceleration;
    int width;
    int height;
};

struct Body createBody();
struct Body updateBody(struct Body body);
struct Body updateForces(struct Body body);
struct Body checkCollision(struct Body rect1, struct Body rect2);
struct Body checkInsideBounds(struct Body body, int boundXMax, int boundXMin, int boundYMax, int boundYMin);

struct Body checkCollision(struct Body rect1, struct Body rect2)
{
    float dx = (rect1.position.x + rect1.width / 2) - (rect2.position.x + rect2.width / 2);
    float dy = (rect1.position.y + rect1.height / 2) - (rect2.position.y + rect2.height / 2);
    float width = (rect1.width + rect2.width) / 2;
    float height = (rect1.height + rect2.height) / 2;
    float crossWidth = width * dy;
    float crossHeight = height * dx;

    if (abs((int)dx) <= width && abs((int)dy) <= height)
    {
        if (crossWidth > crossHeight)
        {
            if ((crossWidth >= (-crossHeight)))
            {
                rect1.velocity.y *= -RESTITUTION;
                rect1.position.y += (height - dy);
            }
            else
            {
                rect1.velocity.x *= -RESTITUTION;
                rect1.position.x -= (dx + width);
            }
        }
        else
        {
            if ((crossWidth >= -(crossHeight)))
            {
                rect1.velocity.x *= -RESTITUTION;
                rect1.position.x += (width - dx);
            }
            else
            {
                rect1.velocity.y *= -RESTITUTION;
                rect1.position.y -= (dy + height);
            }
        }
    }
    return rect1;
}

/*
struct Body checkCollision(struct Body rect1, struct Body rect2)
{

    if (rect1.position.x < rect2.position.x + rect2.width &&
        rect1.position.x + rect1.width > rect2.position.x &&
        rect1.position.y < rect2.position.y + rect2.height &&
        rect1.position.y + rect1.height > rect2.position.y)
    {

        if (rect1.position.y <= rect2.position.y && rect1.position.y + rect1.height >= rect2.position.y)
        {
            float dy = (rect1.position.y + rect1.height) - rect2.position.y;
            rect1.position.y -= dy;
            rect1.velocity.y *= -RESTITUTION;
        }
        else if (rect2.position.y <= rect1.position.y && rect2.position.y + rect2.height >= rect1.position.y)
        {

            float dy = (rect2.position.y + rect2.height) - rect1.position.y;
            rect1.position.y += dy;
            rect1.velocity.y *= -RESTITUTION;
        }
        else if (rect2.position.x <= rect1.position.x && rect2.position.x + rect2.width >= rect1.position.x)
        {

            float dx = (rect2.position.x + rect2.width) - rect1.position.x;
            rect1.position.x += dx;
            rect1.velocity.x *= -RESTITUTION;
        }
        else if (rect1.position.x <= rect2.position.x && rect1.position.x + rect1.width >= rect2.position.x)
        {
            float dx = (rect1.position.x + rect1.width) - rect2.position.x;
            rect1.position.x -= dx;
            rect1.velocity.x *= -RESTITUTION;
        }
    }

    return rect1;
}


*/

struct Body createBody(struct vector position, struct vector size)
{

    struct vector velocity = {0, 0};
    struct vector acceleration = {0, 0};
    struct Body body = {
        position,
        velocity,
        acceleration,
        (int)size.x,
        (int)size.y};
    return body;
}

struct Body updateBody(struct Body body)
{
    body = updateForces(body);
    body = checkInsideBounds(body, MAX_X, 0, MAX_Y, 0);
    return body;
}

struct Body updateForces(struct Body body)
{
    body.position.x += body.velocity.x;
    body.position.y += body.velocity.y;

    body.velocity.x *= FRICTION;
    body.velocity.y *= FRICTION;

    body.velocity.x += body.acceleration.x;
    body.velocity.y += body.acceleration.y;

    body.acceleration.x = 0;
    body.acceleration.y = 0;

    return body;
}

struct Body checkInsideBounds(struct Body body, int boundXMax, int boundXMin, int boundYMax, int boundYMin)
{
    if (body.position.x < boundXMin)
    {
        body.position.x = boundXMin + 1;
        body.velocity.x *= -RESTITUTION;
    }
    else if (body.position.x + body.width > boundXMax)
    {
        body.position.x = boundXMax - body.width - 1;
        body.velocity.x *= -RESTITUTION;
    }

    if (body.position.y < boundYMin)
    {
        body.position.y = boundYMin + 1;
        body.velocity.y *= -RESTITUTION;
    }
    else if (body.position.y + body.height > boundYMax)
    {
        body.position.y = boundYMax - body.height - 1;
        body.velocity.y *= -RESTITUTION;
    }

    return body;
}
