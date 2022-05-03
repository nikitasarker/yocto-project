//
// # Yocto/Geometry: Geometry operations
//
// Yocto/Geometry defines basic geometry operations, including computation of
// basic geometry quantities, ray-primitive intersection, point-primitive
// distance, primitive bounds, and several interpolation functions.
// Yocto/Geometry is implemented in `yocto_geometry.h`.
//

//
// LICENSE:
//
// Copyright (c) 2016 -- 2021 Fabio Pellacini
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef _YOCTO_GEOMETRY_H_
#define _YOCTO_GEOMETRY_H_

// -----------------------------------------------------------------------------
// INCLUDES
// -----------------------------------------------------------------------------

#include <utility>

#include "yocto_math.h"

// -----------------------------------------------------------------------------
// USING DIRECTIVES
// -----------------------------------------------------------------------------
namespace yocto {

// using directives
using std::pair;

}  // namespace yocto

// -----------------------------------------------------------------------------
// AXIS ALIGNED BOUNDING BOXES
// -----------------------------------------------------------------------------
namespace yocto {

// Axis aligned bounding box represented as a min/max vector pairs.
struct bbox2f {
  vec2f min = {flt_max, flt_max};
  vec2f max = {flt_min, flt_min};

  vec2f&       operator[](int i);
  const vec2f& operator[](int i) const;
};

// Axis aligned bounding box represented as a min/max vector pairs.
struct bbox3f {
  vec3f min = {flt_max, flt_max, flt_max};
  vec3f max = {flt_min, flt_min, flt_min};

  vec3f&       operator[](int i);
  const vec3f& operator[](int i) const;
};

// Empty bbox constant.
inline const auto invalidb2f = bbox2f{};
inline const auto invalidb3f = bbox3f{};

// Bounding box properties
inline vec2f center(const bbox2f& a);
inline vec2f size(const bbox2f& a);

// Bounding box comparisons.
inline bool operator==(const bbox2f& a, const bbox2f& b);
inline bool operator!=(const bbox2f& a, const bbox2f& b);

// Bounding box expansions with points and other boxes.
inline bbox2f merge(const bbox2f& a, const vec2f& b);
inline bbox2f merge(const bbox2f& a, const bbox2f& b);
inline void   expand(bbox2f& a, const vec2f& b);
inline void   expand(bbox2f& a, const bbox2f& b);

// Bounding box properties
inline vec3f center(const bbox3f& a);
inline vec3f size(const bbox3f& a);

// Bounding box comparisons.
inline bool operator==(const bbox3f& a, const bbox3f& b);
inline bool operator!=(const bbox3f& a, const bbox3f& b);

// Bounding box expansions with points and other boxes.
inline bbox3f merge(const bbox3f& a, const vec3f& b);
inline bbox3f merge(const bbox3f& a, const bbox3f& b);
inline void   expand(bbox3f& a, const vec3f& b);
inline void   expand(bbox3f& a, const bbox3f& b);

}  // namespace yocto

// -----------------------------------------------------------------------------
// RAYS
// -----------------------------------------------------------------------------
namespace yocto {

// Ray epsilon
inline const auto ray_eps = 1e-4f;

struct ray2f {
  vec2f o    = {0, 0};
  vec2f d    = {0, 1};
  float tmin = ray_eps;
  float tmax = flt_max;
};

// Rays with origin, direction and min/max t value.
struct ray3f {
  vec3f o    = {0, 0, 0};
  vec3f d    = {0, 0, 1};
  float tmin = ray_eps;
  float tmax = flt_max;
};

// Computes a point on a ray
inline vec2f ray_point(const ray2f& ray, float t);
inline vec3f ray_point(const ray3f& ray, float t);

}  // namespace yocto

// -----------------------------------------------------------------------------
// CONES
// -----------------------------------------------------------------------------
namespace yocto {

struct cone_data {
  vec3f origin = {0, 0, 0};
  vec3f dir    = {0, 0, 1};
  float spread;

  float tmin = ray_eps;
  float tmax = flt_max;
};

}  // namespace yocto

// -----------------------------------------------------------------------------
// TRANSFORMS
// -----------------------------------------------------------------------------
namespace yocto {

// Transforms rays.
inline ray3f transform_ray(const mat4f& a, const ray3f& b);
inline ray3f transform_ray(const frame3f& a, const ray3f& b);

// Transforms bounding boxes by matrices.
inline bbox3f transform_bbox(const mat4f& a, const bbox3f& b);
inline bbox3f transform_bbox(const frame3f& a, const bbox3f& b);

}  // namespace yocto

// -----------------------------------------------------------------------------
// PRIMITIVE BOUNDS
// -----------------------------------------------------------------------------
namespace yocto {

// Primitive bounds.
inline bbox3f point_bounds(const vec3f& p);
inline bbox3f point_bounds(const vec3f& p, float r);
inline bbox3f line_bounds(const vec3f& p0, const vec3f& p1);
inline bbox3f line_bounds(const vec3f& p0, const vec3f& p1, float r0, float r1);
inline bbox3f triangle_bounds(
    const vec3f& p0, const vec3f& p1, const vec3f& p2);
inline bbox3f quad_bounds(
    const vec3f& p0, const vec3f& p1, const vec3f& p2, const vec3f& p3);
inline bbox3f sphere_bounds(const vec3f& p, float r);
inline bbox3f capsule_bounds(
    const vec3f& p0, const vec3f& p1, float r0, float r1);

}  // namespace yocto

// -----------------------------------------------------------------------------
// GEOMETRY UTILITIES
// -----------------------------------------------------------------------------
namespace yocto {

// Line properties.
inline vec3f line_point(const vec3f& p0, const vec3f& p1, float u);
inline vec3f line_tangent(const vec3f& p0, const vec3f& p1);
inline float line_length(const vec3f& p0, const vec3f& p1);

// Triangle properties.
inline vec3f triangle_point(
    const vec3f& p0, const vec3f& p1, const vec3f& p2, const vec2f& uv);
inline vec3f triangle_normal(const vec3f& p0, const vec3f& p1, const vec3f& p2);
inline float triangle_area(const vec3f& p0, const vec3f& p1, const vec3f& p2);

// Quad properties.
inline vec3f quad_point(
    const vec3f& p0, const vec3f& p1, const vec3f& p2, const vec2f& uv);
inline vec3f quad_normal(
    const vec3f& p0, const vec3f& p1, const vec3f& p2, const vec3f& p3);
inline float quad_area(
    const vec3f& p0, const vec3f& p1, const vec3f& p2, const vec3f& p3);

// Triangle tangent and bitangent from uv
inline pair<vec3f, vec3f> triangle_tangents_fromuv(const vec3f& p0,
    const vec3f& p1, const vec3f& p2, const vec2f& uv0, const vec2f& uv1,
    const vec2f& uv2);

// Quad tangent and bitangent from uv. Note that we pass a current_uv since
// internally we may want to split the quad in two and we need to known where
// to do it. If not interested in the split, just pass zero2f here.
inline pair<vec3f, vec3f> quad_tangents_fromuv(const vec3f& p0, const vec3f& p1,
    const vec3f& p2, const vec3f& p3, const vec2f& uv0, const vec2f& uv1,
    const vec2f& uv2, const vec2f& uv3, const vec2f& current_uv);

// Interpolates values over a line parameterized from a to b by u. Same as lerp.
template <typename T>
inline T interpolate_line(const T& p0, const T& p1, float u);

// Interpolates values over a triangle parameterized by u and v along the
// (p1-p0) and (p2-p0) directions. Same as barycentric interpolation.
template <typename T>
inline T interpolate_triangle(
    const T& p0, const T& p1, const T& p2, const vec2f& uv);

// Interpolates values over a quad parameterized by u and v along the
// (p1-p0) and (p2-p1) directions. Same as bilinear interpolation.
template <typename T>
inline T interpolate_quad(
    const T& p0, const T& p1, const T& p2, const T& p3, const vec2f& uv);

// Interpolates values along a cubic Bezier segment parametrized by u.
template <typename T>
inline T interpolate_bezier(
    const T& p0, const T& p1, const T& p2, const T& p3, float u);

// Computes the derivative of a cubic Bezier segment parametrized by u.
template <typename T>
inline T interpolate_bezier_derivative(
    const T& p0, const T& p1, const T& p2, const T& p3, float u);

// Interpolated line properties.
inline vec3f line_point(const vec3f& p0, const vec3f& p1, float u);
inline vec3f line_tangent(const vec3f& t0, const vec3f& t1, float u);

// Interpolated triangle properties.
inline vec3f triangle_point(
    const vec3f& p0, const vec3f& p1, const vec3f& p2, const vec2f& uv);
inline vec3f triangle_normal(
    const vec3f& n0, const vec3f& n1, const vec3f& n2, const vec2f& uv);

// Interpolated quad properties.
inline vec3f quad_point(const vec3f& p0, const vec3f& p1, const vec3f& p2,
    const vec3f& p3, const vec2f& uv);
inline vec3f quad_normal(const vec3f& n0, const vec3f& n1, const vec3f& n2,
    const vec3f& n3, const vec2f& uv);

}  // namespace yocto

