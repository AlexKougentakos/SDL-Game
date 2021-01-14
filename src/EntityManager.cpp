#include <iostream>
#include "./EntityManager.h"
#include "./Collision.h"
#include "./Components/ColliderComponent.h"

Game *game = new Game();

void EntityManager::ClearData()
{
	for (auto& entity : entities)
	{
		entity->Destroy();
	}
}

void EntityManager::Update(float deltaTime)
{
	for (auto& entity : entities)
	{
		entity->Update(deltaTime);
	}
}

void EntityManager::Render()
{
	for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++)
	{
		for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber)))
		{
			entity->Render();
		}
	}
}

bool EntityManager::HasNoEntities() const
{
	return entities.size() == 0;
}

unsigned int EntityManager::GetEntityCount() const
{
	return entities.size();
}

std::vector<Entity*> EntityManager::GetEntities() const
{
	return entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const
{
	std::vector<Entity*> selectedEntities;
	for (auto& entity : entities)
	{
		if (entity->layer == layer)
		{
			selectedEntities.emplace_back(entity);
		}
	}
	return selectedEntities;
}

void EntityManager::ListAllEntities() const
{
	unsigned int i = 0;
	for (auto& entity : entities)
	{
		std::cout << "Entity[" << i << "]: " << entity->name << std::endl;
		entity->ListAllComponents();
		i++;
	}
}

CollisionType EntityManager::CheckCollisions() const
{
	for (int i = 0; i < entities.size() - 1; i++)
	{
		auto& thisEntity = entities[i];
		if (thisEntity->HasComponent<ColliderComponent>())
		{
			ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();
			for (int j = i + 1; j < entities.size(); j++)
			{
				auto& thatEntity = entities[j];
				if (thisEntity->name.compare(thatEntity->name) != 0 && thatEntity->HasComponent<ColliderComponent>())
				{
					ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>();
					if (Collision::CheckRectangleCollision(thisCollider->collider, thatCollider->collider))
					{
						if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("ENEMY") == 0)
						{
							return PLAYER_ENEMY_COLLISION;
						}
						if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("PROJECTILE") == 0)
						{
							return PLAYER_PROJECTILE_COLLISION;
						}
						if (thisCollider->colliderTag.compare("ENEMY") == 0 && thatCollider->colliderTag.compare("COIN") == 0)
						{
							thatEntity->GetComponent<TransformComponent>()->position = (glm::vec2(Game::ReturnRandomInt(0, PLAY_AREA_MAX_X), Game::ReturnRandomInt(0, PLAY_AREA_MAX_Y)));
							return ENEMY_COIN_COLLISION;
						}
						if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("DROPOFF") == 0)
						{
							return PLAYER_DROPOFF_COLLISION;
						}
						if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("OBSTACLE") == 0)
						{
							return PLAYER_OBSTACLE_COLLISION;
						}
						if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("COIN") == 0)
						{
								//Swaping the entity position for another random position on the map
								thatEntity->GetComponent<TransformComponent>()->position = (glm::vec2(Game::ReturnRandomInt(0, PLAY_AREA_MAX_X), Game::ReturnRandomInt(0, PLAY_AREA_MAX_Y)));
								return PLAYER_COIN_COLLISION;
						}
					}
				}
			}
		}
	}
	return NO_COLLISION;
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer)
{
	Entity *entity = new Entity(*this, entityName, layer);
	entities.emplace_back(entity);
	return *entity;
}
