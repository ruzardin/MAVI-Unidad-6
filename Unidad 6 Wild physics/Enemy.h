#include "BaseObject.h"
using namespace sf;
using namespace std;

class Enemy : public BaseObject {
public:
    Enemy(const string& textureFile, const Vector2f& position, const Vector2f& velocity, float scale, bool horizontalMovement = false);

    void Update(float dt) override;

private:
    const float _gravity = 980.f; // Gravedad (px/s^2)
    const float _bounceFactor = 0.9f; // Factor de rebote (90% de la velocidad previa)
    bool _horizontalMovement; // Si el enemigo se mueve hacia los lados
};
