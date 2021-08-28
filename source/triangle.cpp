#pragma once

#include "../GL/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//                              Criando o nosso primeiro Triângulo!
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Alguns pontos importantes: Tenha configurado sua Janela, e tenha entendido sobre a criação
//  O conteúdo foi inspirado e estudado no site: https://learnopengl.com/Getting-started/Hello-Triangle
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////
//                                          Shaders e Graphics Pipeline 
//
//  Antes de começarmos, precisamos saber o que iremos fazer
//  Então irei dar uma breve resumida em alguns pontos importantes, porém recomendo estudar mais no site proprosto no topo do Header
//
//  Na computação, possuimos um processo muito importante para nós renderizarmos alugum objeto
//  O nome deste processo se chama "Graphics Pipeline"
//  Graphics Pipeline é um conceito que descreve cada etapa que teremos de fazer para renderizar algum objeto em nossa cena.
//
//  No Graphics Pipeline, possuimos 7 etapas para nós renderizarmos um objeto
//  Essas 6 etapas são:
//  VertexData -> Vertex Shader -> Shape Assembly -> Geometry Shader -> Rasterization -> Fragment Shader e Tests and Blending
//
//  A VertexData é o processo inicial, que é quando nós iniciamos nossas vértices e setamos suas posições em um Array
//  A VertexShader irá processar as nossas vértices e enviar para os outros processos de Shader(como ShapeAssembly e FragmentShader)
//  A ShapeAssembly irá ligar as nossas vértices que foram enviadas pela VertexShader para formar a nossa forma geométrica
//  A Rasterization é um processo de rasterizar a nossa forma geométrica e projetar ela em pixels(fragmento de pixels) na tela
//  A FragmentShader é o processo em que colorimos os nossos pixels. 
//
//  Deixei passar 2 processos do Graphics Pipeline, mas que não são importantes para nós agora
//  
///////////////////////////////////////////////////////////////////////////////////////////////////////


float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};


const char *vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}\0";

const char *fragmentShaderSource = 
"#version 330 core\n"
"out vec4 fColor;\n"
"void main()\n"
"{\n"
"   fColor = vec4(0.686f, 0.019f, 1.0f, 1.0f);\n"
"}\0";

unsigned int shaderProgram;
unsigned int VBO;
unsigned int VAO;

void triangle_start()
{
    unsigned int vertexShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Erro ao compilar a VertexShader: " << infoLog << "\n";
    }

    unsigned int fragmentShader;

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Erro ao compilar a FragmentShader: " << infoLog << "\n";
    }

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGenBuffers(1, &VBO);


    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void triangle_render()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}