// -----------------------------------------------------------------------------
// USER INTERFACE UTILITIES
// -----------------------------------------------------------------------------
namespace yocto {

// Generate a ray from a camera
inline ray3f camera_ray(
    const frame3f& frame, float lens, const vec2f& film, const vec2f& image_uv);

// Generate a ray from a camera
inline ray3f camera_ray(const frame3f& frame, float lens, float aspect,
    float film, const vec2f& image_uv);

}  // namespace yocto

// -----------------------------------------------------------------------------
// RAY-PRIMITIVE INTERSECTION FUNCTIONS
// -----------------------------------------------------------------------------
namespace yocto {

// Intersect a ray with a point (approximate)
inline bool intersect_point(
    const ray3f& ray, const vec3f& p, float r, vec2f& uv, float& dist);

// Intersect a ray with infinite cylinder
inline bool intersect_infinite_cylinder(const ray3f& ray, const vec3f& p0,
    const vec3f& p1, float radius, vec3f axis, float* inD, float* outD);

// Intersect a ray with cylinder
inline bool intersect_cylinder(const ray3f& ray, const vec3f& p0,
    const vec3f& p1, float r0, float r1, vec2f& uv, float& dist);

// Intersect a ray with a line
inline bool intersect_line(const ray3f& ray, const vec3f& p0, const vec3f& p1,
    float r0, float r1, vec2f& uv, float& dist);

// Intersect a ray with a triangle
inline bool intersect_triangle(const ray3f& ray, const vec3f& p0,
    const vec3f& p1, const vec3f& p2, vec2f& uv, float& dist);

// Intersect a ray with a quad.
inline bool intersect_quad(const ray3f& ray, const vec3f& p0, const vec3f& p1,
    const vec3f& p2, const vec3f& p3, vec2f& uv, float& dist);

// Intersect a ray with a axis-aligned bounding box
inline bool intersect_bbox(const ray3f& ray, const bbox3f& bbox);

// Intersect a ray with a axis-aligned bounding box
inline bool intersect_bbox(
    const ray3f& ray, const vec3f& ray_dinv, const bbox3f& bbox);

}  // namespace yocto

// -----------------------------------------------------------------------------
// CONE-PRIMITIVE INTERSECTION FUNCTIONS
// -----------------------------------------------------------------------------
namespace yocto {

// Intersect a cone with a point (approximate)
inline bool intersect_point(const cone_data& cone, const vec3f& p, float r,
    std::vector<vec2f>& uv, float& dist);

// Intersect a cone with a line (approximate)
inline bool intersect_line(const cone_data& cone, const vec3f& p0,
    const vec3f& p1, float r0, float r1, vec2f& uv, float& dist);

// Intersect a cone with a cylinder (approximate)
inline bool intersect_cylinder(const cone_data& cone, const vec3f& p0,
    const vec3f& p1, float r0, float r1, std::vector<vec2f>& uv, float& dist);

// Intersect a cone with a triangle (approximate)
inline bool intersect_triangle(const cone_data& cone, const vec3f& p0,
    const vec3f& p1, const vec3f& p2, std::vector<vec2f>& uv, float& dist);

// Intersect a cone with a quad (approximate)
inline bool intersect_quad(const cone_data& cone, const vec3f& p0,
    const vec3f& p1, const vec3f& p2, const vec3f& p3, std::vector<vec2f>& uv,
    float& dist);

// Intersect a ray with a axis-aligned bounding box
inline bool cone_intersect_bbox(
    const cone_data& cone, const bbox3f& bbox, bool printing);

}  // namespace yocto

// -----------------------------------------------------------------------------
// POINT-PRIMITIVE DISTANCE FUNCTIONS
// -----------------------------------------------------------------------------
namespace yocto {

// Check if a point overlaps a position pos withint a maximum distance dist_max.
inline bool overlap_point(const vec3f& pos, float dist_max, const vec3f& p,
    float r, vec2f& uv, float& dist);

// Compute the closest line uv to a give position pos.
inline float closestuv_line(const vec3f& pos, const vec3f& p0, const vec3f& p1);

// Check if a line overlaps a position pos withint a maximum distance dist_max.
inline bool overlap_line(const vec3f& pos, float dist_max, const vec3f& p0,
    const vec3f& p1, float r0, float r1, vec2f& uv, float& dist);

// Compute the closest triangle uv to a give position pos.
inline vec2f closestuv_triangle(
    const vec3f& pos, const vec3f& p0, const vec3f& p1, const vec3f& p2);

// Check if a triangle overlaps a position pos withint a maximum distance
// dist_max.
inline bool overlap_triangle(const vec3f& pos, float dist_max, const vec3f& p0,
    const vec3f& p1, const vec3f& p2, float r0, float r1, float r2, vec2f& uv,
    float& dist);

// Check if a quad overlaps a position pos withint a maximum distance dist_max.
inline bool overlap_quad(const vec3f& pos, float dist_max, const vec3f& p0,
    const vec3f& p1, const vec3f& p2, const vec3f& p3, float r0, float r1,
    float r2, float r3, vec2f& uv, float& dist);

// Check if a bbox overlaps a position pos withint a maximum distance dist_max.
inline bool overlap_bbox(const vec3f& pos, float dist_max, const bbox3f& bbox);

// Check if two bboxe overlap.
inline bool overlap_bbox(const bbox3f& bbox1, const bbox3f& bbox2);

}  // namespace yocto

// -----------------------------------------------------------------------------
//
//
// IMPLEMENTATION
//
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// AXIS ALIGNED BOUNDING BOXES
// -----------------------------------------------------------------------------
namespace yocto {

// Axis aligned bounding box represented as a min/max vector pairs.
inline vec2f& bbox2f::operator[](int i) { return (&min)[i]; }
inline const vec2f& bbox2f::operator[](int i) const { return (&min)[i]; }

// Axis aligned bounding box represented as a min/max vector pairs.
inline vec3f& bbox3f::operator[](int i) { return (&min)[i]; }
inline const vec3f& bbox3f::operator[](int i) const { return (&min)[i]; }

// Bounding box properties
inline vec2f center(const bbox2f& a) { return (a.min + a.max) / 2; }
inline vec2f size(const bbox2f& a) { return a.max - a.min; }

// Bounding box comparisons.
inline bool operator==(const bbox2f& a, const bbox2f& b) {
  return a.min == b.min && a.max == b.max;
}
inline bool operator!=(const bbox2f& a, const bbox2f& b) {
  return a.min != b.min || a.max != b.max;
}

// Bounding box expansions with points and other boxes.
inline bbox2f merge(const bbox2f& a, const vec2f& b) {
  return {min(a.min, b), max(a.max, b)};
}
inline bbox2f merge(const bbox2f& a, const bbox2f& b) {
  return {min(a.min, b.min), max(a.max, b.max)};
}
inline void expand(bbox2f& a, const vec2f& b) { a = merge(a, b); }
inline void expand(bbox2f& a, const bbox2f& b) { a = merge(a, b); }

// Bounding box properties
inline vec3f center(const bbox3f& a) { return (a.min + a.max) / 2; }
inline vec3f size(const bbox3f& a) { return a.max - a.min; }

// Bounding box comparisons.
inline bool operator==(const bbox3f& a, const bbox3f& b) {
  return a.min == b.min && a.max == b.max;
}
inline bool operator!=(const bbox3f& a, const bbox3f& b) {
  return a.min != b.min || a.max != b.max;
}

// Bounding box expansions with points and other boxes.
inline bbox3f merge(const bbox3f& a, const vec3f& b) {
  return {min(a.min, b), max(a.max, b)};
}
inline bbox3f merge(const bbox3f& a, const bbox3f& b) {
  return {min(a.min, b.min), max(a.max, b.max)};
}
inline void expand(bbox3f& a, const vec3f& b) { a = merge(a, b); }
inline void expand(bbox3f& a, const bbox3f& b) { a = merge(a, b); }

}  // namespace yocto

// -----------------------------------------------------------------------------
// RAYS
// -----------------------------------------------------------------------------
namespace yocto {

// Computes a point on a ray
inline vec2f ray_point(const ray2f& ray, float t) { return ray.o + ray.d * t; }
inline vec3f ray_point(const ray3f& ray, float t) { return ray.o + ray.d * t; }

}  // namespace yocto

