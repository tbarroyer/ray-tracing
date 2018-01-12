# include "object.hh"

struct WaterPlane : public Object
{
  WaterPlane(Point3 c, Vector3 n)
    : Object(), center(c), N(n)
  {}

  virtual ~WaterPlane() {}

public:
  Vector3 getNormal(Point3 p);
  Material getMaterial(Point3 p);
  Real rayIntersection(const Ray& ray, Real& t);

private:
  Point3 center;
  Vector3 N;
};
