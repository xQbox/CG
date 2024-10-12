#ifndef IMEMENTO_H
#define IMEMENTO_H

#include <QObject>
#include <QPointF>
#include <memory>

class IMemento : public QObject
{
    Q_OBJECT

    using transformMatrix = std::vector<std::vector<double>>;

public:
    transformMatrix matrix;
    explicit IMemento(transformMatrix inputMatrix);

signals:

};

#endif // IMEMENTO_H
