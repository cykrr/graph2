#ifndef ANIMATION_COMP_H
#define ANIMATION_COMP_H

#include <cstdio>
#include <vector>
#include "entt/entity/registry.hpp"
typedef float(*easing_fn)(float, float, float, float);

struct Animation {
  float begin_value;
  float end_value;
  float duration;
  float elapsed_time;
  float *var;
  easing_fn fn;
  Animation(const Animation &) = default;
  Animation(Animation &) = default;
};

struct AnimationComponent {
  std::vector<Animation> vector;
  AnimationComponent() = default;
};

void add_animation(AnimationComponent &c, const Animation &a) {
  c.vector.push_back(a);
}

void add_animation(entt::registry &r, entt::entity &e, const Animation &a) {
  r.get<AnimationComponent>(e).vector.push_back(a);
}


bool run_animation(Animation & a, float dt ) {
    if (a.var == NULL) return true;

    a.elapsed_time += dt;
    if (a.elapsed_time > a.duration)
      return true;

    // printf("init: %f end: %f done %d", a.begin_value, a.end_value, a.elapsed_time > a.duration);
    // printf("elapsed: %f duration: %f", a.elapsed_time, a.duration);
    // printf("val: %f\n", *a.var);

    *(a.var) = a.fn(a.elapsed_time, a.begin_value, a.end_value - a.begin_value, a.duration);
    return false;
}

bool animation_update(AnimationComponent & a, float dt) {
  for (Animation & a : a.vector) {
    run_animation(a, dt);
  }
}

#endif

