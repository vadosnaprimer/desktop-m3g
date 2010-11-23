#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
#include <iostream>
using namespace std;


TEST (Material)
{
    int object_type = M3G_TYPE_MATERIAL;
    unsigned int object_index;
    M3GMaterialStruct material;

    material.ambient_color  = 0x12345678;
    material.diffuse_color  = 0x23456789;
    material.emissive_color = 0x34567891;
    material.specular_color = 0x45678912;
    material.shininess      = 3;
    material.vertex_color_tracking_enabled = true;

    M3GWriter* writer = new M3GWriter ("material.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeMaterial   (material);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("material.m3g");
    M3GMaterialStruct material2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readMaterial    (&material2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_MATERIAL, object_type);
    CHECK_EQUAL (1, object_index);

    // diffuse color以外は成分は無い
    CHECK_EQUAL (0x00345678, material2.ambient_color);
    CHECK_EQUAL (0x23456789, material2.diffuse_color);
    CHECK_EQUAL (0x00567891, material2.emissive_color);
    CHECK_EQUAL (0x00678912, material2.specular_color);
    CHECK_EQUAL (3,          material2.shininess);
    CHECK_EQUAL (true,       material2.vertex_color_tracking_enabled);
    
    /*
    cout << hex;
    cout << "amient color   = 0x" << material2.ambient_color  << "\n";
    cout << "diffuse color  = 0x" << material2.diffuse_color  << "\n";
    cout << "emissive color = 0x" << material2.emissive_color << "\n";
    cout << "specular color = 0x" << material2.specular_color << "\n";
    cout << dec;
    cout << "shininess = " << material2.shininess      << "\n";
    cout << "vertex color tracking = " << material2.vertex_color_tracking_enabled << "\n";
    */

    delete reader;
}
