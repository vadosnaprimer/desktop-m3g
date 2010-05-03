#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <iosfwd>

namespace m3g {


  /**
   *
   */
class Object
{
public:
  Object ();
  ~Object ();

  /**
   *
   */
    void* getExportedEntity () const;

  /**
   *
   */
    void setExportedEntity (void* exported_entity);

  std::ostream& print (std::ostream& out) const;

private:

  void* exported_entity;
};

}  // using namespace std;

std::ostream& operator<< (std::ostream& out, const m3g::Object& obj);


#endif
