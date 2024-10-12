#include "myscene.h"
#include <QtMath>
#include <QDebug>

#define PD(var1, var2) qDebug() << "The Value of" << var1 << "is" << var2 << "\n";


MyScene::MyScene(QWidget *parent)
    : QWidget(parent)
{
    matrix = std::vector<std::vector<double>>(3, std::vector<double>(3, 0));
    matrix[0][0] = 1;
    matrix[1][1] = 1;
    matrix[2][2] = 1;

    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowTitleHint);
//    addPosition(QPointF(-width() / 2, height() / 2));
    setMirrorY();
    setDrawAxis(1);
    setDrawCenter(1);
    setDrawGrid(1);
    setDrawSceneRect(0);
    figures.push_back(std::make_unique<Tank>(this, QPointF(applyTransformMatrix(QPointF(matrix[2][0],matrix[2][1])))));
    printPoint(applyTransformMatrix(QPointF(matrix[2][0],matrix[2][1])));
}

QPointF MyScene::applyInverseMatrix(transformMatrix regularMatrix, const QPointF &point)
{
    auto a = regularMatrix[0][0] * (regularMatrix[1][1] * regularMatrix[2][2] - regularMatrix[1][2] * regularMatrix[2][1]);
    auto b = regularMatrix[0][1] * (regularMatrix[1][0] * regularMatrix[2][2] - regularMatrix[1][2] * regularMatrix[2][0]);
    auto p = regularMatrix[0][2] * (regularMatrix[1][0] * regularMatrix[2][1] - regularMatrix[1][1] * regularMatrix[2][0]);

    auto determinant = (a - b + p);

     transformMatrix retValue = std::vector<std::vector<double>>(3, std::vector<double>(3, 0));
    retValue[0][0] = (regularMatrix[1][1] * regularMatrix[2][2] - regularMatrix[1][2] * regularMatrix[2][1]) / determinant;
    retValue[0][1] =  -(regularMatrix[1][0] * regularMatrix[2][2] - regularMatrix[1][2] * regularMatrix[2][0]) / determinant;
    retValue[0][2] = (regularMatrix[1][0] * regularMatrix[2][1] - regularMatrix[1][1] * regularMatrix[2][0]) / determinant;
    retValue[1][0] = -(regularMatrix[0][1] * regularMatrix[2][2] - regularMatrix[0][2] * regularMatrix[2][1]) / determinant;
    retValue[1][1] = (regularMatrix[0][0] * regularMatrix[2][2] - regularMatrix[0][2] * regularMatrix[2][0]) / determinant;
    retValue[1][2] = -(regularMatrix[0][0] * regularMatrix[2][1] - regularMatrix[0][1] * regularMatrix[2][0]) / determinant;
    retValue[2][0] = (regularMatrix[0][1] * regularMatrix[1][2] - regularMatrix[0][2] * regularMatrix[1][1]) / determinant;
    retValue[2][1] = -(regularMatrix[0][0] * regularMatrix[1][2] - regularMatrix[0][2] * regularMatrix[1][0]) / determinant;
    retValue[2][2] = (regularMatrix[0][0] * regularMatrix[1][1] - regularMatrix[0][1] * regularMatrix[1][0]) / determinant;

     for (size_t i = 0; i < 3; ++i)
     {
         for (size_t j = 0; j < 3; ++j)
         {
             if (i > j)
             {
                std::swap(retValue[i][j], retValue[j][i]);
             }
         }
     }
     auto x = point.x(); auto y = point.y();
     QPointF retPoint{};
     retPoint.setX((x * retValue[0][0] + y * retValue[1][0] + retValue[2][0]) / (x * retValue[0][2] + y * retValue[1][2] + retValue[2][2]));
     retPoint.setY((x * retValue[0][1] + y * retValue[1][1] + retValue[2][1]) / (x * retValue[0][2] + y * retValue[1][2] + retValue[2][2]));

     return retPoint;
}

void MyScene::saveScreen()
{
    // Создаем QPixmap с размерами виджета
    QPixmap pixmap(size());
    // Рисуем содержимое виджета в pixmap
    render(&pixmap);

    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить изображение", "", "Images (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty())
    {
        pixmap.save(fileName);
    }
}
MyScene::transformMatrix MyScene::getTransformMatrix() const
{
    return matrix;
}


