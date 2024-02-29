#include "raylib.h"

#define GRAVITY 0.6f
#define JUMP_FORCE 15.0f

int main(){
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Jump!");

    Texture2D dino = LoadTexture("textures/textures/blob.png");
    Texture2D obstacle = LoadTexture("textures/textures/obstacles.png");

    float dinoPosY = screenHeight - dino.height * 1.0f; 
    float dinoVelY = 0;

    Rectangle dinoCollision = {0, dinoPosY, dino.width * 0.08f, dino.height * 0.08f}; 
    Rectangle obstacleCollision = {screenWidth, screenHeight - obstacle.height * 0.04f, obstacle.width * 0.04f, obstacle.height * 0.04f}; 

    bool obstacleActive = false;
    bool gameOver = false;
    bool restartClicked = false;

    Rectangle restartButton = {screenWidth / 2 - 100, screenHeight / 2 + 40, 200, 50};

    SetTargetFPS(60);

    while (!WindowShouldClose()){
        if (!gameOver && !restartClicked){
            if (IsKeyPressed(KEY_SPACE) && dinoPosY >= screenHeight - dino.height * 0.1f){ 
                dinoVelY = -JUMP_FORCE;
            }

            dinoVelY += GRAVITY;
            dinoPosY += dinoVelY;

            if (dinoPosY >= screenHeight - dino.height * 0.1f){ 
                dinoPosY = screenHeight - dino.height * 0.1f; 
                dinoVelY = 0;
            }

            dinoCollision.y = dinoPosY; 
            if (!obstacleActive){
                obstacleCollision.x = static_cast<float>(screenWidth);
                obstacleActive = true;
            } else{
                obstacleCollision.x -= 6;
                if (obstacleCollision.x + obstacleCollision.width < 0){
                    obstacleActive = false;
                }
            }

            if (CheckCollisionRecs(dinoCollision, obstacleCollision)){
                gameOver = true;
            }
        }

        //restart button click
        if (gameOver && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(GetMousePosition(), restartButton)){
            gameOver = false;
            restartClicked = true;
            dinoPosY = screenHeight - dino.height * 0.1f;
            dinoCollision.y = dinoPosY; 
            obstacleCollision.x = screenWidth; 
        }

        //restart click state
        if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            restartClicked = false;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        //draw "dinosaur"
        DrawTextureEx(dino, {0, dinoPosY}, 0, 0.1f, WHITE); 

        //add obstacles
        if (obstacleActive){
            DrawTextureEx(obstacle, {obstacleCollision.x, obstacleCollision.y}, 0, 0.05f, WHITE); 
        }

        if (gameOver){
            DrawText("Game Over!", screenWidth / 2 - MeasureText("Game Over!", 40) / 2, screenHeight / 2 - 20, 40, RED);
            DrawRectangleLines(static_cast<int>(restartButton.x), static_cast<int>(restartButton.y),
                               static_cast<int>(restartButton.width), static_cast<int>(restartButton.height), BLACK);
            DrawText("Restart", screenWidth / 2 - MeasureText("Restart", 20) / 2, screenHeight / 2 + 55, 20, BLACK);
        }

        EndDrawing();
    }

    UnloadTexture(dino);
    UnloadTexture(obstacle);
    CloseWindow();

    return 0;
}