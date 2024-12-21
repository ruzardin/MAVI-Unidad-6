#include "Crosshair.h"
using namespace sf;
using namespace std;

Crosshair::Crosshair(const string& textureFile)
    : BaseObject(textureFile) {
    SetScale(0.09f);
    
    FloatRect bounds = _sprite.getLocalBounds();
    _sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Crosshair::Update(const Vector2i& mousePosition) {
    SetPosition({ static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) });
}