void MyScene::setTransformMatrix(transformMatrix inputMatrix)
{
    matrix = inputMatrix;
}


void MyScene::setDefaultTransformMatrix()
{
    matrix[0][0] = 1;
    matrix[0][1] = 0;
    matrix[0][2] = 0;
    matrix[1][0] = 0;
    matrix[1][1] = 1;
    matrix[1][2] = 0;
    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;
    setMirrorY();
}

void MyScene::toDefaultSetting()
{
    setDefaultTransformMatrix();
    for (auto &elem : figures)
    {
         elem->setDefault();
    }
    update();
}


void MyScene::printTransformMatrix()
{
    QDebug debug = qDebug();
    debug.setAutoInsertSpaces(false);

    for (const auto& row : matrix)
    {
        for (const auto& element : row)
        {
            debug  << element << " ";
        }
        debug << "\n";
    }
}
void MyScene::printPoint(const QPointF &point)
{
    qDebug() << "--------------Point-----------\n";
    qDebug() << "(" << point.x() << ":" << point.y() << ")" <<  " - Точка\n";
    qDebug() << "------------------------------\n";
}

void MyScene::printRect(const QRectF &rect, QString nameCurrentRect)
{
    if (nameCurrentRect.size() != 0)
        qDebug() << nameCurrentRect << "\\/\\/\\/\\/\\/\n";
    qDebug() << "---------------Rect------------------\n";
    qDebug() << "(" << rect.topLeft().x() << ":" << rect.topLeft().y() << ")" <<  " - Верх лево\n";
    qDebug() << "(" << rect.topRight().x() << ":" << rect.topRight().y() << ")" <<  " - Верх право\n";
    qDebug() << "(" << rect.bottomLeft().x() << ":" << rect.bottomLeft().y() << ")" <<  " - Низ лево\n";
    qDebug() << "(" << rect.bottomRight().x() << ":" << rect.bottomRight().y() << ")" <<  " - Низ право\n";
    qDebug() << "-------------------------------------\n";
}

void MyScene::printLine(Line line)
{

    QDebug debug = qDebug();
    debug.setAutoInsertSpaces(false);
    debug << "--------------Line-----------\n";
    debug << "(" << line[0].x() << ":" << line[0].y() << ") ->";
    debug << "(" << line[1].x() << ":" << line[1].y() << ")\n";
    debug << "------------------------------\n";
}

void MyScene::checkDebug()
{
    qDebug() << "In Funcion.Step here\n";
}

void MyScene::displayWarningMessage(QString message)
{
    QMessageBox::warning(this, "Внимание!", message);
}

void MyScene::addFiguresCenter(const QPointF &offset)
{
    for (auto &elem : figures)
    {
        elem->addFigureCenter(offset);
    }
    update();
}

void MyScene::setFiguresCenter(const QPointF &newCenter)
{
    for (auto &elem : figures)
    {
        elem->setFigureCenter(newCenter);
    }
    update();
}

QPointF MyScene::getFiguresCenter(size_t index)
{
    if (index > figures.size())
    {
        // TODO Throw catch func
    }
    return figures[index].get()->getFigureCenter();
}

void MyScene::addFigureCenter(const QPointF &offset, size_t index)
{
    if (index > figures.size())
    {
        // TODO Throw catch func
    }
    figures[index].get()->addFigureCenter(offset);
}

void MyScene::addFiguresAngle(double angle)
{
    for (auto &elem : figures)
    {
        elem->addFigureAngle(angle);
    }
    update();
}

void MyScene::setFiguresAngle(double angle)
{
    for (auto &elem : figures)
    {
        elem->setFigureAngle(angle);
    }
    update();
}

QPointF MyScene::getFiguresAngle(size_t index)
{
    return QPointF(0,0);
}

void MyScene::addFigureAngle(const QPointF &offset, size_t index)
{

}

void MyScene::addFiguresScale(const QPointF &inputScale)
{
    for (auto &elem : figures)
    {
        elem->addFigureScale(inputScale);
    }
}

