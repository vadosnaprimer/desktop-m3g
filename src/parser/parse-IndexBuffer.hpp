
#ifndef __PARSE_INDEX_BUFFER_HPP__
#define __PARSE_INDEX_BUFFER_HPP__

#include <strstream>
#include <iostream>
#include <vector>
#include "../IndexBuffer.hpp"

void parse_IndexBuffer (std::istrstream& iss, std::vector<m3g::Object3D*>& objs, m3g::IndexBuffer* ibuf);

#endif



