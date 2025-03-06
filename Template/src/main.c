#include "raylib.h"
#include <stdlib.h>

int main(int argc, char ** argv){

    InitWindow(640, 480, "My Window!!");

    SetWindowState(FLAG_WINDOW_RESIZABLE);

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(IsKeyDown(KEY_SPACE) ? PURPLE : SKYBLUE);
        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}