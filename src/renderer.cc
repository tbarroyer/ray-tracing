# include "renderer.hh"

# define ANTI 5.0

Real randf(Real l, Real h)
{
  if (l > h)
    std::swap(l, h);

  Real ajd = (h - l) / 4.0;

  h -= ajd;
  l += ajd;

  return l + static_cast<Real>(rand()) / (static_cast<Real>(RAND_MAX/(h-l)));
}

void Renderer::render(Image2D<Color>& image, int max_depth)
{
  std::cout << "Rendering into image ... might take a while." << std::endl;
  image = Image2D<Color>(myWidth, myHeight);

  #pragma omp parallel for schedule(dynamic)
  for (int y = 1; y < myHeight - 1; ++y)
  {
    Real    ty   = (Real) y / (Real)(myHeight-1);
    Vector3 dirL = (1.0f - ty) * myDirUL + ty * myDirLL;
    Vector3 dirR = (1.0f - ty) * myDirUR + ty * myDirLR;
    dirL        /= dirL.norm();
    dirR        /= dirR.norm();

    Real    tym   = (Real) (y-1) / (Real)(myHeight-1);
    Vector3 dirLm = (1.0f - tym) * myDirUL + tym * myDirLL;
    Vector3 dirRm = (1.0f - tym) * myDirUR + tym * myDirLR;
    dirLm        /= dirLm.norm();
    dirRm        /= dirRm.norm();

    Real    typ   = (Real) (y+1) / (Real)(myHeight-1);
    Vector3 dirLp = (1.0f - typ) * myDirUL + typ * myDirLL;
    Vector3 dirRp = (1.0f - typ) * myDirUR + typ * myDirLR;
    dirLp        /= dirLp.norm();
    dirRp        /= dirRp.norm();

    for (int x = 1; x < myWidth - 1; ++x) 
    {
      Real    tx   = (Real) x / (Real)(myWidth-1);
      Real    txm   = (Real) (x - 1) / (Real)(myWidth-1);
      Real    txp   = (Real) (x + 1) / (Real)(myWidth-1);

      Color avg(0, 0, 0);
      // ANTI ALIASING
      for (int j = 0; j < int(ANTI); ++j)
      {
//        Vector3 dir  = (1.0f - tx) * dirL + tx * dirR;
        Vector3 dirm  = (1.0f - txm) * dirLm + txm * dirRm;
        Vector3 dirp  = (1.0f - txp) * dirLp + txp * dirRp;

        Vector3 dir = Vector3(randf(dirm[0], dirp[0]), randf(dirm[1], dirp[1]), randf(dirm[2], dirp[2]));

//        std::cout << dir << " " << dirp << " " << dirm << "\n";

        Ray eye_ray  = Ray(myOrigin, dir, max_depth);
        Color result = trace(eye_ray);
        avg += result;
      }
      avg = avg * (1 / ANTI);
      image.at(x, y) = avg.clamp();
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

  if (io < 0)
    io = -io;
  else
  {
    N = Vector3(0.0, 0.0, 0.0) - N;
    std::swap(in, out);
  }
  Real eta = in / out;

  Real k = 1 - eta * eta * (1 - io * io);
  if (k < 0)
  {
    has = false;
    Vector3 out_ = Vector3(0.0, 0.0, 0.0);
    return Ray(p, out_, 0);
  }

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
      out += n_c * m.coef_refraction;
      out.clamp();
    }
    else
    {
      out += background(ray) * m.coef_refraction;
      out.clamp();
    }
  }
  
  return out;
}
