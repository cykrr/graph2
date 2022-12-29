#ifndef ENTITY_H
#define ENTITY_H
#include "entt/entity/registry.hpp"
entt::entity create_entity(entt::registry & r, float *vertices, unsigned int vertex_count);

#endif
