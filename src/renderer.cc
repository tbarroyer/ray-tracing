# include "renderer.hh"


void Renderer::render(Image2D<Color>& image, int max_depth)
{
  std::cout << "Rendering into image ... might take a while." << std::endl;
  image = Image2D<Color>(myWidth, myHeight);
  for (int y = 0; y < myHeight; ++y)
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

Color Renderer::illumination(const Ray& /*ray*/, Object* obj, Point3 p)
{
  Material m = obj->getMaterial(p);
  Color c(0.0, 0.0, 0.0);
  for (Light* light : ptrScene->myLights)
  {
    // Apply diffusion
    Vector3 dir = light->direction(p);
    Vector3 N = obj->getNormal(p);
    Real kd = dir.dot(N);
    c = c + (m.diffuse * kd * light->color(p)).clamp();
    c = c.clamp();

    // TODO Apply specular
    Vector3 W = Vector3(0.0, 0.0, 0.0) - N;

    Real b = dir.dot(W);
    if (b > 0.0)
      continue;

    c += (pow(b, m.shinyness) * m.specular * light->color(p)).clamp();
    c = c.clamp();
  }
  c = c + m.ambient;
  return c.clamp();
}

Color Renderer::background(const Ray& ray)
{
  Color result = Color( 0.0, 0.0, 0.0 );
  for (Light* light : ptrScene->myLights)
  {
    Real cos_a = light->direction(ray.origin).dot(ray.direction);
    if (cos_a > 0.99f)
    {
      Real a = acos(cos_a) * 360.0 / M_PI / 8.0;
      a = std::max(1.0f - a, 0.0f);
      result += light->color(ray.origin) * a * a;
    }
  }
  if (ptrBack != 0) result += ptrBack->backgroundColor(ray);
  return result;
}

Ray refractionRay(const Ray& ray, const Point3& p, Vector3 N, const Material& m, bool& has)
{
  Real io = ray.direction.dot(N);
  if (io > 1)
    io = 1;
  else if (io < -1)
    io = -1;

  Real in = m.out_refractive_index;
  Real out = m.in_refractive_index;

  std::cout << " " << p << " ";

  if (io < 0)
  {
    std::cout << " IN ";
    io = -io;
  }
  else
  {
    std::cout << " OUT ";
    N = Vector3(0.0, 0.0, 0.0) - N;
    std::swap(in, out);
  }
  Real eta = in / out;

  Real k = 1 - eta * eta * (1 - io * io);
  /*if (k < 0)
  {
    std::cout << k << " NO REF\n";
    has = false;
    Vector3 out_ = Vector3(0.0, 0.0, 0.0);
    return Ray(p, out_, 0);
  }*/

  Vector3 out_ = eta * ray.direction + (eta * io - sqrtf(k)) * N;

  return Ray(p, out_, ray.depth - 1);
}

Color Renderer::trace(const Ray& ray)
{
  assert(ptrScene != 0);
  Object* obj_i = 0;
  Point3 p_i;

  Real ri = ptrScene->rayIntersection(ray, obj_i, p_i);

  if (ri >= 0.0f)
    return background(ray);

  Material m = obj_i->getMaterial(p_i);
  Color out = illumination(ray, obj_i, p_i) * m.coef_diffusion;
  out.clamp();

  if (m.coef_reflexion != 0 && ray.depth > 0)
  {
    Vector3 N = obj_i->getNormal(p_i);
    N = ray.direction - 2 * ray.direction.dot(N) * N;
    Ray n_ray = Ray(p_i, N, ray.depth - 1);
    Color n_c = trace(n_ray);
    out += n_c * m.coef_reflexion * m.specular;
    out.clamp();
  }

  if (m.coef_refraction != 0 && ray.depth > 0)
  {
    bool has = true;
    Ray n_ray = refractionRay(ray, p_i, obj_i->getNormal(p_i), m, has);
    if (has)
    {
      Color n_c = trace(n_ray);
  //    std::cout << "(" << n_c[0] << " " << n_c[1] << " " << n_c[2] << ") ";
      out += n_c * m.coef_refraction;
      out.clamp();
    }
    else
    {
      //out = Color(1.0, 0.0, 0.0);
      out.clamp();
    }
  }
  
  if (ray.depth == 2)
    std::cout << "(" << out[0] << " " << out[1] << " " << out[2] << ")" << "\n";

  return out;
}
