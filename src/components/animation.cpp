#include "components/animation.hpp"

void add_animation(AnimationComponent &c, const Animation &a, int group)
{
  c.groups[group].push_back(a);
}

void add_animation(Entity &e, const Animation &a, int group)
{
  e.get<AnimationComponent>().groups[group].push_back(a);
}


inline
bool run_animation(Animation & a, double dt)
{
    if (a.var == NULL) return true;
    // printf("elapsed: %f dt: %f\n", a.elapsed_time, dt);
    if (a.elapsed_time + dt > a.duration) {
      *(a.var) = a.fn(a.duration, a.begin_value, a.change, a.duration);
      // printf("End value %.2f; delta = %.2f\n",
             // *a.var * 180 / M_PI, *a.var - a.begin_value);
      return true;
  }
    a.elapsed_time+=dt;
    *(a.var) = a.fn(a.elapsed_time, a.begin_value, a.change, a.duration);
    return false;
}


void animation_update(AnimationComponent & a, float dt)
{
  for (std::vector<Animation> & g : a.groups) {
    for (Animation & a : g) {
      if (run_animation(a, dt)) {
        // printf("listo\n");
        g.erase(std::remove_if(g.begin(), g.end(), [&] (const Animation & lh) { return lh.begin_value == a.begin_value;}), g.end());
      }
    }
  }
}

int create_animation_group(Entity &e) {
  AnimationComponent & c = e.get<AnimationComponent>();
  c.groups.push_back(std::vector<Animation>());
  return c.groups.size() - 1;
}


int clear_animation_group(Entity &e, int group) {
  e.get<AnimationComponent>().groups[group].clear();
  return true;
}
