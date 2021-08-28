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
//
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


//  Agora, vamos partir para a criação do triângulo!

//  Para começarmos, iniciamos uma matriz que indica os valores das nossas vértices
//  O OpenGL trabalha com coordenadas normalizadas, e por isso, os valores vão de "-1.0f" até "1.0f"
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};


//  Agora, vamos entrar na parte de Shaders
//  Nós iremos criar 2 strings que irão armazenar a codificação para a VertexShader e FragmentShader
//  O OpenGL moderno tem uma linguagem própria para programarmos as Shaders, que é a GLSL
//  A GLSL é uma linguagem de shading feita para substituir o uso de uma linguagem como Assembly para criamos Shaders
//  E uma observação importante, é que o GLSL é compilando em Runtime!

//  Vamos começar criando o código-fonte da VertexShader
//  Por enquanto, usaremos os arquivos de Shader no próprio arquivo do Triangulo
//  Só que mais pra frente, iremos aprender a como expandir, e criar arquivos separados para as shaders!
//  Mas por enquanto, ficaremos apenas usando Strings :(

//  No inicio do código-fonte, precisamos indicar ao OpenGL, qual versão estamos usando
//  Como eu uso a versão "3.3", indicarei como "#version 330"
//  Ao lado do "#version 330" tem a palavra "core", que indica que estamos trabalhando com o Perfil principal OpenGL em modo Core
//  Após este trecho de código, indicamos um "layout" com uma localização(location) com o valor de 0
//  recebendo um valor de input(int) com um tipo de variável "vec3" com o nome de "aPos"
//  Espera... Foi muitas informações para você? Ok, explicarei passo a passo...
//  O trecho "location = 0", indica o atributo de VAO que será buscada pela Shader
//  Ops, não expliquei o que é VAO? Fique tranquilo, ao decorrer do código irei explicar o que é VAO
//  Mas por enquanto, apenas saiba que esta parte será um atributo VAO que será buscada pela Shader
//  O trecho em que indicamos "in vec3 aPos", significa que queremos uma entrada(input) do tipo vetor3(vec3) com o nome de aPos,
//  que é uma referencia para a posição do nosso triangulo.. O nome pode ser qualquer um, coloquei "aPos" porque acho mais bonito :)
//  Percebos que após isso, coloquei uma função "void main" bem estilo a linguage C... Pois é, o bom do GLSL é que se parece bastante com C
//  Após colocar a função "main", colocamos um atributo que se chama "gl_Position", do próprio OpenGL para indicarmos a posição do nosso triangulo, 
//  Que recebe uma função "vec4", que possue 4 parametros...
//  O primeiro, segundo e terceiro parametro, indica a posição "X Y e Z" do nosso triangulo
//  O quarto e ultimo parametro, indica a posição "W" do objeto... Porém não precisamos disso agora, então deixaremos apenas como "1.0f"
const char *vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}\0";


//  Agora, vamos criar o nosso código fonte da FragmentShader...
//  Não é tão diferente do código fonte da VertexShader, porém muda um pouco na hora da I/O
//  Ao invés de atribuirmos um valor de entrada, apenas iremos atribuir um valor de saída "out vec4 fColor"
//  Este valor de saída irá fazer o Output(saída) da cor para o nosso triangulo
//  Lembrando que o valor "fColor" recebe uma função de 4 dimensões, contendo o valor R, G, B como primeiro parametro, 
//  E o Alpha da cor no ultimo parametro.
//  O OpenGL trabalha com coordenadas normalizadas, então as cores só vão de "-1.0f" até "1.0f"
const char *fragmentShaderSource = 
"#version 330 core\n"
"out vec4 fColor;\n"
"void main()\n"
"{\n"
"   fColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\0";



//  Agora, nós preciamos criar um programa de shader(Shader Program)
//  "O que é o programa de Shader?"
//  O programa de shader irá atribuir a VertexShader para a FragmentShader
//  Para isso, primeiro precisamos criar uma variável que será o ID do programa de Shader
unsigned int shaderProgram;


//  Bom, antes de prosseguirmos, precisamos criar uma variável que indicará o ID da VBO
//  O que é uma VBO?
//  Uma VBO é uma forma de nós armazenarmos todos os dados da nossa vértice para a memória da GPU(placa de vídeo)
//  Usar VBO é extremamente rápido, e não gastaremos muito do processamento
unsigned int VBO;


//  Nós também precisamos criar uma variável que indicará o ID da VAO
//  O que é uma VAO?
//  A VAO é uma forma de nós administrarmos(controlarmos) os dados da nossa VBO
unsigned int VAO;


