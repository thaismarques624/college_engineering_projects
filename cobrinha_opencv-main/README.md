# Welcome to CobrinhaOpencv!

Esse projeto foi desenvolvido para a disciplina de Linguagem de Programação I - 2023.1 - do professor Derzu Omaia. O objetivo era implementar um dos temas sugeridos em aula utilizando a OpenCv em C++. 
>Optei por escolher o jogo retrô da Serpente, comum em aparelhos dos anos 2000, adaptando para a cobrinha ser a face detectada pela webcam e a comida ser um pequeno quadrado vermelho, assim que colide com a face, ele muda de posição "aleatoriamente" e acrescenta +1 ao placar, lembrando que cada partida dura 60 segundos. 

Obs.: Importante salientar que esse código foi feito em ambiente Linux-Ubuntu.

# Requisitos pedidos
 1. Faça a modelagem das classes que serão utilizadas no sistema   
    utilizando diagrama UML de classe.
 2. Usar bastante métodos. 

 3. O programa deve rodar indefinidamente, até que o usuário escolha   
    sair. Exiba um menu (modo texto ou na tela).

 4. Exibir pontuação final, e salvar em arquivo a maior pontuação   
    (record).

 5. Usar a biblioteca OpenCV, Yolo ou OpenPose para detectar algum
    objeto    ou jogador.
   
 6. Exibir uma comida na tela do programa uma comida (pode ser uma foto 
    de uma comida, ou um círculo/quadrado/triângulo. Varie o desenho da 
    comida, e a posição que ela será exibida. Exiba apenas uma comida
    por    vez.

 7. Verificar se a face do jogador está sobre a comida. Se tiver uma
    nova    comida deve ser gerada em outra posição e a pontuação
    incrementada.
 8. Exibir na tela se a pontuação atual do jogador. O jogador terá 1 
    minuto para comer o máximo de comidas possíveis.

 9. ~~Toque um som toda vez que o usuário comer uma comida.~~ (Não implementado nessa versão)
  

# Diagrama UML

![cobrinha](https://github.com/GabriellyMarques02/cobrinhaOpencv/blob/main/cobrinhas.drawio.png)

### Algumas informações necessárias: 

    Cobrinha: Representa a classe principal que controla o jogo.
        Atributos:
            SCREEN_WIDTH e SCREEN_HEIGHT: Largura e altura da tela.
            FOOD_SIZE: Tamanho dos alimentos.
            GAME_DURATION: Duração do jogo em segundos.
            score: Pontuação do jogador.
            gameOver: Indica se o jogo terminou.
            gameRunning: Indica se o jogo está em execução.
            gameInitialized: Indica se o jogo foi inicializado.
            foods: Vetor de alimentos (objeto da classe Food).
            faceRect: Retângulo da face detectada.
            faceCascade: Classificador em cascata para detecção de rostos.
            startTime: Tempo de início do jogo.
        Métodos:
            generateFood(): Gera um novo alimento.
            drawFoods(Mat& frame): Desenha os alimentos na tela.
            updateGame(Mat& frame): Atualiza o estado do jogo.
            main(): Função principal que inicia o jogo.

    Food: Representa a classe que define os alimentos no jogo.
        Atributos:
            position: Posição do alimento (objeto da classe Point).
        Métodos:
            Food(): Construtor para gerar alimentos com posições aleatórias.


# Exemplos de utilização

### Tela de inicio: 
Assim que executa o arquivo do cobrinha, você se deparara com essa tela: 
![1](https://github.com/GabriellyMarques02/cobrinhaOpencv/blob/main/1.png)
### Tela de fim de jogo e menu de escolha
Assim que os 60 segundos do tempo de partida acaba, então ira imprimir na tela sua pontuação e um menu de escolha(R para reiniciar o jogo ou ESC para sair).<br />
![2](https://github.com/GabriellyMarques02/cobrinhaOpencv/blob/main/2.png)
### O placar fica gravado em um txt
O placar é gravado assim que você reinicia o jogo apertando em R ou quando sair do programa apertando ESC. 
Detalhe o arquivo insere o placar utilizando o metodo de uma fila. 
![3](https://github.com/GabriellyMarques02/cobrinhaOpencv/blob/main/3.png)

# Como compilar? 

Segue os passos para compilar códigos que utilizam Opencv:

 1. Abra a pasta do projeto
 2. Utilize o CMake para facilitar o projeto, então crie um arquivo CMakeLists.txt(dentro da pasta do projeto viu):
  

      cmake_minimum_required(VERSION 2.8)
        project(nome da pasta do projeto)
        find_package( OpenCV REQUIRED )
        add_executable( nome da pasta do projeto arquivodoprojeto.cpp )
        target_link_libraries( nome da pasta do projeto ${OpenCV_LIBS} )
  

 3. Abra o terminal dentro da pasta do projeto
 4. Digite cmake .
 5. Digite make (Obs: se tiver algo errado no projeto acusa aqui)
 6. ./nome (obs- digite que você colocou aqui:  target_link_libraries( **nome da pasta do projeto** ${OpenCV_LIBS} ))

Prontinho!!!

# Referências: 
>https://github.com/opencv/opencv/blob/4.x/data/haarcascades/haarcascade_frontalface_default.xml
https://sites.google.com/site/derzuomaia/tutoriais/instala%C3%A7%C3%A3o-opencv-no-linux-ubuntu
https://medium.com/@carvalho.natalia03/instalando-a-opencv-c-no-linux-98d7fc71e996

