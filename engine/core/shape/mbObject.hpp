#ifndef MB_PROGRAMMER3D_OBJECT_HPP__
#define MB_PROGRAMMER3D_OBJECT_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/


#include <glm/glm.hpp>
#include "../buffer/mbBuffer.hpp"
#include "../texture/mbImage.hpp"
#include "../shader/mbShader.hpp"

namespace MBG
{

	// base
	class mbObject
	{
	public:
		mbObject(const std::string& TexturePath, const glm::vec3& position);
		virtual ~mbObject();
		virtual void claculateTangentBitangent(std::vector<Vertex>& vertex);
		virtual void Draw( mbShader& _shader) = 0;
		inline const glm::mat4& GetMatrixModel() const { return m_model; }
	protected:
		glm::mat4 m_model;
		mbBuffer m_buffer;
		std::string m_texture_path;
		mbImage m_deffuse_map;
		mbImage m_normal_map;
		mbImage m_specular_map;

	};

	// Plane
	class mbPlaneObj
		: public mbObject
	{
	public:
		mbPlaneObj(const std::string& TexturePath,const glm::vec3& position);
		virtual ~mbPlaneObj();

		void Draw( mbShader& _shader);

	};



	// Cube
	class mbCube
		: public mbObject
	{
	public:
		mbCube(const std::string& TexturePath, const glm::vec3& position);
		virtual ~mbCube();

		void Draw( mbShader& _shader);

	};
}
#endif
