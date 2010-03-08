#ifndef __PARSE_TRANSFORMABLE_HPP__
#define __PARSE_TRANSFORMABLE_HPP__

#include <strstream>
#include <iostream>
#include <vector>
#include "../Transformable.hpp"

void parse_Transformable (std::istrstream& iss, std::vector<m3g::Object3D*>& objs, m3g::Transformable* obj);


#endif
