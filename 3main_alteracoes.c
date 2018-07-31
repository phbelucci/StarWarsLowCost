#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>

#define FPS 60
#define TELA_LARGURA  800
#define TELA_ALTURA  400


int main(void)
{
    //------------------------------------- inicializacao Bibl. ALLEGRO -------------------------------------
    // Inicializa a Allegro
    al_init();

    //------------------------------------- Variaveis para JANELAS/IMAGENS -------------------------------------
    // Variável representando a janela principal
    ALLEGRO_DISPLAY *janela = NULL;
    // Variável representando a imagem
    ALLEGRO_BITMAP *backGround = NULL;
    ALLEGRO_BITMAP *nave = NULL;
    ALLEGRO_BITMAP *tiro = NULL;
    ALLEGRO_BITMAP *obst = NULL;
    ALLEGRO_BITMAP *explo = NULL;

    //------------------------------------- Variaveis para ENVENTOS -------------------------------------
    //Variavel ponteiro para fila de enventos
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    //declara o timer do programa
    ALLEGRO_TIMER *timer = NULL;
     //Variavel de velocidade em frame/segundos



    //------------------------------------- inicializacao JANELAS e IMAGENS ---------------------------------
    // Inicializa o add-on para utilização de imagens
    al_init_image_addon();

    // Configura a janela
    janela = al_create_display(TELA_LARGURA, TELA_ALTURA);

    // Carrega o as imagens para o jogo
    backGround = al_load_bitmap("img/background.jpg");
    nave = al_load_bitmap ("img/nave1.png");
    tiro = al_load_bitmap ("img/tiro.png");
    obst = al_load_bitmap ("img/asteroide.png");
    explo = al_load_bitmap ("img/explo.png");

    // Desenha as imagens na tela
    al_draw_bitmap(backGround, 0, 0, 0);

    // Atualiza a tela
    al_flip_display();

    //------------------------------------- inicializacao EVENTOS---------------------------------
    //Inicializa variável timer com FPS definido
    timer = al_create_timer(1.0 / FPS);

    //inicializa addon do teclado
    al_install_keyboard();

    //Inicializa variável fila de eventos
    fila_eventos = al_create_event_queue();

    //registra  timer e teclado na fila de eventos
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());

    //inicia a contagem do timer
    al_start_timer(timer);

    //Cria variavel para receber o tipo de evento detectado
    ALLEGRO_EVENT evento;


    //--------------------------- PARAMETROS DO JOGO---------------------------------

    //Declara e inicializa Variavel para sair do jogo
    bool sair = 0;

    //Declara e inicializa Variaveis com a posição X dos objetos
    float posXBackGround=0;
    float posXNave= 0;
    float posXTiro = 150;
    float posXObst = 850;
    float posXExplo = 0;

    //Declara e inicializa Variaveis com a posição Y dos objetos
    float posYBackGround=0;
    float posYNave= 150;
    float posYTiro = 150;
    float posYObst = 150;
    float posYExplo = 150;

    //Declara e inicializa Variaveis com a velocidade dos objetos
    float velNave= 3;
    float velTiro = 5;
    float velObst = 2;

    //Declara e inicializa Variavel para contagem de tempo
    int tempoExplo = 999;

    //Declara e inicializa Variaveis de controle do teclado
    bool cima = 0;
    bool baixo = 0;
    bool freia = 0;
    bool acelera = 0;

    while(!sair){
        //Aguarda pelo proximo evento e, quando ocorrer, pega o ultimo evento da fila e atribui a variavel evento
        al_wait_for_event(fila_eventos, &evento);

        //****************************************************************************
	//Se o evento for o timer...
	//****************************************************************************
        if(evento.type == ALLEGRO_EVENT_TIMER){
            //Posicionamento do background (VELOCIDADE DA NAVE)
            posXBackGround -= velNave;
            if(posXBackGround<=(TELA_LARGURA*-2)){
                posXBackGround=0;
            }

            //Posicionamento do tiro
            posXTiro += (velTiro+velNave);
            posYTiro = posYNave+8;

            if(posXTiro>820){
                posXTiro = posXNave+90;
            }

            //Posicionamento do obst
            posXObst -= (velObst+velNave);
            if(posXObst<-100){
                posXObst = 900;
            }

            //Colisao Tiro x Obst
            if (posXTiro >= posXObst){
                posXExplo = posXObst;
                posYExplo = posYObst;
                posXObst = 850;
                posXTiro = 150;
                tempoExplo = 0;
            }
            if(tempoExplo<10){
                posXExplo -= velObst;
                tempoExplo++;
            }else{
                posXExplo = 900;
            }

            //Desenha objetos(com seu novo posicionamento) na tela
            al_draw_bitmap(backGround, posXBackGround, posYBackGround, 0);
            al_draw_bitmap(nave, posXNave, posYNave, 0);
            al_draw_bitmap(tiro, posXTiro, posYTiro, 0);
            al_draw_bitmap(obst, posXObst, posYObst, 0);
            al_draw_bitmap(explo, posXExplo, posYExplo, 0);

            //Atualiza a tela
            al_flip_display();
        }

        //****************************************************************************
	//se o evento for PRESSIONAR uma tecla...
	//****************************************************************************
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN){
                //verifica qual tecla foi pressionada
                switch(evento.keyboard.keycode){
                //seta para cima
                case ALLEGRO_KEY_UP:
                    cima = 1;
                    break;
                //seta para baixo
                case ALLEGRO_KEY_DOWN:
                    baixo = 1;
                    break;
                //seta para esquerda
                case ALLEGRO_KEY_LEFT:
                    freia = 1;
                    break;
                //seta para direita.
                case ALLEGRO_KEY_RIGHT:
                    acelera = 1;
                    break;
                //esc. sair=1 faz com que o programa saia do loop principal
                case ALLEGRO_KEY_ESCAPE:
                    sair = 1;
                }
            }

        //****************************************************************************
	//se o evento for SOLTAR uma tecla...
	//****************************************************************************
            if (evento.type == ALLEGRO_EVENT_KEY_UP){
                //verifica qual tecla foi pressionada
                switch(evento.keyboard.keycode){
                //seta para cima
                case ALLEGRO_KEY_UP:
                    cima = 0;
                    break;
                //seta para baixo
                case ALLEGRO_KEY_DOWN:
                    baixo = 0;
                    break;
                //seta para esquerda
                case ALLEGRO_KEY_LEFT:
                    freia = 0;
                    break;
                //seta para direita.
                case ALLEGRO_KEY_RIGHT:
                    acelera = 0;
                    break;
                }
            }

            if(cima)posYNave-=3;
            if(baixo)posYNave+=3;
            if(freia)velNave-=0.1;
            if(acelera)velNave+=0.1;

    }

    // Finaliza o timer, janela e fila_eventos
    al_destroy_timer(timer);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}
