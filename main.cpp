#include "trex.h"
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <tuple>

int RandomInt(int min, int max) { return min + (rand() % (max - min)); }

#define RandomSpriteFrame(sprite_group) RandomInt(0, sprite_group.sprite_count)

int main() {
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Trex Run");
  SetTargetFPS(60);

  float ground_level_y = SCREEN_HEIGHT - 150; // rest/running height

  const Texture2D GAME_SPRITES = LoadTexture("resources/all-sprites.png");

  const Texture2D TREX_TEXTURES = LoadTexture("resources/trex.png");
  SpriteGroup TREX_GROUP = {
      .texture = TREX_TEXTURES,
      .start = {0.f, 0.f},
      .sprite_count = 6,
      .sprite_size = {(float)TREX_TEXTURES.width / TREX_GROUP.sprite_count,
                      (float)TREX_TEXTURES.height},
  };

  float trex_ground_y = ground_level_y - TREX_GROUP.texture.height;

  RenderedSprite TREX = {.sprite_group = &TREX_GROUP,
                         .sprite_frame = 0,
                         .position = {75, trex_ground_y}};

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
      .start = {0.f, (float)GROUND_PIECES.texture.height - 25},
      .sprite_count = 3,
      .sprite_size = {(float)GROUND_PIECES.texture.width /
                          GROUND_PIECES.sprite_count,
                      20},
  };

  RenderedSprite GROUND[] = {
      {
          .sprite_group = &GROUND_PIECES,
          .sprite_frame = RandomSpriteFrame(GROUND_PIECES),
          .position = {0, ground_level_y - GROUND_PIECES.sprite_size.height},
      },
      {
          .sprite_group = &GROUND_PIECES,
          .sprite_frame = RandomSpriteFrame(GROUND_PIECES),
          .position = {GROUND_PIECES.sprite_size.width,
                       ground_level_y - GROUND_PIECES.sprite_size.height},
      }};

  int frame_counter = 0;

  int game_speed = 4;
  int max_jump_height = 200;
  int is_jumping = 0; // 0 = not jumping, 1 = jumping, -1 = falling
  int jump_speed = 10;

  SpriteGroup OBSTACLE_SPRITES[] = {SMALL_CACTI, LARGE_CACTI, CACTI_GROUP,
                                    PTERS};

  RenderedSprite rendered_sprite_groups[] = {
      RenderedSprite{
          .sprite_group = &SMALL_CACTI,
          .sprite_frame = RandomSpriteFrame(SMALL_CACTI),
          .position = Vector2{SCREEN_WIDTH - SMALL_CACTI.sprite_size.width,
                              ground_level_y - SMALL_CACTI.sprite_size.height}},
  };

  bool has_collided = false;

  int score = 0;

  while (!WindowShouldClose()) {

    if (has_collided) {

    } else {
      if (IsKeyPressed(KEY_SPACE) && is_jumping == 0) {
        is_jumping = 1;
      }

      if (is_jumping != 0) {
        if (TREX.position.y <= trex_ground_y - max_jump_height) {
          is_jumping = -1;
        } else if (TREX.position.y >= trex_ground_y && is_jumping == -1) {
          is_jumping = 0;
          TREX.position.y = trex_ground_y;
        }

        if (TREX.position.y > trex_ground_y - max_jump_height / 1.25f) {
          TREX.position.y += is_jumping * -1 * jump_speed;
        } else {
          TREX.position.y += is_jumping * -1 * jump_speed / 3.f;
        }
      }

      frame_counter++;
      if (frame_counter >= 60 / game_speed) {
        score++;
        frame_counter = 0;
        if (is_jumping != 0) {
          TREX.sprite_frame = 0;
        } else {
          if (TREX.sprite_frame == 2)
            TREX.sprite_frame = 3;
          else if (TREX.sprite_frame == 3 || TREX.sprite_frame == 0)
            TREX.sprite_frame = 2;
        }
      }

      for (int i = 0;
           i < (int)(sizeof(rendered_sprite_groups) / sizeof(RenderedSprite));
           i++) {
        RenderedSprite *sprite = &rendered_sprite_groups[i];
        if (sprite->position.x >
            0.f - sprite->sprite_group->sprite_size.width) {
          sprite->position.x -= game_speed;
        } else {
          SpriteGroup random_sprite_group = OBSTACLE_SPRITES[RandomInt(
              0, sizeof(OBSTACLE_SPRITES) / sizeof(SpriteGroup))];

          rendered_sprite_groups[i] = RenderedSprite{
              .sprite_group = &random_sprite_group,
              .sprite_frame = RandomSpriteFrame(random_sprite_group),
              .position = {SCREEN_WIDTH - random_sprite_group.sprite_size.width,
                           ground_level_y -
                               random_sprite_group.sprite_size.height}};
        }
        std::tuple<Vector2, float> trex_hitbox = GetRenderedSpriteCircle(&TREX);
        std::tuple<Vector2, float> sprite_hitbox =
            GetRenderedSpriteCircle(sprite);
        if (CheckCollisionCircles(
                std::get<0>(trex_hitbox), std::get<1>(trex_hitbox),
                std::get<0>(sprite_hitbox), std::get<1>(sprite_hitbox))) {
          has_collided = true;
        }
      }

      for (int i = 0; i < (int)(sizeof(GROUND) / sizeof(RenderedSprite)); i++) {
        RenderedSprite *ground_piece = &GROUND[i];
        if (ground_piece->position.x +
                ground_piece->sprite_group->sprite_size.width >
            0) {
          ground_piece->position.x -= game_speed;
        } else {
          if (i < (int)(sizeof(GROUND) / sizeof(RenderedSprite)) - 1) {
            GROUND[i] = GROUND[i + 1];
            GROUND[i + 1] = RenderedSprite{
                .sprite_group = &GROUND_PIECES,
                .sprite_frame = RandomSpriteFrame(GROUND_PIECES),
                .position = {GROUND_PIECES.sprite_size.width,
                             ground_level_y - GROUND_PIECES.sprite_size.height},
            };
          } else {
            std::cout << i << " is last" << std::endl;
          }
        }
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawSpriteGroup(*TREX.sprite_group, TREX.sprite_frame, TREX.position);

    for (RenderedSprite sprite : rendered_sprite_groups) {
      DrawSpriteGroup(*sprite.sprite_group, sprite.sprite_frame,
                      sprite.position);
    }

    for (int i = 0; i < (int)(sizeof(GROUND) / sizeof(RenderedSprite)); i++) {
      RenderedSprite ground_piece = GROUND[i];
      DrawSpriteGroup(*ground_piece.sprite_group, ground_piece.sprite_frame,
                      ground_piece.position);
    }

    DrawText(TextFormat("Score: %i", score), SCREEN_WIDTH - 100, 5, 15, GRAY);

    EndDrawing();
  }

  UnloadTexture(GAME_SPRITES);
  UnloadTexture(TREX_TEXTURES);

  CloseWindow();
  return 0;
}
