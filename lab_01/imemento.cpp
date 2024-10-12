#include "imemento.h"
#include "myscene.h"
IMemento::IMemento(transformMatrix inputMatrix) : matrix(std::move(inputMatrix))
{

}
