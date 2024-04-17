#include <SFML/Graphics.hpp>
#include <iostream>
#include <omp.h>

int main() {
    // Încarcă imaginea
    sf::Image image;
    /*if (!image.loadFromFile("C:/Users/danut/Desktop/APD_P2/image1.jpg"))*/
    if (!image.loadFromFile("C:/Users/danut/Desktop/APD_P2/crocus-1279508_1280.png")) {
        std::cerr << "Nu am putut încărca imaginea.\n";
        return 1;
    }

    // Afișează imaginea inițială
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);

    // Corectează culorile imaginii în mod paralel
    sf::Color correction(50, 100, -50);

#pragma omp parallel
    {
        // Obține identificatorul firului de execuție
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        // Calculează porțiunea de lucru a fiecărui fir de execuție
        int chunk_size = image.getSize().y / num_threads;
        int start_row = thread_id * chunk_size;
        int end_row = (thread_id == num_threads - 1) ? image.getSize().y : (thread_id + 1) * chunk_size;

        // Corectează culorile imaginii pentru porțiunea asignată
        for (unsigned int y = start_row; y < end_row; ++y) {
            for (unsigned int x = 0; x < image.getSize().x; ++x) {
                sf::Color pixel = image.getPixel(x, y);
                pixel.r = static_cast<sf::Uint8>(std::min(255, static_cast<int>(pixel.r) + correction.r));
                pixel.g = static_cast<sf::Uint8>(std::min(255, static_cast<int>(pixel.g) + correction.g));
                pixel.b = static_cast<sf::Uint8>(std::max(0, static_cast<int>(pixel.b) + correction.b));
                image.setPixel(x, y, pixel);
            }
        }
    }

    // Afișează imaginea corectată
    texture.loadFromImage(image);
    sprite.setTexture(texture);

    // Salvează imaginea corectată
    image.saveToFile("output_image_parallel.jpg");
    std::cout << "Imaginea corectată a fost salvată cu succes.\n";

    // Afișează fereastra cu imaginea corectată
    sf::RenderWindow window(sf::VideoMode(image.getSize().x, image.getSize().y), "Imagine corectată (Paralel)");
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
