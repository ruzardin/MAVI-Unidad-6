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

void Game::_Update(float dt)
{
    // Aceleración base para las teclas
    const float maxAcceleration = 100.0f; // Aceleración máxima
    const float friction = 50.0f;         // Fricción para desacelerar
    const float maxSpeed = 300.0f;        // Velocidad máxima

    // Reiniciar aceleración
    _pBall->SetAcceleration(Vector2f(0.0f, 0.0f));

    // Aplicar input de teclado para acelerar
    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        _pBall->AddAcceleration(Vector2f(maxAcceleration, 0.0f));
    }
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        _pBall->AddAcceleration(Vector2f(-maxAcceleration, 0.0f));
    }
    if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        _pBall->AddAcceleration(Vector2f(0.0f, -maxAcceleration));
    }
    if (Keyboard::isKeyPressed(Keyboard::Down))
    {
        _pBall->AddAcceleration(Vector2f(0.0f, maxAcceleration));
    }

    // Obtener velocidad actual
    Vector2f velocity = _pBall->GetVelocity();

    // Aplicar fricción si no hay aceleración
    Vector2f acceleration = _pBall->GetAcceleration();
    if (acceleration.x == 0.0f)
    {
        if (velocity.x > 0.0f)
            velocity.x = std::max(0.0f, velocity.x - friction * dt);
        else if (velocity.x < 0.0f)
            velocity.x = std::min(0.0f, velocity.x + friction * dt);
    }
    if (acceleration.y == 0.0f)
    {
        if (velocity.y > 0.0f)
            velocity.y = std::max(0.0f, velocity.y - friction * dt);
        else if (velocity.y < 0.0f)
            velocity.y = std::min(0.0f, velocity.y + friction * dt);
    }

    // Limitar la velocidad máxima
    if (velocity.x > maxSpeed) velocity.x = maxSpeed;
    if (velocity.x < -maxSpeed) velocity.x = -maxSpeed;
    if (velocity.y > maxSpeed) velocity.y = maxSpeed;
    if (velocity.y < -maxSpeed) velocity.y = -maxSpeed;

    // Actualizar la velocidad en el objeto
    _pBall->SetVelocity(velocity);

    // Actualizar la posición y estado del objeto
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
