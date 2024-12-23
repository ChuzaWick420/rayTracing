#include "./predefined_materials.hpp"

std::shared_ptr<Lambertian> Predefined_Materials::Lam_sptr_Lam_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
std::shared_ptr<Dielectric> Predefined_Materials::Di_sptr_Di_material = std::make_shared<Dielectric>(1.00 / 1.50);
std::shared_ptr<Metal> Predefined_Materials::Met_sptr_Met_material = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
