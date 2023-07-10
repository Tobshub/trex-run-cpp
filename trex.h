#include <raylib.h>
#include <tuple>

struct SpriteGroup {
  const Texture2D texture;
  Vector2 start;
  int sprite_count;
  struct {
    float width;
    float height;
  } sprite_size;
};

struct RenderedSprite {
  const SpriteGroup *sprite_group;
  int sprite_frame;
  Vector2 position;
};

void DrawSpriteGroup(SpriteGroup sprite_group, int frame, Vector2 position);

Rectangle GetRenderedSpriteRect(RenderedSprite *sprite);
std::tuple<Vector2, float> GetRenderedSpriteCircle(RenderedSprite *sprite);