void MyScene::setFiguresScale(const QPointF &inputScale)
{
    for (auto &elem : figures)
    {
        elem->setFigureScale(inputScale);
    }
}

QPointF MyScene::getFiguresScale(size_t index)
{

    return QPointF(0,0);
}

void MyScene::addFigureScale(const QPointF &offset, size_t index)
{
}

MyScene::Line MyScene::createLine(const QPointF &point1, const QPointF &point2)
{
   Line line = { point1, point2 };
   return line;
}


//std::vector<IFigure> MyScene::getVisiableFigures()
//{
//    QRectF visiableRect = getVisiableUserRect();
//    return std::ve;
//}

void MyScene::uploadSave()
{
    Caretaker::get().restore();
    update();
}


QPointF MyScene::applyTransformMatrix(const QPointF &point)
{
    auto x = point.x(); auto y = point.y();
    QPointF retValue{};

    retValue.setX((x * matrix[0][0] + y * matrix[1][0] + matrix[2][0]) / (x * matrix[0][2] + y * matrix[1][2] + matrix[2][2]));
    retValue.setY((x * matrix[0][1] + y * matrix[1][1] + matrix[2][1]) / (x * matrix[0][2] + y * matrix[1][2] + matrix[2][2]));

    return retValue;
}

QPointF MyScene::applyMatrix(transformMatrix regularMatrix,const QPointF &point)
{
    auto x = point.x(); auto y = point.y();
    QPointF retValue{};

    retValue.setX((x * regularMatrix[0][0] + y * regularMatrix[1][0] + regularMatrix[2][0]) / (x * regularMatrix[0][2] + y * regularMatrix[1][2] + regularMatrix[2][2]));
    retValue.setY((x * regularMatrix[0][1] + y * regularMatrix[1][1] + regularMatrix[2][1]) / (x * regularMatrix[0][2] + y * regularMatrix[1][2] + regularMatrix[2][2]));

    return retValue;
}

void MyScene::printMatrix(const transformMatrix inputMatrix)
{

    QDebug debug = qDebug();
    debug.setAutoInsertSpaces(false);

    for (const auto& row : inputMatrix)
    {
        for (const auto& element : row)
        {
            debug  << element << " ";
        }
        debug << "\n";
    }
}

void MyScene::setScale(const QPointF &scale)
{

    matrix[0][0] = scale.x();
    matrix[1][1] = scale.y();
    update();
}

void MyScene::setAngle(const double &angle)
{
    auto angle_ = qDegreesToRadians(angle);

    matrix[0][0] = qCos(angle_);
    matrix[0][1] = -qSin(angle_);

    matrix[0][1] = qSin(angle_);
    matrix[1][1] = qCos(angle_);
    update();
}

void MyScene::setMirrorX()
{
    matrix[0][0] = -1;
    update();

}


void MyScene::setMirrorY()
{
    matrix[1][1] = -1;
    update();

}

void MyScene::setMirrorYX()
{
    matrix[0][1] = 1;
    matrix[1][0] = 1;
    update();
}

void MyScene::setMirrorCenter()
{
    matrix[0][0] = -1;
    matrix[1][1] = -1;
    update();
}

void MyScene::setDrawGrid(bool drawGrid)
{
    isDrawGrid = drawGrid;
    update();
}

void MyScene::setDrawAxis(bool drawAxis)
{
    isDrawAxis = drawAxis;
    update();
}

void MyScene::setDrawCenter(bool drawCenter)
{
    isDrawCenter = drawCenter;
    update();
}

void MyScene::setDrawSceneRect(bool drawSceneRect)
{
    isSceneRect = drawSceneRect;
    update();
}

void MyScene::addScale(const QPointF &scale)
{
    matrix[0][0] += scale.x();
    matrix[1][1] -= scale.y(); // - из-за того, что y инвертирован
    if (matrix[0][0] <= 0.2 || matrix[1][1] >= -0.2)
    {
        setScale(QPointF(0.2, -0.2));
        displayWarningMessage("Масштаб не может быть меньше 0.2");
    }
    if (matrix[0][0] >= 2.5 || matrix[1][1] <= -2.5)
    {
        setScale(QPointF(2.5, -2.5));
        displayWarningMessage("Масштаб не может быть больше 2.5");
    }
}

