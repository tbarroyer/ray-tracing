# pragma once

# include "color.hh"

struct Material {
  Color ambient;
  Color diffuse;
  Color specular;
  Real shinyness;

  Real coef_diffusion;
  Real coef_reflexion;
  Real coef_refraction;
  Real in_refractive_index;
  Real out_refractive_index;

  /// Mixes two material (t=0 gives m1, t=1 gives m2, t=0.5 gives their average)
  static Material mix( Real t, const Material& m1, const Material& m2 )
  {
    Material m;
    Real s = 1.0f - t;
    m.ambient = s * m1.ambient + t * m2.ambient;
    m.diffuse = s * m1.diffuse + t * m2.diffuse;
    m.specular = s * m1.specular + t * m2.specular;
    m.shinyness = s * m1.shinyness + t * m2.shinyness;
    m.coef_diffusion = s * m1.coef_diffusion + t * m2.coef_diffusion;
    m.coef_reflexion = s * m1.coef_reflexion + t * m2.coef_reflexion;
    m.coef_refraction = s * m1.coef_refraction + t * m2.coef_refraction;
    m.in_refractive_index = s * m1.in_refractive_index + t * m2.in_refractive_index;
    m.out_refractive_index = s * m1.out_refractive_index + t * m2.out_refractive_index;
    return m;
  }

  /// Default constructor
  Material() {}

  /// Constructor from colors and shinyness.
  Material( Color amb, Color diff, Color spec, Real shiny = 0.0f,
      Real cdiff = 1.0f, Real crefl = 0.0f, Real crefr = 0.0f,
      Real in_ridx = 1.0f, Real out_ridx = 1.0f )
    : ambient( amb ), diffuse( diff ), specular( spec ), shinyness( shiny ),
    coef_diffusion( cdiff ), coef_reflexion( crefl ), coef_refraction( crefr ),
    in_refractive_index( in_ridx ), out_refractive_index( out_ridx )
  {}

  static Material whitePlastic() 
  {
    Material m;
    m.ambient   = Color( 0.1, 0.1, 0.1 );
    m.diffuse   = Color( 0.7, 0.7, 0.7 );
    m.specular  = Color( 1.0, 1.0, 0.98 );
    m.shinyness = 5.0;
    m.coef_diffusion  = 0.98f;
    m.coef_reflexion  = 0.02f;
    m.coef_refraction = 0.0f;
    m.in_refractive_index  = 1.0f;
    m.out_refractive_index = 1.0f;
    return m;
  }

  static Material blackPlastic() 
  {
    Material m;
    m.ambient   = Color( 0.0, 0.0, 0.0 );
    m.diffuse   = Color( 0.05, 0.05, 0.05 );
    m.specular  = Color( .08, .08, 0.8 );
    m.shinyness = 5.0;
    m.coef_diffusion  = 0.98f;
    m.coef_reflexion  = 0.02f;
    m.coef_refraction = 0.0f;
    m.in_refractive_index  = 1.0f;
    m.out_refractive_index = 1.0f;
    return m;
  }

  static Material redPlastic() 
  {
    Material m;
    m.ambient   = Color( 0.1, 0.0, 0.0 );
    m.diffuse   = Color( 0.85, 0.05, 0.05 );
    m.specular  = Color( 1.0, 0.8, 0.8 );
    m.shinyness = 5.0;
    m.coef_diffusion  = 1.0f;
    m.coef_reflexion  = 0.05f;
    m.coef_refraction = 0.0f;
    m.in_refractive_index  = 1.0f;
    m.out_refractive_index = 1.0f;
    return m;
  }
  static Material bronze() 
  {
    Material m;
    m.ambient   = Color( 0.1125, 0.0675, 0.054 );
    m.diffuse   = Color( 0.714, 0.4284, 0.18144 );
    m.specular  = Color( 0.9, 0.8, 0.7 );
    // m.specular  = Color( 0.393548, 0.271906, 0.166721 );
    m.shinyness = 56; // 25.6;
    m.coef_diffusion  = 0.5f;
    m.coef_reflexion  = 0.5f;
    m.coef_refraction = 0.0f;
    m.in_refractive_index  = 1.0f;
    m.out_refractive_index = 1.0f;
    return m;
  }
  static Material emerald() 
  {
    Material m;
    m.ambient   = Color( 0.0115, 0.0745, 0.0215 );
    m.diffuse   = Color( 0.09568, 0.77424, 0.10 );
    m.specular  = Color( 0.9, 1.0, 0.9 ); // Color( 0.633, 0.727811, 0.633 );
    m.shinyness = 56;//0.6*128.0;
    m.coef_diffusion  = 0.15f;
    m.coef_reflexion  = 0.2f;
    m.coef_refraction = 0.65f;
    m.in_refractive_index  = 1.5f;
    m.out_refractive_index = 1.0f;
    return m;
  }
  static Material glass() 
  {
    Material m;
    m.ambient   = Color( 0.0, 0.0, 0.0 );
    m.diffuse   = Color( 0.95, 0.95, 1.0 );
    m.specular  = Color( 1.0, 1.0, 1.0 );
    m.shinyness = 80.0f;
    m.coef_diffusion  = 0.01f;
    m.coef_reflexion  = 0.05f;
    m.coef_refraction = 0.94f;
    m.in_refractive_index  = 1.5f;
    m.out_refractive_index = 1.0f;
    return m;
  }
  static Material glass2() 
  {
    Material m;
    m.ambient   = Color( 0.0, 0.0, 0.0 );
    m.diffuse   = Color( 0.95, 0.95, 1.0 );
    m.specular  = Color( 1.0, 1.0, 1.0 );
    m.shinyness = 80.0f;
    m.coef_diffusion  = 0.01f;
    m.coef_reflexion  = 0.02f;
    m.coef_refraction = 0.97f;
    m.in_refractive_index  = 1.0f;
    m.out_refractive_index = 1.1f;
    return m;
  }

  static Material glass3() 
  {
    Material m;
    m.ambient   = Color( 0.0, 0.0, 0.0 );
    m.diffuse   = Color( 0.95, 0.95, 1.0 );
    m.specular  = Color( 1.0, 1.0, 1.0 );
    m.shinyness = 80.0f;
    m.coef_diffusion  = 0.01f;
    m.coef_reflexion  = 0.02f;
    m.coef_refraction = 0.97f;
    m.in_refractive_index  = 1.1f;
    m.out_refractive_index = 1.0f;
    return m;
  }

  static Material mirror() 
  {
    Material m;
    m.ambient   = Color( 0.0, 0.0, 0.0 );
    m.diffuse   = Color( 0.95, 0.95, 1.0 );
    m.specular  = Color( 1.0, 1.0, 1.0 );
    m.shinyness = 80.0f;
    m.coef_diffusion  = 0.02f;
    m.coef_reflexion  = 0.98f;
    m.coef_refraction = 0.00f;
    m.in_refractive_index  = 1.1f;
    m.out_refractive_index = 1.0f;
    return m;
  }

  static Material blueWater()
  {
    Material m;
    m.ambient   = Color( 0.1, 0.1, 0.2 );
    m.diffuse   = Color( 0.1, 0.6, 0.8 );
    m.specular  = Color( 1.0, 1.0, 1.0 );
    m.shinyness = 70.0f;
    m.coef_diffusion  = 0.01f;
    m.coef_reflexion  = 0.1f;
    m.coef_refraction = 0.9f;
    m.in_refractive_index  = .97f;
    m.out_refractive_index = 1.0f;
    return m;
  }

};
