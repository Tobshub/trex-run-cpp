#include "trex.h"
#include <raylib.h>

Rectangle GetRenderedSpriteRect(RenderedSprite *sprite_group) {
  return Rectangle{
      sprite_group->position.x,
      sprite_group->position.y,
      sprite_group->sprite_group->sprite_size.width,
      sprite_group->sprite_group->sprite_size.height,
  };
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
