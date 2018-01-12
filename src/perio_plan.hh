# include "object.hh"

struct PerioPlane : public Object
{
  PerioPlane(Point3 c, Vector3 n,
                Material main_m, Material band_m, Real w)
    : Object(), center(c), N(n), m_main(main_m), m_band(band_m), width(w)
  {}

  virtual ~PerioPlane() {}

public:
  Vector3 getNormal(Point3 p);
  Material getMaterial(Point3 p);
  Real rayIntersection(const Ray& ray, Real& t);

private:
  Point3 center;
  Vector3 N;
  Material m_main;
  Material m_band;
  Real width;
};
