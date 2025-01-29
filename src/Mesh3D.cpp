#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "../include/glad/glad.h"
#include "../include/Mesh3D.hpp"


void Mesh3D::create_mesh(std::vector<GLfloat> vertex_data)
{
    /*
    // -> data de vértices: xyz normalizados [-1, 1] y rgb normalizados [0, 1]
    vertex_data = {
        // -> 0 - vértice 1
        -0.7f, -0.7f, 0.0f, // -> v inferior izquierdo
            0.0f, 1.0f, 1.0f,   // -> rgb
                                // -> 1 - vértice 2
            0.7f, -0.7f, 0.0f,  // -> v inferior derecho
            1.0f, 0.0f, 1.0f,   // -> rgb
                                // -> 2 - vértice 3
            0.7f, 0.7f, 0.0f,   // -> v superior derecho
            0.0f, 1.0f, 1.0f,   // -> rgb
                                // -> 3 - vértice 4
            -0.7f, 0.7f, 0.0f,  // -> v superior izquierdo
            1.0f, 0.0f, 1.0f,   // -> rgb

    };
    */
    
    m_vertex_data = vertex_data;

    // -> crear VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // -> crear VBO
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(
            GL_ARRAY_BUFFER, 
            sizeof(GLfloat) * m_vertex_data.size(), 
            m_vertex_data.data(), 
            GL_STATIC_DRAW
    );

    // -> especificar atributos de vértices
    glEnableVertexAttribArray(0);                  // -> habilita el atributo de vértice 0 (posición)
    glVertexAttribPointer(
            0, // -> atributo de vértice 0
            3, // -> 3 componentes de posición (xyz)
            GL_FLOAT,            // > tipo de dato
            GL_FALSE,            // -> normalizar
            sizeof(GLfloat) * 6, // -> stride
            0                    // -> offset
    );

    glEnableVertexAttribArray(1); // -> habilita el atributo de vértice 1 (color)
    glVertexAttribPointer(
            1,                   // -> atributo de vértice 1
            3,                   // -> 3 componentes de color (rgb)
            GL_FLOAT,            // -> tipo de dato
            GL_FALSE,            // -> normalizar
            sizeof(GLfloat) * 6, // -> stride
            (GLvoid *)(sizeof(GLfloat) * 3) // -> offset (rgb empieza en la posición 3)
    );

    // -> crear IBO / EBO
    m_index_data = {0, 1, 3, 3, 2, 1};

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER, 
            sizeof(GLuint) * m_index_data.size(),
            m_index_data.data(), 
            GL_STATIC_DRAW
    );

    // -> limpiar
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

}

void Mesh3D::translate(float x, float y, float z)
{
    m_model_matrix = glm::translate(m_model_matrix, glm::vec3(x, y, z));
}

void Mesh3D::rotate(float angle, glm::vec3 axis)
{
    m_model_matrix = glm::rotate(m_model_matrix, glm::radians(angle), axis);
}

void Mesh3D::scale(float x, float y, float z)
{
    m_model_matrix = glm::scale(m_model_matrix, glm::vec3(x, y, z));
}

glm::mat4 Mesh3D::get_model_matrix()
{
    return m_model_matrix;
}

Mesh3D::~Mesh3D()
{
    std::cout << "Liberando recursos de Mesh3D" << std::endl;

    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}
