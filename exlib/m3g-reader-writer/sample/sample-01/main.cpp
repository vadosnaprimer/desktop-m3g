#include "M3GReader.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;
const char* input_file_name = "simple.m3g";

int main (int argc, char** argv)
{
    cout << "read " << input_file_name << "\n";

    int          object_type;
    unsigned int object_index;
    M3GReader*   reader = new M3GReader(input_file_name);

    // M3G ident
    reader->readID ();

    // Section 1 has Header object only.
    M3GHeaderStruct header;
    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readHeader   (&header);
    reader->endObject    ();
    reader->endSection   ();

    // Section 2 has 12 objects.
    while (reader->startSection ()) {
        while (reader->startObject  (&object_type, &object_index)) {
            cout << "object_type = " << object_type << "\n";
            switch (object_type) {
            case M3G_TYPE_BACKGROUND: {
                M3GObject3DStruct    obj;
                M3GBackgroundStruct  bg;
                reader->readObject3D   (&obj);
                reader->readBackground (&bg);
                break;
            }
            case M3G_TYPE_CAMERA: {
                M3GObject3DStruct      obj;
                M3GTransformableStruct tra;
                M3GNodeStruct          nod;
                M3GCameraStruct        cam;
                reader->readObject3D      (&obj);
                reader->readTransformable (&tra);
                reader->readNode          (&nod);
                reader->readCamera        (&cam);
                break;
            }
            case M3G_TYPE_VERTEX_ARRAY: {
                M3GObject3DStruct     obj;
                M3GVertexArrayStruct  varry;
                reader->readObject3D    (&obj);
                reader->readVertexArray (&varry);
                break;
            }
            case M3G_TYPE_VERTEX_BUFFER: {
                M3GObject3DStruct      obj;
                M3GVertexBufferStruct  vbuf;
                reader->readObject3D     (&obj);
                reader->readVertexBuffer (&vbuf);
                break;
            }
            case M3G_TYPE_TRIANGLE_STRIP_ARRAY: {
                M3GObject3DStruct           obj;
                M3GIndexBufferStruct        ibuf;
                M3GTriangleStripArrayStruct tris;
                reader->readObject3D           (&obj);
                reader->readIndexBuffer        (&ibuf);
                reader->readTriangleStripArray (&tris);
                break;
            }
            case M3G_TYPE_POLYGON_MODE: {
                M3GObject3DStruct     obj;
                M3GPolygonModeStruct  plymd;
                reader->readObject3D     (&obj);
                reader->readPolygonMode  (&plymd);
                break;
            }
            case M3G_TYPE_MATERIAL: {
                M3GObject3DStruct obj;
                M3GMaterialStruct mat;
                reader->readObject3D (&obj);
                reader->readMaterial (&mat);
                break;
            }
            case M3G_TYPE_APPEARANCE: {
                M3GObject3DStruct   obj;
                M3GAppearanceStruct app;
                reader->readObject3D   (&obj);
                reader->readAppearance (&app);
                break;
            }
            case M3G_TYPE_MESH: {
                M3GObject3DStruct      obj;
                M3GTransformableStruct tra;
                M3GNodeStruct          nod;
                M3GMeshStruct          msh;
                reader->readObject3D      (&obj);
                reader->readTransformable (&tra);
                reader->readNode          (&nod);
                reader->readMesh          (&msh);
                break;
            }
            case M3G_TYPE_LIGHT: {
                M3GObject3DStruct      obj;
                M3GTransformableStruct tra;
                M3GNodeStruct          nod;
                M3GLightStruct         lgh;
                reader->readObject3D      (&obj);
                reader->readTransformable (&tra);
                reader->readNode          (&nod);
                reader->readLight         (&lgh);
                break;
            }
            case M3G_TYPE_WORLD: {
                M3GObject3DStruct      obj;
                M3GTransformableStruct tra;
                M3GNodeStruct          nod;
                M3GGroupStruct         grp;
                M3GWorldStruct         wld;
                reader->readObject3D      (&obj);
                reader->readTransformable (&tra);
                reader->readNode          (&nod);
                reader->readGroup         (&grp);
                reader->readWorld         (&wld);
                break;
            }
            default: {
                cout << "Not implemented\n";
                abort ();
            }
            }
            reader->endObject    ();
        }
        reader->endSection   ();
    }

    cout << "all objects was read.\n";
    return 0;
}
