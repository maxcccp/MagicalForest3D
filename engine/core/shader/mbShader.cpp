#include "mbShader.hpp"

#include <GL/glew.h>

#include <fstream>
#include <iostream>




using namespace std;






/*......................................................................................................*/
/*=======================================  SECONDARY FUNCTION ========================================= */
/*......................................................................................................*/

// � 1.0 ��������������� �������

/*
*  ������ ���� �������
*/
std::string LoadShaderFile(const std::string& fileName)
{
	// ������� ����� ����
	std::ifstream file;
	file.open(fileName.c_str());

	// ��������� ���� ����� ���������
	std::string output;
	std::string line;

	// ������ ����
	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
		std::cout << "Unable to load shader: " << fileName << std::endl;

	return output;
}


/*
*	�������� �� ������� � �������
*/
void ShaderError(unsigned int shader, unsigned int flag, bool isProgram, const std::string& message)
{
	int success = 0;
	char error[1024] = { 0 };
	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE) {
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << "Error: " << error << std::endl;
	}
}


/*
*	������� �������
*/
unsigned int CreateShader(const std::string& text, unsigned int type)
{
	unsigned int shader = glCreateShader(type);

	if (shader == 0)
		std::cerr << "Error compiling shader type " << type << std::endl;

	const char* p[1];
	p[0] = text.c_str();
	int lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	ShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}


void  MBG::mbShader::PrintDebug()
{
#ifdef __cplusplus
	cout << "\nInformation-Shader: " << m_nameShader << "\nProgramShaderID: " << m_Program << "\nVertexShaderID: " << m_VertxShader << "\nFragmentShaderID: " << m_FragmentShader << endl;
#else
	printf("\nInformation-Shader: \nProgramShader: %d\nVertexShader: %d\nFragmentShader: %d\n", m_Program, m_VertxShader, m_FragmentShader);
#endif
}




// � 1.1 ������� ������



/*
*	�����������
*/
MBG::mbShader::mbShader()
{

	m_VertxShader = 0;
	m_FragmentShader = 0;
	m_GeometriShader = 0;
	m_Program = 0;

}



/*
*  ����������
*/
MBG::mbShader::~mbShader()
{
	glDeleteProgram(m_Program);
}



/*
*  ���������� ��������� ��������� ��� ������������ ����
*/
void MBG::mbShader::Update()
{
	// ������� ������� ������ ���������
	DeleteShaderProgram();

	// �������� ����� ��������� � ��������� ����� ��������
	m_Program = glCreateProgram();
	m_VertxShader = CreateShader(LoadShaderFile(m_nameShader + ".vs"), GL_VERTEX_SHADER);
	m_FragmentShader = CreateShader(LoadShaderFile(m_nameShader + ".fs"), GL_FRAGMENT_SHADER);

	// ��������� ������� � ����������
	glAttachShader(m_Program, m_VertxShader);
	glAttachShader(m_Program, m_FragmentShader);



	// ������� ��������
	glLinkProgram(m_Program);
	ShaderError(m_Program, GL_LINK_STATUS, true, "Error linking shader program");

	// ��������� ���������� ���������
	glValidateProgram(m_Program);
	ShaderError(m_Program, GL_LINK_STATUS, true, "Invalid shader program");


	PrintDebug();

	glDeleteShader(m_VertxShader);
	glDeleteShader(m_FragmentShader);
	m_VertxShader = 0;
	m_FragmentShader = 0;




}






/*
*  �������� ������� �� ����� 1
*/
void MBG::mbShader::Loading(const string & nameShader)
{

	// �������� �������� ���� ������ ���������� ������ ������
	m_nameShader.insert(0, nameShader);


	m_Program = glCreateProgram();
	m_VertxShader = CreateShader(LoadShaderFile(nameShader + ".vs"), GL_VERTEX_SHADER);
	m_FragmentShader = CreateShader(LoadShaderFile(nameShader + ".fs"), GL_FRAGMENT_SHADER);




	// ��������� ������� � ����������
	glAttachShader(m_Program, m_VertxShader);
	glAttachShader(m_Program, m_FragmentShader);

	// ������� ��������
	glLinkProgram(m_Program);
	ShaderError(m_Program, GL_LINK_STATUS, true, "Error linking shader program");

	// ��������� ���������� ���������
	glValidateProgram(m_Program);
	ShaderError(m_Program, GL_LINK_STATUS, true, "Invalid shader program");

	// information shader to console
	PrintDebug();



	glDeleteShader(m_VertxShader);
	glDeleteShader(m_FragmentShader);
	m_VertxShader = 0;
	m_FragmentShader = 0;


}


/*
*  �������� ������� �� ����� 2
*/
void MBG::mbShader::LoadDetal(const string& vs, const string& gs, const string& fs)
{

	m_VertxShader = CreateShader(LoadShaderFile(vs), GL_VERTEX_SHADER);
	if(!gs.empty() && gs!="")
		m_GeometriShader = CreateShader(LoadShaderFile(gs), GL_GEOMETRY_SHADER);
	if (!fs.empty() && fs != "")
		m_FragmentShader = CreateShader(LoadShaderFile(fs), GL_FRAGMENT_SHADER);
	else
		m_FragmentShader = 0;

	m_Program = glCreateProgram();

	// �������� �������� ���� ������ ���������� ������ ������
	m_nameShader.insert(0, vs);
	cout << "Loading-Shader: " << m_nameShader << endl;
	printf("ProgramShaderID: %d\nVertexShaderID: %d\nGeometryShaderID: %d\nFragmentShaderID: %d\n", m_Program, m_VertxShader, m_GeometriShader, m_FragmentShader);
}




