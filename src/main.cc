# include <iostream>
# include <fstream>
# include <sstream>
# include <string>

# include "scene.hh"
# include "sphere.hh"
# include "material.hh"
# include "point_light.hh"
# include "renderer.hh"
# include "image2Dwriter.hh"
# include "background.hh"

# define FOV (M_PI / 4)
# define RATIO (640.0 / 480.0)
# define H 480
# define W 640
# define DEEP 20

using namespace std;

Vector3 getDir(Point2 p, Vector3& orig)
{
  Vector3 dir = Vector3(((2.0 * p[0] / W) - 1.0) * tan(FOV / 2.0) * RATIO,
                        ((2.0 * (H - p[1]) / H) - 1.0) * tan(FOV / 2.0),
                        -1.0);
  dir = dir - orig;
  Real n = dir.norm();
  return dir / n;
}

int main()
{
  // Creates a 3D scene
  Scene scene;
  
  // Light at infinity
  Light* light0 = new PointLight(Point4(10, 6, -12, 1), Color(1.0, 1.0, 1.0));

  Light* light1 = new PointLight(Point4(7, 5, -30, 1), Color(1.0, 1.0, 1.0));

  scene.addLight(light0);
  //scene.addLight(light1);

  // Objects
  Sphere* sphere1 = new Sphere(Point3(-5, 6, -30), 4.0, Material::bronze());
  Sphere* sphere2 = new Sphere(Point3(0, 4, -20), 2.0, Material::emerald());
  Sphere* sphere3 = new Sphere(Point3(0, 4, -20), 1.999, Material::glass2());

//  scene.addObject(sphere1);
  scene.addObject(sphere2);
//  scene.addObject(sphere3);

  // Rendering
  Renderer renderer(scene);
  Background* back = new MyBackground();
  renderer.setBackground(back);
  Vector3 orig(0, 0, -0/*.5*/);
  // FOV
  Vector3 dirUL = getDir(Point2(0.0, 0.0), orig);
  Vector3 dirUR = getDir(Point2(W  , 0.0), orig);
  Vector3 dirLL = getDir(Point2(0.0,   H), orig);
  Vector3 dirLR = getDir(Point2(W  ,   H), orig);

  std::cout << dirUL << "\n";
  std::cout << dirUR << "\n";
  std::cout << dirLL << "\n";
  std::cout << dirLR << "\n";

  renderer.setViewBox(orig, dirUL, dirUR, dirLL, dirLR);

  Image2D<Color> image(W, H);
  renderer.setResolution(image.w(), image.h());
  renderer.render(image, DEEP);
  ofstream output("output.ppm");
  Image2DWriter<Color>::write(image, output, true);
  output.close();

  return 0;
}
