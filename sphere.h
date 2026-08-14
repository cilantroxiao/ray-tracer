#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
    public: 
        sphere(const point3& center, double radius) : center(center), radius(std::fmax(0,radius)) {}

        bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
            // a = d . d
            // b = -2d . (C - Q)
            // c = (C - Q) . (C - Q) - r^2
            vec3 oc = center - r.origin();
            auto d = r.direction();
            auto a = d.length_squared();
            auto h = dot(d, oc);
            auto c = oc.length_squared() - radius*radius;

            auto discriminant = h*h - a*c;

            //if discriminant 
            //        > 0, 2 real solutions (pass through)
            //        < 0, 0 real solutions (miss)
            //        = 0, 1 real solution  (tangent)
            if (discriminant < 0)
                return false;
            
            auto sqrtd = std::sqrt(discriminant);
            
            // nearest root in acceptable range
            auto root = (h - sqrtd) / a;
            if (root <= ray_tmin|| ray_tmax <= root){
                root = (h + sqrtd) / a;
                // no real solution
                if (root <= ray_tmin|| ray_tmax <= root)
                    return false;
            }

            // in range
            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);

            return true;

        }

    private:
        point3 center;
        double radius;
};
#endif