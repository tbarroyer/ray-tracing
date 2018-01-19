# include "object.hh"

struct WaterPlane : public Object
{
  WaterPlane(Point3 c, Vector3 n, Real phase)
    : Object(), center(c), N(n), phase_(phase)
  {}

  virtual ~WaterPlane() {}

public:
  Vector3 getNormal(Point3 p);
  Material getMaterial(Point3 p);
  Real rayIntersection(const Ray& ray, Real& t);

private:
  Real phase_;
  Point3 center;
  Vector3 N;
};
