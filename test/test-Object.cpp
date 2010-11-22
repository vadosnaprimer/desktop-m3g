#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/Object.hpp"
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

static void* ptr = 0;
static void func (void* p)
{
    ptr = p;
}

TEST (Object_mark)
{
    void* entity = (void*)0x12345678;
    Object* obj = new Object;
    obj->setExportedEntity (entity);
    obj->mark (func);
    
    CHECK_EQUAL (entity, ptr);
}