/*
*  �������� ��������� ��������� �������������
*/
void MBG::mbShader::DeleteShaderProgram()
{

	// ������ ������ ��������� ���� ID �� ����� ����(0)
	if (this->m_Program != 0) {
		// ����� ��� ��� ������� ����������� ������ �� �������� ����������
		glUseProgram(0);
		// � ����� ������ ������� ��������� ��������
		glDeleteProgram(this->m_Program);
		// ��������� ������� ��������
		this->m_Program = 0;
	}

}

/////////////////////////////////////////////////////////////////////////
// �������� ��� �������� ������� � ���� ��������� ��� ���������� �� GPU
void MBG::mbShader::LinkProgram()
{
	// ��������� ������� � ����������
	if (m_VertxShader)
		glAttachShader(m_Program, m_VertxShader);
	if (m_GeometriShader)
		glAttachShader(m_Program, m_GeometriShader);
	if (m_FragmentShader)
		glAttachShader(m_Program, m_FragmentShader);

	// ������� ��������
	glLinkProgram(m_Program);
	ShaderError(m_Program, GL_LINK_STATUS, true, "Error linking shader program");

	// ��������� ���������� ���������
	glValidateProgram(m_Program);
	ShaderError(m_Program, GL_LINK_STATUS, true, "Invalid shader program");

	// ������� ������ ��� ��� �� �� ��������� � ��� ��� ��� ��� ��� �� GPU
	if (m_VertxShader)
		glDeleteShader(m_VertxShader);
	if (m_FragmentShader)
		glDeleteShader(m_FragmentShader);
	if (m_GeometriShader)
		glDeleteShader(m_GeometriShader);
	m_VertxShader = m_FragmentShader = m_GeometriShader = 0;
}

/*
*  ����� ��������� �������
*/
void MBG::mbShader::Use()
{
	glUseProgram(m_Program);
}



/*
* �������� ��������� ��������
*/
void MBG::mbShader::UnUse()
{
	glUseProgram(0);
}




/*
* �������� ������������
*/
void MBG::mbShader::operator=(const mbShader& obj)
{
	this->m_FragmentShader = obj.m_FragmentShader;
	this->m_GeometriShader = obj.m_GeometriShader;
	this->m_VertxShader = obj.m_VertxShader;
	this->m_Program = obj.m_Program;

}




void MBG::mbShader::SetUniform(const string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_Program, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void MBG::mbShader::SetUniform(const string &name, int value) const
{
	glUniform1i(glGetUniformLocation(m_Program, name.c_str()), value);
}
// ------------------------------------------------------------------------
void MBG::mbShader::SetUniform(const string &name, float value) const
{
	glUniform1f(glGetUniformLocation(m_Program, name.c_str()), value);
}
// ------------------------------------------------------------------------
void MBG::mbShader::SetUniform(const string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(m_Program, name.c_str()), 1, &value[0]);
}
void MBG::mbShader::SetUniform(const string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(m_Program, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void MBG::mbShader::SetUniform(const string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(m_Program, name.c_str()), 1, &value[0]);
}

void MBG::mbShader::SetUniform(const string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(m_Program, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void MBG::mbShader::SetUniform(const string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(m_Program, name.c_str()), 1, &value[0]);
}
void MBG::mbShader::SetUniform(const string &name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(m_Program, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void MBG::mbShader::SetUniform(const string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(m_Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void MBG::mbShader::SetUniform(const string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(m_Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void MBG::mbShader::SetUniform(const string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


/* SetAttributeVertexInt */
void MBG::mbShader::SetAttributeVertexInt(const string & name, int sizePoint, int stride, const void * pointer)
{
	/* �������� ����������� � 0 ��� ������ � c\c++*/
	int AttribLoc = glGetAttribLocation(m_Program, name.c_str());

	glEnableVertexAttribArray(AttribLoc);
	glVertexAttribPointer(AttribLoc, sizePoint, GL_INT, GL_FALSE, stride, pointer);
	cout << "attribute: " << AttribLoc << endl;

	if (AttribLoc < 0)
		cout << "Error attribute: " << name << endl;

}


/* SetAttributeVertexFloat */
void MBG::mbShader::SetAttributeVertexFloat(const std::string& name, int sizePoint, int stride, const void* pointer)
{
	/* �������� ����������� � 0 ��� ������ � c\c++*/
	int AttribLoc = glGetAttribLocation(m_Program, name.c_str());

	glEnableVertexAttribArray(AttribLoc);
	glVertexAttribPointer(AttribLoc, sizePoint, GL_FLOAT, GL_FALSE, stride, pointer);

	if (AttribLoc < 0)
		cout << "Error attribute: " << name << endl;

}










