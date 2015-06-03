/* 
 * File:   GraphLines.cpp
 * Author: matt
 * 
 * Created on 03 June 2015, 12:42
 */


#include <iostream>

#include "GraphLines.h"

GraphLines::GraphLines(uint16_t inScreenWidth, uint16_t inScreenHeight)
: screenWidth(inScreenWidth)
, screenHeight(inScreenHeight - 100)
, currentMaxYValue(0)
{
    m_graphPoints.reserve(MAXIMUM_GRAPH_POINTS);
}

GraphLines::GraphLines(const GraphLines& orig)
{
}

GraphLines::~GraphLines()
{
}

void GraphLines::setPoint(float value)
{
    setPointLock.lock();
    if (currentMaxYValue < value)
    {
        yValueChange(value);
    }
    if (m_graphPoints.size() > MAXIMUM_GRAPH_POINTS)
    {
        m_graphPoints.erase(m_graphPoints.begin(), m_graphPoints.begin() + (m_graphPoints.size() - MAXIMUM_GRAPH_POINTS));
    }
    m_graphPoints.push_back(GraphPoint(screenHeight - (screenHeight * ((100.0 / currentMaxYValue * value) / 100.0)) + 50, value));
    setPointLock.unlock();
}

void GraphLines::update()
{
    m_vertices.clear();
    if (m_graphPoints.size() <= 1)
    {
        return;
    }
    else
    {
        m_vertices.clear();
        uint32_t graphSize = m_graphPoints.size() - 1;
        uint32_t index = 0;

        while (index < graphSize)
        {
            m_vertices.push_back(sf::Vertex(sf::Vector2f((index + 1) * GRAPH_POINT_DISTANCE_SEPERATION, m_graphPoints[index].getScreenPosition())));
            m_vertices.push_back(sf::Vertex(sf::Vector2f((index + 2) * GRAPH_POINT_DISTANCE_SEPERATION, m_graphPoints[index + 1].getScreenPosition())));
            ++index;
        }
        m_vertices.push_back(sf::Vertex(sf::Vector2f((index + 1)*10, m_graphPoints[index].getScreenPosition())));
    }
}

void GraphLines::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // apply the transform
    states.texture = NULL; // apply the tileset texture
    target.draw(&m_vertices[0], m_vertices.size(), sf::Lines, states); // draw the vertex array
}



/************************ PRIVATE METHODS ************************/

/**
 * This goes throught the elements and adjusts them to fit on the screen so that if we have a spike the graph will adjust
 * @param newYValue the new maximum value to be set
 */
void GraphLines::yValueChange(float newYValue)
{
    currentMaxYValue = newYValue;
    if (currentMaxYValue == 0)
    {
        return;
    }
    std::vector<GraphPoint>::iterator it = m_graphPoints.begin();
    float preVal = 100.0 / currentMaxYValue;
    while (it != m_graphPoints.end())
    {
        std::cout << "Values " << it->getValue() << "\n";
        std::cout << "new value " << screenHeight - (screenHeight * ((preVal * it->getValue()) / 100.0)) << "\n";
        it->setScreenPosition(screenHeight - (screenHeight * ((preVal * it->getValue()) / 100.0)) + 50);
        ++it;
    }
}