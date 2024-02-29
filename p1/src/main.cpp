#include "raylib.h"
#include <cstring>
#include <cstdlib>
#include <ctime>   
#include <cstdio>  

#define ROWS 3
#define COLS 3

#define SQUARE_SIZE 100
#define BOARD_OFFSET_X 50
#define BOARD_OFFSET_Y 50
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50

typedef enum {EMPTY, PLAYER_X, PLAYER_O} CellState;

CellState board[ROWS][COLS];
bool isPlayerXTurn = true;
bool gameOver = false;
char winnerMessage[20] = "";
int scorePlayerX = 0;
int scorePlayerO = 0;
CellState startingPlayer = PLAYER_O; //player O starts first

Rectangle resetButton;
Rectangle playButton;

enum GameState { PLAYING, RESET };
GameState gameState = PLAYING;

void InitGame() {
    //initialize the board to begin EMPTY
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = EMPTY;
        }
    }

    //alternate between player O and player X starting
    if (startingPlayer == PLAYER_O)
        startingPlayer = PLAYER_X;
    else
        startingPlayer = PLAYER_O;

    isPlayerXTurn = (startingPlayer == PLAYER_X);

    gameOver = false;
    std::strcpy(winnerMessage, "");
}

void CheckWinner() {
    //check rows, columns, and diagonals for a winner
    for (int i = 0; i < ROWS; i++) {
        if (board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            gameOver = true;
            if (board[i][0] == PLAYER_X) {
                std::strcpy(winnerMessage, "X Wins!");
                scorePlayerX++;
            }
            else {
                std::strcpy(winnerMessage, "O Wins!");
                scorePlayerO++;
            }
            return;
        }

        if (board[0][i] != EMPTY && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            gameOver = true;
            if (board[0][i] == PLAYER_X) {
                std::strcpy(winnerMessage, "X Wins!");
                scorePlayerX++;
            }
            else {
                std::strcpy(winnerMessage, "O Wins!");
                scorePlayerO++;
            }
            return;
        }
    }

    //check for diagonal wins
    if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        gameOver = true;
        if (board[0][0] == PLAYER_X) {
            std::strcpy(winnerMessage, "X Wins!");
            scorePlayerX++;
        }
        else {
            std::strcpy(winnerMessage, "O Wins!");
            scorePlayerO++;
        }
        return;
    }

    if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        gameOver = true;
        if (board[0][2] == PLAYER_X) {
            std::strcpy(winnerMessage, "X Wins!");
            scorePlayerX++;
        }
        else {
            std::strcpy(winnerMessage, "O Wins!");
            scorePlayerO++;
        }
        return;
    }

    //draw???
    bool isDraw = true;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == EMPTY) {
                isDraw = false;
                break;
            }
        }
    }

    if (isDraw){
        gameOver = true;
        std::strcpy(winnerMessage, "Draw!");
    }
}

void UpdateGame(){
    if (gameState == PLAYING){
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !gameOver){
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            int row = (mouseY - BOARD_OFFSET_Y) / SQUARE_SIZE;
            int col = (mouseX - BOARD_OFFSET_X) / SQUARE_SIZE;

            if (row >= 0 && row < ROWS && col >= 0 && col < COLS && board[row][col] == EMPTY){
                board[row][col] = isPlayerXTurn ? PLAYER_X : PLAYER_O;
                isPlayerXTurn = !isPlayerXTurn;

                CheckWinner();
            }
        }

        //reset button 
        if (gameOver) {
            gameState = RESET;
        }
    } else if (gameState == RESET) {
        //reset game once button is clicked
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), resetButton)) {
            InitGame();
            gameState = PLAYING;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), playButton)) {
            gameState = PLAYING;
        }
    }
}

