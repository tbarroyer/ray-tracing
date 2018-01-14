# include "water_plan.hh"

# include <iostream>

# define A 0.0
# define R 0.3
# define L 1
# define PHASE 0.0

Real t(Real x, Real y)
{
  return x * cos(A) + y * sin(A);
}

Real f(Real x, Real y, Real a)
{
  return R * cos(2 * 3.14 * t(x, y) / a + PHASE);
}

Vector3 WaterPlane::getNormal(Point3 p)
{
  Vector3 N_ = Vector3(0,0,0) - N;
  N_[0] += f(p[0], 0, 1);
  N_[2] += f(p[2], 0, 1.5);
  return N_ / N_.norm();
}

Material WaterPlane::getMaterial(Point3 p)
{
  return Material::blueWater();
}

Real WaterPlane::rayIntersection(const Ray& ray, Real& t)
{
  Vector3 N_ = Vector3(0,0,0) - N;//getNormal(Point3(0, 0, 0));
  N_ = N_ / N_.norm();
  Real denom = N_.dot(ray.direction);
  if (denom > 1e-6)
  {
    Vector3 P = center - ray.origin;
    t = P.dot(N_) / denom;
//    if (ray.origin[0] != 0)
//      std::cout << ray.origin << " " << t << "\n";
    if (t >= 1e-2)// || t == 0)
    {
//      std::cout << t << "\n";
      return -100.0;
    }
  } 

  return 100.0;
}
