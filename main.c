#include <raylib.h>
#include <stdio.h>

void callback(void *bufferData, unsigned int frames) {
  (void)bufferData;
  (void)frames;
}

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

  AttachAudioStreamProcessor(music.stream, callback);

  float time_played = 0.0f;
  float time_length = 0.0f;
  float time_duration = 0.0f;
  char time_played_str[8];
  char time_length_str[8];
  char time_duration_str[8];

  while (!WindowShouldClose()) {
    UpdateMusicStream(music);

    // Get user input
    if (IsKeyPressed(KEY_SPACE)) {
      if (IsMusicStreamPlaying(music))
        PauseMusicStream(music);
      else
        ResumeMusicStream(music);
    }

    // Update the counters
    time_played = GetMusicTimePlayed(music);
    time_length = GetMusicTimeLength(music);
    time_duration = time_played / time_length;
    if (time_duration > 1.0f)
      time_duration = 1.0f;

    sprintf(time_played_str, "%.2f", time_played);
    sprintf(time_length_str, "%.2f", time_length);
    sprintf(time_duration_str, "%.2f", time_duration);

    // Draw
    BeginDrawing();

    ClearBackground(BLACK);

    DrawText(time_played_str, 380, 170, 20, RAYWHITE);
    DrawText(time_length_str, 380, 200, 20, RAYWHITE);
    DrawText(time_duration_str, 380, 230, 20, RAYWHITE);

    EndDrawing();
  }

  UnloadMusicStream(music);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
