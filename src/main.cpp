#include <ctime>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

#include "Game.h"

using namespace std;

static inline std::string int2Str(int x) {
    std::stringstream type;
    type << x;
    return type.str();
}

int main(){
    Game *game = new Game;
    sf::RenderWindow window(sf::VideoMode(1000, 775), "REVERSI", sf::Style::Close);
    window.setFramerateLimit(30);

    sf::Texture tile1, tile2, piece1, piece2, glow, wood, button;

    if (!tile1.loadFromFile("../photos/tile1.jpg")
        || !tile2.loadFromFile("../photos/tile2.jpg")
        || !piece1.loadFromFile("../photos/piece1.png")
        || !piece2.loadFromFile("../photos/piece2.png")
        || !glow.loadFromFile("../photos/glow.png")
        || !wood.loadFromFile("../photos/wood.jpg")
        || !button.loadFromFile("../photos/button.png")) {
        exit(1);
    }

    const float size = (800 - 45) / 8.0;

    glow.setSmooth(true);

    sf::RectangleShape squares[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sf::RectangleShape square(sf::Vector2f(size, size));

            if(i % 2 == 0) {
                if(j % 2 == 0) {
                    square.setTexture(&tile1);
                } else {
                    square.setTexture(&tile2);
                }
            }
            if(i % 2 == 1){
                if(j % 2 == 0) {
                    square.setTexture(&tile2);
                } else {
                    square.setTexture(&tile1);
                }
            }
            square.setPosition((float)i * (size + 1) + 5, (float)j * (size + 1) + 5);
            squares[i][j] = square;
        }
    }

    sf::Font font;
    font.loadFromFile("../photos/arial.ttf");

    sf::Text currentTurnText("Current turn:", font);
    currentTurnText.setCharacterSize(14);
    currentTurnText.setPosition(850, 75);

    sf::Text turn("BLACK", font);
    turn.setCharacterSize(30);
    turn.setPosition(850, 100);

    sf::Text scoreText("Score: \nBlack-White",font);
    scoreText.setPosition(850, 150);
    scoreText.setCharacterSize(16);

    sf::Text scores("-", font);
    scores.setCharacterSize(30);
    scores.setPosition(850, 200);

    sf::Text buttonText1("NEW GAME", font);
    buttonText1.setPosition(805, 510);
    buttonText1.setFillColor(sf::Color::Red);

    sf::RectangleShape background(sf::Vector2f(400, 770));
    sf::RectangleShape score_bg(sf::Vector2f(180, 300));
    sf::RectangleShape button1(sf::Vector2f(180, 100));
    sf::RectangleShape button2(sf::Vector2f(180, 100));

    background.setPosition(767, 0);
    background.setTexture(&wood);
    score_bg.setPosition(797, 10);
    button1.setPosition(797, 480);
    score_bg.setFillColor(sf::Color(0, 0, 0, 125));
    button1.setTexture(&button);

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                delete game;
                return 0;
            }
        }

        window.clear();

        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        int row = localPosition.x / int(size + 5);
        int col = localPosition.y / int(size + 5);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus()) {
            if (localPosition.x > 797 && localPosition.x < 977 ) {
                if (localPosition.y > 480 && localPosition.y < 580) {
                    delete game;
                    game = new Game();
                }
            }
            game->click(row, col);
        }

        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++){

                window.pushGLStates();
                window.draw(squares[i][j]);
                window.popGLStates();

                float radius = (size - 10) / 2;
                float smallRadius = (size - 10) / 5;

                if(game->Get_Board(i, j) > 0) {
                    sf::CircleShape circle(radius);
                    piece1.setSmooth(true);
                    piece2.setSmooth(true);
                    circle.setTexture(game->Get_Board(i, j) == 1 ? &piece1 : &piece2);
                    circle.setPosition((float)i * (size + 1) + 10, (float)j * (size + 1) + 10);
                    window.pushGLStates();
                    window.draw(circle);
                    window.popGLStates();
                } else if (game->Get_Board(i, j) == -1) {
                    sf::CircleShape circle2(smallRadius);
                    circle2.setTexture(&glow);
                    circle2.setFillColor(sf::Color(255, 255, 255));
                    circle2.setPosition((float)i * (size + 1) + 35, (float)j * (size + 1) + 35);
                    window.pushGLStates();
                    window.draw(circle2);
                    window.popGLStates();
                }
            }
        }

        turn.setPosition(850, 100);
        turn.setCharacterSize(30);
        turn.setFillColor(sf::Color::Green);
        turn.setStyle(sf::Text::Regular);

        if (game->Get_gameOver()) {
            if (game->Get_White() > game->Get_Black()) {
                turn.setString("GAME OVER:\n WHITE WON");
            } else if (game->Get_White() < game->Get_Black()) {
                turn.setString("GAME OVER:\n BLACK WON");
            } else {
                turn.setString("GAME OVER:\n TIED");
            }
            turn.setPosition(200, 300);
            turn.setCharacterSize(72);
            turn.setFillColor(sf::Color::Red);
            turn.setStyle(sf::Text::Bold);

        } else if (game->GetCurrentTurn() == 2) {
            turn.setString("BLACK");
        } else {
            turn.setString("WHITE");
        }

        scores.setString(int2Str(game->Get_Black()) + "-" + int2Str(game->Get_White()));

        window.pushGLStates();
        window.draw(background);
        window.draw(score_bg);
        window.draw(turn);
        window.draw(scores);
        window.draw(button1);
        window.draw(currentTurnText);
        window.draw(scoreText);
        window.draw(buttonText1);
        window.popGLStates();

        window.display();
    }

    delete game;
    return 0;
}