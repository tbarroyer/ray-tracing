# include <iostream>
# include <fstream>
# include <sstream>
# include <string>

# include "scene.hh"
# include "perio_plan.hh"
# include "water_plan.hh"
# include "sphere.hh"
# include "lib/material.hh"
# include "point_light.hh"
# include "renderer.hh"
# include "lib/image2Dwriter.hh"
# include "background.hh"

# define FOV (M_PI / 4)
# define RATIO (1280.0 / 720.0)
# define H 720
# define W 1280
# define DEEP 10

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

Scene* get_scene(size_t i) {
  // Creates a 3D scene
  Scene* scene = new Scene();

  // Light at infinity
  Light* light0 = new PointLight(Point4(10, 6, -12, 1), Color(1.0, 1.0, 1.0));

  Light* light1 = new PointLight(Point4(7, 5, -30, 1), Color(1.0, 1.0, 1.0));

  scene->addLight(light0);
  //scene.addLight(light1);

  // Objects
  Sphere* sphere1 = new Sphere(Point3(-5. + 0.1 * i, -1 - cos(i * 0.02), -15), 1.0, Material::bronze());
  Sphere* sphere2 = new Sphere(Point3(0. - 0.05 * i, -1 + sin(i * 0.01), -5), 2.0, Material::glass3());
  Sphere* sphere3 = new Sphere(Point3(0, -1 + i * 0.04, -5), 1.999, Material::glass2());
  Sphere* sphere4 = new Sphere(Point3(-3, 2, -10), 1, Material::emerald());

  Sphere* sphere5 = new Sphere(Point3(3, 2, -10), 1.4, Material::mirror());

  WaterPlane* plan = new WaterPlane(Point3(1, -1, 1), Vector3(0, 5, 0), .3 * i);


  PerioPlane* planun = new PerioPlane(Point3(1, -6, 1), Vector3(0, 5, 0),
      //Material::whitePlastic(), Material::blackPlastic(), 0.1f);
      Material::whitePlastic(), Material::blackPlastic(), 0.1f);

  scene->addObject(sphere1);
  scene->addObject(sphere2);
  scene->addObject(sphere3);
  scene->addObject(sphere4);
  scene->addObject(sphere5);

  scene->addObject(plan);
  scene->addObject(planun);

  return scene;
}

int main()
{
  for (size_t i = 0; i < 25 * 5; ++i) {
    Scene* s = get_scene(i);
    Scene& scene = *s;

    // Rendering
    Renderer renderer(scene);
    Background* back = new MyBackground();
    renderer.setBackground(back);
    Vector3 orig(0, 0, 0.);
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
    std::string n = std::to_string(i);
    std::string filename = "video/" + std::string(4 - n.length(), '0') + n + ".ppm";
    ofstream output(filename);
    Image2DWriter<Color>::write(image, output, true);
    output.close();
    delete s;
  }
  return 0;
}
