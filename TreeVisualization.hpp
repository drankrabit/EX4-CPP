// ************************
// 326538022
// itay.alexandrov@gmail.com
// ************************
#ifndef TREEVISUALIZATION_HPP
#define TREEVISUALIZATION_HPP

#include <SFML/Graphics.hpp>
#include "tree.hpp"
#include <cmath>

template <typename T>
class TreeVisualization {
public:
    TreeVisualization(Tree<T>* tree) : tree(tree) {}

    void draw(sf::RenderWindow& window) {
        if (tree->get_root() != nullptr) {
            drawNode(window, tree->get_root(), 400, 50, 200);
        }
    }

private:
    Tree<T>* tree;

    void drawNode(sf::RenderWindow& window, Node<T>* node, float x, float y, float xOffset) {
        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(x - 20, y - 20);
        window.draw(circle);

        sf::Font font;
        if (!font.loadFromFile("/home/user/.local/share/fonts/arial.ttf")) {
            throw std::runtime_error("Failed to load font");
        }
        sf::Text text;
        text.setFont(font);
        text.setString(node->value.to_string());
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::White);
        text.setPosition(x - 10, y - 10);
        window.draw(text);

        float newY = y + 100;
        float newXOffset = xOffset / 2;
        for (size_t i = 0; i < node->children.size(); ++i) {
            float newX = x + ((i - node->children.size() / 2) * xOffset);
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y)),
                sf::Vertex(sf::Vector2f(newX, newY))
            };
            window.draw(line, 2, sf::Lines);
            drawNode(window, node->children[i], newX, newY, newXOffset);
        }
    }
};

#endif // TREEVISUALIZATION_HPP
