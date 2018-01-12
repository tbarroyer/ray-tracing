# include "perio_plan.hh"

# include <iostream>

Vector3 PerioPlane::getNormal(Point3 p)
{
  return Vector3(0,0,0) - N;
}

Material PerioPlane::getMaterial(Point3 p)
{
//  return m_main;
  if (fabs(p[0]) - int(abs(p[0])) < width || fabs(p[2]) - int(abs(p[2])) < width)
    return m_band;
  return m_main;
}

Real PerioPlane::rayIntersection(const Ray& ray, Real& t)
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
