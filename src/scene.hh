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

  Scene() {}

  ~Scene() 
  {
    for (Light* light : myLights)
      delete light;
    for (Object* obj : myObjects)
      delete obj;
  }

  void addObject(Object* anObject)
  {
    myObjects.push_back(anObject);
  }

  void addLight(Light* aLight)
  {
    myLights.push_back(aLight);
  }
  
  Real rayIntersection(const Ray& ray, Object*& object, Point3& p);

private:
  Scene(const Scene&) = delete;
  Scene& operator=( const Scene& ) = delete;
};