void MyScene::addAngle(const double &angle)
{
    auto angle_ = qDegreesToRadians(angle);

    matrix[0][0] *= qCos(angle_);
    matrix[0][1] *= -qSin(angle_);

    matrix[0][1] *= qSin(angle_);
    matrix[1][1] *= qCos(angle_);
}

QPointF MyScene::screenToUser(const QPointF &point)
{
     return applyMatrix(matrix, point);
}



QRectF MyScene::getVisiableUserRect()
{
    QPointF topLeft = applyMatrix(matrix, this->rect().topLeft());
    QPointF bottomRight = applyMatrix(matrix,this->rect().bottomRight());
    QRectF retValue(topLeft, bottomRight);
    return retValue;
}



void MyScene::addPosition(const QPointF &point)
{
    matrix[2][0] -= point.x();
    matrix[2][1] -= point.y();
    update();
}

void MyScene::setPosition(const QPointF &point)
{
    matrix[2][0] = point.x();
    matrix[2][1] = point.y();
    update();
}

void MyScene::drawAxis()
{
    auto visiableRect = getVisiableUserRect();
    if (visiableRect.topLeft().x() <= 0  && visiableRect.topRight().x() >= 0)
    {
        myLightupLine(QPointF(0, visiableRect.bottomLeft().y()), QPointF(0, visiableRect.topLeft().y()));
    }
    if (visiableRect.topRight().y() >= 0  && visiableRect.bottomRight().y() <= 0)
    {
        myLightupLine(QPointF(visiableRect.bottomLeft().x(), 0), QPointF(visiableRect.bottomRight().x(), 0));
    }
}

void MyScene::drawGrid()
{
    const int gridSpace = 150 ;
    QRectF visiableRect = getVisiableUserRect();
    printRect(visiableRect);

    auto scaleFactor = std::ceil(matrix[0][0]);

    if (isSceneRect)
    {
        painter->drawRect((width() - visiableRect.width()) / 2, (height() - visiableRect.height()) / 2, visiableRect.width(), visiableRect.height());
        painter->setClipRect((width() - visiableRect.width()) / 2, (height() - visiableRect.height()) / 2, visiableRect.width(), visiableRect.height());
    }

    const QPointF center = QPointF(matrix[2][0], matrix[2][1]);

    auto leftVerticalLines = std::abs(std::ceil(visiableRect.topLeft().x() / gridSpace)) + 1;
    auto topHorizontalLines = std::abs(std::ceil(visiableRect.topLeft().y() / gridSpace)) + 1;

    auto rightVerticalLines = std::abs(std::ceil(visiableRect.topRight().x() / gridSpace)) + 1;
    auto bottomHorizontalLines = std::abs(std::ceil(visiableRect.bottomRight().y() / gridSpace)) + 1;

        QPen pen = painter->pen();
        painter->setPen(QPen(Qt::lightGray, 3));

    for (auto i = static_cast<int>(isDrawAxis); i < leftVerticalLines * scaleFactor; ++i)
    {
        myLightupLine(QPointF(-i * gridSpace, visiableRect.topRight().y()), QPointF(- i * gridSpace, visiableRect.bottomRight().y() ));
    }

    for (auto i = static_cast<int>(isDrawAxis); i < topHorizontalLines * scaleFactor; ++i)
    {
        myLightupLine(QPointF(visiableRect.topLeft().x(), i * gridSpace), QPointF(visiableRect.topRight().x(), i * gridSpace));
    }


    for (auto i = static_cast<int>(isDrawAxis); i < rightVerticalLines * scaleFactor; ++i)
    {
        myLightupLine(QPointF(i * gridSpace, visiableRect.bottomRight().y()), QPointF(i * gridSpace, visiableRect.topRight().y()));
    }

    for (auto i = static_cast<int>(isDrawAxis); i < bottomHorizontalLines * scaleFactor; ++i)
    {
        myLightupLine(QPointF(visiableRect.bottomLeft().x(), -i * gridSpace), QPointF(visiableRect.bottomRight().x(), -i * gridSpace));
    }

    painter->setPen(QPen(Qt::black, 5));

    for (auto i = static_cast<int>(isDrawAxis); i < leftVerticalLines * scaleFactor; ++i)
    {
        painter->drawText(applyInverseMatrix(matrix, QPointF(- i * gridSpace, 0) + QPointF(-20, 30)), QString("%1").arg((-i * gridSpace)));
    }

    for (auto i = static_cast<int>(isDrawAxis); i < topHorizontalLines * scaleFactor; ++i)
    {
        painter->drawText(applyInverseMatrix(matrix, (QPointF(0, i * gridSpace) + QPointF(-80, 20))), QString("%1").arg((i * gridSpace )));
    }

    for (auto i = static_cast<int>(isDrawAxis); i < rightVerticalLines * scaleFactor; ++i)
    {
        painter->drawText(applyInverseMatrix(matrix, QPointF(i * gridSpace, 0) + QPointF(-20, 30)), QString("%1").arg((i * gridSpace  )));
    }

    for (auto i = static_cast<int>(isDrawAxis); i < bottomHorizontalLines * scaleFactor; ++i)
    {
        painter->drawText(applyInverseMatrix(matrix, QPointF(0, -i * gridSpace) + QPointF(-80, 20)), QString("%1").arg((-i * gridSpace )));
    }

    painter->setPen(pen);
}

