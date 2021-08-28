///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//                              Criando a primeira Janela utilizando GLFW
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Alguns pontos importantes: Tenha o GLFW instalado, e tenha o GLAD instalado
//  O conteúdo foi inspirado e estudado no site: https://learnopengl.com/
//
/////////////////////////////////////////////////////////////////////////////////////////////////


//  Outro ponto MUITO importante, é que você pelo menos saiba a base de C/C++ para podermos prosseguir sem dúvidas de sintaxe e como a linguagem funciona


//  Incluindo o Glad e o GLFW 
//  Importante que o Glad sempre seja incluido antes do GLFW
#include "../GL/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "triangle.cpp"

//  Função que será chamada quando redimensionarmos a janela
//  Todos os nossos conteúdos que aparecerá na janela, sera redimensionado para se encaixar nela
void onResizable(GLFWwindow *window, int width, int height)
{
    //  Utilizamos o "glViewport" para manipularmos a janela de exibição do programa
    //  O primeiro parametro dessa função indica a posição "X" do objeto que está na janela será deslocada
    //  O segundo parametro dessa função indica a posição "Y" do objeto que está na janela que será deslocada
    //  O terceiro parametro indica a largura da janela no qual sera redimensionada
    //  O quarto paraametro indica a altura da janela no qual sera redimensionada
    glViewport(0, 0, width, height);
}

//  Função para nós usarmos os Inputs
//  Podendo ser o teclado ou mouse
//  O unico parametro dessa função, indica qual janela queremos que funciona tal input
void inputManager(GLFWwindow *window)
{
    //  Par nós verificarmos qual tecla foi pressioada, usamos a função "glfwGetKey"
    //  O primeiro parametro dessa função, indica em qual janela nós queremos que o input funcione
    //  O segundo parametro indica qual tecla nós queremos verificar, que no nosso caso é o "GLFW_KEY_ESCAPE", ou, o "ESCAPE"(também chamado de "ESC")
    //  Para sabermos se foi pressionado, basta verificar a igualdade da verificaçõ com o "GLFW_PRESS" ...
    //  Que verifica se a tecla "GLFW_KEY_ESCAPE" na janela atual foi pressionada 
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){

        //  Caso a verificação foi verdadeira, então faremos tal ação
        //  Nossa ação vai ser fechar a janela caso clicarmos no "ESC"
        //  Para isso, utilizaremos a função "glfwSetWindowShouldClose"
        //  O primeiro parametro dessa função, indica qual janela nós queremos fechar
        //  O segundo parametro indica o estado da função. Se for "true", então fechará a janela
        //  Se for false, não acontecerá nada porque a janela está aberta e não fechará com o estado "false"
        glfwSetWindowShouldClose(window, true);
    }
}


