#include "VertexArray.hpp"

#include <glad/glad.h>
#include <iostream>

namespace engine::gl
{
    VertexArray::VertexArray()
        : m_VAO(0), m_VBO(0), m_IndicesSize(0)
    {}

    VertexArray::VertexArray(std::vector<Vertex>& vertices, std::vector<uint>& indices)
        : m_IndicesSize(indices.size())
	{
        // create buffers/arrays
        glGenVertexArrays(1, &m_VAO);

        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindVertexArray(m_VAO);
        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_UV));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndicesSize * sizeof(uint), &indices[0], GL_STATIC_DRAW);

        glBindVertexArray(0);
	}

    VertexArray::~VertexArray()
	{
        if (m_VAO != 0)
        {
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteBuffers(1, &m_VBO);
            glDeleteBuffers(1, &m_EBO);
            m_VAO = 0;
            m_VBO = 0;
            m_EBO = 0;
        }
	}

	void VertexArray::render()
	{
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_IndicesSize, GL_UNSIGNED_INT, 0);
	}

    void VertexArray::unbind()
    {
        glBindVertexArray(0);
    }
}
