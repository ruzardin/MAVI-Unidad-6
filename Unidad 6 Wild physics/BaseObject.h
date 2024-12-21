#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class BaseObject {
public:
    BaseObject(const string& textureFile);
    virtual ~BaseObject();

    virtual void Update(float dt);
    virtual void Draw(RenderWindow* window);

    void SetPosition(const Vector2f& position);
    void SetVelocity(const Vector2f& velocity);
    void SetScale(float scale);

    Vector2f GetPosition() const;
    FloatRect GetBounds() const;

protected:
    Sprite _sprite;
    Texture _texture;
    Vector2f _velocity;
};
