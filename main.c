#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LEN(xs) sizeof(xs) / sizeof(xs[0])

uint16_t global_frames[1024] = {0};
size_t global_frames_count = 0;

void callback(void *bufferData, unsigned int frames) {
  if (frames > ARRAY_LEN(global_frames) / 2) {
    frames = ARRAY_LEN(global_frames) / 2;
  }
  memcpy(global_frames, bufferData, sizeof(int16_t) * frames * 2);
  global_frames_count = frames;
}

int main(int argc, char **argv) {
  const int init_w = 800;
  const int init_h = 450;
  const char *title = "vivi";
  InitWindow(init_w, init_h, title);
  SetTargetFPS(30);
  InitAudioDevice();

  Music music = LoadMusicStream("assets/JNATHYN - Genesis.wav");
  PlayMusicStream(music);
  SetMusicVolume(music, 0.5f);

  printf("music.frameCount = %u\n", music.frameCount);
  printf("music.stream.sampleRate = %u\n", music.stream.sampleRate);
  printf("music.stream.sampleSize = %u\n", music.stream.sampleSize);
  printf("music.stream.channels = %u\n", music.stream.channels);

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

    int w = GetRenderWidth();
    int h = GetRenderHeight();

    float cell_width = (float)GetRenderWidth() / global_frames_count;
    for (size_t i = 0; i < global_frames_count; ++i) {
      int16_t sample = *(int16_t *)&global_frames[i];
      if (sample > 0) {
        float t = (float)sample / INT16_MAX;
        DrawRectangle(i * cell_width, h / 2 - h / 2 * t, cell_width,
                      h / 2 + (h / 2 * t), RED);
      } else {
        float t = (float)sample / INT16_MIN;
        DrawRectangle(i * cell_width, h / 2, cell_width, h / 2 - (h / 2 * t),
                      RED);
      }
    }

    DrawText(time_played_str, 1, h - 24, 20, RAYWHITE);
    DrawText(time_duration_str, w / 2 - 10, h - 24, 20, RAYWHITE);
    DrawText(time_length_str, w - 64, h - 24, 20, RAYWHITE);

    EndDrawing();
  }

  UnloadMusicStream(music);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
