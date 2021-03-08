#ifndef __MB_PHYSICS_WORLD_HPP__
#define __MB_PHYSICS_WORLD_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/

// glm
#include <glm/glm.hpp>
// bt
#include <bullet/btBulletDynamicsCommon.h>


#if defined NDEBUG & defined _MSC_VER

#pragma comment(lib,"BulletCollision.lib")
#pragma comment(lib,"BulletDynamics.lib")
#pragma comment(lib,"LinearMath.lib")
#endif



namespace mb
{
	namespace phys
	{
		class mbPhysicsWorld
		{
		public:
			mbPhysicsWorld(const glm::vec3& setGravity = glm::vec3(0.0f, -50.0f, 0.0f));
			virtual ~mbPhysicsWorld();

			void SetGravite(const glm::vec3& setGravity);
			void UpdatePhysics(float stepFrame = 60.0f);

			static const  mbPhysicsWorld* GET_THIS() { return m_thisClass; }
			btDynamicsWorld*  GetDynamicWorld()const { return m_dynamicsWorld; }
		private:
			// bullet physics API
			btAlignedObjectArray<btCollisionShape*>	m_collisionShapes;			// сохранить формы столкновения, для удаления / очистки
			btBroadphaseInterface*					m_broadphase;
			btCollisionDispatcher*					m_dispatcher;
			btConstraintSolver*						m_solver;
			btDefaultCollisionConfiguration*		m_collisionConfiguration;
			btDynamicsWorld*						m_dynamicsWorld;			// это самый важный класс

			static mbPhysicsWorld* m_thisClass;
		};

	}
}
#endif//__MB_PHYSICS_WORLD_HPP__