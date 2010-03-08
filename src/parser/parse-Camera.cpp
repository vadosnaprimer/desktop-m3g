#include <strstream>
#include <iostream>
#include <vector>
#include "../Camera.hpp"
#include "../Transform.hpp"
#include "../m3gexcept.hpp"
#include "parse-Node.hpp"
using namespace std;
using namespace m3g;

void parse_Camera (istrstream& iss, vector<Object3D*>& objs)
{
  Camera* cam = new Camera;

  parse_Node (iss, objs, cam);

  unsigned char projection_type;
  iss.read ((char*)&projection_type, 1);
  if (projection_type == Camera::GENERIC) {
    float matrix[16];
    iss.read ((char*)matrix, 64);
    Transform tra;
    tra.set (matrix);
    cam->setGeneric (tra);

  } else if (projection_type == Camera::PARALLEL) {
    float fovy;
    float aspect_ratio;
    float near;
    float far;
    iss.read ((char*)&fovy, 4);
    iss.read ((char*)&aspect_ratio, 4);
    iss.read ((char*)&near, 4);
    iss.read ((char*)&far,  4);
    cam->setParallel (fovy, aspect_ratio, near, far);

  } else if (projection_type == Camera::PERSPECTIVE) {
    float fovy;
    float aspect_ratio;
    float near;
    float far;
    iss.read ((char*)&fovy, 4);
    iss.read ((char*)&aspect_ratio, 4);
    iss.read ((char*)&near, 4);
    iss.read ((char*)&far,  4);
    cam->setPerspective (fovy, aspect_ratio, near, far);
  } else {
    throw domain_error ("Unknown camera type.");
  }

  objs.push_back (cam);


  /*
  cam->print(cout);
  cam->Transformable::print(cout);
  cam->Node::print(cout);
  cam->Object3D::print(cout);
  */

}
