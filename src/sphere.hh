# pragma once

# include "object.hh"

struct Sphere : public Object {
  
  // Virtual destructor since object contains virtual methods.
  virtual ~Sphere() {}

  // Creates a sphere of center \a xc and radius \a r.
  Sphere(Point3 xc, Real r, const Material& m)
    : Object(), center(xc), radius(r), material(m)
  {}

public:
  Vector3 getNormal(Point3 p);

  Material getMaterial(Point3 p);

  Real rayIntersection(const Ray& ray, Real& t);

public:
  Point3 center;
  Real radius;
  Material material;
};
