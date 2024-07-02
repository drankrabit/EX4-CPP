// ************************
// 326538022
// itay.alexandrov@gmail.com
// ************************
#include <SFML/Graphics.hpp>
#include "TreeVisualization.hpp"
#include "tree.hpp"
#include "complex.hpp"

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");

    // Create a tree for demonstration
    Tree<Complex> tree;
    Node<Complex> root(Complex(1.0, 1.0));
    tree.add_root(root);

    Node<Complex> child1(Complex(2.0, 2.0));
    Node<Complex> child2(Complex(3.0, 3.0));
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);

    TreeVisualization<Complex> treeVis(&tree);

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear screen
        window.clear();

        // Draw the tree
        treeVis.draw(window);

        // Update the window
        window.display();
    }

    return 0;
}
