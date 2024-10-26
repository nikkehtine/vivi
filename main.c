#include <raylib.h>
#include <stdio.h>

int main(int argc, char **argv) {
  const int w = 800;
  const int h = 450;
  const char *title = "vivi";
  InitWindow(w, h, title);
  SetTargetFPS(60);
  InitAudioDevice();

  Music music = LoadMusicStream("assets/JNATHYN - Genesis.wav");
  PlayMusicStream(music);
  SetMusicVolume(music, 0.5f);

  while (!WindowShouldClose()) {
    UpdateMusicStream(music);

    if (IsKeyPressed(KEY_SPACE)) {
      if (IsMusicStreamPlaying(music))
        PauseMusicStream(music);
      else
        ResumeMusicStream(music);
    }

    // Draw
    BeginDrawing();

    ClearBackground(RED);
    DrawText("Hello, world!", 350, 200, 20, BLACK);

    EndDrawing();
  }

  UnloadMusicStream(music);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