void MyScene::LightupPoint4Ellipse(const QPointF &Center, double x, double y, double angle, int side)
{
    QPointF rotatedRight = rotatePoint(x, y, -angle);
    QPointF rotatedLeft = rotatePoint(x, y, angle);

    if (side == 1) // Низ
    {
          myLightupPoint(QPointF(Center.x() + rotatedLeft.x(), Center.y() - rotatedLeft.y()));
          myLightupPoint(QPointF(Center.x() - rotatedRight.x(), Center.y() - rotatedRight.y()));
    }
    else if (side == 2) // Верх
    {
          myLightupPoint(QPointF(Center.x() - rotatedLeft.x(), Center.y() + rotatedLeft.y()));
          myLightupPoint(QPointF(Center.x() + rotatedRight.x(), Center.y() + rotatedRight.y()));
    }
    else if (side == 3) // Право
    {
          myLightupPoint(QPointF(Center.x() + rotatedRight.x(), Center.y() + rotatedRight.y()));
          myLightupPoint(QPointF(Center.x() + rotatedLeft.x(), Center.y() - rotatedLeft.y()));
    }
    else if (side == 4) // Лево
    {
          myLightupPoint(QPointF(Center.x() - rotatedRight.x(), Center.y() - rotatedRight.y()));
          myLightupPoint(QPointF(Center.x() - rotatedLeft.x(), Center.y() + rotatedLeft.y()));
    }
    else if (side == 0)
    {
        myLightupPoint(QPointF(Center.x() + rotatedLeft.x(), Center.y() - rotatedLeft.y()));
        myLightupPoint(QPointF(Center.x() - rotatedRight.x(), Center.y() - rotatedRight.y()));
        myLightupPoint(QPointF(Center.x() - rotatedLeft.x(), Center.y() + rotatedLeft.y()));
        myLightupPoint(QPointF(Center.x() + rotatedRight.x(), Center.y() + rotatedRight.y()));
    }

}

void MyScene::myLightupPoint(const QPointF &point)
{
    painter->drawPoint(applyInverseMatrix(matrix, point));
}

