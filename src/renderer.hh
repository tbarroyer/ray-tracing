# pragma once

# include "lib/color.hh"
# include "lib/image2D.hh"
# include "lib/ray.hh"
# include "scene.hh"
# include "background.hh"

struct Renderer {
//  std::vector<Light*> myLights;
//  std::vector<Object*> myObjects;

  Scene* ptrScene;
  Background* ptrBack;

  Point3 myOrigin;

  Vector3 myDirUL;
  Vector3 myDirUR;
  Vector3 myDirLL;
  Vector3 myDirLR;

  int myWidth;
  int myHeight;

  Renderer() : ptrScene(0) {}
  Renderer(Scene& scene) : ptrScene(&scene) {}
  ~Renderer()
  {
    delete ptrBack;

    /*for (Light* light : myLights)
      delete light;
    for (Object* obj : myObjects)
      delete obj;*/
  }

  void setScene(Scene& aScene) { ptrScene = &aScene; }
  
  void setBackground(Background* aBack) { ptrBack = aBack; }

  Color background(const Ray& ray);
  
  void setViewBox(Point3 origin, 
                  Vector3 dirUL, Vector3 dirUR, Vector3 dirLL, Vector3 dirLR)
  {
    myOrigin = origin;
    myDirUL = dirUL;
    myDirUR = dirUR;
    myDirLL = dirLL;
    myDirLR = dirLR;
  }

  void setResolution(int width, int height)
  {
    myWidth  = width;
    myHeight = height;
  }

  void render(Image2D<Color>& image, int max_depth);

  Color illumination(const Ray& ray, Object* obj, Point3 p);

  Color trace(const Ray& ray);
};
