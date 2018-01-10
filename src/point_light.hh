# pragma once

# include "light.hh"

struct PointLight : public Light {
  Point4 position;
  Color emission;
  Material material;

  PointLight(Point4 pos, 
             Color emission_color,
             Color ambient_color  = Color(0.0, 0.0, 0.0),
             Color diffuse_color  = Color(1.0, 1.0, 1.0),
             Color specular_color = Color(1.0, 1.0, 1.0))
    : position(pos), emission( emission_color),
      material(ambient_color, diffuse_color, specular_color)
  {}
  
  /// Destructor.
  ~PointLight() {}

  Vector3 direction(const Vector3& p) const
  {
    Vector3 pos(position.data());
    if (position[3] == 0.0)
      return pos / pos.norm() ;
    pos /= position[3];
    pos -= p;
    return pos / pos.norm();
  }

  /// @return the color of this light viewed from the given point \a p.
  Color color(const Vector3& /* p */) const
  {
    return emission;
  }
  
};
