#include <raylib.h>

struct UniqueSpriteGroup {
  const Texture2D texture;
  Vector2 start;
  int sprite_count;
  struct {
    float width;
    float height;
  } sprite_size;
  unsigned int current_frame;
};

struct SpriteGroup {
  const Texture2D texture;
  Vector2 start;
  int sprite_count;
  struct {
    float width;
    float height;
  } sprite_size;
};

void DrawSpriteGroup(UniqueSpriteGroup sprite_ground, int frame,
                     Vector2 position);
void DrawSpriteGroup(SpriteGroup sprite_ground, int frame, Vector2 position);
