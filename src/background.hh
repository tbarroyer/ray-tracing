# pragma once

# include "color.hh"
# include "ray.hh"

struct Background {
  virtual Color backgroundColor( const Ray& ray ) = 0;
};

struct MyBackground : public Background {
  Color backgroundColor(const Ray& ray);
};
