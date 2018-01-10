# include <cmath>
# include "sphere.hh"

Vector3 Sphere::getNormal(Point3 p)
{
  Vector3 u = p - center;
  Real   l2 = u.dot( u );
  if ( l2 != 0.0 )
    u /= sqrt(l2);
  return u;
}

Material Sphere::getMaterial(Point3 /* p */)
{
  return material;
}

Real Sphere::rayIntersection(const Ray& ray, Real& p)
{
  Vector3 L = center - ray.origin;

  Real tca = L.dot(ray.direction);
  if (tca < 0)
    return 100.0;

  Real d2 = L.dot(L) - tca * tca;
  if (d2 > radius * radius)
    return 100.0;

  Real thc = sqrt(radius * radius - d2);

  Real t0 = tca - thc;
  Real t1 = tca + thc;

  if (t0 > t1)
    std::swap(t0, t1);

  if (t0 < 0) {
    t0 = t1;
    if (t0 < 0)
        return 100.0;
  }

  p = t0;
  return -100.0;
}
