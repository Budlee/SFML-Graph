/* 
 * File:   GraphLines.h
 * Author: matt
 *
 * Created on 03 June 2015, 12:42
 */

#ifndef GRAPHLINES_H
#define	GRAPHLINES_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>
#include <mutex>
#include <inttypes.h>
#include "GraphPoint.h"

#define GRAPH_POINT_DISTANCE_SEPERATION 10
#define MAXIMUM_GRAPH_POINTS 200

class GraphLines : public sf::Drawable, public sf::Transformable {
public:
    GraphLines(uint16_t inScreenWidth, uint16_t inScreenHeight);
    GraphLines(const GraphLines& orig);
    virtual ~GraphLines();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void setPoint(float value);
    void update();



private:
    void yValueChange(float newYValue);


    std::vector<GraphPoint> m_graphPoints;
    std::vector<sf::Vertex> m_vertices;

    std::mutex setPointLock;

    uint16_t screenWidth, screenHeight;
    uint32_t currentMaxYValue;

};

#endif	/* GRAPHLINES_H */

