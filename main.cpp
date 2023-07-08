#include "trex.h"
#include <raylib.h>

int main() {
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Trex Run");
  SetTargetFPS(60);

  const Texture2D GAME_SPRITES = LoadTexture("resources/all-sprites.png");

  UniqueSpriteGroup TREX = {
      .texture = LoadTexture("resources/trex.png"),
      .start = {0.f, 0.f},
      .sprite_count = 6,
      .sprite_size = {(float)TREX.texture.width / TREX.sprite_count,
                      (float)TREX.texture.height},
      .current_frame = 0,
  };

  float ground_level_y = SCREEN_HEIGHT - 150; // rest/running height

  const SpriteGroup PTERS = {
      .texture = GAME_SPRITES,
      .start = {255.f, 0.f},
      .sprite_count = 2,
      .sprite_size = {95.f, (float)PTERS.texture.height - 55},
  };

  const SpriteGroup SMALL_CACTI = {
      .texture = GAME_SPRITES,
      .start = {444.f, 0.f},
      .sprite_count = 6,
      .sprite_size = {34.f, (float)SMALL_CACTI.texture.height - 55},
  };

  const SpriteGroup LARGE_CACTI = {
      .texture = GAME_SPRITES,
      .start = {450.f + 204.f, 0.f},
      .sprite_count = 4,
      .sprite_size = {49.f, (float)LARGE_CACTI.texture.height - 30},
  };

  const SpriteGroup CACTI_GROUP = {
      .texture = GAME_SPRITES,
      .start = {450.f + 204.f + 196.f, 0.f},
      .sprite_count = 1,
      .sprite_size = {100.f, (float)CACTI_GROUP.texture.height - 30},
  };

  const SpriteGroup GROUND_PIECES = {
      .texture = GAME_SPRITES,
      .start = {0.f, (float)GROUND_PIECES.texture.height - 20},
      .sprite_count = 3,
      .sprite_size = {(float)GROUND_PIECES.texture.width /
                          GROUND_PIECES.sprite_count,
                      20},
  };

  float trex_ground_y = ground_level_y - TREX.texture.height;
  Vector2 trex_position = {150, trex_ground_y}; // current trex position

  int current_frame = 2;
  int frame_counter = 0;

  int game_speed = 5;
  int max_jump_height = 175;
  int is_jumping = 0; // 0 = not jumping, 1 = jumping, -1 = falling
  int jump_speed = 10;

  while (!WindowShouldClose()) {

    if (IsKeyPressed(KEY_SPACE) && is_jumping == 0) {
      is_jumping = 1;
    }

    if (is_jumping != 0) {
      if (trex_position.y <= trex_ground_y - max_jump_height) {
        is_jumping = -1;
      } else if (trex_position.y >= trex_ground_y && is_jumping == -1) {
        is_jumping = 0;
        trex_position.y = trex_ground_y;
      }

      if (is_jumping == 1) {
        trex_position.y -= jump_speed;
      } else if (is_jumping == -1) {
        trex_position.y += jump_speed;
      }
    }

    frame_counter++;

    if (is_jumping != 0) {
      TREX.current_frame = 0;
    } else if (frame_counter >= 60 / game_speed) {
      frame_counter = 0;
      if (TREX.current_frame == 2)
        TREX.current_frame = 3;
      else if (TREX.current_frame == 3 || TREX.current_frame == 0)
        TREX.current_frame = 2;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawSpriteGroup(TREX, TREX.current_frame, trex_position);

    DrawTexture(GAME_SPRITES, 0, 0, WHITE);
    DrawTextureRec(
        SMALL_CACTI.texture,
        Rectangle{
            SMALL_CACTI.start.x + (3 * SMALL_CACTI.sprite_size.width),
            SMALL_CACTI.start.y,
            SMALL_CACTI.sprite_size.width,
            SMALL_CACTI.sprite_size.height,
        },
        {trex_position.x + 200,
         ground_level_y - SMALL_CACTI.sprite_size.height},
        WHITE);
    DrawTextureRec(
        LARGE_CACTI.texture,
        Rectangle{LARGE_CACTI.start.x + (3 * LARGE_CACTI.sprite_size.width),
                  LARGE_CACTI.start.y, LARGE_CACTI.sprite_size.width,
                  LARGE_CACTI.sprite_size.height},
        {trex_position.x + 350,
         ground_level_y - LARGE_CACTI.sprite_size.height},
        WHITE);
    DrawTextureRec(CACTI_GROUP.texture,
                   Rectangle{CACTI_GROUP.start.x, CACTI_GROUP.start.y,
                             CACTI_GROUP.sprite_size.width,
                             CACTI_GROUP.sprite_size.height},
                   {trex_position.x + 500,
                    ground_level_y - CACTI_GROUP.sprite_size.height},
                   WHITE);
    DrawSpriteGroup(GROUND_PIECES, 0,
                    {0, ground_level_y - GROUND_PIECES.sprite_size.height});
    DrawTextureRec(
        PTERS.texture,
        Rectangle{PTERS.start.x + (0 * PTERS.sprite_size.width), PTERS.start.y,
                  PTERS.sprite_size.width, PTERS.sprite_size.height},
        {50, ground_level_y - PTERS.sprite_size.height + 100}, WHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
