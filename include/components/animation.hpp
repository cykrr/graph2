#ifndef ANIMATION_COMP_H
#define ANIMATION_COMP_H

#include <cstdio>
#include <vector>
#include "entity.hpp"

typedef float(*easing_fn)(float, float, float, float);

typedef struct Animation Animation;


struct AnimationComponent {
  std::vector<std::vector<Animation>> groups;
  AnimationComponent() = default;
};



struct Animation {
  float begin_value;
  float change; // variation of ^ initial value
  float duration;
  float *var;
  easing_fn fn;

  double elapsed_time = 0;

  Animation(const Animation &) = default;
  Animation(Animation &) = default;
  // Is this allowed?
  Animation(float begin_value, float change, float duration, float *variable,
            easing_fn fn) : begin_value(begin_value), change(change),
    duration(duration), var(variable), fn(fn) {}
};


void add_animation(Entity &e, const Animation &a, int group = 0);
void add_animation(AnimationComponent &c, const Animation &a);
bool run_animation(Animation & a, double dt);
void add_animation(AnimationComponent &c, const Animation &a, int group = 0);
void animation_update(AnimationComponent & a, float dt);

int create_animation_group(Entity & e);
int clear_animation_group(Entity & e, int group = 0);



#endif

