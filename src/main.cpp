#include "raylib.h"
#include "Grid.h"
#include "Constants.h"
#include "Enemy.h"

Grid grid;
vector<Enemy> enemies;
float enemySpawnTimer;
float enemySpawnDelay;
int enemyCounter;
void RemoveEnemy(Enemy* enemy)
{
    int enemyId = enemy->Id;
    enemies.erase(std::remove_if(enemies.begin(), // from start of list
                                  enemies.end(),   // to the end
                                  [enemyId](const Enemy &e)
                                  {
                                      return e.Id == enemyId;
                                  }), //  moves all items to be removed to the end of the 
                                      // list, then returns start of range to erase
                   enemies.end());
}
void SetEnemyNextTargetPosition(Enemy* enemy)
{
    Cell enemyTargetCell = grid.GetNextPoint(enemy->cellPostion.x, enemy->cellPostion.y);

    //Enemy reached to final target - Destroy it
    if(enemy->cellPostion.x == enemyTargetCell.positionX && enemy->cellPostion.y == enemyTargetCell.positionY)
    {
        RemoveEnemy(enemy);
        return;
    }

    enemy->SetCellPosition((Vector2){enemyTargetCell.positionX, enemyTargetCell.positionY});
    Vector2 targetPos = {enemyTargetCell.positionX * cellSize + cellSize / 2, enemyTargetCell.positionY*cellSize + cellSize / 2};
    enemy->SetTarget(targetPos);
}
Vector2 GetRandomSpawnCellPosition()
{
    Vector2 spawnPos;
    int randNum = GetRandomNumberInRange(4);
    switch (randNum)
    {
    case 0:
        spawnPos = {GetRandomNumberInRange(cols), 0};
        break;
    case 1:
        spawnPos = {0, GetRandomNumberInRange(rows)};
        break;
    case 2:
        spawnPos = {GetRandomNumberInRange(cols), rows - 1};
        break;
    case 3:
        spawnPos = {cols - 1, GetRandomNumberInRange(rows)};
        break;

    default:
        spawnPos = {GetRandomNumberInRange(cols), 0};
        break;
    }

    return spawnPos;
}
void SpawnNewEnemy()
{
    // Enemy starts at top-left corner
    Vector2 enemyCellPos = GetRandomSpawnCellPosition();
    Cell enemyCell = grid.GetCell(enemyCellPos.x, enemyCellPos.y);
    Vector2 enemyPos = {enemyCell.positionX * cellSize + cellSize/2, enemyCell.positionY * cellSize + cellSize/2};
    Enemy enemy(enemyPos, enemyCounter++);
    enemy.SetCellPosition(enemyCellPos);

    
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

    enemySpawnDelay = 0.5f;
    //SpawnNewEnemy();

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        enemySpawnTimer += GetFrameTime();

        if(enemySpawnTimer > 0.5f)
        {
            SpawnNewEnemy();
            enemySpawnTimer = 0;
            enemySpawnDelay = GetRandomNumberInRange(7)/10;
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
