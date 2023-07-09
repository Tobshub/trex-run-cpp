#include "trex.h"
#include <cstdlib>
#include <raylib.h>

int RandomInt(int min, int max) { return min + (rand() % (max - min + 1)); }

struct RenderedSprite {
  SpriteGroup sprite_group;
  int sprite_frame;
  Vector2 position;
};

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
  Vector2 trex_position = {75, trex_ground_y}; // current trex position

  int frame_counter = 0;

  int game_speed = 6;
  int max_jump_height = 175;
  int is_jumping = 0; // 0 = not jumping, 1 = jumping, -1 = falling
  int jump_speed = 10;

  RenderedSprite rendered_sprite_groups[] = {
      RenderedSprite{
          .sprite_group = SMALL_CACTI,
          .sprite_frame = RandomInt(0, SMALL_CACTI.sprite_count),
          .position = Vector2{SCREEN_WIDTH - SMALL_CACTI.sprite_size.width,
                              ground_level_y - SMALL_CACTI.sprite_size.height}},
  };

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

    for (int i = 0; i < sizeof(rendered_sprite_groups) / sizeof(RenderedSprite);
         i++) {
      RenderedSprite *sprite = &rendered_sprite_groups[i];
      if (sprite->position.x > 0.f - sprite->sprite_group.sprite_size.width) {
        sprite->position.x -= game_speed; // ???
      } else {
        sprite->position.x =
            (float)SCREEN_WIDTH + sprite->sprite_group.sprite_size.width;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawSpriteGroup(TREX, TREX.current_frame, trex_position);

    DrawTexture(GAME_SPRITES, 0, 0, WHITE);

    for (RenderedSprite sprite : rendered_sprite_groups) {
      DrawSpriteGroup(sprite.sprite_group, sprite.sprite_frame,
                      sprite.position);
    }

    DrawSpriteGroup(GROUND_PIECES, 0,
                    {0, ground_level_y - GROUND_PIECES.sprite_size.height});

    EndDrawing();
  }

  UnloadTexture(GAME_SPRITES);
  UnloadTexture(TREX.texture);

  CloseWindow();
  return 0;
}
