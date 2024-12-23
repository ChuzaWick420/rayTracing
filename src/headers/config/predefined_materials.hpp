#ifndef PREDEFINED_MATERIALS
#define PREDEFINED_MATERIALS

#include <memory>
#include "../lambertian/lambertian.hpp"
#include "../dielectric/dielectric.hpp"
#include "../metal/metal.hpp"

struct Predefined_Materials {
    static std::shared_ptr<Lambertian> Lam_sptr_Lam_material;
    static std::shared_ptr<Dielectric> Di_sptr_Di_material;
    static std::shared_ptr<Metal> Met_sptr_Met_material;
};

#endif
