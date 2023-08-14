#include "shader.h"
#include <stdio.h>
#include <stdlib.h>

namespace qub3d
{
	GLuint build_shader(const char* vert_src, const char* frag_src, const char* name)
	{
		GLuint vert = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vert, 1, &vert_src, 0);
		glCompileShader(vert);

		#ifdef QUB3D_DEBUG
			int success;
			char info[1024];

			glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(vert, 1024, nullptr, info);
				printf("Vertex shader %s info:\n%s\n%s", name, vert_src, info);
				exit(-1);
			}
		#endif

		GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(frag, 1, &frag_src, 0);
		glCompileShader(frag);

		#ifdef QUB3D_DEBUG
			glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(frag, 1024, nullptr, info);
				printf("Fragment shader %s info:\n%s\n%s", name, frag_src, info);
				exit(-1);
			}
		#endif

		GLuint shader = glCreateProgram();
		glAttachShader(shader, vert);
		glAttachShader(shader, frag);
		glLinkProgram(shader);

		#ifdef QUB3D_DEBUG
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, nullptr, info);
				printf("Shader %s info:\n%s", name, info);
				exit(-1);
			}
		#endif

		// Shaders were copied and linked together in program.
		// We don't need them anymore.
		glDeleteShader(vert);
		glDeleteShader(frag);

		return shader;
	}

	void set_shader_mat4(GLuint shader, const mat4x4 mat, const char* name)
	{
		const GLint location = glGetUniformLocation(shader, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
	}
}