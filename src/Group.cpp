#include "Group.hpp"
#include <iostream>
#include <algorithm>
#include "RayIntersection.hpp"
#include "Sprite3D.hpp"
#include "Exception.hpp"
using namespace m3g;
using namespace std;


Group:: Group ()
{
  setObjectType (OBJTYPE_GROUP);
}

Group:: ~Group ()
{
}

Group* Group:: duplicate () const
{
  Group* grp  = new Group (*this);
  Node*  node = Node::duplicate();
  *(Node*)grp = *node;
  delete node;

  for (int i = 0; i < (int)children.size(); i++) {
    grp->children[i] = this->children[i]->duplicate();
    grp->children[i]->setParent (grp);
  }
  return grp;
}


void Group:: addChild (Node* child)
{
  if (child == NULL) {
    throw NullPointException (__FILE__, __func__, "Child is NULL.");
  }
  if (child == this || child->getObjectType() == OBJTYPE_WORLD) {
    throw IllegalArgumentException (__FILE__, __func__, "Object type of node is invalid, type=%d.", child->getObjectType());
  }
  if (child->getParent() != NULL && child->getParent() != this) {
    throw IllegalArgumentException (__FILE__, __func__, "Added child is already a member of other group.");
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
    throw IllegalArgumentException (__FILE__, __func__, "Chldren index is invalid, index=%d.", index);
  }

  return children[index];
}

int Group:: getChildCount () const
{
  return children.size();
}

bool Group:: pick (int scope, float ox, float oy, float oz, float dx, float dy, float dz, RayIntersection* ri) const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, pick is not implemented.");
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

  // SkinnedMeshの場合特殊な処理が必要。
  // 仕様書を見よ。
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

  for (int i = 0; i < (int)children.size(); i++) {
    glPushMatrix ();
    children[i]->render (pass, index);
    glPopMatrix ();
  }

#if 0  
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
#endif

}
  


std::ostream& Group:: print (std::ostream& out) const
{
  out << "Group: " << children.size() << " nodes\n";
  //for (int i = 0; i < (int)children.size(); i++) {
  //  out << "  [" << i << "] : ";
  //  children[i]->print(out);
  //}
  return out;
}

std::ostream& operator<< (std::ostream& out, const Group& grp)
{
  return grp.print (out);
}


