# include "water_plan.hh"

# include <iostream>

Vector3 WaterPlane::getNormal(Point3 p)
{
  return Vector3(0,0,0) - N;
}

Material WaterPlane::getMaterial(Point3 p)
{
  return Material::blueWater();
}

Real WaterPlane::rayIntersection(const Ray& ray, Real& t)
{
  Vector3 N_ = Vector3(0, 0, 0) - N;
  Real denom = N_.dot(ray.direction);
  if (denom > 1e-6)
  {
    Vector3 P = center - ray.origin;
    t = P.dot(N_) / denom;
    if (t >= 1e-4)
      return -100.0;
  } 

  return 100.0;
}
