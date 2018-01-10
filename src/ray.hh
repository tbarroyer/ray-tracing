# pragma once

# include "point_vector.hh"

struct Ray {
  Point3 origin;
  Vector3 direction;
  int depth;
  
  Ray() {}
  
  Ray(const Point3& o, const Vector3& dir, int d = 1)
    : origin(o), direction(dir), depth(d)
  {
    Real l = direction.norm();
    if (l != 1.0f)
        direction /= l;
  }
};
