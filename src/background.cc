# include "background.hh"

Color MyBackground::backgroundColor(const Ray& ray)
{
  if (ray.direction[1] <= 0)
//    return Color(1, 1, 1);
    return Color(.6, .6, .8);
  if (ray.direction[1] <= 0.5)
    return Color(1 - ray.direction[1], 1 - ray.direction[1], 1).clamp();
  return Color(0.5, 0.5, 1);
}
