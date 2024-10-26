#include <stdio.h>
#include <raylib.h>

int main(int argc, char **argv)
{
    const int w = 800;
    const int h = 450;
    const char *title = "vivi";
    InitWindow(w, h, title);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Hello, world!", 350, 200, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
