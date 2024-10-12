#ifndef ISAVEABLE_H
#define ISAVEABLE_H
#include <memory>

class IMemento;

class ISaveable
{
public:
    virtual void save() = 0;
    virtual void restore(std::unique_ptr<IMemento> memento) = 0;
};

#endif // ISAVEABLE_H