//  Agora, vamos criar uma função que irá iniciar e configurar o nosso triangulo
//  Chamarei de "triangle_start", mas chame da forma que quiser!
void triangle_start()
{

    //  Vamos criar uma variável que indicará o ID da nossa VertexShader
    unsigned int vertexShader;

    //  Aqui, criaremos uma shader com a função "glCreateShader" e que será atribuida na nossa variável "vertexShader"
    //  O primeiro e unico parametro desta função, indica qual o tipo de Shader nós queremos criar. 
    //  Como estamos criando uma VertexShader, então colocaremos o valor "GL_VERTEX_SHADER"
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //  Agora, precisamos iniciar o processo de compilação da nossa VertexShader
    //  Para começarmos, precisamos primeiramente indicarmos que a nossa variável "vertexShader" receberá os valores do nosso código-fonte
    //  Para isso, precisamos usar a função "glShaderSource" contendo 4 parametros
    //  O primeiro paramentro da função, indica qual variável nós queremos atribuir, que no nosso caso é a "vertexShader"
    //  O segundo parametro indica quantos valores temos em nosso array...
    //  Como assim? Bom, estamos usando uma string para o código-fonte da nossa VertexShader, então não precisamos nos preocupar com isso
    //  Porém, se estivéssemos usando um array, este segundo parametro indica em até qual valor do array nós queremos atribuir o nosso código GLSL para o ID
    //  "vertexShader"
    //  O terceiro parametro, indica qual código nós queremos, qual source nos queremos.. No nosso caso, é a "vertexShaderSource"
    //  O quarto e ultimo parametro indica o tamanho do array... Como eu havia dito, não estamos usando array, então vamos deixar em "NULL"
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    //  Agora, vamos executar a função que compila a nossa VertexShader
    //  O primeiro e unico parametro, apenas indica qual o ID da Shader nós queremos.. No nosso caso, é o ID "vertexShader"
    glCompileShader(vertexShader);

    //  OPICIONAL: Caso você queira saber se deu algum erro na compilação da VertexShader, basta realizar este código:
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Erro ao compilar a VertexShader: " << infoLog << "\n";
    }
    //


    //  Agora, faremos o mesmo processo que fizemos com a VertexShader porém agora com o FragmentShader
    //  Iniciamos criando a variável que indicará o ID da fragmentShader
    unsigned int fragmentShader;

    //  Criaremos este ID. Porém desta vez, passando o tipo da shader como "GL_FRAGMENT_SHADER"
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    //  Aqui faremos o mesmo processo da compilação da VertexShader, porém trocando tudo por FragmentShader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    
    //  OPICIONAL: Caso você queira saber se deu algum erro na compilação da FragmentShader, basta realizar este código:
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Erro ao compilar a FragmentShader: " << infoLog << "\n";
    }
    //


    //  Agora, vamos começar a criar o nosso Programa de Shader...
    //  Para começarmos, precisamos criar o ID do Programa, com a função "glCreateProgram"
    //  Está função apenas criará o ID do nosso programa sendo atribuida a nossa variável que vai indicar este ID
    shaderProgram = glCreateProgram();

    //  Após isso, iremos atribuir a nossa VertexShader para a FragmentShader
    //  Vamos usar a função "glAttachShader" para atribuirmos as nossas Shaders ao programa
    //  A função "glAttachShader" possue 2 parametros...
    //  O primeiro parametro indica o ID do programa que queremos, e o segundo parametro indica a Shader que queremos atribuir
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    //  Agora, linkaremos o nosso Programa, e a VertexShader será atribuida para a FragmentShader
    glLinkProgram(shaderProgram);


    //  Como não precisamos mais, deletaremos nossa VertexShader e FragmentShader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    
    //  Agora, precisaremos configurar a VBO e VAO
    //  Como foi explicado anteriormente, a VBO guarda nossas informações dos dados da nossa vértice na GPU
    //  E a VAO controla esses dados da VBO

    //  Para começarmos, vamos criar o nosso ID que indicará a VBO
    //  utilizaremos a função "glGenBuffers" para gerarmos a VBO
    //  O primeiro parametro da função, indica quantos buffers nós queremos
    //  Como só criamos uma VBO, indicarei o valor de "1"
    //  Mas se você quiser criar mais de uma VBO, fique a vontade!
    //  O segundo parametro indica qual a variável que será atribuida o ID, no meu caso, será a variável "VBO"
    glGenBuffers(1, &VBO);

    
    //  Agora, nós precisamos gerar o nosso ID que indicará a VAO
    //  O processo é o mesmo de gerar o ID da VBO, só muda o nome da função :)
    glGenVertexArrays(1, &VAO);

    //  Agora, vamos ligar a nossa VAO
    //  Para fazer isso, basta pedirmos o ID que será ligado, que no caso é a VAO
    //  LEMBRANDO: é muito importante ligarmos a VAO, antes de ligarmos a VBO
    glBindVertexArray(VAO);

    
    //  Agora, ligaremos a VBO
    //  Usaremos uma função diferente, que contém 2 parametros
    //  O primeiro parametro indica o o destino que o nosso Buffer está linkado
    //  E o segundo parametro indica o ID da VBO que nós queremos
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //  Agora, nós precisamos fazer a cópia dos nossos dados para a memória Buffer
    //  O primeiro argumento da função que fará isso, indica o destino que o nosso Buffer será copiado
    //  É tudo uma questão de Contexto.. Então o OpenGL reconhecerá que nós ligamos a VBO com o Destino "GL_ARRAY_BUFFER" e será copiado pelo nosso ID "VBO"
    //  O segundo parametro indica o tamanho dos dados que nós iremos copiar. No nosso caso, vamos copiar as vértices do triangulo, então indicaremos
    //  o tamanho dessas vértices utilizando a função do C/C++ sizeof, que retorná o valor em BYTES
    //  O terceiro parametro indica qual o dado que copiaremos, que será a "vertices"
    //  O quarto e ultimo parametro indica o dado no qual a placa de vídeo irá Gerenciar
    //  Os dados que a placa de vídeo pode gerenciar, são: "GL_STATIC_DRAW" | "GL_DYNAMIC_DRAW" | "GL_STREAM_DRAW"
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //  O que são estes dados que a placa de vídeo pode gerenciar?
    //  GL_STATIC_DRAW: Todos os dados serão criados uma vez e usados várias vezes
    //  GL_DYNAMIC_DRAW: Todos os dados serão criados e alterados muitas vezes, e usados várias vezes
    //  GL_STREAM_DRAW: Todos os dados serão criados uma vez e usados poucas vezes
    //  Um Exeplo rápido: Imagine que você queria um triangulo que se mova aleatóriamente pela tela...
    //  Ao invés de nós atribuirmos o valor "GL_STATIC_DRAW", nós podemos usar o valor "GL_DYNAMIC_DRAW" que
    //  garantirá que a placa de vídeo irá atualizar os dados das vértices sem ocorrer alguma chance de erros

    
    //  Bom, infelizmente a nossa VAO não sabe o que fazer com as nossas vértices...
    //  Então é por isso, que precisamos instruir a VAO com a função "glVertexAttribPointer"
    //  O primeiro parametro da função indica a LOCALIZAÇÂO do atributo de VAO que queremos instruir...
    //  Lembra que lá no nosso código-fonte da VertexShader, indicamos um "(location = 0)"? Então, é neste parametro que indicamos a localização deste Atributo
    //  caso colocassemos um "(location = 10)" então precisariamos colocar o valor "10" neste parametro
    //  O segundo parametro indica quantos elementos nós usaremos por cada Stride da nossá vertice
    //  O terceiro parametro, indica qual o tipo dos dados que nós iremos usar, que no nosso caso, as vértices é em float, então coloaremos "GL_FLOAT"
    //  O quarto parametro indica se nós queremos Normalizar as coordenadas. Como já está normalizada, deixaremos como "GL_FALSE"
    //  O quinto parametro indica quantos Strides nós usaremos da nossa vértice...
    //  Nossa vértice tem apenas 3 Strides, porém precisamos multiplicar estes Strides pelo tamanho em BYTES do tipo "float"
    //  O sexto e ultimo parametro indica qual posição nós queremos dos nossos Strides da vértice
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    //  Agora nós precisamos ativar o nosso atributo de VAO, indicando a LOCALIZAÇÂO dela
    //  No nosso caso, ativaremos apenas o atribudo que está na localização "0"
    glEnableVertexAttribArray(0);
}


//  Agora, precisamos criar uma função que irá renderizar o nosso Triângulo!
void triangle_render()
{
    //  Primeiro, nós precisamos usar o nosso Programa de Shader para carregar e usarmos as Shaders
    glUseProgram(shaderProgram);

    //  Agora, nós precisamos ligar a nossa VAO para usarmos e controlar os nossos dados que está na GPU
    glBindVertexArray(VAO);

    //  E por fim, usaremos a função "glDrawArrays" para desenharmos nosso Triângulo
    //  O primeiro argumento indica o tipo primitivo que queremos para renderizarmos o nosso triângulo
    //  O nosso tipo primitivo seria apenas o "GL_TRIANGLES"
    //  O segundo parametro indica em qual Stride nós queremos usar
    //  O terceiro e ultimo parametro, indica quantos vértices nós queremos renderizar. Para renderizarmos todos, indicaremos os 3 unicos vértices :)
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

//  Uma função bônus para nós deletarmos a VBO, VAO e o nosso Programa de Shader
void triangle_delete()
{
    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}



//  E pronto!
//  Caso você fizer tudo certinho, seu triangulo será renderizado na janela
//  Lembre-se de colocar as funções deste arquivo no arquivo da janela :)