void DrawGame() {
    //clear the screen
    BeginDrawing();
    ClearBackground(RAYWHITE);

    //draw board
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            //grids
            Rectangle square = {(float)(BOARD_OFFSET_X + j * SQUARE_SIZE),
                                (float)(BOARD_OFFSET_Y + i * SQUARE_SIZE),
                                (float)SQUARE_SIZE,
                                (float)SQUARE_SIZE};
            DrawRectangleRec(square, LIGHTGRAY);

            //X's & O's
            if (board[i][j] == PLAYER_X) {
                float xPosition = square.x + (SQUARE_SIZE - MeasureText("X", SQUARE_SIZE)) / 2;
                float yPosition = square.y + (SQUARE_SIZE - MeasureText("X", SQUARE_SIZE)) / 2 - SQUARE_SIZE / 10; // Move up a bit more
                DrawText("X", xPosition, yPosition, SQUARE_SIZE, BLUE);
            } else if (board[i][j] == PLAYER_O) {
                float xPosition = square.x + (SQUARE_SIZE - MeasureText("O", SQUARE_SIZE)) / 2;
                float yPosition = square.y + (SQUARE_SIZE - MeasureText("O", SQUARE_SIZE)) / 2 - SQUARE_SIZE / 10; // Move up a bit more
                DrawText("O", xPosition, yPosition, SQUARE_SIZE, RED);
            }
        }
    }

    //grid lines
    for (int i = 1; i < ROWS; i++) {
        DrawLine(BOARD_OFFSET_X, BOARD_OFFSET_Y + i * SQUARE_SIZE, BOARD_OFFSET_X + COLS * SQUARE_SIZE, BOARD_OFFSET_Y + i * SQUARE_SIZE, BLACK);
        DrawLine(BOARD_OFFSET_X, BOARD_OFFSET_Y + i * SQUARE_SIZE + 1, BOARD_OFFSET_X + COLS * SQUARE_SIZE, BOARD_OFFSET_Y + i * SQUARE_SIZE + 1, BLACK); // Bolder line
    }
    for (int j = 1; j < COLS; j++) {
        DrawLine(BOARD_OFFSET_X + j * SQUARE_SIZE, BOARD_OFFSET_Y, BOARD_OFFSET_X + j * SQUARE_SIZE, BOARD_OFFSET_Y + ROWS * SQUARE_SIZE, BLACK);
        DrawLine(BOARD_OFFSET_X + j * SQUARE_SIZE + 1, BOARD_OFFSET_Y, BOARD_OFFSET_X + j * SQUARE_SIZE + 1, BOARD_OFFSET_Y + ROWS * SQUARE_SIZE, BLACK); // Bolder line
    }

    //draw whose turn it is (only if the game is still ongoing)
    if (!gameOver) {
        char turnMessage[20];
        sprintf(turnMessage, "Turn: %s", isPlayerXTurn ? "Player X" : "Player O");
        float textWidth = MeasureText(turnMessage, 20);
        float textX = (GetScreenWidth() - textWidth) / 2;
        DrawText(turnMessage, textX, 10, 20, BLACK);
    }

    //scoreboard
    char scoreXText[20], scoreOText[20];
    sprintf(scoreXText, "Player X: %d", scorePlayerX);
    sprintf(scoreOText, "Player O: %d", scorePlayerO);
    DrawText(scoreXText, 10, GetScreenHeight() - 50, 20, BLUE);
    DrawText(scoreOText, 10, GetScreenHeight() - 30, 20, RED);

    if (gameState == RESET) {
        DrawRectangleRec(resetButton, GRAY);

        //center the text
        float textX = resetButton.x + (resetButton.width - MeasureText("Reset", 20)) / 2;
        float textY = resetButton.y + (resetButton.height - 20) / 2;
        DrawText("Reset", textX, textY, 20, WHITE);
    }

    //display winner
    if (gameOver) {
        Color textColor;
        if (std::strcmp(winnerMessage, "X Wins!") == 0) {
            textColor = BLUE;
        } else if (std::strcmp(winnerMessage, "O Wins!") == 0) {
            textColor = RED;
        } else {
            textColor = BLACK;
        }

        float textWidth = MeasureText(winnerMessage, 40);
        float textX = (GetScreenWidth() - textWidth) / 2;

        DrawText(winnerMessage, textX, 10, 40, textColor);
    }

    EndDrawing();
}

int main() {
    //initialization
    const int screenWidth = 400;
    const int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "Tic Tac Toe");
    SetTargetFPS(60);

    InitGame();

    resetButton = {(screenWidth - BUTTON_WIDTH) / 2, (screenHeight - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT};
    playButton = {(screenWidth - BUTTON_WIDTH) / 2, (screenHeight - BUTTON_HEIGHT) / 2 + 60, BUTTON_WIDTH, BUTTON_HEIGHT};

    //main game loop
    while (!WindowShouldClose()){

        //update
        UpdateGame();

        //draw
        DrawGame();
    }

    //cleanup
    CloseWindow();

    return 0;
}