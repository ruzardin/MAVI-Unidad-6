#include "Game.h"

Game::Game() {
    _pWnd = new RenderWindow(VideoMode(800, 600, 32), "Fast & Furious");

    // Crear el objeto BaseObject para el círculo
    _pBall = new BaseObject("ball.png");
    _pBall->SetScale(0.1f);
    _pBall->SetPosition(Vector2f(-_pBall->GetPosition().x, 300.0f)); // Inicia a la mitad verticalmente
    _pBall->SetVelocity(Vector2f(100.0f, 0.0f)); // Velocidad inicial en el eje X

    // Configurar velocidades
    _velocidad = 100.0f;
    _velocidadFinal = 500.0f;
    _incremento = 50.0f;
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

void Game::_Update(float dt) {
    _pBall->Update(dt);

    // Movimiento horizontal
    Vector2f pos = _pBall->GetPosition();
    pos.x += _velocidad * dt;

    if (pos.x > 800.0f) // 800 es el ancho de la ventana
    {
        pos.x = -_pBall->GetVelocity().x * dt; // Reingresar por la izquierda
        _pBall->SetPosition(pos);

        // Incrementar la velocidad
        Vector2f velocity = _pBall->GetVelocity();
        velocity.x += 20.0f; // Aumentar la velocidad en X
        _pBall->SetVelocity(velocity);
    }

    // Si sale de la pantalla, reinicia y aumenta la velocidad
    if (pos.x > _pWnd->getSize().x) {
        pos.x = -_pBall->GetPosition().x; // Reaparece desde la izquierda
        if (_velocidad < _velocidadFinal) {
            _velocidad += _incremento;
        }
    }

    _pBall->SetPosition(pos);
}

void Game::_ProcessEvents() {
    Event evt;
    while (_pWnd->pollEvent(evt)) {
        if (evt.type == Event::Closed) {
            _pWnd->close();
        }
    }
}
