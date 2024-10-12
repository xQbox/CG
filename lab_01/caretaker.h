#ifndef CARETAKER_H
#define CARETAKER_H

#include <QObject>
#include <QMessageBox>
#include <memory>
#include <stack>
#include "imemento.h"
class IMemento;
class ISaveable;

class Caretaker : public QObject
{
    Q_OBJECT
    std::stack<std::pair<std::unique_ptr<IMemento>, ISaveable *>> mementos;

private:
    Caretaker();
public:
    static Caretaker &get();

public:
    void store(std::unique_ptr<IMemento> memento, ISaveable *saveObject);
    void restore();
signals:

};

#endif // CARETAKER_H
