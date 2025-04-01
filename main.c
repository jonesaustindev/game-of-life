#include "raylib.h"
#include <math.h>
#include <stdio.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#define CELL_SIZE 10
#define CELL_WIDTH (SCREEN_WIDTH / CELL_SIZE)
#define CELL_HEIGHT (SCREEN_HEIGHT / CELL_SIZE)

int getNeighborCount(int currentGrid[CELL_HEIGHT][CELL_WIDTH], int x, int y) {
  int count = 0;

  for (int ny = -1; ny <= 1; ny++) {
    for (int nx = -1; nx <= 1; nx++) {
      if (ny == 0 && nx == 0) {
        continue;
      }

      int gridY = (y + ny + CELL_HEIGHT) % CELL_HEIGHT;
      int gridX = (x + nx + CELL_WIDTH) % CELL_WIDTH;

      count += currentGrid[gridY][gridX];
    }
  }

  return count;
}

void initGrid(int grid[CELL_HEIGHT][CELL_WIDTH]) {
  for (int y = 0; y < CELL_HEIGHT; y++) {
    for (int x = 0; x < CELL_WIDTH; x++) {
      // 0 = dead, 1 = alive
      grid[y][x] = 0;
    }
  }
}

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life");
  SetTargetFPS(60);

  int currentGen[CELL_HEIGHT][CELL_WIDTH];
  int nextGen[CELL_HEIGHT][CELL_WIDTH];

  initGrid(currentGen);
  initGrid(nextGen);

  bool isPlaying = false;

  float tickRate = 0.1f;
  float lastUpdateTime = 0.0f;

  char speedText[60];

  while (!WindowShouldClose()) {
    // update
    if (IsKeyPressed(KEY_SPACE)) {
      isPlaying = !isPlaying;
    }

    if (IsKeyPressed(KEY_R)) {
      isPlaying = false;
      initGrid(currentGen);
      initGrid(nextGen);
    }

    if (IsKeyPressed(KEY_UP)) {
      tickRate = fmax(0.01f, tickRate - 0.05f);
    }

    if (IsKeyPressed(KEY_DOWN)) {
      tickRate += 0.05f;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      Vector2 pos = GetMousePosition();
      int gridMouseY = (int)(pos.y / CELL_SIZE);
      int gridMouseX = (int)(pos.x / CELL_SIZE);

      if (gridMouseX >= 0 && gridMouseX < CELL_WIDTH && gridMouseY >= 0 &&
          gridMouseY < CELL_HEIGHT) {
        currentGen[gridMouseY][gridMouseX] = 1;
      }
    }

    ///////////
    // Rules //
    ///////////

    /* - Any live cell with fewer than two live neighbours dies, as if by
     * underpopulation.
     *
     * - Any live cell with two or three live neighbours lives on
     * to the next generation.
     *
     * - Any live cell with more than three live
     * neighbours dies, as if by overpopulation.
     *
     * - Any dead cell with exactly three live neighbours becomes a live cell,
     * as if by reproduction. **/

    if (isPlaying && (GetTime() - lastUpdateTime >= tickRate)) {
      lastUpdateTime = GetTime();

      for (int y = 0; y < CELL_HEIGHT; y++) {
        for (int x = 0; x < CELL_WIDTH; x++) {
          int neighborCount = getNeighborCount(currentGen, x, y);

          if (currentGen[y][x] == 1) {
            if (neighborCount == 2 || neighborCount == 3) {
              nextGen[y][x] = 1;
            }
          } else {
            if (neighborCount == 3) {
              nextGen[y][x] = 1;
            }
          }
        }
      }

      for (int y = 0; y < CELL_HEIGHT; y++) {
        for (int x = 0; x < CELL_WIDTH; x++) {
          currentGen[y][x] = nextGen[y][x];
          nextGen[y][x] = 0;
        }
      }
    }

    // draw
    BeginDrawing();

    ClearBackground(BLACK);

    if (isPlaying) {
      DrawText("Press SPACE to pause.", 20, 20, 20, LIGHTGRAY);
    } else {
      DrawText("Draw cells then press SPACE to play.", 20, 20, 20, LIGHTGRAY);
    }
    DrawText("Press R to reset.", 20, 50, 20, LIGHTGRAY);
    sprintf(speedText, "Speed: %.2f updates/sec. UP/DOWN to control the speed.",
            1.0f / tickRate);
    DrawText(speedText, 20, 80, 20, LIGHTGRAY);

    for (int y = 0; y < CELL_HEIGHT; y++) {
      for (int x = 0; x < CELL_WIDTH; x++) {
        if (currentGen[y][x] == 1) {
          DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE,
                        LIGHTGRAY);
        }
      }
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
