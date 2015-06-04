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
    window->setActive(true);
    while (window->isOpen())
    {
        window->clear();
        glines->update();
        window->draw(*glines);
        window->display();
    }
}

void oandaThread(sf::RenderWindow* window, GraphLines *glines, std::string *accessId, std::string *accessToken)
{
    OanadaPricePuller op(glines, *accessId, *accessToken);
    while (window->isOpen())
    {
        op.getTick();
    }
}

int main(int argc, const char* argv[])
{
    if(argc != 3)
    {
        std::cerr<<"Need id and token\n";
        std::exit(1);
    }
    
    std::string aId = argv[1];
    std::string aTok = argv[2];
    
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    window.setFramerateLimit(60);
    window.setActive(false);
    GraphLines glines(window.getSize().x, window.getSize().y);
    std::thread render(renderingThread, &window, &glines);
    std::thread oanda(oandaThread, &window, &glines,&aId ,&aTok);
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