#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define TELA_LARGURA  800
#define TELA_ALTURA  550
#define FPS 60


int main(void)
{
    //------------------------------------- Variaveis para JANELAS -------------------------------------
    // Variável representando a janela principal
    ALLEGRO_DISPLAY *janela = NULL;
    // Variável representando a imagem
    ALLEGRO_BITMAP *imagem = NULL;
    ALLEGRO_BITMAP *nave = NULL;

    //------------------------------------- Variaveis para ENVENTOS -------------------------------------
    //Variavel para envento
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    //declara o timer do programa
    ALLEGRO_TIMER *timer = NULL;
    //Variavel de velocidade em frame/segundos

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
    //Carrega imagem da a nave
    nave = al_load_bitmap("img/nave.png");
    // Desenha a nave na tela
    al_draw_bitmap(nave, 150, 300, 0);

    // Atualiza a tela
    al_flip_display();

    //------------------------------------- inicializacao EVENTOS---------------------------------
    //cria o timer com o intervalo de tempo para background
    timer = al_create_timer(1.0 / FPS);
    //cria fila de eventos
    fila_eventos = al_create_event_queue();
    //registra o timer na fila de eventos
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    //inicia a contagem do timer
    al_start_timer(timer);

    int posxBackGround=0;
    int velNave=8;

    while(1){
        //Cria variavel para receber o evento
        ALLEGRO_EVENT evento;
        //Aguarda pelo proximo evento e, quando ocorrer, pega o ultimo evento da fila e atribuia a variavel evento
        al_wait_for_event(fila_eventos, &evento);

        //Se o evento for o timer...
        if(evento.type == ALLEGRO_EVENT_TIMER){
            //Desloca o background
            posxBackGround=posxBackGround - velNave;
            if(posxBackGround<=(TELA_LARGURA*-2)){
               posxBackGround=0;
               }
            al_draw_bitmap(imagem, posxBackGround, 0, 0);
            // Desenha a nave na tela
            al_draw_bitmap(nave, 150, 300, 0);
            //Atualiza a tela
            al_flip_display();
        }


    }

    // Finaliza a timer, janela e fila_eventos
    al_destroy_timer(timer);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}