void MyScene::myLightupLine(const QPointF &start, const QPointF &stop)
{
    auto x1 = start.x();
     auto y1 = start.y();
     auto x2 = stop.x();
     auto y2 = stop.y();

     auto dx = abs(x2 - x1);
     auto dy = abs(y2 - y1);

     int sx = (x2 > x1) ? 1 : -1;
     int sy = (y2 > y1) ? 1 : -1;

     bool isSteep = dy > dx;

     if (isSteep) {
         std::swap(x1, y1);
         std::swap(x2, y2);
         std::swap(dx, dy);
         std::swap(sx, sy);
     }

     auto incrE = 2 * dy;
     auto incrNE = 2 * (dy - dx);
     auto f = 2 * dy - dx;

     if (isSteep)
         myLightupPoint(QPointF(y1, x1));  // Если крутая, то X и Y поменяны
     else
         myLightupPoint(QPointF(x1, y1));

     while ((sx > 0 && x1 <= x2) || (sx < 0 && x1 >= x2)) {
         if (f > 0) {
             y1 += sy;
             f += incrNE;
         } else {
             f += incrE;
         }
         x1 += sx;
         if (isSteep)
             myLightupPoint(QPointF(y1, x1));  // Если крутая, то X и Y поменяны
         else
             myLightupPoint(QPointF(x1, y1));
     }

//        auto x1 = start.x();
//        auto y1 = start.y();
//        auto x2 = stop.x();
//        auto y2 = stop.y();

//        auto dx = abs(x2 - x1);
//        auto dy = abs(y2 - y1);

//        int sx = (x2 > x1) ? 1 : -1;  // Определяем направление движения по X
//        int sy = (y2 > y1) ? 1 : -1;  // Определяем направление движения по Y

//        bool isSteep = dy > dx;  // Проверка на крутизну линии

//        // Если линия крутая, меняем X и Y местами
//        if (isSteep) {
//            std::swap(x1, y1);
//            std::swap(x2, y2);
//            std::swap(dx, dy);
//        }

//        auto incrE = 2 * dy;
//        auto incrNE = 2 * (dy - dx);
//        auto f = 2 * dy - dx;

//        // Рисуем первую точку
//        if (isSteep)
//            myLightupPoint(QPointF(y1, x1));  // Если крутая, то X и Y поменяны
//        else
//            myLightupPoint(QPointF(x1, y1));

//        // Основной цикл для отрисовки линии
//        while (x1 != x2) {  // Условие выхода из цикла: x1 должен достичь x2
//            if (f > 0) {
//                y1 += sy;  // Двигаемся по Y только если ошибка превышает порог
//                f += incrNE;
//            } else {
//                f += incrE;
//            }
//            x1 += sx;  // Двигаемся по X каждый шаг

//            // Рисуем очередную точку
//            if (isSteep)
//                myLightupPoint(QPointF(y1, x1));  // Если линия крутая
//            else
//                myLightupPoint(QPointF(x1, y1));  // Если линия пологая
//        }

}

QPointF MyScene::rotatePoint(int x, int y, double angle)
{
    double x_new = static_cast<double>(x * cos(angle) - y * sin(angle));
    double y_new = static_cast<double>(x * sin(angle) + y * cos(angle));
    return QPointF(x_new, y_new);
}



