
struct Vector2 rotateVector(struct Vector2 vector, float rotation)
{
   float tempx = vector.x;
   float tempy = vector.y;
   vector.x = tempx * cos(rotation) - tempy * sin(rotation);
   vector.y = tempx * sin(rotation) + tempy * cos(rotation);
   return vector;
}

float mag (struct Vector2 vector) {
    return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}
