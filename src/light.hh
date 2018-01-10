# pragma once

# include "point_vector.hh"

struct Light {
  Light() {}

  virtual ~Light() {}
  
  virtual Vector3 direction(const Vector3& p) const = 0;

  virtual Color color(const Vector3& p) const = 0;
};
