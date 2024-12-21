#include "Enemy.h"
using namespace sf;
using namespace std;

Enemy::Enemy(const string& textureFile, const Vector2f& position, const Vector2f& velocity, float scale, bool horizontalMovement)
    : BaseObject(textureFile), _horizontalMovement(horizontalMovement) {
    SetPosition(position);
    SetVelocity(velocity);
    SetScale(scale);

}

void Enemy::Update(float dt) {

    // Aplicar gravedad al eje Y
    _velocity.y += _gravity * dt;

    // Mover el sprite según la velocidad actual
    BaseObject::Update(dt);

    // Obtener los límites de la ventana
    const float groundLevel = 600.f;  // Suelo
    const float windowWidth = 800.f; // Ancho de la ventana

    // Detectar colisión con el suelo
    if (GetPosition().y + GetBounds().height >= groundLevel) {
        // Ajustar posición para no atravesar el suelo
        SetPosition({ GetPosition().x, groundLevel - GetBounds().height });

        // Invertir la velocidad y aplicar factor de rebote
        _velocity.y = -_velocity.y * _bounceFactor;

    }

    // Movimiento horizontal y teletransporte en los bordes
    if (_horizontalMovement) {
        // Si el enemigo sale por la izquierda o derecha, aparece en el lado opuesto
        if (GetPosition().x + GetBounds().width < 0.f) {
            SetPosition({ windowWidth, GetPosition().y });
        }
        else if (GetPosition().x > windowWidth) {
            SetPosition({ -GetBounds().width, GetPosition().y });
        }
    }


}
