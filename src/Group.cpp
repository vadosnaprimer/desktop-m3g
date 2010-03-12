#include "Group.hpp"
#include <iostream>
#include <algorithm>
#include "RayIntersection.hpp"
#include "Sprite3D.hpp"
#include "m3gexcept.hpp"
using namespace m3g;
using namespace std;


Group:: Group ()
{
  setObjectType (OBJTYPE_GROUP);
}

Group:: ~Group ()
{
}

void Group:: addChild (Node* child)
{
  if (child == 0) {
    throw null_point_error ("Added child is NULL.");
  }
  if (child == this || child->getObjectType() == OBJTYPE_WORLD) {
    throw invalid_argument ("Added child is illegal.");
  }
  if (child->getParent() != NULL && child->getParent() != this) {
    throw invalid_argument ("Added child is already a member of other group.");
  }

  child->setParent (this);
  children.push_back (child);
}

int Group:: animate (int world_time)
{
  //cout << "Group: animate, time=" << world_time << "\n";

  Node:: animate (world_time);

  for (int i = 0; i < (int)children.size(); i++) {
    children[i]->animate (world_time);
  }

  return 0;
}

Node* Group:: getChild (int index) const
{
  if (index < 0 || index >= (int)children.size()) {
    throw invalid_argument ("Index is out of bound.");
  }

  return children[index];
}

int Group:: getChildCount () const
{
  return children.size();
}

bool Group:: pick (int scope, float ox, float oy, float oz, float dx, float dy, float dz, RayIntersection* ri) const
{
  throw not_implemented_error ("Sorry, Group:: pick is not implemented.");
  return false;
}

void Group:: removeChild (Node* child)
{
  std::vector<Node*>::iterator it;
  for (it = children.begin(); it < children.end(); it++) {
    if (*it == child) {
      children.erase (it);
      child->setParent (NULL);
      break;
    }
  }
}

void Group:: findByObjectType (int type, std::vector<Object3D*>& objs) const
{
  for (int i = 0; i < (int)children.size(); i++) {
    children[i]->findByObjectType (type, objs);
  }
  if (getObjectType() == type) {
    objs.push_back (const_cast<Group*>(this));
  }
}

/**
 * Note: Group should be rendered via all rendering pass.
 */
void Group:: render (int pass, int index) const
{
  //cout << "Group: render\n";
  Node::render (pass, index);
  
  vector<Sprite3D*> sprts;

  for (int i = 0; i < (int)children.size(); i++) {
    if (children[i]->getObjectType() == OBJTYPE_SPRITE3D) {
      sprts.push_back (dynamic_cast<Sprite3D*>(children[i]));
    }
    else {
      glPushMatrix ();
      children[i]->render (pass, index);
      glPopMatrix ();
    }
  }

  sort (sprts.begin(), sprts.end(), Sprite3D::sort_by_layer);
  for (int i = 0; i < (int)sprts.size(); i++) {
      glPushMatrix ();
      sprts[i]->render (pass, index);
      glPopMatrix ();
  }
}
  


std::ostream& Group:: print (std::ostream& out) const
{
  out << "Group: " << children.size() << " nodes\n";
  for (int i = 0; i < (int)children.size(); i++) {
    out << "  [" << i << "] : ";
    children[i]->print(out);
  }
  return out;
}

std::ostream& operator<< (std::ostream& out, const Group& grp)
{
  return grp.print (out);
}


