#ifndef MB_PROGRAMMER3D_BUFFER_HPP__
#define MB_PROGRAMMER3D_BUFFER_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/


#include <vector>

#include "../model/mbMesh.hpp"
#include "../../common/mbType.hpp"


namespace MBG
{

	class mbBuffer
	{
	public:
		mbBuffer();
		virtual ~mbBuffer();

		void CreateVertexBuffer(Vertex* vertices, unsigned int* indices = nullptr);
		void CreateVertexBuffer(std::vector<Vertex> vertices, std::vector<unsigned int> indices = std::vector<unsigned int>(0));

		void SetAttribPosition(const unsigned int& _position=mbPOSITION_ATTRIBUTE);
		void SetAttribNormal(const unsigned int& _normal=mbNORMAL_ATTRIBUTE);
		void SetAttribTexCoord(const unsigned int& _texCoord=mbTEXTURECOORD_ATTRIBUTE);
		void SetAttribTangent(const unsigned int& _Tangent=mbTANGENT_ATTRIBUTE);
		void SetAttribBiTangent(const unsigned int& _biTangent=mbBITANGENT_ATTRIBUTE);

		void DeleteBuffer()const;
		void BindVertexArrray()const;
		void UnBindVertexArray()const;

		inline const unsigned int GetVertexBufferID() const{ return m_vao; }
		inline const bool GetDidDataAnloaded() const{ return m_data_anloaded; }

	protected:
	private:
		bool m_data_anloaded;
		unsigned int m_vao;
		unsigned int m_vbo;
		unsigned int m_ebo;

		std::vector<unsigned int>	m_indices;
		std::vector<Vertex>			m_vertices;

	};


}
#endif
