#include <stdio.h>
#include <iostream>
#include <thread> 
#include <inttypes.h>
#include "GraphLines.h"
#include "OanadaPricePuller.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

void renderingThread(sf::RenderWindow* window, GraphLines *glines)
{
    // the rendering loop  

//    glines->setPoint(32);
//    glines->setPoint(58);
//    glines->setPoint(134);
//    glines->setPoint(4);
//    glines->setPoint(82);
//    glines->setPoint(16);
//    glines->setPoint(256);
    window->setActive(true);
    while (window->isOpen())
    {
        window->clear();
        glines->update();
        window->draw(*glines);
        window->display();
    }
}

void oandaThread(sf::RenderWindow* window, GraphLines *glines)
{
    OanadaPricePuller op(glines);
    while (window->isOpen())
    {
        op.getTick();
    }
}

int main(int argc, const char* argv[])
{

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    window.setFramerateLimit(60);
    window.setActive(false);
    GraphLines glines(window.getSize().x, window.getSize().y);
    std::thread render(renderingThread, &window, &glines);
    std::thread oanda(oandaThread, &window, &glines);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


    }

    return 0;
}