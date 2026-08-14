#ifndef HITTABLE_H
#define HITTABLE_H

#include "main.h"

class hit_record {
    public:
        point3 p;
        vec3 normal;
        double t;
        bool front_face;

        // Set the hit record normal vector
        void set_face_normal(const ray& r, const vec3& outward_normal) {
            // Assume outward_normal unit length
            // positive (same direction) = false
            // negative (diff direction) = true
            front_face = dot(r.direction(), outward_normal) < 0;
            // if ray inside sphere, norm is with vector so negative
            // if ray outside sphere, norm against vector 
            // norm always pointing outward
            normal = front_face ? outward_normal : -outward_normal;
        }
};

class hittable {
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;

};

#endif