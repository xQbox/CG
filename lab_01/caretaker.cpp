#include "caretaker.h"
#include "isaveable.h"
#include "myscene.h"
#include <QDebug>
Caretaker::Caretaker() : QObject(nullptr)
{

}

Caretaker &Caretaker::get()
{
    static Caretaker obj;
    return obj;
}

void Caretaker::store(std::unique_ptr<IMemento> memento, ISaveable *saveObject)
{
    if (memento && saveObject)
    {
        mementos.push(std::pair<std::unique_ptr<IMemento>, ISaveable *>(std::move(memento), saveObject));
    }

//    mementos.emplace(std::pair<std::unique_ptr<IMemento>, ISaveable *>(std::move(memento), saveObject));
}

void Caretaker::restore()
{
    if (mementos.empty())
    {
        QMessageBox::warning(nullptr, "Внимание!", "Нет сохранений");
        return;
    }

    mementos.top().second->restore(std::move(mementos.top().first));
    mementos.pop();
}
