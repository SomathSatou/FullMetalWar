#ifndef MATERIAL_H
#define MATERIAL_H
#include <string>

class Material {
public:
    Material(): m_identifiant(""), m_ambient_r(0), m_ambient_g(0), m_ambient_b(0), m_diffuse_r(0), m_diffuse_g(0), m_diffuse_b(0), m_specular_r(0), m_specular_g(0), m_specular_b(0), m_shininess(0) {}
    Material(const std::string& i, const float ar, const float ag, const float ab, const float dr, const float dg, const float db, const float sr, const float sg, const float sb, const float shiny):
        m_identifiant(i), m_ambient_r(ar), m_ambient_g(ag), m_ambient_b(ab), m_diffuse_r(dr), m_diffuse_g(dg), m_diffuse_b(db), m_specular_r(sr), m_specular_g(sg), m_specular_b(sb), m_shininess(shiny){}

    const std::string& getIdentifiant() const { return m_identifiant; }
    float getAR() const{ return m_ambient_r; }
    float getAG() const{ return m_ambient_g; }
    float getAB() const{ return m_ambient_b; }
    float getDR() const{ return m_diffuse_r; }
    float getDG() const{ return m_diffuse_g; }
    float getDB() const{ return m_diffuse_b; }
    float getSR() const{ return m_specular_r; }
    float getSG() const{ return m_specular_g; }
    float getSB() const{ return m_specular_b; }
    float getShine() const{ return m_shininess; }

private:
    std::string m_identifiant;
    // AMBIENT
    float m_ambient_r;
    float m_ambient_g;
    float m_ambient_b;
    // DIFFUSE
    float m_diffuse_r;
    float m_diffuse_g;
    float m_diffuse_b;
    // SPECULAR
    float m_specular_r;
    float m_specular_g;
    float m_specular_b;
    // SHININESS
    float m_shininess;

};

#endif // MATERIAL_H
