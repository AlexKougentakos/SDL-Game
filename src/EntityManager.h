#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "./Entity.h"
#include "./Component.h"
#include "Constants.h"
#include <vector>

class EntityManager {
private:
	std::vector<Entity*> entities;
public:
	void ClearData();
	void Update(float deltaTime);
	void Render();
	void MoveEntity(const Entity* thatEntity);
	bool HasNoEntities() const;
	unsigned int GetEntityCount() const;
	void ListAllEntities() const;
	std::vector<Entity*> GetEntities() const;
	std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
	Entity& AddEntity(std::string entityName, LayerType layer);
	CollisionType CheckCollisions() const;
};

#endif
