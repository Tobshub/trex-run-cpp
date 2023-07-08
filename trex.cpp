#include "trex.h"
#include <raylib.h>

void DrawSpriteGroup(SpriteGroup sprite_group, unsigned int frame,
                     Vector2 position) {
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
void DrawSpriteGroup(UniqueSpriteGroup sprite_group, unsigned int frame,
                     Vector2 position) {
  DrawSpriteGroup(SpriteGroup{sprite_group.texture,
                              sprite_group.start,
                              sprite_group.sprite_count,
                              {sprite_group.sprite_size.width,
                               sprite_group.sprite_size.height}},
                  frame, position);
};
