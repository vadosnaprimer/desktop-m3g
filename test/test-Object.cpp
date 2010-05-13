#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Object.hpp"
using namespace std;
using namespace m3g;

TEST (Object_defautlt_variables)
{
    Object* obj = new Object;

    CHECK_EQUAL ((void*)0, obj->getExportedEntity());
}

TEST (Object_set_variables)
{
    Object* obj = new Object;
    obj->setExportedEntity((void*)0x12345678);

    CHECK_EQUAL ((void*)0x12345678, obj->getExportedEntity());

}

