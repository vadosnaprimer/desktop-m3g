
#ifndef __PROPERTY_HPP__
#define __PROPERTY_HPP__

#include <iosfwd>


namespace m3g {

  /**
   *
   */
class Property
{
public:
  Property (const char* name, int value);
  ~Property ();

  const char* name () const;
  int value () const;

  std::ostream& print (std::ostream& out) const;

  const char* property_name;
  int         property_value;
};


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Property& prop);

#endif
