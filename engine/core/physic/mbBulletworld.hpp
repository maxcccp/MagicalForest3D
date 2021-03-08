#ifndef BULLETWORLD_HPP
#define BULLETWORLD_HPP

#include <bullet/btBulletDynamicsCommon.h>

#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../material/mbMaterial.hpp"

#include <list>


enum RigidBodyTags {
	PLAYER,
	OBSTACLE,
	FLOOR,
	MISC
};


struct RigidBodyTagMaterial {
	btRigidBody* body;
	unsigned short tag;
	Material m_Material;

	/* 
	RigidBodyTagMaterial(){}
	RigidBodyTagMaterial(const RigidBodyTagMaterial &rbtm){}
	*/
};



class BulletWorld
{


public:

	BulletWorld(glm::vec3 gravity);
	~BulletWorld();

	std::list<RigidBodyTagMaterial*> getBodies(){return bodies;}
	btDiscreteDynamicsWorld* getWorld(){return world;}
	void setBodiesList(std::list<RigidBodyTagMaterial*>& bodylist){bodies = bodylist;}

	void addBody(RigidBodyTagMaterial* rbtm);

	btRigidBody* addFloor(glm::vec3 origin_location, glm::vec3 floor_normal, float plane_constant, Material mat);
	btRigidBody* addSphere(float rad, float x, float y, float z, float mass,Material spheremat,int sphereTag=MISC);
	btRigidBody* addBox(float width, float height, float depth, float x, float y, float z, float mass, Material mat, int boxTag=MISC);

	void addFloor(Material& mat, float z);
	void updateFloor(Material& mat, float z);

	void stepSimulate(){world->stepSimulation(btScalar(1 / 60.0));}

private:
	btDiscreteDynamicsWorld* world;
	btDispatcher* dispatcher;
	btCollisionConfiguration* collisionConfig;		// какой алгоритм столкновения использовать?
	btBroadphaseInterface* broadphase;				// должен ли Bullet исследовать каждый объект или просто то, что близко друг к другу
	btConstraintSolver* solver;						// решать столкновения, применять силы, импульсы

													// вектор для хранения всех твердых тел
	std::list<RigidBodyTagMaterial*> bodies;

};

#endif