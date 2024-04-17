#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Încarcă imaginea
    sf::Image image;
    /*if (!image.loadFromFile("C:/Users/danut/Desktop/APD_P/2150905070.jpg"))*/
    if (!image.loadFromFile("C:/Users/danut/Desktop/APD_P/lady-1348396_1280.png"))
    {
        std::cerr << "Nu am putut încărca imaginea.\n";
        return 1;
    }

    // Afișează imaginea inițială
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);

    // Corectează culorile imaginii
    sf::Color correction(50, 100, -50); // Modifică culorile cu +50 la roșu, +100 la verde și -50 la albastru
    for (unsigned int x = 0; x < image.getSize().x; ++x) {
        for (unsigned int y = 0; y < image.getSize().y; ++y) {
            sf::Color pixel = image.getPixel(x, y);
            pixel.r = static_cast<sf::Uint8>(std::min(255, static_cast<int>(pixel.r) + correction.r));
            pixel.g = static_cast<sf::Uint8>(std::min(255, static_cast<int>(pixel.g) + correction.g));
            pixel.b = static_cast<sf::Uint8>(std::max(0, static_cast<int>(pixel.b) + correction.b));
            image.setPixel(x, y, pixel);
        }
    }

    // Afișează imaginea corectată
    texture.loadFromImage(image);
    sprite.setTexture(texture);

    // Salvează imaginea corectată
    image.saveToFile("output_image.jpg");
    std::cout << "Imaginea corectată a fost salvată cu succes.\n";

    // Afișează fereastra cu imaginea corectată
    sf::RenderWindow window(sf::VideoMode(image.getSize().x, image.getSize().y), "Imagine corectată");
    window.clear();
    window.draw(sprite);
    window.display();

    // Așteaptă închiderea ferestrei
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}