// -----------------------------------------------------------------------------
// TRANSFORMS
// -----------------------------------------------------------------------------
namespace yocto {

// Transforms rays and bounding boxes by matrices.
inline ray3f transform_ray(const mat4f& a, const ray3f& b) {
  return {transform_point(a, b.o), transform_vector(a, b.d), b.tmin, b.tmax};
}
inline ray3f transform_ray(const frame3f& a, const ray3f& b) {
  return {transform_point(a, b.o), transform_vector(a, b.d), b.tmin, b.tmax};
}
inline bbox3f transform_bbox(const mat4f& a, const bbox3f& b) {
  auto corners = {vec3f{b.min.x, b.min.y, b.min.z},
      vec3f{b.min.x, b.min.y, b.max.z}, vec3f{b.min.x, b.max.y, b.min.z},
      vec3f{b.min.x, b.max.y, b.max.z}, vec3f{b.max.x, b.min.y, b.min.z},
      vec3f{b.max.x, b.min.y, b.max.z}, vec3f{b.max.x, b.max.y, b.min.z},
      vec3f{b.max.x, b.max.y, b.max.z}};
  auto xformed = bbox3f();
  for (auto& corner : corners)
    xformed = merge(xformed, transform_point(a, corner));
  return xformed;
}
inline bbox3f transform_bbox(const frame3f& a, const bbox3f& b) {
  auto corners = {vec3f{b.min.x, b.min.y, b.min.z},
      vec3f{b.min.x, b.min.y, b.max.z}, vec3f{b.min.x, b.max.y, b.min.z},
      vec3f{b.min.x, b.max.y, b.max.z}, vec3f{b.max.x, b.min.y, b.min.z},
      vec3f{b.max.x, b.min.y, b.max.z}, vec3f{b.max.x, b.max.y, b.min.z},
      vec3f{b.max.x, b.max.y, b.max.z}};
  auto xformed = bbox3f();
  for (auto& corner : corners)
    xformed = merge(xformed, transform_point(a, corner));
  return xformed;
}

}  // namespace yocto

// -----------------------------------------------------------------------------
// PRIMITIVE BOUNDS
// -----------------------------------------------------------------------------
namespace yocto {

// Primitive bounds.
inline bbox3f point_bounds(const vec3f& p) { return {p, p}; }
inline bbox3f point_bounds(const vec3f& p, float r) {
  return {min(p - r, p + r), max(p - r, p + r)};
}
inline bbox3f line_bounds(const vec3f& p0, const vec3f& p1) {
  return {min(p0, p1), max(p0, p1)};
}
inline bbox3f line_bounds(
    const vec3f& p0, const vec3f& p1, float r0, float r1) {
  return {min(p0 - r0, p1 - r1), max(p0 + r0, p1 + r1)};
}
inline bbox3f triangle_bounds(
    const vec3f& p0, const vec3f& p1, const vec3f& p2) {
  return {min(p0, min(p1, p2)), max(p0, max(p1, p2))};
}
inline bbox3f quad_bounds(
    const vec3f& p0, const vec3f& p1, const vec3f& p2, const vec3f& p3) {
  return {min(p0, min(p1, min(p2, p3))), max(p0, max(p1, max(p2, p3)))};
}
inline bbox3f sphere_bounds(const vec3f& p, float r) { return {p - r, p + r}; }
inline bbox3f capsule_bounds(
    const vec3f& p0, const vec3f& p1, float r0, float r1) {
  return {min(p0 - r0, p1 - r1), max(p0 + r0, p1 + r1)};
}

}  // namespace yocto

// -----------------------------------------------------------------------------
// GEOMETRY UTILITIES
// -----------------------------------------------------------------------------
namespace yocto {

// Line properties.
inline vec3f line_tangent(const vec3f& p0, const vec3f& p1) {
  return normalize(p1 - p0);
}
inline float line_length(const vec3f& p0, const vec3f& p1) {
  return length(p1 - p0);
}

// Triangle properties.
inline vec3f triangle_normal(
    const vec3f& p0, const vec3f& p1, const vec3f& p2) {
  return normalize(cross(p1 - p0, p2 - p0));
}
inline float triangle_area(const vec3f& p0, const vec3f& p1, const vec3f& p2) {
  return length(cross(p1 - p0, p2 - p0)) / 2;
}

// Quad propeties.
inline vec3f quad_normal(
    const vec3f& p0, const vec3f& p1, const vec3f& p2, const vec3f& p3) {
  return normalize(triangle_normal(p0, p1, p3) + triangle_normal(p2, p3, p1));
}
inline float quad_area(
    const vec3f& p0, const vec3f& p1, const vec3f& p2, const vec3f& p3) {
  return triangle_area(p0, p1, p3) + triangle_area(p2, p3, p1);
}

// Interpolates values over a line parameterized from a to b by u. Same as lerp.
template <typename T>
inline T interpolate_line(const T& p0, const T& p1, float u) {
  return p0 * (1 - u) + p1 * u;
}
// Interpolates values over a triangle parameterized by u and v along the
// (p1-p0) and (p2-p0) directions. Same as barycentric interpolation.
template <typename T>
inline T interpolate_triangle(
    const T& p0, const T& p1, const T& p2, const vec2f& uv) {
  return p0 * (1 - uv.x - uv.y) + p1 * uv.x + p2 * uv.y;
}
// Interpolates values over a quad parameterized by u and v along the
// (p1-p0) and (p2-p1) directions. Same as bilinear interpolation.
template <typename T>
inline T interpolate_quad(
    const T& p0, const T& p1, const T& p2, const T& p3, const vec2f& uv) {
  if (uv.x + uv.y <= 1) {
    return interpolate_triangle(p0, p1, p3, uv);
  } else {
    return interpolate_triangle(p2, p3, p1, 1 - uv);
  }
}

// Interpolates values along a cubic Bezier segment parametrized by u.
template <typename T>
inline T interpolate_bezier(
    const T& p0, const T& p1, const T& p2, const T& p3, float u) {
  return p0 * (1 - u) * (1 - u) * (1 - u) + p1 * 3 * u * (1 - u) * (1 - u) +
         p2 * 3 * u * u * (1 - u) + p3 * u * u * u;
}
// Computes the derivative of a cubic Bezier segment parametrized by u.
template <typename T>
inline T interpolate_bezier_derivative(
    const T& p0, const T& p1, const T& p2, const T& p3, float u) {
  return (p1 - p0) * 3 * (1 - u) * (1 - u) + (p2 - p1) * 6 * u * (1 - u) +
         (p3 - p2) * 3 * u * u;
}

// Interpolated line properties.
inline vec3f line_point(const vec3f& p0, const vec3f& p1, float u) {
  return p0 * (1 - u) + p1 * u;
}
inline vec3f line_tangent(const vec3f& t0, const vec3f& t1, float u) {
  return normalize(t0 * (1 - u) + t1 * u);
}

// Interpolated triangle properties.
inline vec3f triangle_point(
    const vec3f& p0, const vec3f& p1, const vec3f& p2, const vec2f& uv) {
  return p0 * (1 - uv.x - uv.y) + p1 * uv.x + p2 * uv.y;
}
inline vec3f triangle_normal(
    const vec3f& n0, const vec3f& n1, const vec3f& n2, const vec2f& uv) {
  return normalize(n0 * (1 - uv.x - uv.y) + n1 * uv.x + n2 * uv.y);
}

// Interpolated quad properties.
inline vec3f quad_point(const vec3f& p0, const vec3f& p1, const vec3f& p2,
    const vec3f& p3, const vec2f& uv) {
  if (uv.x + uv.y <= 1) {
    return triangle_point(p0, p1, p3, uv);
  } else {
    return triangle_point(p2, p3, p1, 1 - uv);
  }
}
inline vec3f quad_normal(const vec3f& n0, const vec3f& n1, const vec3f& n2,
    const vec3f& n3, const vec2f& uv) {
  if (uv.x + uv.y <= 1) {
    return triangle_normal(n0, n1, n3, uv);
  } else {
    return triangle_normal(n2, n3, n1, 1 - uv);
  }
}

// Interpolated sphere properties.
inline vec3f sphere_point(const vec3f p, float r, const vec2f& uv) {
  return p + r * vec3f{cos(uv.x * 2 * pif) * sin(uv.y * pif),
                     sin(uv.x * 2 * pif) * sin(uv.y * pif), cos(uv.y * pif)};
}
inline vec3f sphere_normal(const vec3f p, float r, const vec2f& uv) {
  return normalize(vec3f{cos(uv.x * 2 * pif) * sin(uv.y * pif),
      sin(uv.x * 2 * pif) * sin(uv.y * pif), cos(uv.y * pif)});
}

// Triangle tangent and bitangent from uv
inline pair<vec3f, vec3f> triangle_tangents_fromuv(const vec3f& p0,
    const vec3f& p1, const vec3f& p2, const vec2f& uv0, const vec2f& uv1,
    const vec2f& uv2) {
  // Follows the definition in http://www.terathon.com/code/tangent.html and
  // https://gist.github.com/aras-p/2843984
  // normal points up from texture space
  auto p   = p1 - p0;
  auto q   = p2 - p0;
  auto s   = vec2f{uv1.x - uv0.x, uv2.x - uv0.x};
  auto t   = vec2f{uv1.y - uv0.y, uv2.y - uv0.y};
  auto div = s.x * t.y - s.y * t.x;

  if (div != 0) {
    auto tu = vec3f{t.y * p.x - t.x * q.x, t.y * p.y - t.x * q.y,
                  t.y * p.z - t.x * q.z} /
              div;
    auto tv = vec3f{s.x * q.x - s.y * p.x, s.x * q.y - s.y * p.y,
                  s.x * q.z - s.y * p.z} /
              div;
    return {tu, tv};
  } else {
    return {{1, 0, 0}, {0, 1, 0}};
  }
}

// Quad tangent and bitangent from uv.
inline pair<vec3f, vec3f> quad_tangents_fromuv(const vec3f& p0, const vec3f& p1,
    const vec3f& p2, const vec3f& p3, const vec2f& uv0, const vec2f& uv1,
    const vec2f& uv2, const vec2f& uv3, const vec2f& current_uv) {
  if (current_uv.x + current_uv.y <= 1) {
    return triangle_tangents_fromuv(p0, p1, p3, uv0, uv1, uv3);
  } else {
    return triangle_tangents_fromuv(p2, p3, p1, uv2, uv3, uv1);
  }
}

}  // namespace yocto