int main()
{

    //  Agora, vamos começar a criar setar as propriedades ao nosso GFLW, configurar e criar nossa Janela
    //  Estará tudo documentado e explicado, então não será tão dificil de entender

    //  Para começarmos, vamos iniciar o GLFW com a função "glfwInit"
    glfwInit();
    

    //  Agora, configuraremos o GLFW para entender as versões que estamos utilizando do OpenGL
    //  A função que usaremos é a "glfwWindowHint"
    //  A "glfwWindowHint" é uma função que usaremos bastante em nossos projetos para setarmos as configurações e propriedades da Janela
    //  No nosso caso, estaremos apenas indicando a versão do OpenGL. Mas se vocẽ quiser, por exemplo, pode setar alguma outra propriedade com essa função
    //  Como por exemplo, com a função "glfwWindowHint" você pode indicar se a Janela será Redimensionável ou não
    //  Vamos parar de conversa e começar a configurar...

    //  Para começar, vamos indicar a maior versão do OpenGL
    //  No meu caso, estou usando a versão "3.3" então estarei indicando a versão 3
    //  O primeiro parametro dessa função indica a ação/indicação que queremos a nossa janela/glfw
    //  Como queremos indicar a maior versão do GLFW, então colocaremos "GLFW_CONTEXT_VERSION_MAJOR"
    //  E o segundo parametro indica o estadao da ação/indicação, que no nosso caso, estará indicando o estado da versão
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    //  Aqui é a mesma coisa da passada, porém indicando a menor versão do OpenGL
    //  No meu caso, só estou usando o OpenGL 3, então estarei indicando o valor "3"
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    
    //  Agora, nós precisamos fazer algo muito importante
    //  Precisamos setar a propriedade de Perfil do OpenGL
    //  Como eu tinha dito, estaremos usando a "glfwWindowHint" para algumas configurações
    //  O primeiro parametro vamos indicar que queremos usar o Perfil Principal do OpenGL
    //  E o segundo parametro indica que o nosso Perfil do OpenGL irá puxar as funções mais importantes do OpenGL
    //  E também tirará a compatibilidade com hardwares mais antigos.
    //  Resumindo: O segundo parametro apenas configura o nosso perfil OpenGL para o modo Core
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    //  Agora vamos fazer uma verificação simples pra rodar o nosso Programa em sistemas da Apple
    //  Não entrarei muito em detalhes sobre a função, apenas o que é esse "#ifdef"
    //  "#ifdef" é uma verificação do C/C++ que verifica algumas coisas mais específicas
    //  No nosso caso estamos verificando se o usuário que está usando o programa, está em algum sistema da Apple
    //  Se estiver, então ele executa a função que está dentro dessa verificação
    //  E após isso, encerraremos a verificação com "#endif"  
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif


    //  Agora, vamos criar a nossa janela...

    //  Para criamos a janela, precisamos usar um atributo do GLFW que se chama "GLFWwindow"
    //  O valor desta variável que guarda a "GLFWwindow" é "glfwCreateWindow"
    //  O primeiro parametro indica a Largura da Janela
    //  O segundo parametro indica a Altura da Janela
    //  O terceiro programa indica o título da Janela
    //  O quarto parametro indica em qual monitor o programa irá inicir, e se estará em tela cheia
    //  No meu caso, como eu não quero, estarei indicando "NULL"
    //  O quinto parametro indica se queremos compartilhar nossa Janela com Outra
    //  No meu caso deixarei "NULL" porque não quero
    GLFWwindow *window = glfwCreateWindow(800, 600, "Programa com GLFW e OpenGL", NULL, NULL);

    //  Vamos verificar se ocorreu erros na criação da Janela
    if(!window)
    {
        std::cerr << "Ocorreu um erro ao criar a janela" << "\n";

        //  Caso ocorrer algum erro, o GLFW irá terminar
        glfwTerminate();

        //  E retornar o nosso programa como "NULL", ou seja, irá interromper o programa
        return -1;
    }

    
    //  Agora, vamos criar nosso contexto OpenGL
    //  O OpenGL trabalha muito com contextos, e por isso é muito importante conhecermos isso
    //  Em seus projetos OpenGL, você verá muito do uso de Contextos, e por isso é importante conhecer sobre eles
    //  Caso vocẽ queria saber mais sobre, você poderá pesquisar na internet como funciona os Contextos
    //  Não explicarei agora porque veremos o contexto OpenGL na prática

    //  Mas por agora, vamos apenas criar-lo
    //  A função "glfwMakeContextCurrent" cria um contexto OpenGL para nós
    //  Com um único parâmetro, sendo em qual janela queremmos este contexto
    glfwMakeContextCurrent(window);


    //  Está função é um Callback para a nossa função que criamos, a "onResizable"
    //  Todas as nossas ações quando redimensionarmos a janela será feito na função "onResizeble"
    //  E sendo chamada por essa função "glfwSetFramebufferSizeCallback"
    glfwSetFramebufferSizeCallback(window, onResizable);

    
    //  Agora vamos carregar o nosso GLAD
    //  Para carregar, vamos fazer uma simples verificação para saber se foi carregado ou não
    //  Caso não seja carregado, indicará um erro e terá o programa com um retorno nulo(-1)
    //  NOTE: "glfwGetProcAddres" retorna o endereço do núcleo OpenGL, caso for compatível com o contexto atual
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Ocorreu um erro ao carregar o GLAD" << "\n";
        return -1;
    }

    triangle_start();

    //  Aqui está o nosso GameLoop principal
    //  A função "glfwWindowShouldClose" retorna "true" caso a janela esteja fechada, e "false" caso não esteja fechada
    while(!glfwWindowShouldClose(window))
    {
        //  Carregando nossa função de Inputs
        inputManager(window);

        //  Limpando nossa tela com "glClearColor"
        //  Limpar a tela seria como colocar um background com uma cor própria
        //  O primeiro, segundo e terceiro argumento especifica as cores R, G, B
        //  O quarto parametro indica se a cor é Alpha
        //  1.0f é opaco, e menos que isso começa a ficar mais transparente
        //  NOTE: O OpenGL trabalha com coordenadas normalizadas, então as cores só vão de "-1.0f" a "1.0f"
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


        //  Agora, vamos limpar os buffers da tela
        //  A função "glClear" limpa todos os buffers da tela para preservar os novos valores
        //  Por exemplo: Criamos um sistema que troca de cor repetidamente, indo de verde pra azul, e azul pra amarelo
        //  A função "glClear" irá limpar os buffers para preservar os novos valores
        //  Ou seja, se da cor verde for para azul, a função "glClear" limpará as buffers da cor verde para preserver a cor azul.
        //  Isto foi um exemplo bom? Talvez, mas espero que tenha entendido.

        //  A função "glClear" recebe um parametro
        //  Este parametro pode ser varios, porém indicaremos apenas o tipo "GL_COLOR_BUFFER_BIT"
        //  O tipo "GL_COLOR_BUFFER_BIT" indica as buffers que estão atualmente ativados para a gravação de cores
        glClear(GL_COLOR_BUFFER_BIT);

        triangle_render();

        //  Agora, vamos trocar os buffers da tela...
        //  A função "glSwapBuffers" troca os buffers "frontal e traseiro" da janela especificada. 
        //  Se o intervalo de troca for maior que zero, o driver da GPU espera o número especificado de atualizações de tela antes de trocar os buffers.
        glfwSwapBuffers(window);

        //  Agora, apenas colocamos uma função sem parametros para atualizar todos os eventos que acontecerão
        glfwPollEvents();
    }

    //  Após o término do Game Loop, finalizamos o GLFW
    glfwTerminate();
    
    return 0;
}