#include "mbPhysicsWorld.hpp"

#include <iostream>



using namespace glm;






// static pointer class
mb::phys::mbPhysicsWorld* mb::phys::mbPhysicsWorld::m_thisClass = nullptr;



//.............
// Constructor
//.............
mb::phys::mbPhysicsWorld::mbPhysicsWorld(const glm::vec3& setGravity )
{
	if (m_thisClass == nullptr)
	{
		m_thisClass = this;
		m_collisionConfiguration = new btDefaultCollisionConfiguration(); // ������������ ������������ �������� ��������� �� ��������� ��� ������, ��������� ������������
		m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration); //������������ ��������� ������������ �� ���������
		m_broadphase = new btDbvtBroadphase();
		m_solver = new btSequentialImpulseConstraintSolver; // �������� ����������� �� ���������
		m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
		m_dynamicsWorld->setGravity(btVector3(setGravity.x, setGravity.y, setGravity.z));
		m_dynamicsWorld->getSolverInfo().m_splitImpulse = true;
	}
	else
		std::cout << "Warning: class PhysicsWorls has already been created* \n" << std::endl;
}




//............
// Distructor
//............
mb::phys::mbPhysicsWorld::~mbPhysicsWorld()
{
	if (m_thisClass != nullptr)
	{

		//�������� � �������� ������� �������� / �������������
		for (int i = m_dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--) // ������� ������� ���� �� ���� �������� � ������� ��
		{
			btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
				delete body->getMotionState();

			m_dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}


		for (int j = 0; j < m_collisionShapes.size(); j++) //������� ������������ �����
		{
			btCollisionShape* shape = m_collisionShapes[j];
			delete shape;
		}

		m_collisionShapes.clear();
		delete m_dynamicsWorld;
		delete m_solver;
		delete m_broadphase;
		delete m_dispatcher;
		delete m_collisionConfiguration;
	}
	
}



//............
// SetGravite
//............
void mb::phys::mbPhysicsWorld::SetGravite(const glm::vec3& setGravity)
{
	m_dynamicsWorld->setGravity(btVector3(setGravity.x, setGravity.y, setGravity.z));
}


//.............
// StepPhysics
//.............
void mb::phys::mbPhysicsWorld::UpdatePhysics(float stepFrame)
{
	//��� ������ �����, ����� ��������� ���������.
	if (this->m_dynamicsWorld) 
		this->m_dynamicsWorld->stepSimulation(1.0f / stepFrame);
}