void MyScene::myLightupEllipse(const QPointF &Center, int rx, int ry, double angle_, int side)
{
//    float dx, dy, d1, d2, x, y;
//       x = 0;
//       y = ry;
//       angle_ = qDegreesToRadians(angle_);
//       // Первоначальное значение параметра принятия решения в первой области
//       d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
//       dx = 2 * ry * ry * x;
//       dy = 2 * rx * rx * y;

//       while (dx < dy)
//       {
//           // Поворот точки на угол angle_


//               auto rotatedPoint1 = rotatePoint(x, y, angle_);
//               auto rotatedPoint2 = rotatePoint(x, -y, angle_);

////           LightupPoint4Ellipse(Center, x_rotated, y_rotated, side);
//                   myLightupPoint(QPointF(Center.x() - rotatedPoint1.x(), Center.y() + rotatedPoint1.y()));
//                   myLightupPoint(QPointF(Center.x() + rotatedPoint2.x(), Center.y() - rotatedPoint2.y()));
//           if (d1 < 0)
//           {
//               x++;
//               dx = dx + (2 * ry * ry);
//               d1 = d1 + dx + (ry * ry);
//           }
//           else
//           {
//               x++;
//               y--;
//               dx = dx + (2 * ry * ry);
//               dy = dy - (2 * rx * rx);
//               d1 = d1 + dx - dy + (ry * ry);
//           }
//       }

//       d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);

//       while (y >= 0)
//       {
//           float x_rotated = x * qCos(angle_) - y * qSin(angle_);
//           float y_rotated = x * qSin(angle_) + y * qCos(angle_);
//           LightupPoint4Ellipse(Center, x_rotated, y_rotated, side);

//           if (d2 > 0) {
//               y--;
//               dy = dy - (2 * rx * rx);
//               d2 = d2 + (rx * rx) - dy;
//           } else {
//               y--;
//               x++;
//               dx = dx + (2 * ry * ry);
//               dy = dy - (2 * rx * rx);
//               d2 = d2 + dx - dy + (rx * rx);
//           }
//       }
//    int xc = static_cast<int>(Center.x());
//    int yc = static_cast<int>(Center.y());

//    int x = 0;
//    int y = ry;
//    long a2 = rx * rx;
//    long b2 = ry * ry;
//    long err = b2 - (2 * ry - 1) * a2;
//    long stopX = 2 * b2 * x;
//    long stopY = 2 * a2 * y;

//    // Первая часть эллипса (до наклона)
//    while (stopX <= stopY) {
//        auto rotatedPoint1 = rotatePoint(x, y, angle_);
//        auto rotatedPoint2 = rotatePoint(x, -y, angle_);
////        LightupPoint4Ellipse(Center, rotatedPoint1.x(), rotatedPoint1.y(), side);
//        myLightupPoint(QPointF(xc + rotatedPoint1.x(), yc + rotatedPoint1.y()));
//        myLightupPoint(QPointF(xc - rotatedPoint1.x(), yc + rotatedPoint1.y()));
//        myLightupPoint(QPointF(xc + rotatedPoint2.x(), yc - rotatedPoint2.y()));
//        myLightupPoint(QPointF(xc - rotatedPoint2.x(), yc - rotatedPoint2.y()));

//        x++;
//        stopX += 2 * b2;
//        if (err < 0) {
//            err += stopX + b2;
//        } else {
//            y--;
//            stopY -= 2 * a2;
//            err += stopX - stopY + b2;
//        }
//    }

//     Вторая часть эллипса (после наклона)
//    x = rx;
//    y = 0;
//    err = a2 - (2 * rx - 1) * b2;
//    stopX = 2 * b2 * y;
//    stopY = 2 * a2 * x;

//    while (stopX <= stopY) {
//        auto rotatedPoint1 = rotatePoint(x, y, angle_);
//        auto rotatedPoint2 = rotatePoint(-x, y, angle_);

////        myLightupPoint(QPointF(xc + rotatedPoint1.x(), yc + rotatedPoint1.y()));
//        myLightupPoint(QPointF(xc - rotatedPoint1.x(), yc + rotatedPoint1.y()));
//        myLightupPoint(QPointF(xc + rotatedPoint2.x(), yc - rotatedPoint2.y()));
////        myLightupPoint(QPointF(xc - rotatedPoint2.x(), yc - rotatedPoint2.y()));

//        y++;
//        stopX += 2 * a2;
//        if (err < 0) {
//            err += stopX + a2;
//        } else {
//            x--;
//            stopY -= 2 * b2;
//            err += stopX - stopY + a2;
//        }
//    }

      int x = 0;
      int y = ry;
      int a_sqr = rx * rx;
      int b_sqr = ry * ry;
      int delta = 4 * b_sqr * ((x + 1) * (x + 1)) + a_sqr * ((2 * y - 1) * (2 * y - 1)) - 4 * a_sqr * b_sqr; // Функция координат точки (x+1, y-1/2)
      while (a_sqr * (2 * y - 1) > 2 * b_sqr * (x + 1))
      {
          LightupPoint4Ellipse(Center, x, y, angle_, side);
          if (delta < 0)
          {
              ++x;
              delta += 4 * b_sqr * (2 * x + 3);
          }
          else
          {
              ++x;
              delta = delta - 8 * a_sqr * (y - 1) + 4 * b_sqr * (2 * x + 3);
              --y;
          }
      }
      delta = b_sqr * ((2 * x + 1) * (2 * x + 1)) + 4 * a_sqr * ((y + 1) * (y + 1)) - 4 * a_sqr * b_sqr; // Функция координат точки (x+1/2, y-1)
      while (y + 1 != 0)
      {
          LightupPoint4Ellipse(Center, x, y, angle_, side);
          if (delta < 0)
          {
              --y;
              delta += 4 * a_sqr * (2 * y + 3);
          }
          else
          {
              --y;
              delta = delta - 8 * b_sqr * (x + 1) + 4 * a_sqr * (2 * y + 3);
              ++x;
          }
      }
}

