#include "trex.h"
#include <algorithm>
#include <raylib.h>
#include <tuple>

Rectangle GetRenderedSpriteRect(RenderedSprite *sprite) {
  return Rectangle{
      sprite->position.x,
      sprite->position.y,
      sprite->sprite_group->sprite_size.width,
      sprite->sprite_group->sprite_size.height,
  };
}

float Min(float a, float b) { return a < b ? a : b; }

std::tuple<Vector2, float> GetRenderedSpriteCircle(RenderedSprite *sprite) {
  float r = Min(sprite->sprite_group->sprite_size.width,
                sprite->sprite_group->sprite_size.height) /
            2.f;
  return std::make_tuple(
      Vector2{sprite->position.x + r, sprite->position.y + r}, r);
}

void DrawSpriteGroup(SpriteGroup sprite_group, int frame, Vector2 position) {
  DrawTextureRec(
      sprite_group.texture,
      Rectangle{
          sprite_group.start.x + ((frame % sprite_group.sprite_count) *
                                  sprite_group.sprite_size.width),
          sprite_group.start.y,
          sprite_group.sprite_size.width,
          sprite_group.sprite_size.height,
      },
      position, WHITE);
}
