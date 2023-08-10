#ifndef QUB3D_SHADER_H
#define QUB3D_SHADER_H

#include <glad.h>
#include <linmath.h>

GLuint build_shader_program(const char* vert_src, const char* frag_src, const char* name);

void set_matrix4fv_uniform(GLuint shader, const char* name, const mat4x4 mat) {
	const GLint location = glGetUniformLocation(shader, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}

#endif // QUB3D_SHADER_H