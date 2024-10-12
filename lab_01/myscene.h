#ifndef MYSCENE_H
#define MYSCENE_H

#include <QWidget>
#include <QPointF>
#include <QMouseEvent>
#include <QPainter>
#include <QRectF>
#include <QMessageBox>
#include <QPixmap>
#include <QFileDialog>

#include <vector>
#include <memory>
#include "ifigure.h"
#include "tank.h"
#include "caretaker.h"

class MyScene : public QWidget
{
    Q_OBJECT
    using transformMatrix = std::vector<std::vector<double>>;
//    using vectorFigure = std::vector<std::unique_ptr<IFigure>>;
    using Line = std::array<QPointF, 2>;

//  Сетка сначала идут вертикальные линии до середины, затем идут горизонтальные линии
//    using Grid = std::vector<Line>;


private:
    // TODO Удалить
    transformMatrix matrix;
    // TODO  Удалить
    transformMatrix viewMatrix;
    bool isClicked;
    bool isDragging;
    QPointF startPosition;
    QPainter *painter;
    bool isDrawGrid;
    bool isDrawAxis;
    bool isDrawCenter;
    bool isSceneRect;
    std::vector<std::unique_ptr<IFigure>> figures;


public:
    MyScene(QWidget *parent = nullptr);
    ~MyScene();

/*
 * ========================
 * Блок общих функций - ???
 * ========================
*/
    static QPointF applyInverseMatrix(transformMatrix regularMatrix, const QPointF &point);
    void saveScreen();
    QPointF rotatePoint(int x, int y, double angle);
/*
 * ======================================================
 * Блок функций для работы с матрицей трансформации Камеры
 * ======================================================
*/

/*
 * ======================================================
 * Блок функций для работы с матрицей трансформации сцены
 * ======================================================
*/
    transformMatrix getTransformMatrix() const;
    void setTransformMatrix(transformMatrix inputMatrix);
    void setDefaultTransformMatrix();
    void toDefaultSetting();
    QPointF applyTransformMatrix(const QPointF &point);
    QPointF applyMatrix(transformMatrix regularMatrix, const QPointF &point);
/*
 * ===================================
 * Блок функций для вывода информации
 * ===================================
*/
    static void printMatrix(const transformMatrix inputMatrix);
    void printTransformMatrix();
     static void printPoint(const QPointF &point);
     static void printRect(const QRectF &rect, QString nameCurrentRect = "");
     static void printLine(Line line);
     static void checkDebug();
    void displayWarningMessage(QString message);

    // TODO сделать получения центров всех фигур (центр=индекс)


/*
 * ========================
 * Блок функций управления
 * ========================
*/
    void setDrawGrid(bool drawGrid);
    void setDrawAxis(bool drawAxis);
    void setDrawCenter(bool drawCenter);
    void setDrawSceneRect(bool drawSceneRect);

/*
 * =====================================
 * Блок функций перевода координат сцены
 * =====================================
*/
    QPointF screenToUser(const QPointF &point);

/*
 * ===================================
 * Блок функций для работы со сценой
 * ===================================
*/

public:

    void drawGrid();
    void drawAxis();

    void addScale(const QPointF &scale);
    void addAngle(const double &angle);

    void addPosition(const QPointF &point);
    void setPosition(const QPointF &point);
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void setScale(const QPointF &scale);
    void setAngle(const double &angle);
    void setMirrorX();
    void setMirrorY();
    void setMirrorYX();
    void setMirrorCenter();

    QRectF getVisiableUserRect();
/*
 * ==========================================
 * Блок функций для работы со объектами сцены
 * ==========================================
*/

private:
    void LightupPoint4Ellipse(const QPointF &Center, double x, double y, double angle, int side);

public:
    void myLightupPoint(const QPointF &point);
    void myLightupLine(const QPointF &start, const QPointF &stop);
    void myLightupEllipse(const QPointF &Center, int rx, int ry, double angle_, int side);
    void myLightupCircle(const QPointF &Center, double radius, double angle, int side);


    void addFiguresCenter(const QPointF &offset);
    void setFiguresCenter(const QPointF &newCenter);
    QPointF getFiguresCenter(size_t index);
    void addFigureCenter(const QPointF &offset, size_t index);

    void addFiguresAngle(double angle);
    void setFiguresAngle(double angle);
    QPointF getFiguresAngle(size_t index);
    void addFigureAngle(const QPointF &offset, size_t index);

    void addFiguresScale(const QPointF &inputScale);
    void setFiguresScale(const QPointF &inputScale);
    QPointF getFiguresScale(size_t index);
    void addFigureScale(const QPointF &offset, size_t index);

/*
 * ================================
 * Блок функций для работы с камеры
 * ================================
*/
private:
    Line createLine(const QPointF& point1, const QPointF& point2);

public:



//    std::vector<IFigure> getVisiableFigures();

/*
 * ======================================
 * Блок функций перевода координат камеры
 * ======================================
*/


/*
 * =============================================
 * Блок функций для работы с системой сохранений
 * =============================================
*/
    void uploadSave();
};
#endif // MYSCENE_H
