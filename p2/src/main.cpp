#include "raylib.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 450
#define GRID_SIZE 20

#define BOX_PADDING_X 50
#define BOX_PADDING_Y 50
#define BOX_WIDTH (SCREEN_WIDTH - BOX_PADDING_X * 2)
#define BOX_HEIGHT (SCREEN_HEIGHT - BOX_PADDING_Y * 2 + GRID_SIZE / 2)

typedef struct Snake{
    Vector2 position;
    Vector2 speed;
    Vector2 lastMoveDirection;
} Snake;

typedef struct Food{
    Vector2 position;
    bool active;
} Food;

bool CheckCollisionWithBox(Vector2 position){
    return (position.x < BOX_PADDING_X || position.x >= SCREEN_WIDTH - BOX_PADDING_X ||
            position.y < BOX_PADDING_Y || position.y >= SCREEN_HEIGHT - BOX_PADDING_Y);
}

int main(void){
    //initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake");

    //snake
    Snake snake = { {10 * GRID_SIZE + BOX_PADDING_X, 10 * GRID_SIZE + BOX_PADDING_Y}, {GRID_SIZE, 0}, {GRID_SIZE, 0}};
    int snakeLength = 1;
    Vector2 snakeTail[100] = {0};

    //food
    Food food = {{0}, false};

    //retry button
    Rectangle retryButton = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, 100, 40};

    bool gameOver = false;
    bool retryClicked = false;

    int score = 0;

    SetTargetFPS(10);

    while (!WindowShouldClose()) //main game loop
    {
        //update
        if (!gameOver){
            if (!food.active){
                food.position = (Vector2){static_cast<float>(GetRandomValue(0, (BOX_WIDTH / GRID_SIZE) - 1) * GRID_SIZE) + BOX_PADDING_X,
                                          static_cast<float>(GetRandomValue(0, ((BOX_HEIGHT - GRID_SIZE) / GRID_SIZE) - 1) * GRID_SIZE) + BOX_PADDING_Y};
                food.active = true;
            }

            for (int i = snakeLength - 1; i > 0; --i){
                snakeTail[i] = snakeTail[i - 1];
            }
            snakeTail[0] = snake.position;

            snake.position.x += snake.speed.x;
            snake.position.y += snake.speed.y;

            //adjust snake position to align with the grid
            snake.position.x = (static_cast<int>((snake.position.x - BOX_PADDING_X) / GRID_SIZE) * GRID_SIZE) + BOX_PADDING_X;
            snake.position.y = (static_cast<int>((snake.position.y - BOX_PADDING_Y) / GRID_SIZE) * GRID_SIZE) + BOX_PADDING_Y;

            //input handling
            if (IsKeyPressed(KEY_RIGHT) && snake.lastMoveDirection.x == 0){
                snake.speed = (Vector2){GRID_SIZE, 0};
                snake.lastMoveDirection = (Vector2){GRID_SIZE, 0};
            } else if (IsKeyPressed(KEY_LEFT) && snake.lastMoveDirection.x == 0){
                snake.speed = (Vector2){-GRID_SIZE, 0};
                snake.lastMoveDirection = (Vector2){-GRID_SIZE, 0};
            } else if (IsKeyPressed(KEY_UP) && snake.lastMoveDirection.y == 0){
                snake.speed = (Vector2){0, -GRID_SIZE};
                snake.lastMoveDirection = (Vector2){0, -GRID_SIZE};
            } else if (IsKeyPressed(KEY_DOWN) && snake.lastMoveDirection.y == 0){
                snake.speed = (Vector2){0, GRID_SIZE};
                snake.lastMoveDirection = (Vector2){0, GRID_SIZE};
            }

            if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && snake.lastMoveDirection.x == 0){
                snake.speed = (Vector2){GRID_SIZE, 0};
                snake.lastMoveDirection = (Vector2){GRID_SIZE, 0};
            } else if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && snake.lastMoveDirection.x == 0){
                snake.speed = (Vector2){-GRID_SIZE, 0};
                snake.lastMoveDirection = (Vector2){-GRID_SIZE, 0};
            } else if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && snake.lastMoveDirection.y == 0){
                snake.speed = (Vector2){0, -GRID_SIZE};
                snake.lastMoveDirection = (Vector2){0, -GRID_SIZE};
            } else if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && snake.lastMoveDirection.y == 0){
                snake.speed = (Vector2){0, GRID_SIZE};
                snake.lastMoveDirection = (Vector2){0, GRID_SIZE};
            }

            //collision with walls or self
            if (CheckCollisionWithBox(snake.position) || snake.position.x >= SCREEN_WIDTH - GRID_SIZE ||
                snake.position.y >= SCREEN_HEIGHT - GRID_SIZE){
                gameOver = true;
            }
            for (int i = 1; i < snakeLength; ++i){
                if (snake.position.x == snakeTail[i].x && snake.position.y == snakeTail[i].y){
                    gameOver = true;
                    break;
                }
            }

            //collision with food
            if (CheckCollisionRecs((Rectangle){snake.position.x, snake.position.y, GRID_SIZE, GRID_SIZE},
                                   (Rectangle){food.position.x, food.position.y, GRID_SIZE, GRID_SIZE})){
                food.active = false;
                snakeLength++;
                score += 10;
            }
        } else { //game over
            if (CheckCollisionPointRec(GetMousePosition(), retryButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                gameOver = false;
                retryClicked = true;

                //reset snake and food position
                snake.position = (Vector2){10 * GRID_SIZE + BOX_PADDING_X, 10 * GRID_SIZE + BOX_PADDING_Y};
                snake.speed = (Vector2){GRID_SIZE, 0};
                snake.lastMoveDirection = (Vector2){GRID_SIZE, 0};
                snakeLength = 1;
                food.active = false;
                score = 0;
            } else{
                retryClicked = false;
            }
        }

        //draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //draw box outline
        DrawRectangleLines(BOX_PADDING_X, BOX_PADDING_Y, BOX_WIDTH, BOX_HEIGHT, BLACK);

        //draw snake
        for (int i = 0; i < snakeLength; ++i){
            DrawRectangle(snakeTail[i].x, snakeTail[i].y, GRID_SIZE, GRID_SIZE, DARKGREEN);
        }

        //draw food
        if (food.active){
            DrawRectangle(food.position.x, food.position.y, GRID_SIZE, GRID_SIZE, RED);
        }

        //display retry button
        if (gameOver){
            DrawRectangleLinesEx(retryButton, 3, GRAY);
            DrawText("Retry", static_cast<int>(retryButton.x) + 20, static_cast<int>(retryButton.y) + 10, 20, BLACK);
        }

        //update scoreboard
        DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);

        EndDrawing();
    }

    //de-initialization
    CloseWindow();

    return 0;
}