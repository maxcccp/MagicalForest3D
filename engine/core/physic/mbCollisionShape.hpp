#ifndef __MB_COLLISIONSHAPE_HPP__
#define __MB_COLLISIONSHAPE_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/


#include "mbPhysicsWorld.hpp"





namespace mb
{

	namespace phys
	{
		enum COLLISION_SHAPE { CAPSULA, BOX, SPHERE, PLANE };


		class mbCollisionShape
		{
		public:
			mbCollisionShape(COLLISION_SHAPE _collisionType, glm::vec3 _originlocation, glm::vec3 _volume, float _mass = 0.0f, float _radius = 5.0f);
			virtual ~mbCollisionShape();

			void Drow(glm::mat4& _matModel);
			void MoveShape(float _x, float _y = 0.0f, float _z = 0.0f);

			btRigidBody* GetBody() { return m_pBody; }
			static const unsigned short GetCountBody() { return m_countBody; }
		private:

			btRigidBody*			m_pBody;
			static unsigned short	m_countBody;
			glm::mat4*				m_mat4GraphicsModel;

		};


	}
}
#endif//__MB_COLLISIONSHAPE_HPP__