# pragma once

# include "color.hh"
# include "image2D.hh"
# include "ray.hh"

struct Renderer {
  Scene* ptrScene;
  Point3 myOrigin;

  Vector3 myDirUL;
  Vector3 myDirUR;
  Vector3 myDirLL;
  Vector3 myDirLR;

  int myWidth;
  int myHeight;

  Renderer() : ptrScene(0) {}
  Renderer(Scene& scene) : ptrScene(&scene) {}
  void setScene(Scene& aScene) { ptrScene = &aScene; }
  
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


  void render(Image2D<Color>& image, int max_depth)
  {
    std::cout << "Rendering into image ... might take a while." << std::endl;
    image = Image2D<Color>(myWidth, myHeight );
    for (int y = 0; y < myHeight; ++y ) 
    {
      Real    ty   = (Real) y / (Real)(myHeight-1);
      Vector3 dirL = (1.0f - ty) * myDirUL + ty * myDirLL;
      Vector3 dirR = (1.0f - ty) * myDirUR + ty * myDirLR;
      dirL        /= dirL.norm();
      dirR        /= dirR.norm();
      for (int x = 0; x < myWidth; ++x) 
      {
        Real    tx   = (Real) x / (Real)(myWidth-1);
        Vector3 dir  = (1.0f - tx) * dirL + tx * dirR;
        Ray eye_ray  = Ray(myOrigin, dir, max_depth);
        Color result = trace(eye_ray);
        image.at(x, y) = result.clamp();
      }
    }
    std::cout << "Done." << std::endl;
  }

  Color illumination(const Ray& /*ray*/, Object* obj, Point3 p)
  {
    Material m = obj->getMaterial(p);
    Color c(0.0, 0.0, 0.0);
    for (Light* light : ptrScene->myLights)
    {
      Vector3 dir = light->direction(p);
      Vector3 N = obj->getNormal(p);

      dir = dir / dir.norm();
      N = N / N.norm();

      Real kd = dir.dot(N);
      
      c += m.diffuse * kd * light->color(p);
    }
    c = c.clamp();
    return c + m.ambient;
  }

  Color trace(const Ray& ray)
  {
    assert(ptrScene != 0);
    Object* obj_i = 0;
    Point3 p_i;

    Real ri = ptrScene->rayIntersection(ray, obj_i, p_i);

    if (ri >= 0.0f)
      return Color(0.0, 0.0, 0.0);
    return illumination(ray, obj_i, p_i);
  }

};