// -----------------------------------------------------------------------------
// IMPLEMENTATION OF USER INTERFACE UTILITIES
// -----------------------------------------------------------------------------
namespace yocto {

// Generate a ray from a camera
inline ray3f camera_ray(const frame3f& frame, float lens, const vec2f& film,
    const vec2f& image_uv) {
  auto e = vec3f{0, 0, 0};
  auto q = vec3f{
      film.x * (0.5f - image_uv.x), film.y * (image_uv.y - 0.5f), lens};
  auto q1  = -q;
  auto d   = normalize(q1 - e);
  auto ray = ray3f{transform_point(frame, e), transform_direction(frame, d)};
  return ray;
}

// Generate a ray from a camera
inline ray3f camera_ray(const frame3f& frame, float lens, float aspect,
    float film_, const vec2f& image_uv) {
  auto film = aspect >= 1 ? vec2f{film_, film_ / aspect}
                          : vec2f{film_ * aspect, film_};
  auto e    = vec3f{0, 0, 0};
  auto q    = vec3f{
      film.x * (0.5f - image_uv.x), film.y * (image_uv.y - 0.5f), lens};
  auto q1  = -q;
  auto d   = normalize(q1 - e);
  auto ray = ray3f{transform_point(frame, e), transform_direction(frame, d)};
  return ray;
}

}  // namespace yocto

// -----------------------------------------------------------------------------
// IMPLEMENRTATION OF RAY-PRIMITIVE INTERSECTION FUNCTIONS
// -----------------------------------------------------------------------------
namespace yocto {

// Intersect a ray with a point (approximate)
inline bool intersect_point(
    const ray3f& ray, const vec3f& p, float r, vec2f& uv, float& dist) {
  // find parameter for line-point minimum distance
  auto w = p - ray.o;
  auto t = dot(w, ray.d) / dot(ray.d, ray.d);

  // exit if not within bounds
  if (t < ray.tmin || t > ray.tmax) return false;

  // test for line-point distance vs point radius
  auto rp  = ray.o + ray.d * t;
  auto prp = p - rp;
  if (dot(prp, prp) > r * r) return false;

  // intersection occurred: set params and exit
  uv   = {0, 0};
  dist = t;
  return true;
}

// ========= my extension =========
// Intersect a ray with infinite cylinder
inline bool intersect_infinite_cylinder(const ray3f& ray, const vec3f& p0,
    const vec3f& p1, float radius, vec3f axis, float* inD, float* outD) {
  // subtract cylinder centre from ray origin, to translate problem at (0,0,0).
  vec3f r_c = ray.o - p0;

  // get radius squared
  float r_2 = radius * radius;

  // get vector that is perpendicular to both the ray and cylinder axis
  vec3f n = cross(ray.d, axis);

  float ln = length(n);

  // check if is parallel
  if (equal(ln, 0.0f)) {
    *inD  = -1.0e21f;
    *outD = 1.0e21f;
    return length(r_c - dot(r_c, axis) * axis) <= radius;
  }
  n = normalize(n);

  float d = abs(dot(r_c, n));

  if (d <= radius) {
    vec3f O = cross(r_c, axis);

    float t = -dot(O, n) / ln;

    O = normalize(cross(n, axis));

    float s = abs(sqrtf(r_2 - d * d) / dot(ray.d, O));

    *inD  = t - s;
    *outD = t + s;

    return true;
  }

  return false;
}

// Intersect a ray with a cylinder
inline bool intersect_cylinder(const ray3f& ray, const vec3f& p0,
    const vec3f& p1, float r0, float r1, vec2f& uv, float& dist) {
  // printf("ray direction: %f, %f, %f\n", ray.d.x, ray.d.y, ray.d.z);
  vec3f axis = normalize(p1 - p0);
  vec3f normal, point;

  float baseDistance = -dot(-axis, p0);
  float topDistance  = -dot(axis, p1);

  float dc, dw, t;
  float inD, outD; /* Object  intersection dists.	*/
  // 0 top, 1 side, 2 base
  unsigned char sideIn;
  unsigned char sideOut;

  if (!intersect_infinite_cylinder(ray, p0, p1, r0, axis, &inD, &outD)) {
    return false;
  }

  sideIn = sideOut = 1;

  /*	Intersect the ray with the bottom end-cap plane.		*/

  dc = dot(-axis, ray.d);
  dw = dot(-axis, ray.o) + baseDistance;

  if (dc == 0.0f) { /* If parallel to bottom plane	*/
    if (dw >= 0.0f) {
      return false;
    }
  } else {
    t = -dw / dc;
    if (dc >= 0.0f) { /* If far plane	*/
      if (t > inD && t < outD) {
        outD    = t;
        sideOut = 2;
      }
      if (t < inD) {
        return false;
      }
    } else { /* If near plane	*/
      if (t > inD && t < outD) {
        inD    = t;
        sideIn = 2;
      }
      if (t > outD) {
        return false;
      }
    }
  }

  // Intersect the ray with the top end-cap plane.

  dc = dot(axis, ray.d);
  dw = dot(axis, ray.o) + topDistance;

  if (dc == 0.0f) { /* If parallel to top plane	*/
    if (dw >= 0.0f) {
      return false;
    }
  } else {
    t = -dw / dc;
    if (dc >= 0.0f) { /* If far plane	*/
      if (t > inD && t < outD) {
        outD    = t;
        sideOut = 0;
      }
      if (t < inD) {
        return false;
      }
    } else { /* If near plane	*/
      if (t > inD && t < outD) {
        inD    = t;
        sideIn = 0;
      }
      if (t > outD) {
        return false;
      }
    }
  }

  if (inD < 0 && outD < 0) return false;

  bool          entering = true;
  unsigned char side     = sideIn;
  if (inD < outD && inD > 0) {
    t     = inD;
    point = ray.o + t * ray.d;

  } else if (outD > 0) {
    t = outD;

    point = ray.o + t * ray.d;

    side     = sideOut;
    entering = false;

  } else {
    return false;
  }

  // INSERTED
  // setup intersection params
  auto u = ray.d;
  auto v = p1 - p0;
  auto w = ray.o - p0;

  // compute values to solve a linear system
  auto a   = dot(u, u);
  auto b   = dot(u, v);
  auto c   = dot(v, v);
  auto d   = dot(u, w);
  auto e   = dot(v, w);
  auto det = a * c - b * b;

  // compute Parameters on both ray and segment
  auto t_ = (b * e - c * d) / det;
  auto s  = (a * e - b * d) / det;

  // exit if not within bounds
  if (t_ < ray.tmin || t_ > ray.tmax) return false;

  // clamp segment param to segment corners
  s = clamp(s, (float)0, (float)1);

  // intersection occurred: set params and exit
  uv   = {s, 0};
  dist = t;

  return true;
}
// ========= my extension ends =========

// Intersect a ray with a line
inline bool intersect_line(const ray3f& ray, const vec3f& p0, const vec3f& p1,
    float r0, float r1, vec2f& uv, float& dist) {
  // setup intersection params
  auto u = ray.d;
  auto v = p1 - p0;
  auto w = ray.o - p0;

  // compute values to solve a linear system
  auto a   = dot(u, u);
  auto b   = dot(u, v);
  auto c   = dot(v, v);
  auto d   = dot(u, w);
  auto e   = dot(v, w);
  auto det = a * c - b * b;

  // check determinant and exit if lines are parallel
  // (could use EPSILONS if desired)
  if (det == 0) return false;

  // compute Parameters on both ray and segment
  auto t = (b * e - c * d) / det;
  auto s = (a * e - b * d) / det;

  // exit if not within bounds

  if (t < ray.tmin || t > ray.tmax) return false;

  // clamp segment param to segment corners
  s = clamp(s, (float)0, (float)1);

  // compute segment-segment distance on the closest points
  auto pr  = ray.o + ray.d * t;
  auto pl  = p0 + (p1 - p0) * s;
  auto prl = pr - pl;

  // check with the line radius at the same point
  auto d2 = dot(prl, prl);
  auto r  = r0 * (1 - s) + r1 * s;
  if (d2 > r * r) return {};

  // intersection occurred: set params and exit
  // uv   = {s, sqrt(d2) / r};
  uv   = {s, 0};
  dist = t;
  return true;
}

// Intersect a ray with a sphere
inline bool intersect_sphere(
    const ray3f& ray, const vec3f& p, float r, vec2f& uv, float& dist) {
  // compute parameters
  auto a = dot(ray.d, ray.d);
  auto b = 2 * dot(ray.o - p, ray.d);
  auto c = dot(ray.o - p, ray.o - p) - r * r;

  // check discriminant
  auto dis = b * b - 4 * a * c;
  if (dis < 0) return false;

  // compute ray parameter
  auto t = (-b - sqrt(dis)) / (2 * a);

  // exit if not within bounds
  if (t < ray.tmin || t > ray.tmax) return false;

  // try other ray parameter
  t = (-b + sqrt(dis)) / (2 * a);

  // exit if not within bounds
  if (t < ray.tmin || t > ray.tmax) return false;

  // compute local point for uvs
  auto plocal = ((ray.o + ray.d * t) - p) / r;
  auto u      = atan2(plocal.y, plocal.x) / (2 * pif);
  if (u < 0) u += 1;
  auto v = acos(clamp(plocal.z, -1.0f, 1.0f)) / pif;

  // intersection occurred: set params and exit
  uv   = {u, v};
  dist = t;
  return true;
}

// Intersect a ray with a triangle
inline bool intersect_triangle(const ray3f& ray, const vec3f& p0,
    const vec3f& p1, const vec3f& p2, vec2f& uv, float& dist) {
  // compute triangle edges
  auto edge1 = p1 - p0;
  auto edge2 = p2 - p0;

  // compute determinant to solve a linear system
  auto pvec = cross(ray.d, edge2);
  auto det  = dot(edge1, pvec);

  // check determinant and exit if triangle and ray are parallel
  // (could use EPSILONS if desired)
  if (det == 0) return false;
  auto inv_det = 1.0f / det;

  // compute and check first bricentric coordinated
  auto tvec = ray.o - p0;
  auto u    = dot(tvec, pvec) * inv_det;
  if (u < 0 || u > 1) return false;

  // compute and check second bricentric coordinated
  auto qvec = cross(tvec, edge1);
  auto v    = dot(ray.d, qvec) * inv_det;
  if (v < 0 || u + v > 1) return false;

  // compute and check ray parameter
  auto t = dot(edge2, qvec) * inv_det;
  if (t < ray.tmin || t > ray.tmax) return false;

  // intersection occurred: set params and exit
  uv   = {u, v};
  dist = t;
  return true;
}

// Intersect a ray with a quad.
inline bool intersect_quad(const ray3f& ray, const vec3f& p0, const vec3f& p1,
    const vec3f& p2, const vec3f& p3, vec2f& uv, float& dist) {
  if (p2 == p3) {
    return intersect_triangle(ray, p0, p1, p3, uv, dist);
  }
  auto hit  = false;
  auto tray = ray;
  if (intersect_triangle(tray, p0, p1, p3, uv, dist)) {
    hit       = true;
    tray.tmax = dist;
  }
  if (intersect_triangle(tray, p2, p3, p1, uv, dist)) {
    hit       = true;
    uv        = 1 - uv;
    tray.tmax = dist;
  }
  return hit;
}

// Intersect a ray with a axis-aligned bounding box
inline bool intersect_bbox(const ray3f& ray, const bbox3f& bbox) {
  // determine intersection ranges
  auto invd = 1.0f / ray.d;
  auto t0   = (bbox.min - ray.o) * invd;
  auto t1   = (bbox.max - ray.o) * invd;
  // flip based on range directions
  if (invd.x < 0.0f) swap(t0.x, t1.x);
  if (invd.y < 0.0f) swap(t0.y, t1.y);
  if (invd.z < 0.0f) swap(t0.z, t1.z);
  auto tmin = max(t0.z, max(t0.y, max(t0.x, ray.tmin)));
  auto tmax = min(t1.z, min(t1.y, min(t1.x, ray.tmax)));
  tmax *= 1.00000024f;  // for double: 1.0000000000000004
  return tmin <= tmax;
}

// Intersect a ray with a axis-aligned bounding box
inline bool intersect_bbox(
    const ray3f& ray, const vec3f& ray_dinv, const bbox3f& bbox) {
  auto it_min = (bbox.min - ray.o) * ray_dinv;
  auto it_max = (bbox.max - ray.o) * ray_dinv;
  auto tmin   = min(it_min, it_max);
  auto tmax   = max(it_min, it_max);
  auto t0     = max(max(tmin), ray.tmin);
  auto t1     = min(min(tmax), ray.tmax);
  t1 *= 1.00000024f;  // for double: 1.0000000000000004
  return t0 <= t1;
}

}  // namespace yocto

