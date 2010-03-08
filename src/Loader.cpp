#include <iostream>
#include "Loader.hpp"
#include "Object3D.hpp"
//#include "parser/Parser.hpp"
using namespace std;
using namespace m3g;

/**
 * コンストラクタ.
 */
Loader:: Loader ()
{
}

/**
 * デストラクタ.
 */
Loader:: ~Loader ()
{
}


std::vector<Object3D*> Loader:: load (void* data, int offset)
{
    vector<Object3D*> objs;
    return objs;
}

std::vector<Object3D*> Loader:: load (const char* name)
{
  /*
    M3GParser parser(name);
    
    return parser.parse();
  */
  std::vector<Object3D*> objs;
  return objs;
}

std::ostream& operator<< (std::ostream& out, const Loader& p)
{
    return out;
}
