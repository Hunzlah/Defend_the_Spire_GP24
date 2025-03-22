#include "raylib.h"
#include "Grid.h"
#include "Constants.h"
#include "Enemy.h"

Grid grid;
vector<Enemy> enemies;
float enemySpawnTimer;

void SetEnemyNextTargetPosition(Enemy* enemy)
{
    Cell enemyTargetCell = grid.GetNextPoint(enemy->cellPostion.x, enemy->cellPostion.y);
    enemy->SetCellPosition((Vector2){enemyTargetCell.positionX, enemyTargetCell.positionY});
    Vector2 targetPos = {enemyTargetCell.positionX * cellSize + cellSize / 2, enemyTargetCell.positionY*cellSize + cellSize / 2};
    enemy->SetTarget(targetPos);
}
void SpawnNewEnemy()
{
    // Enemy starts at top-left corner
    Vector2 enemyPos = { 0.0f, 0.0f };
    
    Enemy enemy(enemyPos);
    enemy.SetCellPosition(enemyPos);

    
    SetEnemyNextTargetPosition(&enemy);

    enemies.push_back(enemy);
}
int main() {
    InitWindow(screenWidth, screenHeight, "Grid with Tower and Enemy");
    SetTargetFPS(60);

    

    // Tower at center
    int towerX = cols / 2;
    int towerY = rows / 2;
    grid.Initialize();
    grid.SetTowerCell(towerX, towerY, TOWER);
    grid.SetPathToTower(towerX, towerY);

    //SpawnNewEnemy();

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        enemySpawnTimer += GetFrameTime();

        if(enemySpawnTimer > 2)
        {
            SpawnNewEnemy();
            enemySpawnTimer = 0;
        }

        for(Enemy& enemy : enemies )
        {
            enemy.Update();
            if(enemy.CurrentDistanceToTarget() <= 1)
            {
                SetEnemyNextTargetPosition(&enemy);
            }
            enemy.Draw();
        }
        

        

        grid.Draw();
        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