// -----------------------------------------------------------------------------
// IMPLEMENRTATION OF CONE-PRIMITIVE INTERSECTION FUNCTIONS
// -----------------------------------------------------------------------------
namespace yocto {

// Intersect a cone with a point (approximate)
inline bool intersect_point(const cone_data& cone, const vec3f& p, float radius,
    std::vector<vec2f>& uv, float& dist) {
  auto ray = ray3f{cone.origin, cone.dir};
  ray.tmin = cone.tmin;
  ray.tmax = cone.tmax;

  vec3f coneCircleV = cone.origin +
                      cone.dir * (length((p + radius) - cone.origin));

  float coneCircleR = length(coneCircleV - cone.origin) * tanf(cone.spread);

  // compute plane coordenate system
  vec3f planeXAxis = normalize(cross(vec3f{0.0f, 0.0f, 1.0f}, -cone.dir));
  vec3f planeYAxis = normalize(cross(-cone.dir, planeXAxis));

  /*approximation through rays
  Shoot rays inside the circle and estimate the area
      _x_
    x/   \x
   x|  x  |x
    x\_x_/x

  */

  int   nPoints = 0;
  vec3f direction;

  float minDistance = flt_max;
  float t_dist      = -1;

  vec3f point;
  float phi = (sqrtf(5.0f) + 1.0f) * 0.5f;
  phi *= phi;
  float theta, r;

  for (int i = 1; i <= N_CONE_POINTS; i++) {
    if (i > N_CONE_POINTS) {
      r = 1.0f;
    } else {
      r = sqrtf(i - 0.5f) / sqrtf(N_CONE_POINTS - 0.5f);
    }

    theta = 2.0f * pi * i / phi;

    point = coneCircleV + (planeXAxis * coneCircleR * r * cos(theta) +
                              planeYAxis * coneCircleR * r * sin(theta));

    direction = normalize(point - cone.origin);
    vec2f uv_ = {};
    if (intersect_point(ray, p, r, uv_, t_dist)) {
      uv.push_back(uv_);

      if (minDistance > t_dist) {
        minDistance = t_dist;
      }

      nPoints++;
    }
  }

  float areaFraction = nPoints / N_CONE_POINTS;

  if (areaFraction <= 0.3f) {
    return false;
  }

  if (t_dist != -1) {
    // intersection occurred: set params and exit
    dist = t_dist;
    return true;
  }

  return false;
}

// Intersect a cone with a line (approximate)
inline bool intersect_line(const cone_data& cone, const vec3f& p0,
    const vec3f& p1, float r0, float r1, std::vector<vec2f>& uv, float& dist) {
  auto ray = ray3f{cone.origin, cone.dir};
  ray.tmin = cone.tmin;
  ray.tmax = cone.tmax;

  vec3f coneCircleV = cone.origin +
                      cone.dir * (length((max(p0, p1) + r0) - cone.origin));

  float coneCircleR = length(coneCircleV - cone.origin) * tanf(cone.spread);

  // compute plane coordenate system
  vec3f planeXAxis = normalize(cross(vec3f{0.0f, 0.0f, 1.0f}, -cone.dir));
  vec3f planeYAxis = normalize(cross(-cone.dir, planeXAxis));

  /*approximation through rays
  Shoot rays inside the circle and estimate the area
      _x_
    x/   \x
   x|  x  |x
    x\_x_/x

  */

  int   nPoints = 0;
  vec3f direction;

  float minDistance = flt_max;
  float t_dist      = -1;

  vec3f point;
  float phi = (sqrtf(5.0f) + 1.0f) * 0.5f;
  phi *= phi;
  float theta, r;

  for (int i = 1; i <= N_CONE_POINTS; i++) {
    if (i > N_CONE_POINTS) {
      r = 1.0f;
    } else {
      r = sqrtf(i - 0.5f) / sqrtf(N_CONE_POINTS - 0.5f);
    }

    theta = 2.0f * pi * i / phi;

    point = coneCircleV + (planeXAxis * coneCircleR * r * cos(theta) +
                              planeYAxis * coneCircleR * r * sin(theta));

    direction = normalize(point - cone.origin);
    vec2f uv_ = {};
    if (intersect_line(ray, p0, p1, r0, r1, uv_, t_dist)) {
      uv.push_back(uv_);

      if (minDistance > t_dist) {
        minDistance = t_dist;
      }

      nPoints++;
    }
  }

  float areaFraction = nPoints / N_CONE_POINTS;

  if (areaFraction <= 0.3f) {
    return false;
  }

  if (t_dist != -1) {
    // intersection occurred: set params and exit
    dist = t_dist;
    return true;
  }

  return false;
}

// Intersect a cone with a cylinder (approximate)
inline bool intersect_cylinder(const cone_data& cone, const vec3f& p0,
    const vec3f& p1, float r0, float r1, std::vector<vec2f>& uv, float& dist) {
  auto ray = ray3f{cone.origin, cone.dir};
  ray.tmin = cone.tmin;
  ray.tmax = cone.tmax;

  vec3f coneCircleV = cone.origin +
                      cone.dir * (length((max(p0, p1) + r0) - cone.origin));

  float coneCircleR = length(coneCircleV - cone.origin) * tanf(cone.spread);

  // compute plane coordenate system
  vec3f planeXAxis = normalize(cross(vec3f{0.0f, 0.0f, 1.0f}, -cone.dir));
  vec3f planeYAxis = normalize(cross(-cone.dir, planeXAxis));

  /*approximation through rays
  Shoot rays inside the circle and estimate the area
      _x_
    x/   \x
   x|  x  |x
    x\_x_/x

  */

  int   nPoints = 0;
  vec3f direction;

  float minDistance = flt_max;
  float t_dist      = -1;

  vec3f point;
  float phi = (sqrtf(5.0f) + 1.0f) * 0.5f;
  phi *= phi;
  float theta, r;

  for (int i = 1; i <= N_CONE_POINTS; i++) {
    if (i > N_CONE_POINTS) {
      r = 1.0f;
    } else {
      r = sqrtf(i - 0.5f) / sqrtf(N_CONE_POINTS - 0.5f);
    }

    theta = 2.0f * pi * i / phi;

    point = coneCircleV + (planeXAxis * coneCircleR * r * cos(theta) +
                              planeYAxis * coneCircleR * r * sin(theta));

    direction = normalize(point - cone.origin);
    vec2f uv_ = {};
    if (intersect_cylinder(ray, p0, p1, r0, r1, uv_, t_dist)) {
      // if (intersect_line(ray, p0, p1, r0, r1, uv_, t_dist)) {
      uv.push_back(uv_);

      if (minDistance > t_dist) {
        minDistance = t_dist;
      }

      nPoints++;
    }
  }

  float areaFraction = nPoints / N_CONE_POINTS;

  if (areaFraction <= 0.3f) {
    return false;
  }

  if (t_dist != -1) {
    // intersection occurred: set params and exit
    dist = t_dist;
    return true;
  }

  return false;
}

// Intersect a cone with a triangle (approximate)
inline bool intersect_triangle(const cone_data& cone, const vec3f& p0,
    const vec3f& p1, const vec3f& p2, std::vector<vec2f>& uv, float& dist) {
  auto ray = ray3f{cone.origin, cone.dir};
  ray.tmin = cone.tmin;
  ray.tmax = cone.tmax;

  vec3f coneCircleV = cone.origin +
                      cone.dir * (length((max(p0, p1) + p2) - cone.origin));

  float coneCircleR = length(coneCircleV - cone.origin) * tanf(cone.spread);

  // compute plane coordenate system
  vec3f planeXAxis = normalize(cross(vec3f{0.0f, 0.0f, 1.0f}, -cone.dir));
  vec3f planeYAxis = normalize(cross(-cone.dir, planeXAxis));

  /*approximation through rays
  Shoot rays inside the circle and estimate the area
      _x_
    x/   \x
   x|  x  |x
    x\_x_/x

  */

  int   nPoints = 0;
  vec3f direction;

  float minDistance = flt_max;
  float t_dist      = -1;

  vec3f point;
  float phi = (sqrtf(5.0f) + 1.0f) * 0.5f;
  phi *= phi;
  float theta, r;

  for (int i = 1; i <= N_CONE_POINTS; i++) {
    if (i > N_CONE_POINTS) {
      r = 1.0f;
    } else {
      r = sqrtf(i - 0.5f) / sqrtf(N_CONE_POINTS - 0.5f);
    }

    theta = 2.0f * pi * i / phi;

    point = coneCircleV + (planeXAxis * coneCircleR * r * cos(theta) +
                              planeYAxis * coneCircleR * r * sin(theta));

    direction = normalize(point - cone.origin);
    vec2f uv_ = {};
    if (intersect_triangle(ray, p0, p1, p2, uv_, t_dist)) {
      uv.push_back(uv_);

      if (minDistance > t_dist) {
        minDistance = t_dist;
      }

      nPoints++;
    }
  }

  float areaFraction = nPoints / N_CONE_POINTS;

  if (areaFraction <= 0.3f) {
    return false;
  }

  if (t_dist != -1) {
    // intersection occurred: set params and exit
    dist = t_dist;
    return true;
  }

  return false;
}

// Intersect a cone with a quad (approximate)
inline bool intersect_quad(const cone_data& cone, const vec3f& p0,
    const vec3f& p1, const vec3f& p2, const vec3f& p3, std::vector<vec2f>& uv,
    float& dist) {
  auto ray = ray3f{cone.origin, cone.dir};
  ray.tmin = cone.tmin;
  ray.tmax = cone.tmax;

  vec3f coneCircleV = cone.origin +
                      cone.dir * (length((max(p0, p1) + p2) - cone.origin));

  float coneCircleR = length(coneCircleV - cone.origin) * tanf(cone.spread);

  // compute plane coordenate system
  vec3f planeXAxis = normalize(cross(vec3f{0.0f, 0.0f, 1.0f}, -cone.dir));
  vec3f planeYAxis = normalize(cross(-cone.dir, planeXAxis));

  /*approximation through rays
  Shoot rays inside the circle and estimate the area
      _x_
    x/   \x
   x|  x  |x
    x\_x_/x

  */

  int   nPoints = 0;
  vec3f direction;

  float minDistance = flt_max;
  float t_dist      = -1;

  vec3f point;
  float phi = (sqrtf(5.0f) + 1.0f) * 0.5f;
  phi *= phi;
  float theta, r;

  for (int i = 1; i <= N_CONE_POINTS; i++) {
    if (i > N_CONE_POINTS) {
      r = 1.0f;
    } else {
      r = sqrtf(i - 0.5f) / sqrtf(N_CONE_POINTS - 0.5f);
    }

    theta = 2.0f * pi * i / phi;

    point = coneCircleV + (planeXAxis * coneCircleR * r * cos(theta) +
                              planeYAxis * coneCircleR * r * sin(theta));

    direction = normalize(point - cone.origin);
    vec2f uv_ = {};
    if (intersect_quad(ray, p0, p1, p2, p3, uv_, t_dist)) {
      uv.push_back(uv_);

      if (minDistance > t_dist) {
        minDistance = t_dist;
      }

      nPoints++;
    }
  }

  float areaFraction = nPoints / N_CONE_POINTS;

  if (areaFraction <= 0.3f) {
    return false;
  }

  if (t_dist != -1) {
    // intersection occurred: set params and exit
    dist = t_dist;
    return true;
  }

  return false;
}

struct AABBPolygon {
  unsigned char nPoints;
  unsigned char point[6];

