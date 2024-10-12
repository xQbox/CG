#ifndef TANK_H
#define TANK_H

#include "ifigure.h"
#include <QPointF>
#include <QtMath>
#include "imemento.h"
#include "isaveable.h"

class MyScene;

class Tank : public IFigure
{
    Q_OBJECT
public:
    double uploadAngle();
    Tank(MyScene *parent, const QPointF &center);
    void draw() override;
    bool isPointInFigure(const QPointF &scenePoint) const override;

    double uploadScaleY();
    double uploadScaleX();
};

#endif // TANK_H
