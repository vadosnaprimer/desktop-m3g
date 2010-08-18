#include "Object.hpp"
#include <iostream>
using namespace m3g;
using namespace std;
#include <typeinfo>

Object:: Object () : exported_entity(0)
{
}

Object:: ~Object ()
{
}

void* Object:: getExportedEntity () const
{
    return exported_entity;
}

void Object:: setExportedEntity (void* entity)
{
    exported_entity = entity;
}

void Object:: mark (void(*func)(void*)) const
{
    if (func == NULL)
        return;

    //cout << "marked " << typeid(*this).name() << ", " << exported_entity << "\n";
    (*func)(exported_entity);
}


std::ostream& Object:: print (std::ostream& out) const
{
    out << "Object: ";
    out << "  exported_entity=" << exported_entity;
    return out;
}

std::ostream& operator<< (std::ostream& out, const m3g::Object& obj)
{
    return obj.print (out);
}


