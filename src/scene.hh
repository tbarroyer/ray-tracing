# pragma once

# include <cassert>
# include <vector>
# include <iostream>
# include <limits>

# include "object.hh"
# include "light.hh"

struct Scene {
  std::vector<Light*> myLights;
  std::vector<Object*> myObjects;

  /// Default constructor. Nothing to do.
  Scene() {}

  /// Destructor. Frees objects.
  ~Scene() 
  {
    for (Light* light : myLights)
      delete light;
    for (Object* obj : myObjects)
      delete obj;
  }

  /// Adds a new object to the scene.
  void addObject(Object* anObject)
  {
    myObjects.push_back(anObject);
  }

  /// Adds a new light to the scene.
  void addLight(Light* aLight)
  {
    myLights.push_back(aLight);
  }
  
  /// returns the closest object intersected by the given ray.
  Real rayIntersection(const Ray& ray, Object*& object, Point3& p)
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

private:
  Scene(const Scene&) = delete;
  Scene& operator=( const Scene& ) = delete;
};
