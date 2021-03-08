#include "mbCollisionShape.hpp"

#include <iostream>





using namespace glm;





// count body objects
unsigned short mb::phys::mbCollisionShape::m_countBody = 0;

// Diclaration function
btRigidBody* CreateBoxShape(glm::vec3 _originlocation, glm::vec3 _volome, float _mass=1.0f);
btRigidBody* CreateSphere(float red = 10.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f, float mas = 1.0f);
btRigidBody* CreateStaticPlane(glm::vec3 _originlocation, glm::vec3 _volome, float _mass = 0.0f, float planeconstant = 2.5f);







//.............
// Constructor
//.............
mb::phys::mbCollisionShape::mbCollisionShape(COLLISION_SHAPE _collisionType, glm::vec3 _location, glm::vec3 _amount, float _mass, float _radius)
{
	this->m_pBody = nullptr;
	this->m_mat4GraphicsModel = nullptr;
	
	// sample shape
	switch (_collisionType)
	{
	case phys::CAPSULA:
		m_countBody++;
		break;
	case phys::BOX:
		if (!m_pBody) {
			m_pBody = CreateBoxShape(_location, _amount, _mass);
	
			mbPhysicsWorld::GET_THIS()->GetDynamicWorld()->addRigidBody(m_pBody);
			
			m_countBody++;
		}
		break;
	case phys::SPHERE:
		if (!m_pBody) {
			m_pBody = CreateSphere(_radius, _location.x, _location.y, _location.z, _mass);
			mbPhysicsWorld::GET_THIS()->GetDynamicWorld()->addRigidBody(m_pBody);
		
			m_countBody++;
		}
		break;
	case phys::PLANE:
		if (!m_pBody) {
			m_pBody = CreateStaticPlane(_location, _amount,_mass);
			mbPhysicsWorld::GET_THIS()->GetDynamicWorld()->addRigidBody(m_pBody);

			m_countBody++;
		}
		break;
	default:
		std::cout << "*The body has already been created!" << std::endl;
		break;
	}


}


//............
// Distructor
//............
mb::phys::mbCollisionShape::~mbCollisionShape()
{
}


//..............
//GraphicObject
//..............
void mb::phys::mbCollisionShape::Drow(glm::mat4& _matModel)
{
	
	// получить значени€ значение оболочки
	btDefaultMotionState* BodyMotionState = (btDefaultMotionState*)m_pBody->getMotionState();

	// gl matrix
	BodyMotionState->m_graphicsWorldTrans.getOpenGLMatrix((btScalar*)&_matModel);
}



//...........
// MoveShape
//...........
void  mb::phys::mbCollisionShape::MoveShape(float _x, float _y, float _z)
{
	m_pBody->setActivationState(1);
	btTransform initialTransform1;

	
	initialTransform1 = m_pBody->getCenterOfMassTransform();
	initialTransform1.setOrigin(btVector3 (_x, _y, _z));
	m_pBody->setCenterOfMassTransform(initialTransform1);
	
	//альтернатива
	//m_pBody->applyCentralImpulse(btVector3(_x, _y, _z));
	
}




//...................
// CreateBoxShape
//...................
btRigidBody* CreateBoxShape(glm::vec3 _originlocation, glm::vec3 _volome, float _mass)
{
	btCollisionShape* BoxShape = new btBoxShape(btVector3(_volome.x, _volome.y, _volome.z));
	// btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),50);
	
	
	btVector3 localInertia(0, 0, 0);
	if (_mass != 0.0)
		BoxShape->calculateLocalInertia(_mass, localInertia);

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(_originlocation.x, _originlocation.y, _originlocation.z));

	btDefaultMotionState* myMotionState = new btDefaultMotionState(transform); //motionstate предоставл€ет возможности интерпол€ции и только синхронизирует Ђактивныеї объекты
	btRigidBody::btRigidBodyConstructionInfo RigidBoxInfo(_mass, myMotionState, BoxShape, localInertia);
	
	btRigidBody* pBoxBody = new btRigidBody(RigidBoxInfo);

	return pBoxBody;
}


//...................
// CreateSphereShape
//...................
btRigidBody* CreateSphere(float red, float x, float y, float z, float _mas)
{
	// создадим плоскость заземлени€ [статическое твердое тело]
	btSphereShape* sphere = new btSphereShape(red);
	

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(x, y, z));
	btDefaultMotionState* sphereMotionState = new btDefaultMotionState(btTransform(btQuaternion(x, y, z), btVector3(0, -1, 0)));
	//btDefaultMotionState* sphereMotionState = new btDefaultMotionState(transform);
	
	btVector3 inercia(0, 0, 0);
	if (_mas != 0.0f)
		sphere->calculateLocalInertia(_mas, inercia);

	btRigidBody::btRigidBodyConstructionInfo RigidBodySphereInfo(_mas, sphereMotionState, sphere, inercia);

	btRigidBody* body = new btRigidBody(RigidBodySphereInfo);

	//bodys.push_back( sphereRigidBody );
	return  body;
}


//......................
// —оздание пола(земли)
//......................
btRigidBody* CreateStaticPlane(glm::vec3 _originlocation, glm::vec3 _volome, float _mass, float planeconstant)
{
	
	//btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(0.0, 1.0, 0.0), (btScalar)2.5);
	btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(_volome.x, _volome.y, _volome.z), (btScalar)planeconstant);
	
	btVector3 inertia(0, 0, 0);							// инерци€ составл€ет 0,0,0 дл€ статического объекта, иначе
		
	if (_mass != 0.0)
		plane->calculateLocalInertia(_mass, inertia);	// это может быть определено этой функцией (дл€ всех видов фигур)

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(_originlocation.x, _originlocation.y, _originlocation.z));
	btMotionState* motion = new btDefaultMotionState(t);

	btRigidBody::btRigidBodyConstructionInfo RigidBodyPlaneInfo(_mass, motion, plane, inertia);

	btRigidBody* pStaticPlane = new btRigidBody(RigidBodyPlaneInfo);

	return pStaticPlane;
}