void MyScene::myLightupCircle(const QPointF &Center, double radius, double angle, int side)
{
    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error = 0;
    while(y >= 0)
    {
        LightupPoint4Ellipse(Center, x, y, angle, side);
        error = 2 * (delta + y) - 1;
        if (delta < 0 && error <= 0)
        {
            ++x;
            delta += 2 * x + 1;
            continue;
        }
        if (delta > 0 && error > 0)
        {
            --y;
            delta += 1 - 2 * y;
            continue;
        }
        ++x;
        delta += 2 * (x - y);
        --y;
    }
}


void MyScene::paintEvent(QPaintEvent *event)
{

    painter = new QPainter(this);

    painter->setFont(QFont("Calibri", 12));
    QPen pen = QPen(Qt::lightGray, 2);

    if (isDrawGrid)
    {
        pen = QPen(Qt::lightGray, 2);
        painter->setPen(pen);
        drawGrid();
    }

    if (isDrawAxis)
    {
        pen = QPen(Qt::black, 5);
        painter->setPen(pen);
        drawAxis();
    }

    if (isDrawCenter)
    {
        pen = QPen(Qt::blue, 10);

//        const QPointF center = QPointF(matrix[2][0], matrix[2][1]);
        painter->setPen(pen);
        myLightupPoint(QPointF(0, 0));
//        painter->drawText(QPointF(matrix[2][0], matrix[2][1]) + QPointF(20, -20), "0");
    }

    painter->setPen(QPen(Qt::red, 4));
    for (auto &elem : figures)
    {
        elem->draw();
    }
    painter->setPen(pen);
    printRect(getVisiableUserRect());
    delete painter;
}


void MyScene::wheelEvent(QWheelEvent *event)
{
    // TODO сделать проверку на отрицателный угол для фигур
    auto angle = event->angleDelta().y();
    // timer запустить и сохранить
    qDebug() << angle << "Угол\n";
    if (angle < 0)
    {
        if (!isClicked)
        {
            // сцена
            addScale(QPointF(0.1, 0.1));
        }
        else
        {
            // фигура
            addFiguresScale(QPointF(0.1, 0.1));
        }
    }
    else
    {
        //  сцена
        if (!isClicked)
        {
            addScale(QPointF(-0.1, -0.1));
        }
        else
        {
        // фигура
            addFiguresScale(QPointF(-0.1,-0.1));
        }
    }
    update();
}


void MyScene::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDragging = 1;
        startPosition = applyInverseMatrix(matrix, event->pos());


        QPointF clickedPoint = applyInverseMatrix(matrix, event->pos());

        isClicked = false;
        for (auto &elem : figures)
        {
            if (elem->isPointInFigure(clickedPoint))
            {
                isClicked = true;
                elem->save();
                break;
            }
        }
    }
}

void MyScene::mouseMoveEvent(QMouseEvent *event)
{
    auto scaleFactor = matrix[0][0];
    if (matrix[0][0] > 2)
        scaleFactor = 2 * matrix[0][0];
    printTransformMatrix();
    if (isClicked)
    {
        addFiguresCenter((applyInverseMatrix(matrix, event->pos()) - startPosition));
        startPosition = applyInverseMatrix(matrix, event->pos());
    }
    else if (isDragging)
    {
        addPosition((applyInverseMatrix(matrix, event->pos()) - startPosition));
        startPosition = applyInverseMatrix(matrix, event->pos());
    }
}

void MyScene::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDragging = 0;
//        for (auto &elem : figures)
//        {
//            printMatrix(elem->getTransformMatrix());
//        }
    }
}

void MyScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Z && event->modifiers() & Qt::ControlModifier)
    {
        uploadSave();
    }
    QWidget::keyPressEvent(event);
}

MyScene::~MyScene()
{

}