  AABBPolygon(unsigned char type) {
    // ---
    if (type == 0) {
      nPoints = 6;

      point[0] = 1;
      point[1] = 5;
      point[2] = 4;
      point[3] = 6;
      point[4] = 2;
      point[5] = 3;

      // 0--
    } else if (type == 1) {
      nPoints = 6;

      point[0] = 0;
      point[1] = 2;
      point[2] = 3;
      point[3] = 1;
      point[4] = 5;
      point[5] = 4;

      // +--
    } else if (type == 2) {
      nPoints = 6;

      point[0] = 0;
      point[1] = 2;
      point[2] = 3;
      point[3] = 7;
      point[4] = 5;
      point[5] = 4;

      // -0-
    } else if (type == 3) {
      nPoints = 6;

      point[0] = 0;
      point[1] = 4;
      point[2] = 6;
      point[3] = 2;
      point[4] = 3;
      point[5] = 1;

      // 00-
    } else if (type == 4) {
      nPoints = 4;

      point[0] = 0;
      point[1] = 2;
      point[2] = 3;
      point[3] = 1;

      // +0-
    } else if (type == 5) {
      nPoints = 6;

      point[0] = 0;
      point[1] = 2;
      point[2] = 3;
      point[3] = 7;
      point[4] = 5;
      point[5] = 1;

      // -+-
    } else if (type == 6) {
      nPoints = 6;

      point[0] = 0;
      point[1] = 4;
      point[2] = 6;
      point[3] = 7;
      point[4] = 3;
      point[5] = 1;

      // 0+-
    } else if (type == 7) {
      nPoints = 6;

      point[0] = 0;
      point[1] = 2;
      point[2] = 6;
      point[3] = 7;
      point[4] = 3;
      point[5] = 1;

      // ++-
    } else if (type == 8) {
      nPoints = 6;

      point[0] = 0;
      point[1] = 2;
      point[2] = 6;
      point[3] = 7;
      point[4] = 5;
      point[5] = 1;

      // --0
    } else if (type == 9) {
      nPoints = 6;

      point[0] = 0;
      point[1] = 1;
      point[2] = 5;
      point[3] = 4;
      point[4] = 6;
      point[5] = 2;

      // 0-0
    } else if (type == 10) {
      nPoints = 4;

      point[0] = 0;
      point[1] = 1;
      point[2] = 5;
      point[3] = 4;

      // +-0
    } else if (type == 11) {
      nPoints = 6;

      point[0] = 0;
      point[1] = 1;
      point[2] = 3;
      point[3] = 7;
      point[4] = 5;
      point[5] = 4;

      // -00
    } else if (type == 12) {
      nPoints = 4;

      point[0] = 0;
      point[1] = 4;
      point[2] = 6;
      point[3] = 2;

      // 000
    } else if (type == 13) {
      nPoints = 0;

      // +00
    } else if (type == 14) {
      nPoints = 4;

      point[0] = 1;
      point[1] = 3;
      point[2] = 7;
      point[3] = 5;

      // -+0
    } else if (type == 15) {
      nPoints = 6;

      point[0] = 0;
      point[1] = 4;
      point[2] = 6;
      point[3] = 7;
      point[4] = 3;
      point[5] = 2;

      // 0+0
    } else if (type == 16) {
      nPoints = 4;

      point[0] = 2;
      point[1] = 6;
      point[2] = 7;
      point[3] = 3;

      // ++0
    } else if (type == 17) {
      nPoints = 6;

      point[0] = 1;
      point[1] = 3;
      point[2] = 2;
      point[3] = 6;
      point[4] = 7;
      point[5] = 5;

      // --+
    } else if (type == 18) {
      nPoints = 6;

      point[0] = 0;
      point[1] = 1;
      point[2] = 5;
      point[3] = 7;
      point[4] = 6;
      point[5] = 2;

      // 0-+
    } else if (type == 19) {
      nPoints = 6;

      point[0] = 0;
      point[1] = 1;
      point[2] = 5;
      point[3] = 7;
      point[4] = 6;
      point[5] = 4;

      // +-+
    } else if (type == 20) {
      nPoints = 6;

      point[0] = 0;
      point[1] = 1;
      point[2] = 3;
      point[3] = 7;
      point[4] = 6;
      point[5] = 4;

      // -0+
    } else if (type == 21) {
      nPoints = 6;

      point[0] = 0;
      point[1] = 4;
      point[2] = 5;
      point[3] = 7;
      point[4] = 6;
      point[5] = 2;

      // 00+
    } else if (type == 22) {
      nPoints = 4;

      point[0] = 4;
      point[1] = 5;
      point[2] = 7;
      point[3] = 6;

      // +0+
    } else if (type == 23) {
      nPoints = 6;

      point[0] = 1;
      point[1] = 3;
      point[2] = 7;
      point[3] = 6;
      point[4] = 4;
      point[5] = 5;

      // -++
    } else if (type == 24) {
      nPoints = 6;

      point[0] = 0;
      point[1] = 4;
      point[2] = 5;
      point[3] = 7;
      point[4] = 3;
      point[5] = 2;

      // 0++
    } else if (type == 25) {
      nPoints = 6;

      point[0] = 2;
      point[1] = 6;
      point[2] = 4;
      point[3] = 5;
      point[4] = 7;
      point[5] = 3;

      // +++
    } else {
      nPoints = 6;

      point[0] = 1;
      point[1] = 3;
      point[2] = 2;
      point[3] = 6;
      point[4] = 4;
      point[5] = 5;
    }
  }
};

inline void setVectorValue(vec3f& vec, int pos, float value) {
  if (pos == 0) {
    vec.x = value;

  } else if (pos == 1) {
    vec.y = value;

  } else {
    vec.z = value;
  }
}

inline float getVectorValue(vec3f vec, int pos) {
  if (pos == 0) {
    return vec.x;

  } else if (pos == 1) {
    return vec.y;

  } else {
    return vec.z;
  }
}

// Intersect a ray with a axis-aligned bounding box
inline bool cone_intersect_bbox(
    const cone_data& cone, const bbox3f& bbox, bool printing) {
  // quick rejection test return false
  // if this function return true then use normal one juust to test out first
  // rejection test
  auto box_centre = (bbox.max + bbox.min) * 0.5f;
  auto box_e      = (bbox.max - bbox.min) * 0.5f;

  // translate box to centre around cone origin
  auto box_cone_vec          = box_centre - cone.origin;
  auto cone_dir_dot_box_cone = dot(cone.dir, box_cone_vec);
  auto radius                = dot(box_e, abs(cone.dir));

  if (cone_dir_dot_box_cone + radius <= 0.0f) {
    // The box is in the halfspace below the supporting plane of the cone.
    // If we only use cone tracing when bounce is zero then we should never
    // reach this
    return false;
  }

  // check if cone axis intersects box
  if (intersect_bbox({cone.origin, cone.dir}, bbox)) {
    return true;
  }

  // Determine the box faces that are visible to the cone vertex.
  int type = 0;
  type += (box_cone_vec.x < -box_e.x ? 2 : (box_cone_vec.x > box_e.x ? 0 : 1));
  type += 3 *
          (box_cone_vec.y < -box_e.y ? 2 : (box_cone_vec.y > box_e.y ? 0 : 1));
  type += 9 *
          (box_cone_vec.z < -box_e.z ? 2 : (box_cone_vec.z > box_e.z ? 0 : 1));

  // if cone vertex inside the box
  if (type == 13) {
    // The cone vertex is in the box.
    return true;
  }
  AABBPolygon polygon = AABBPolygon(type);

  // Test polygon points.
  vec3f X[8], PmV[8];
  float coneDirDOTPmV[8], sqrConeDirDOTPmV[8], sqrLenPmV[8], q;
  int   iMax = -1, jMax = -1;
  float coneCosAngle_2 = cos(cone.spread) * cos(cone.spread);

  for (unsigned char i = 0; i < polygon.nPoints; i++) {
    int j  = polygon.point[i];
    X[j].x = (j & 1 ? box_e.x : -box_e.x);
    X[j].y = (j & 2 ? box_e.y : -box_e.y);
    X[j].z = (j & 4 ? box_e.z : -box_e.z);

    coneDirDOTPmV[j] = dot(cone.dir, X[j]) + cone_dir_dot_box_cone;

    if (coneDirDOTPmV[j] > 0.0f) {
      PmV[j]              = X[j] + box_cone_vec;
      sqrConeDirDOTPmV[j] = coneDirDOTPmV[j] * coneDirDOTPmV[j];
      sqrLenPmV[j]        = dot(PmV[j], PmV[j]);
      q                   = sqrConeDirDOTPmV[j] - coneCosAngle_2 * sqrLenPmV[j];

      if (q > 0.0f) {
        return true;
      }

      // Keep track of the maximum in case we must process box edges.
      // This supports the gradient ascent search.
      if (iMax == -1 || sqrConeDirDOTPmV[j] * sqrLenPmV[jMax] >
                            sqrConeDirDOTPmV[jMax] * sqrLenPmV[j]) {
        iMax = i;
        jMax = j;
      }
    }
  }

  if (iMax == -1) {
    return false;
  }

  // Start the gradient ascent search at index jMax.
  float maxSqrLenPmV     = sqrLenPmV[jMax];
  float maxConeDirDOTPmV = coneDirDOTPmV[jMax];
  vec3f maxX             = X[jMax];
  float maxPmV[]         = {PmV[jMax].x, PmV[jMax].y, PmV[jMax].z};
  int   k0, k1, k2, jDiff;
  float s, fder, numer, denom, DdMmV, det;
  vec3f MmV;
  float coneDirection[] = {cone.dir.x, cone.dir.y, cone.dir.z};

  // Search the counterclockwise edge <corner[jMax],corner[jNext]>.
  int iNext = (iMax < polygon.nPoints - 1 ? iMax + 1 : 0);
  int jNext = polygon.point[iNext];
  jDiff     = jNext - jMax;
  s         = (jDiff > 0 ? 1.0f : -1.0f);
  k0        = abs(jDiff) >> 1;
  fder = s * (coneDirection[k0] * maxSqrLenPmV - maxConeDirDOTPmV * maxPmV[k0]);

  if (fder > 0.0f) {
    // The edge has an interior local maximum in F because
    // F(K[j0]) >= F(K[j1]) and the directional derivative of F at K0
    // is positive.  Compute the local maximum point.
    k1    = (k0 + 1) % 3;
    k2    = (k1 + 1) % 3;
    numer = maxPmV[k1] * maxPmV[k1] + maxPmV[k2] * maxPmV[k2];
    denom = coneDirection[k1] * maxPmV[k1] + coneDirection[k2] * maxPmV[k2];

    setVectorValue(MmV, k0, numer * coneDirection[k0]);
    setVectorValue(MmV, k1,
        denom * (getVectorValue(maxX, k1) + getVectorValue(box_cone_vec, k1)));
    setVectorValue(MmV, k2,
        denom * (getVectorValue(maxX, k2) + getVectorValue(box_cone_vec, k2)));

    // Theoretically, DdMmV > 0, so there is no need to test positivity.
    DdMmV = dot(cone.dir, MmV);
    q     = DdMmV * DdMmV - coneCosAngle_2 * dot(MmV, MmV);

    if (q > 0.0f) {
      return true;
    }

    // Determine on which side of the spherical arc coneDirection lives on.
    // If in the polygon side, then there is an intersection.
    det = s * (coneDirection[k1] * maxPmV[k2] - coneDirection[k2] * maxPmV[k1]);

    if (det <= 0.0f) {
    }
    return (det <= 0.0f);
  }

  // Search the clockwise edge <corner[jMax],corner[jPrev]>.
  int iPrev = (iMax > 0 ? iMax - 1 : polygon.nPoints - 1);
  int jPrev = polygon.point[iPrev];
  jDiff     = jMax - jPrev;
  s         = (jDiff > 0 ? 1.0f : -1.0f);
  k0        = abs(jDiff) >> 1;
  fder      = -s *
         (coneDirection[k0] * maxSqrLenPmV - maxConeDirDOTPmV * maxPmV[k0]);

  if (fder > 0.0f) {
    // The edge has an interior local maximum in F because
    // F(K[j0]) >= F(K[j1]) and the directional derivative of F at K0
    // is positive.  Compute the local maximum point.
    k1    = (k0 + 1) % 3;
    k2    = (k1 + 1) % 3;
    numer = maxPmV[k1] * maxPmV[k1] + maxPmV[k2] * maxPmV[k2];
    denom = coneDirection[k1] * maxPmV[k1] + coneDirection[k2] * maxPmV[k2];

    setVectorValue(MmV, k0, numer * coneDirection[k0]);
    setVectorValue(MmV, k1,
        denom * (getVectorValue(maxX, k1) + getVectorValue(box_cone_vec, k1)));
    setVectorValue(MmV, k2,
        denom * (getVectorValue(maxX, k2) + getVectorValue(box_cone_vec, k2)));

    // Theoretically, DdMmV > 0, so there is no need to test positivity.
    DdMmV = dot(cone.dir, MmV);
    q     = DdMmV * DdMmV - coneCosAngle_2 * dot(MmV, MmV);

    if (q > 0.0f) {
      return true;
    }

    // Determine on which side of the spherical arc coneDirection lives on.
    // If in the polygon side, then there is an intersection.
    det = s * (coneDirection[k1] * maxPmV[k2] - coneDirection[k2] * maxPmV[k1]);

    if (det <= 0.0f) {
    }

    return (det <= 0.0f);
  }
  return false;

  // return intersect_bbox({cone.origin, cone.dir}, bbox);
}

}  // namespace yocto

