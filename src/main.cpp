#include "raylib.h"
#include "game.h"
#include "colors.h"
#include <iostream>
#include <thread>
double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}
int main()
{

    InitWindow(900, 870, "FILL UP PUZZLE TETRIS");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/SEASRN__.ttf", 64, 0, 0);

    Game game = Game();



    while (WindowShouldClose() == false)
    {

        float elapsedTime = GetTime();
        game.elapsed_time = static_cast<int>(elapsedTime);

        UpdateMusicStream(game.music);
        game.HandleInput();
        if (EventTriggered(0.2))
        {
            game.MoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(darkBlue);
        
        DrawTextEx(font, "Score", {765, 15}, 38, 2, WHITE);
       
        DrawTextEx(font, "Next", {765, 175}, 38, 2, WHITE);

        DrawTextEx(font, "Time Elapsed", { 660, 660 }, 38, 2, WHITE);


        if (game.gameOver)
        {
            DrawTextEx(font, "GAME", {720, 450}, 38, 2, WHITE);
            DrawTextEx(font, "OVER", { 720, 490 }, 38, 2, WHITE);
            
        }

        DrawRectangleRounded({720, 55, 170, 60}, 0.3, 6, lightBlue);

        //display output time
        char seconds[10];
        snprintf(seconds, sizeof(seconds), "%d", game.elapsed_time);
        Vector2 textSize_time = MeasureTextEx(font, seconds, 38, 2);
        DrawTextEx(font, seconds, { 690 + (170 - textSize_time.x) / 2, 700 }, 38, 2, WHITE);




        //display score
        char scoreText[10];
        snprintf(scoreText,sizeof(scoreText), "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {720 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({720, 215, 170, 180}, 0.3, 6, lightBlue);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}