#include "components/animation.hpp"

void add_animation(AnimationComponent &c, const Animation &a)
{
  c.vector.push_back(a);
}

void add_animation(entt::registry &r, entt::entity &e, const Animation &a)
{
  r.get<AnimationComponent>(e).vector.push_back(a);
}


inline
bool run_animation(Animation & a, double dt)
{
    printf("elapsed: %f duration: %f\n", a.elapsed_time, dt);
    if (a.elapsed_time + dt > a.duration) {
      *(a.var) = a.fn(a.duration, a.begin_value, a.change, a.duration);
      printf("End value %.2f; delta = %.2f\n",
             *a.var * 180 / M_PI, *a.var - a.begin_value);
      return true;
  }
    a.elapsed_time+=dt;
    if (a.var == NULL) return true;

    *(a.var) = a.fn(a.elapsed_time, a.begin_value, a.change, a.duration);
    return false;
}


void animation_update(AnimationComponent & a, float dt)
{
  for (Animation & a : a.vector) {
    run_animation(a, dt);
  }
}