// -----------------------------------------------------------------------------
// IMPLEMENTATION OF POINT-PRIMITIVE DISTANCE FUNCTIONS
// -----------------------------------------------------------------------------
namespace yocto {

// Check if a point overlaps a position pos withint a maximum distance dist_max.
inline bool overlap_point(const vec3f& pos, float dist_max, const vec3f& p,
    float r, vec2f& uv, float& dist) {
  auto d2 = dot(pos - p, pos - p);
  if (d2 > (dist_max + r) * (dist_max + r)) return false;
  uv   = {0, 0};
  dist = sqrt(d2);
  return true;
}

// Compute the closest line uv to a give position pos.
inline float closestuv_line(
    const vec3f& pos, const vec3f& p0, const vec3f& p1) {
  auto ab = p1 - p0;
  auto d  = dot(ab, ab);
  // Project c onto ab, computing parameterized position d(t) = a + t*(b –
  // a)
  auto u = dot(pos - p0, ab) / d;
  u      = clamp(u, (float)0, (float)1);
  return u;
}

// Check if a line overlaps a position pos withint a maximum distance dist_max.
inline bool overlap_line(const vec3f& pos, float dist_max, const vec3f& p0,
    const vec3f& p1, float r0, float r1, vec2f& uv, float& dist) {
  auto u = closestuv_line(pos, p0, p1);
  // Compute projected position from the clamped t d = a + t * ab;
  auto p  = p0 + (p1 - p0) * u;
  auto r  = r0 + (r1 - r0) * u;
  auto d2 = dot(pos - p, pos - p);
  // check distance
  if (d2 > (dist_max + r) * (dist_max + r)) return false;
  // done
  uv   = {u, 0};
  dist = sqrt(d2);
  return true;
}

// Compute the closest triangle uv to a give position pos.
inline vec2f closestuv_triangle(
    const vec3f& pos, const vec3f& p0, const vec3f& p1, const vec3f& p2) {
  // this is a complicated test -> I probably "--"+prefix to use a sequence of
  // test (triangle body, and 3 edges)
  auto ab = p1 - p0;
  auto ac = p2 - p0;
  auto ap = pos - p0;

  auto d1 = dot(ab, ap);
  auto d2 = dot(ac, ap);

  // corner and edge cases
  if (d1 <= 0 && d2 <= 0) return {0, 0};

  auto bp = pos - p1;
  auto d3 = dot(ab, bp);
  auto d4 = dot(ac, bp);
  if (d3 >= 0 && d4 <= d3) return {1, 0};

  auto vc = d1 * d4 - d3 * d2;
  if ((vc <= 0) && (d1 >= 0) && (d3 <= 0)) return {d1 / (d1 - d3), 0};

  auto cp = pos - p2;
  auto d5 = dot(ab, cp);
  auto d6 = dot(ac, cp);
  if (d6 >= 0 && d5 <= d6) return {0, 1};

  auto vb = d5 * d2 - d1 * d6;
  if ((vb <= 0) && (d2 >= 0) && (d6 <= 0)) return {0, d2 / (d2 - d6)};

  auto va = d3 * d6 - d5 * d4;
  if ((va <= 0) && (d4 - d3 >= 0) && (d5 - d6 >= 0)) {
    auto w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
    return {1 - w, w};
  }

  // face case
  auto denom = 1 / (va + vb + vc);
  auto u     = vb * denom;
  auto v     = vc * denom;
  return {u, v};
}

// Check if a triangle overlaps a position pos withint a maximum distance
// dist_max.
inline bool overlap_triangle(const vec3f& pos, float dist_max, const vec3f& p0,
    const vec3f& p1, const vec3f& p2, float r0, float r1, float r2, vec2f& uv,
    float& dist) {
  auto cuv = closestuv_triangle(pos, p0, p1, p2);
  auto p   = p0 * (1 - cuv.x - cuv.y) + p1 * cuv.x + p2 * cuv.y;
  auto r   = r0 * (1 - cuv.x - cuv.y) + r1 * cuv.x + r2 * cuv.y;
  auto dd  = dot(p - pos, p - pos);
  if (dd > (dist_max + r) * (dist_max + r)) return false;
  uv   = cuv;
  dist = sqrt(dd);
  return true;
}

// Check if a quad overlaps a position pos withint a maximum distance dist_max.
inline bool overlap_quad(const vec3f& pos, float dist_max, const vec3f& p0,
    const vec3f& p1, const vec3f& p2, const vec3f& p3, float r0, float r1,
    float r2, float r3, vec2f& uv, float& dist) {
  if (p2 == p3) {
    return overlap_triangle(pos, dist_max, p0, p1, p3, r0, r1, r2, uv, dist);
  }
  auto hit = false;
  if (overlap_triangle(pos, dist_max, p0, p1, p3, r0, r1, r2, uv, dist)) {
    hit      = true;
    dist_max = dist;
  }
  if (!overlap_triangle(pos, dist_max, p2, p3, p1, r2, r3, r1, uv, dist)) {
    hit = true;
    uv  = 1 - uv;
    // dist_max = dist;
  }
  return hit;
}

// Check if a bbox overlaps a position pos withint a maximum distance dist_max.
inline bool overlap_bbox(const vec3f& pos, float dist_max, const bbox3f& bbox) {
  // computing distance
  auto dd = 0.0f;

  // For each axis count any excess distance outside box extents
  if (pos.x < bbox.min.x) dd += (bbox.min.x - pos.x) * (bbox.min.x - pos.x);
  if (pos.x > bbox.max.x) dd += (pos.x - bbox.max.x) * (pos.x - bbox.max.x);
  if (pos.y < bbox.min.y) dd += (bbox.min.y - pos.y) * (bbox.min.y - pos.y);
  if (pos.y > bbox.max.y) dd += (pos.y - bbox.max.y) * (pos.y - bbox.max.y);
  if (pos.z < bbox.min.z) dd += (bbox.min.z - pos.z) * (bbox.min.z - pos.z);
  if (pos.z > bbox.max.z) dd += (pos.z - bbox.max.z) * (pos.z - bbox.max.z);

  // check distance
  return dd < dist_max * dist_max;
}

// Check if two bboxe overlap.
inline bool overlap_bbox(const bbox3f& bbox1, const bbox3f& bbox2) {
  if (bbox1.max.x < bbox2.min.x || bbox1.min.x > bbox2.max.x) return false;
  if (bbox1.max.y < bbox2.min.y || bbox1.min.y > bbox2.max.y) return false;
  if (bbox1.max.z < bbox2.min.z || bbox1.min.z > bbox2.max.z) return false;
  return true;
}

}  // namespace yocto

#endif
