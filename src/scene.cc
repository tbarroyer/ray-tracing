# include "scene.hh"

Real Scene::rayIntersection(const Ray& ray, Object*& object, Point3& p)
  {
    object = 0;
    Real t = 100.0;
    Real mdist = std::numeric_limits<float>::infinity();

    for (Object* obj : myObjects) {
      Real dist;
      Real in = obj->rayIntersection(ray, dist);
      if (in < 0.0)
      {
        if (dist < mdist)
        {
          t = -100.0;
          object = obj;
          p = ray.origin + ray.direction * dist;
          mdist = dist;
        }
      }
    }
    return t;
  }
