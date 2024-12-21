#include "BaseObject.h"
using namespace sf;
using namespace std;

BaseObject::BaseObject(const string& textureFile) {
    if (!_texture.loadFromFile(textureFile)) {
        throw runtime_error("Failed to load texture: " + textureFile);
    }
    _sprite.setTexture(_texture);
    _velocity = Vector2f(0.f, 0.f);
}

BaseObject::~BaseObject() {}

void BaseObject::Update(float dt) {
    _sprite.move(_velocity * dt);
}

void BaseObject::Draw(RenderWindow* window) {
    if (window) {
        window->draw(_sprite);
    }
}

void BaseObject::SetPosition(const Vector2f& position) {
    _sprite.setPosition(position);
}

void BaseObject::SetVelocity(const Vector2f& velocity) {
    _velocity = velocity;
}

void BaseObject::SetScale(float scale) {
    _sprite.setScale(scale, scale);
}

Vector2f BaseObject::GetPosition() const {
    return _sprite.getPosition();
}

FloatRect BaseObject::GetBounds() const {
    return _sprite.getGlobalBounds();
}
