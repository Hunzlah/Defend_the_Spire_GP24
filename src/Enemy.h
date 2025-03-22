#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Constants.h"


// Enemy that moves toward tower
class Enemy {
    public:
        Vector2 position;
        Vector2 target;
        Vector2 cellPostion;
    
        Enemy(Vector2 pos) : position(pos) {}

        void SetTarget(Vector2 _target)
        {
            target = _target;
        }
        void SetCellPosition(Vector2 _cellPos)
        {
            cellPostion = _cellPos;
        }
        void Update() {
            Vector2 direction = { target.x - position.x, target.y - position.y };
            float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
            if (length > 1.0f) {
                direction.x /= length;
                direction.y /= length;
                position.x += direction.x * speed;
                position.y += direction.y * speed;
            }
        }
        float CurrentDistanceToTarget()
        {
            Vector2 direction = { target.x - position.x, target.y - position.y };
            float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
            return length;
        }
        void Draw() {
            DrawCircle((int)position.x, (int)position.y, 10, BLUE);
        }
    
    private:
        float speed = 1.5f;
    };