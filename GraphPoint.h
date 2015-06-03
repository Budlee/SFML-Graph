/* 
 * File:   GraphPoint.h
 * Author: matt
 *
 * Created on 03 June 2015, 16:31
 */

#ifndef GRAPHPOINT_H
#define	GRAPHPOINT_H

class GraphPoint {
public:
    GraphPoint(float sPos, float val):screenPosition(sPos), value(val){};
    float getScreenPosition(){return screenPosition;}
    float getValue(){return value;}
    void setScreenPosition(float newScreenPos){screenPosition = newScreenPos;};
private:
    float screenPosition;
    float value;
};

#endif	/* GRAPHPOINT_H */

