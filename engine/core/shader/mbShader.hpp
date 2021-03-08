#ifndef MB_PROGRAMMER3D_SHADER_HPP
#define MB_PROGRAMMER3D_SHADER_HPP
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/


#include <map>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define mbGLSL_1_5(src) "#version 150 core\n" # src
#define mbGLSL_2_0(src) "#version 200 core\n" # src
#define mbGLSL_2_1(src) "#version 210 core\n" # src
#define mbGLSL_3_0(src) "#version 300 core\n" # src
#define mbGLSL_3_1(src) "#version 310 core\n" # src
#define mbGLSL_3_2(src) "#version 320 core\n" # src
#define mbGLSL_3_3(src) "#version 330 core\n" # src
#define mbGLSL_4_0(src) "#version 400 core\n" # src
#define mbGLSL_4_1(src) "#version 410 core\n" # src
#define mbGLSL_4_2(src) "#version 420 core\n" # src
#define mbGLSL_4_3(src) "#version 430 core\n" # src
#define mbGLSL_4_4(src) "#version 440 core\n" # src
#define mbGLSL_4_5(src) "#version 450 core\n" # src
#define mbGLSL_4_6(src) "#version 460 core\n" # src



namespace MBG
{

	enum MB_TYPE_SHADER
		{
			VERTEX_SHADER,
			FRAGMENT_SHADER,
			TESSELATION_CONTROL,
			TESSELATION_EVAL,
			GEOMETRY_SHADER,
			MAX_SHADERS
		};

	enum MB_ATTRIBUTE_SHADER
		{
			mbPOSITION_ATTRIBUTE = 0,
			mbNORMAL_ATTRIBUTE,
			mbTEXTURECOORD_ATTRIBUTE,
			mbTANGENT_ATTRIBUTE,
			mbBITANGENT_ATTRIBUTE
		};



	class mbShader
	{
	public:
		mbShader();
		virtual ~mbShader();

		void Loading(const std::string& nameShader);
		void LoadDetal(const std::string& vs, const std::string& gs = "", const std::string& fs = "");


		void Use();
		void UnUse();
		void Update();
		void PrintDebug();
		void LinkProgram();
		void DeleteShaderProgram();

		void SetUniform(const std::string &name, bool value) const;
		void SetUniform(const std::string &name, int value) const;
		void SetUniform(const std::string &name, float value) const;
		void SetUniform(const std::string &name, const glm::vec2 &value) const;
		void SetUniform(const std::string &name, float x, float y) const;
		void SetUniform(const std::string &name, const glm::vec3 &value) const;
		void SetUniform(const std::string &name, float x, float y, float z) const;
		void SetUniform(const std::string &name, const glm::vec4 &value) const;
		void SetUniform(const std::string &name, float x, float y, float z, float w);
		void SetUniform(const std::string &name, const glm::mat2 &mat) const;
		void SetUniform(const std::string &name, const glm::mat3 &mat) const;
		void SetUniform(const std::string &name, const glm::mat4 &mat) const;


		void SetAttributeVertexInt(const std::string& name, int sizePoint, int stride = 0, const void* pointer = 0);
		void SetAttributeVertexFloat(const std::string& name, int sizePoint, int stride = 0, const void* pointer = 0);

		inline const unsigned int& GetProgamID() const { return m_Program; }
		inline const unsigned int& GetVertexShaderID()	const { return m_VertxShader; }
		inline const unsigned int& GetFragmentShaderID() const { return m_FragmentShader; }
		inline const unsigned int& GetGeometryShaderID() const { return m_GeometriShader; }

		void operator =(const mbShader&);

	private:

		unsigned int m_Shader[MAX_SHADERS];

		unsigned int m_VertxShader;
		unsigned int m_FragmentShader;
		unsigned int m_GeometriShader;
		unsigned int m_Program;

		std::string m_nameShader;
	};




	typedef std::vector<mbShader>	BufferShader;
	typedef std::vector<mbShader*>	pBufferShader;

}
#endif
