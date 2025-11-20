//
// Created by lekrieg on 02/11/2025.
//

#include <iostream>
#include <string>
#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Shader.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

int main ()
{
    std::vector<std::pmr::string> shaderFiles =
    {
        "shaders/shader.frag",
    };

    size_t currentShaderIndex = 0;

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(512, 512)), "SFML shader example", sf::Style::Titlebar | sf::Style::Close);

    sf::Texture texture(sf::Vector2u(200, 200));
    sf::Sprite sprite(texture);

    window.setVerticalSyncEnabled(true);

    sf::Texture pngTexture;
    if (!texture.loadFromFile("shaders/test.png"))
    {
        std::cerr << "Error while loading texture" << '\n';
        return -1;
    }

    sf::Shader shader;
    if (!shader.loadFromFile(shaderFiles[currentShaderIndex], sf::Shader::Type::Fragment))
    {
        std::cerr << "Error while loading shaders" << '\n';
        return -1;
    }

    sf::Clock time;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            const auto *keyPressed = event->getIf<sf::Event::KeyPressed>();
            if (keyPressed)
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
                else
                {
                    currentShaderIndex = (currentShaderIndex + 1) % shaderFiles.size();
                    if (!shader.loadFromFile(shaderFiles[currentShaderIndex], sf::Shader::Type::Fragment))
                    {
                        std::cerr << "Error while loading shaders" << '\n';
                        return -1;
                    }
                }
            }
        }

        shader.setUniform("time", time.getElapsedTime().asSeconds());

        window.clear(sf::Color(127, 127, 127));

        sprite.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
        window.draw(sprite, &shader);

        window.display();
    }

    return 0;
}
