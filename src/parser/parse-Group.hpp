
#ifndef __PARSE_GROUP_HPP__
#define __PARSE_GROUP_HPP__

#include <strstream>
#include <iostream>
#include <vector>
#include "../Group.hpp"

void parse_Group (std::istrstream& iss, std::vector<m3g::Object3D*>& objs, m3g::Group* grp=NULL);

#endif


