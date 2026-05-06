#include "raylib.h"
#include "raymath.h"

struct absoluteSquare{
    int num;
    Color color;
};

int main(){
//variables
    int trackerX = 0;
    int trackerY = 0;
    int screenWidth = 1600;
    int screenHeight = 960;
    float squareTimer = 0;
    int score = 0;
    bool canMove = true;
    int freezeFrames = 0;
    int maxFreeze = 10;
    absoluteSquare grid[23][40] = {0,RAYWHITE};
    int setX;
    int setY;
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
    InitWindow(screenWidth, screenHeight, "The Centre of All Pain In the Universe");
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
            DisableCursor();
            SetMousePosition(setX,setY);
            freezeFrames++;
        }
        ballpos = Vector2Clamp(GetMousePosition(), {30,70},{(float)GetScreenWidth() - 30,(float)GetScreenHeight() - 30});

        if (freezeFrames == maxFreeze){
            canMove = true;
            freezeFrames = 0;
        }
        squareTimer += GetFrameTime();

        if (squareTimer >= 1.0f){
            int squareRow = GetRandomValue(0,23);
            int squareColumn = GetRandomValue(0,40);
            grid[squareRow][squareColumn] = {1, colors[GetRandomValue(0,17)]};
            squareTimer = 0;
        }

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
            DrawText(TextFormat("Score: %i",score),0,0,40,BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
