#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QPointF>
#include <QtMath>
#include <QMessageBox>
#include <memory>
#include "isaveable.h"
class MyScene;

class IFigure : public QObject, public ISaveable
{
    Q_OBJECT
    // Remake shared_ptr using
    using transformMatrix = std::vector<std::vector<double>>;

protected:
    MyScene *scene;
    // TODO удалить
    QPointF figureCenter;
    transformMatrix figureMatrix;

public:
    void setFigureCenter(const QPointF &center_);
    void addFigureCenter(const QPointF &center_);
    void addFigureAngle(double inputAngle);
    void setFigureAngle(double inputAngle);
    void addFigureScale(const QPointF &inputScale);
    void setFigureScale(const QPointF &inputScale);


    void setTransformMatrix(transformMatrix inputMatrix);
    void setDefaultTransformMatrix();
    transformMatrix getTransformMatrix() const;

    void applyFigureTransformMatrix();
    QPointF applyFigureTransformMatrix(const QPointF &point);
    double applyFigureTransformMatrixX(double x);
    double applyFigureTransformMatrixY(double y);

    QPointF getFigureCenter() const;
    QPointF getFigureScale() const;
    double getFigureAngle() const;

    void setDefault();
    explicit IFigure(MyScene *parent, const QPointF &center);
    virtual void draw() = 0;
    virtual bool isPointInFigure(const QPointF &scenePoint) const = 0;

signals:


    // ISaveable interface
public:
    void save() override;
    void restore(std::unique_ptr<IMemento> memento) override;
};


#endif // FIGURE_H
