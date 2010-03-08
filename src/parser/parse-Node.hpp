#ifndef __PARSE_NODE_HPP__
#define __PARSE_NODE_HPP__


#include <strstream>
#include <iostream>
#include <vector>
#include "../Node.hpp"

void parse_Node (std::istrstream& iss, std::vector<m3g::Object3D*>& objs, m3g::Node* obj);

#endif
