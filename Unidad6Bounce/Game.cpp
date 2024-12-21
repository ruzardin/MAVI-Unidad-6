#include "Game.h"

Game::Game() {
    _pWnd = new RenderWindow(VideoMode(800, 600, 32), "Fast & Furious");

    // Crear el objeto BaseObject para el círculo
    _pBall = new BaseObject("ball.png");
    _pBall->SetScale(0.1f);
    _pBall->SetPosition(Vector2f(-_pBall->GetPosition().x, 100.0f)); 
    _pBall->SetVelocity(Vector2f(20.0f, 0.0f)); // Velocidad inicial en el eje X

}

Game::~Game() {
    delete _pBall;
    delete _pWnd;
}

void Game::Loop() {
    Clock clock;
    while (_pWnd->isOpen()) {
        float dt = clock.restart().asSeconds();
        _ProcessEvents();
        _Update(dt);
        _Draw();
    }
}

void Game::_Draw() {
    _pWnd->clear(Color::Black);
    _pBall->Draw(_pWnd);
    _pWnd->display();
}

void Game::_Update(float dt)
{
    // Aplicar gravedad al objeto
    _pBall->AddAcceleration(Vector2f(0.0f, 980.0f)); // Aceleración gravitacional ajustada (980 px/s^2).

    // Obtener la posición y velocidad actuales de la esfera
    Vector2f position = _pBall->GetPosition();
    Vector2f velocity = _pBall->GetVelocity();

    // Chequear si el objeto ha alcanzado el suelo
    if (position.y + _pBall->GetVelocity().y * dt >= 490.0f) // Altura de la ventana
    {
        // Limitar la posición para que no atraviese el suelo
        _pBall->SetPosition(Vector2f(position.x, 490.0f));

        // Invertir la velocidad vertical (rebote) con un factor de restitución (porcentaje)
        const float restitution = 0.8f; // 80% de la velocidad con la que impactó.
        _pBall->SetVelocity(Vector2f(velocity.x, -velocity.y * restitution));
    }

    // Actualizar el objeto BaseObject (_pBall)
    _pBall->Update(dt);
}

void Game::_ProcessEvents() {
    Event evt;
    while (_pWnd->pollEvent(evt)) {
        if (evt.type == Event::Closed) {
            _pWnd->close();
        }
    }
}
