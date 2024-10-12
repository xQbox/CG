#include "tank.h"
#include "myscene.h"
#include <QDebug>

double Tank::uploadScaleX()
{
    return std::sqrt((figureMatrix[0][0]) * (figureMatrix[0][0]) + (figureMatrix[0][1]) * (figureMatrix[0][1]));
}

double Tank::uploadScaleY()
{
   return std::sqrt((figureMatrix[1][0]) * (figureMatrix[1][0]) + (figureMatrix[1][1]) * (figureMatrix[1][1]));
}

double Tank::uploadAngle()
{
    return atan2(figureMatrix[0][1] / uploadScaleY(), figureMatrix[0][0] / uploadScaleX());
}


Tank::Tank(MyScene *parent, const QPointF &center) : IFigure(parent, center)
{
}

void Tank::draw()
{
// 0 - весь, 1 - низ, 2 - верх, 3 - право, 4 - лево
// Рисование происходит в координатах поля
// scene->myLightupLine(applyMatrixTransform(QPointF(-120, -150 )), applyMatrixTransform(QPointF(120, -150 ));
// TODO проблема эллипс при увеличении обрезает круг до прямой
// TODO проблема не рисуется прямая линия если в первой точке координата у больше чем координата у второй точки
// scene->myLightupLine(applyFigureTransformMatrix(QPointF(-120, 150)), applyFigureTransformMatrix(QPointF(-120, -60)));
//    (x * figureMatrix[0][0] + y * figureMatrix[1][0] + figureMatrix[2][0]) / (x * figureMatrix[0][2] + y * figureMatrix[1][2] + figureMatrix[2][2])

    // Башня
    scene->myLightupLine(applyFigureTransformMatrix(QPointF(-120  , 150  )), applyFigureTransformMatrix(QPointF(120  , 150  )));
    scene->myLightupLine(applyFigureTransformMatrix(QPointF(-120  , 60  )), applyFigureTransformMatrix(QPointF(-120  , 150 )));
    scene->myLightupLine(applyFigureTransformMatrix(QPointF(120  , 60 )), applyFigureTransformMatrix(QPointF(120 ,  150  )));
    // Корпус
    scene->myLightupLine(applyFigureTransformMatrix(QPointF(-300 , -60 )), applyFigureTransformMatrix(QPointF(300 , -60 )));
    scene->myLightupLine(applyFigureTransformMatrix(QPointF(-300 , 60 )), applyFigureTransformMatrix(QPointF(300 ,  60 )));

    // Гусеницы
    scene->myLightupCircle(applyFigureTransformMatrix(QPointF(0  ,0 )),  50   * applyFigureTransformMatrixX(50), uploadAngle(), 0);
    scene->myLightupCircle(applyFigureTransformMatrix(QPointF(-100 , 0 )), 50  * applyFigureTransformMatrixX(50), uploadAngle(), 0);
    scene->myLightupCircle(applyFigureTransformMatrix(QPointF(100 , 0 )), 50  * applyFigureTransformMatrixX(50), uploadAngle(), 0);
    scene->myLightupCircle(applyFigureTransformMatrix(QPointF(-200 , 0 )), 50  * applyFigureTransformMatrixX(50), uploadAngle(), 0);
    scene->myLightupCircle(applyFigureTransformMatrix(QPointF(200 , 0 )), 50  * applyFigureTransformMatrixX(50), uploadAngle(), 0);


    // Доп гусли
    scene->myLightupCircle(applyFigureTransformMatrix(QPointF(-300 , 0 )), 60  * applyFigureTransformMatrixX(60), uploadAngle(), 4);
    scene->myLightupCircle(applyFigureTransformMatrix(QPointF(300 , 0 )), 60  * applyFigureTransformMatrixX(60), uploadAngle(), 3);

    // Башня (Дуга Эллипса)
    scene->myLightupEllipse(applyFigureTransformMatrix(QPointF(0  , 150 )), 120  * applyFigureTransformMatrixX(120) , 30  * applyFigureTransformMatrixY(30), uploadAngle(),  2);
}

bool Tank::isPointInFigure(const QPointF &scenePoint) const
{
    QPointF pointTmp = scene->applyInverseMatrix(figureMatrix, scenePoint);
//    scene->printPoint(pointTmp);
   // Сделать rect
    if (-120 < pointTmp.x() && pointTmp.x()  < 120 && 60 < pointTmp.y() && pointTmp.y() < 180)
    {
        return true;
    }
    if (-360 < pointTmp.x() && pointTmp.x()  < 360 && -60 < pointTmp.y() && pointTmp.y() < 60)
    {
        return true;
    }
    return false;
}
