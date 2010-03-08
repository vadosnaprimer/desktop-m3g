#ifndef __PARSE_OBJECT3D__
#define __PARSE_OBJECT3D__

#include <strstream>
#include <iostream>
#include <vector>
#include "../Object3D.hpp"

void parse_Object3D (std::istrstream& iss, std::vector<m3g::Object3D*>& objs, m3g::Object3D* obj);


#endif
