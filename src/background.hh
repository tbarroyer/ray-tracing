# pragma once

# include "lib/color.hh"
# include "lib/ray.hh"

struct Background {
  virtual Color backgroundColor( const Ray& ray ) = 0;
};

struct MyBackground : public Background {
  Color backgroundColor(const Ray& ray);
};
