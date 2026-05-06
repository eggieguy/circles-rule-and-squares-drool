#include "raylib.h"
#include "raymath.h"
#include <cmath>

struct absoluteSquare{
    int num;
    Color color;
};

int main(){
//variables
    int trackerX = 0;
    int trackerY = 0;
    int numSquares = 0;
    int screenWidth = 1600;
    int screenHeight = 960;
    int score = 0;
    int freezeFrames = 0;
    int maxFreeze = 5;
    int setX;
    int setY;
    int minTime = 1.0f;
    int subtraction;
    int counter = 0;
    float squareTimer = 0.0f;
    bool canMove = true;
    bool notSame = false;
    absoluteSquare grid[23][40] = {0,RAYWHITE};
    Vector2 savePoint;
    Color colors[18] = {
        LIGHTGRAY,
        GRAY, DARKGRAY, YELLOW,
        GOLD, ORANGE, PINK, RED, MAROON,
        GREEN, LIME, DARKGREEN, SKYBLUE,
        BLUE, DARKBLUE, PURPLE, VIOLET,
        DARKPURPLE
    };
//game and window settings defined and initialised
    SetTargetFPS(60);
    InitWindow(screenWidth, screenHeight, "Circles Rule!");
    Vector2 ballpos = {static_cast<float>(screenWidth)/2, static_cast<float>(screenHeight)/2};
    SetTargetFPS(60);
    DisableCursor();
//game loop
    while(!WindowShouldClose()){
        if (canMove){
            ballpos = GetMousePosition();
        } else{
            savePoint = ballpos;
            setX = static_cast<int>(savePoint.x);
            setY = static_cast<int>(savePoint.y);
            SetMousePosition(setX,setY);
            freezeFrames++;
        }
        ballpos = Vector2Clamp(GetMousePosition(), {30,70},{(float)GetScreenWidth() - 30,(float)GetScreenHeight() - 30});

        if (freezeFrames == maxFreeze){
            canMove = true;
            freezeFrames = 0;
        }
        squareTimer += GetFrameTime();
        subtraction = std::floor(score/10) - 10 * std::floor(score/100);
        minTime -= subtraction/10;

        if (squareTimer >= minTime){
            for (int i = 0; i < numSquares; i++){
                notSame = false;
                while (!notSame){
                    int squareRow = GetRandomValue(0,23);
                    int squareColumn = GetRandomValue(0,40);
                    if (grid[squareRow][squareColumn].num == 0){
                        grid[squareRow][squareColumn] = {1, colors[GetRandomValue(0,17)]};
                        notSame = true;
                    }
                }
            }
            squareTimer = 0;
        }
        if (subtraction == 0){
            if (counter == 0){
                numSquares++;
                counter++;
            }
        } else{
            counter = 0;
        }

        notSame = false;
        BeginDrawing();
            ClearBackground(RAYWHITE);
            trackerY = 0;
            for (auto& row : grid){
                    trackerX = 0;
                for (auto& item : row){
                    if (item.num == 1){
                        DrawRectangle(trackerX * 40, trackerY * 40 + 40, 40, 40, item.color);
                        DrawRectangleLines(trackerX * 40,trackerY * 40 + 40, 40, 40, BLACK);
                    } else {
                        DrawRectangle(trackerX * 40, trackerY * 40 + 40, 40, 40, RAYWHITE);
                    }
                    if (CheckCollisionCircleRec(ballpos, 30, {trackerX * 40, trackerY * 40 + 40, 40, 40})){
                        if (grid[trackerY][trackerX].num == 1){
                            score++;
                            canMove = false;
                            grid[trackerY][trackerX].num = 0;
                        }
                    }
                    trackerX++;
                }
                trackerY++;
            }
            if (freezeFrames == maxFreeze){
                DrawCircleV(savePoint, 30, BLUE);
            } else{
                DrawCircleV(ballpos, 30, BLUE);
            }
            DrawText(TextFormat("Score: %i",score),3,1,39,BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
