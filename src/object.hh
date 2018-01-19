# pragma once

# include "lib/point_vector.hh"
# include "lib/material.hh"
# include "lib/ray.hh"

struct Object {

  Object() {}

  virtual ~Object() {}

  virtual Vector3 getNormal(Point3 p) = 0;

  virtual Material getMaterial(Point3 p) = 0;

  virtual Real rayIntersection(const Ray& ray, Real& p) = 0;

};
