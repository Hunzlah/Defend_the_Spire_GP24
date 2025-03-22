#include "raylib.h"
#include "Grid.h"
#include "Constants.h"
#include "Enemy.h"




int main() {
    InitWindow(screenWidth, screenHeight, "Grid with Tower and Enemy");
    SetTargetFPS(60);

    Grid grid;

    // Tower at center
    int towerX = cols / 2;
    int towerY = rows / 2;
    grid.Initialize();
    grid.SetTowerCell(towerX, towerY, TOWER);
    grid.SetPathToTower(towerX, towerY);

    // Enemy starts at top-left corner
    Vector2 enemyPos = { 0.0f, 0.0f };
    Vector2 towerPos = { towerX * cellSize + cellSize / 2, towerY * cellSize + cellSize / 2 };
    Enemy enemy(enemyPos);
    enemy.SetCellPosition(enemyPos);
    Cell enemyTargetCell = grid.GetNextPoint(enemy.cellPostion.x, enemy.cellPostion.y);
    enemy.SetCellPosition((Vector2){enemyTargetCell.positionX, enemyTargetCell.positionY});
    Vector2 targetPos = {enemyTargetCell.positionX * cellSize + cellSize / 2, enemyTargetCell.positionY*cellSize + cellSize / 2};
    enemy.SetTarget(targetPos);

    while (!WindowShouldClose()) {
        enemy.Update();
        if(enemy.CurrentDistanceToTarget() <= 1)
        {
            enemyTargetCell = grid.GetNextPoint(enemy.cellPostion.x, enemy.cellPostion.y);
            enemy.SetCellPosition((Vector2){enemyTargetCell.positionX, enemyTargetCell.positionY});
            Vector2 targetPos = {enemyTargetCell.positionX * cellSize + cellSize / 2, enemyTargetCell.positionY*cellSize + cellSize / 2};
            enemy.SetTarget(targetPos);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        grid.Draw();
        enemy.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
