#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>

#define TELA_LARGURA  800
#define TELA_ALTURA  400


int main(void)
{

    //------------------------------------- Variaveis para JANELAS -------------------------------------
    // Variável representando a janela principal
    ALLEGRO_DISPLAY *janela = NULL;
    // Variável representando a imagem
    ALLEGRO_BITMAP *imagem = NULL;
    ALLEGRO_BITMAP *nave = NULL;
    ALLEGRO_BITMAP *tiro = NULL;
    ALLEGRO_BITMAP *obst = NULL;
    ALLEGRO_BITMAP *vazio = NULL;
    ALLEGRO_BITMAP *explo = NULL;

    //------------------------------------- Variaveis para ENVENTOS -------------------------------------
    //Variavel para envento
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    //declara o timer do programa
     //Variavel de velocidade em frame/segundos
    ALLEGRO_TIMER *timer = NULL;
    unsigned int velocidade = 80;
    ALLEGRO_TIMER *timer2 = NULL;
    unsigned int velocidade2 = 10;
    ALLEGRO_TIMER *timer3 = NULL;
    unsigned int velocidade3 = 10;
    ALLEGRO_TIMER *timer4 = NULL;
    unsigned int velocidade4 = 100;
    ALLEGRO_TIMER *timer5 = NULL;
    unsigned int velocidade5 = 0;

    //------------------------------------- inicializacao Bibl. ALLEGRO -------------------------------------
    // Inicializa a Allegro
    al_init();

    //------------------------------------- inicializacao JANELAS e IMAGENS ---------------------------------
    // Inicializa o add-on para utilização de imagens
    al_init_image_addon();
    // Configura a janela
    janela = al_create_display(TELA_LARGURA, TELA_ALTURA);
    // Carrega a imagem
    imagem = al_load_bitmap("img/background1.jpg");
    // Desenha a imagem na tela
    al_draw_bitmap(imagem, 0, 0, 0);

    nave = al_load_bitmap ("img/retro-rocket-vector_f.png");
    al_draw_bitmap(nave, 1, 1, 0);

    tiro = al_load_bitmap ("img/sprite_fire.png");
    al_draw_bitmap(tiro, 0, 0,0);


    obst = al_load_bitmap ("img/20101222063104_5025_Asteroid4.png");
    al_draw_bitmap(obst, 0, 0, 0);

    vazio = al_load_bitmap ("img/vazio.png");
    al_draw_bitmap(vazio, 0, 0, 0);

    explo = al_load_bitmap ("img/explo.png");
    al_draw_bitmap(explo, 1, 1, 1);

    // Atualiza a tela
    al_flip_display();

    //------------------------------------- inicializacao EVENTOS---------------------------------
    //cria o timer com o intervalo de tempo para background
    timer = al_create_timer(1.0 / velocidade);
    timer2 = al_create_timer (1.0/velocidade2);
    timer3 = al_create_timer (1.0/velocidade3);
    timer4 = al_create_timer (1.0/velocidade4);
    timer5 = al_create_timer (1.0/velocidade5);
    //cria fila de eventos
    fila_eventos = al_create_event_queue();
    //registra o timer na fila de eventos
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer2));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer3));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer4));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer5));

    //inicia a contagem do timer
    //BACK
    al_start_timer(timer);
    //NAVE
    al_start_timer(timer2);
    //TIRO
    al_start_timer(timer3);
    //OSBT
    al_start_timer(timer4);
    //EXPLO
    al_start_timer(timer5);

    float posxBackGround=0;
    float posxnave= 0;
    float posxtiro = 150;
    float posxobst = 850;
    float posxexplo = 0;

    while(1){
        //Cria variavel para receber o evento
        ALLEGRO_EVENT evento;
        //Aguarda pelo proximo evento e, quando ocorrer, pega o ultimo evento da fila e atribuia a variavel evento
        al_wait_for_event(fila_eventos, &evento);

        //Se o evento for o timer...
        if(evento.type == ALLEGRO_EVENT_TIMER){
            //Desloca o background
            posxBackGround--;
            if(posxBackGround<=(TELA_LARGURA*-2)){
               posxBackGround=0;
               }
            al_draw_bitmap(imagem, posxBackGround, 0,0);

            //Atualiza a tela
            al_flip_display();
        }
        //NAVE PRINCIPAL
        if(evento.type == ALLEGRO_EVENT_TIMER){
            //Desloca o background
            posxnave= 0;
            if(posxnave<=(TELA_LARGURA*-2)){
               posxnave=0;
               }
            al_draw_bitmap(nave, posxnave, 125,10);

            //Atualiza a tela
            al_flip_display();
        }
        //TIROS - DISPAROS
        if(evento.type == ALLEGRO_EVENT_TIMER){
            //Desloca o tiro
            posxtiro ++;
            if(posxtiro <=(TELA_LARGURA*-2)){
               posxtiro=0;
               }
            al_draw_bitmap(tiro, posxtiro, 150,0);

            //Atualiza a tela
            al_flip_display();
        }
        if(evento.type == ALLEGRO_EVENT_TIMER){
            //OBSTC 1
            posxobst = posxobst -1.5;
            if(posxobst <=(TELA_LARGURA*-2)){
               posxobst=0;
               }
            al_draw_bitmap(obst, posxobst, 150,0);
            //Atualiza a tela
            al_flip_display();

        }
        if (posxtiro == posxobst){
            obst = explo;
            explo = vazio;
        }
    }

    // Finaliza a timer, janela e fila_eventos
    al_destroy_timer(timer);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}
