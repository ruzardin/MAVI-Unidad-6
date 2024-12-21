#include "Game.h"
#include <cstdlib>
#include <ctime>
using namespace sf;
using namespace std;

Game::Game()
    : _window(VideoMode(800, 600), "Enemy Shooter Game"), _score(0) {
    _crosshair = new Crosshair("crosshair.png");

    if (!_font.loadFromFile("Life.ttf")) {
        throw runtime_error("Failed to load font");
    }

    _scoreText.setFont(_font);
    _scoreText.setCharacterSize(45);
    _scoreText.setFillColor(Color::Green);
    _scoreText.setPosition(10.f, 10.f);

    srand(static_cast<unsigned>(time(nullptr)));
    _window.setMouseCursorVisible(false);
}

Game::~Game() {
    delete _crosshair;
    for (auto enemy : _enemies) {
        delete enemy;
    }
}

void Game::Run() {
    Clock clock;

    while (_window.isOpen()) {
        float dt = clock.restart().asSeconds();

        ProcessEvents();
        Update(dt);
        Render();
    }
}

void Game::ProcessEvents() {
    Event event;
    while (_window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            _window.close();
        }
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            CheckCollisions();
        }
    }
}

void Game::Update(float dt) {
    _crosshair->Update(Mouse::getPosition(_window));

    for (auto enemy : _enemies) {
        enemy->Update(dt);
    }
    SpawnEnemy();

    _scoreText.setString("Score: " + to_string(_score));

}


void Game::Render() {
    _window.clear(Color::White);
    _window.draw(_scoreText);
    for (auto enemy : _enemies) {
        enemy->Draw(&_window);
    }
    _crosshair->Draw(&_window);
   
    _window.display();
}

void Game::SpawnEnemy() {
   
    if (_enemies.size() < 10 && rand() % 100 < 2) {
        sf::Vector2f position(rand() % 800, 0.f); // Posición inicial aleatoria
        sf::Vector2f velocity(0.f, 0.f);         // Velocidad inicial
        bool horizontalMovement = rand() % 2 == 0; // 50% de probabilidad de movimiento lateral
        if (horizontalMovement) {
            velocity.x = (rand() % 2 == 0 ? -200.f : 200.f); // Velocidad aleatoria a izquierda o derecha
        } 
        float scale = 0.15f;
        _enemies.push_back(new Enemy("enemy.png", position, velocity, scale, horizontalMovement));
    }
}

void Game::CheckCollisions() {
    auto it = _enemies.begin();
    while (it != _enemies.end()) {
        if ((*it)->GetBounds().contains(_crosshair->GetPosition())) {
            delete* it;
            it = _enemies.erase(it);
            _score += 10;
        }
        else {
            ++it;
        }
    }
}
