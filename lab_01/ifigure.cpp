#include "ifigure.h"
#include "caretaker.h"
#include "myscene.h"
#include <QDebug>

IFigure::IFigure(MyScene *parent, const QPointF &center) : scene(parent), figureCenter(center)
{
    figureMatrix = std::vector<std::vector<double>>(3, std::vector<double>(3, 0));
    setDefaultTransformMatrix();
}

void IFigure::save()
{
    // TODO const cast
    Caretaker::get().store(std::make_unique<IMemento>(figureMatrix), this);
}

void IFigure::restore(std::unique_ptr<IMemento> memento)
{
    figureMatrix = memento->matrix;
}

void IFigure::setFigureCenter(const QPointF &center_)
{
    figureMatrix[2][0] = center_.x();
    figureMatrix[2][1] = center_.y();
}

void IFigure::addFigureCenter(const QPointF &center_)
{
    figureMatrix[2][0] += center_.x();
    figureMatrix[2][1] += center_.y();
}

void IFigure::addFigureAngle(double inputAngle)
{
    auto angle_ = qDegreesToRadians(inputAngle);

    figureMatrix[0][0] *= qCos(angle_);
    figureMatrix[0][1] *= qSin(angle_);

    figureMatrix[1][0] *= -qSin(angle_);
    figureMatrix[1][1] *= qCos(angle_);
}

void IFigure::setFigureAngle(double inputAngle)
{
    auto angle_ = qDegreesToRadians(inputAngle);

    figureMatrix[0][0] = qCos(angle_);
    figureMatrix[0][1] = qSin(angle_);

    figureMatrix[1][0] = -qSin(angle_);
    figureMatrix[1][1] = qCos(angle_);
}

void IFigure::addFigureScale(const QPointF &inputScale)
{
    figureMatrix[0][0]  += inputScale.x();
    figureMatrix[1][1]  += inputScale.y();
    if (figureMatrix[0][0] <= 0.2 || figureMatrix[1][1] <= 0.2)
    {
        setFigureScale(QPointF(0.2, 0.2));
        QMessageBox::warning(nullptr, "Внимание", "Масштаб не может быть меньше 0.2");
    }
}

void IFigure::setFigureScale(const QPointF &inputScale)
{
    figureMatrix[0][0]  = inputScale.x();
    figureMatrix[1][1]  = inputScale.y();
}

void IFigure::setTransformMatrix(transformMatrix inputMatrix)
{
    figureMatrix = inputMatrix;
}

void IFigure::setDefaultTransformMatrix()
{
    figureMatrix[0][0] = 1;
    figureMatrix[1][1] = 1;
    figureMatrix[2][2] = 1;
}

IFigure::transformMatrix IFigure::getTransformMatrix() const
{
    return figureMatrix;
}

void IFigure::applyFigureTransformMatrix()
{
    auto x = figureCenter.x(); auto y = figureCenter.y();
    figureCenter.setX((x * figureMatrix[0][0] + y * figureMatrix[1][0] + figureMatrix[2][0]) / (x * figureMatrix[0][2] + y * figureMatrix[1][2] + figureMatrix[2][2]));
    figureCenter.setY((x * figureMatrix[0][1] + y * figureMatrix[1][1] + figureMatrix[2][1]) / (x * figureMatrix[0][2] + y * figureMatrix[1][2] + figureMatrix[2][2]));
}

QPointF IFigure::applyFigureTransformMatrix(const QPointF &point)
{
    auto x = point.x(); auto y = point.y();

    QPointF retValue{};
    retValue.setX((x * figureMatrix[0][0] + y * figureMatrix[0][1] + figureMatrix[2][0]) / (x * figureMatrix[0][2] + y * figureMatrix[1][2] + figureMatrix[2][2]));
    retValue.setY((x * figureMatrix[1][0] + y * figureMatrix[1][1] + figureMatrix[2][1]) / (x * figureMatrix[0][2] + y * figureMatrix[1][2] + figureMatrix[2][2]));

    return retValue;
}

double IFigure::applyFigureTransformMatrixX(double x)
{
//    return ((x * figureMatrix[0][0] + figureMatrix[2][0]) / (x * figureMatrix[0][2] + figureMatrix[2][2]));
    auto b = std::sqrt(figureMatrix[0][0] * figureMatrix[0][0] + figureMatrix[0][1] * figureMatrix[0][1]);

    return b;
}

double IFigure::applyFigureTransformMatrixY(double y)
{
    return std::sqrt(figureMatrix[1][0] * figureMatrix[1][0] + figureMatrix[1][1] * figureMatrix[1][1]);
}

QPointF IFigure::getFigureCenter() const
{
    return figureCenter;
}

QPointF IFigure::getFigureScale() const
{
    return QPointF(figureMatrix[0][0],figureMatrix[1][1]);
}

double IFigure::getFigureAngle() const
{
    return qRadiansToDegrees(std::atan2(figureMatrix[1][0], figureMatrix[0][0]));
}

void IFigure::setDefault()
{
    figureMatrix[0][0] = 1;
    figureMatrix[0][1] = 0;
    figureMatrix[0][2] = 0;
    figureMatrix[1][0] = 0;
    figureMatrix[1][1] = 1;
    figureMatrix[1][2] = 0;
    figureMatrix[2][0] = 0;
    figureMatrix[2][1] = 0;
    figureMatrix[2][2] = 1;
}



