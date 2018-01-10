# pragma once

# include "point_vector.hh"
# include "material.hh"
# include "ray.hh"

struct Object {

  Object() {}

  virtual ~Object() {}

  virtual Vector3 getNormal(Point3 p) = 0;

  virtual Material getMaterial(Point3 p) = 0;

  virtual Real rayIntersection(const Ray& ray, Real& p) = 0;

};
