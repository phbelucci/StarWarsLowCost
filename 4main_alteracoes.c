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

bool colisao(ALLEGRO_BITMAP *obj1, int posYObj1, ALLEGRO_BITMAP *obj2, int posYObj2){
    bool ok = false;
    if ( ( ( posYObj1>posYObj2)&&(posYObj1<(posYObj2+al_get_bitmap_height(obj2)))) || (((posYObj1+al_get_bitmap_height(obj1))>posYObj2)&&((posYObj1+al_get_bitmap_height(obj1))<(posYObj2+al_get_bitmap_height(obj2))))){

        ok = true;
    }


    return ok;
}

int main(void)
{
    //------------------------------------- inicializacao Bibl. ALLEGRO -------------------------------------
    // Inicializa a Allegro
    al_init();

    //------------------------------------- Variaveis para JANELAS/IMAGENS -------------------------------------
    // Variável representando a janela principal
    ALLEGRO_DISPLAY *janela = NULL;
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    // Variável representando a imagem
    ALLEGRO_BITMAP *backGround = NULL;
    ALLEGRO_BITMAP *nave = NULL;
    ALLEGRO_BITMAP *tiro = NULL;
    ALLEGRO_BITMAP *tiro1 = NULL;
    ALLEGRO_BITMAP *tiro2 = NULL;
    ALLEGRO_BITMAP *tiro3 = NULL;
    ALLEGRO_BITMAP *obst = NULL;
    ALLEGRO_BITMAP *obst2 = NULL;
    ALLEGRO_BITMAP *obst3 = NULL;
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
    backGround = al_load_bitmap("img/background1.jpg");
    nave = al_load_bitmap ("img/rocket-312767.png");
    tiro = al_load_bitmap ("img/tiro.png");
    tiro1 = al_load_bitmap ("img/tiro.png");
    tiro2 = al_load_bitmap ("img/tiro.png");
    tiro3 = al_load_bitmap ("img/tiro.png");
    obst = al_load_bitmap ("img/asteroide.png");
    obst2 = al_load_bitmap ("img/asteroide.png");
    obst3 = al_load_bitmap ("img/asteroide.png");
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

    int alturaNave;
    alturaNave = al_get_bitmap_height (nave);
    printf ("Altura nave -  %i", alturaNave);

    int larguraNave;
    larguraNave = al_get_bitmap_width(nave);
    printf ("\nLargura nave -  %i", larguraNave);

    int posXBackGround=0;
    int posXNave = (30)+50;
    int posXTiro = 150;
    int posXTiro1 = 150;
    int posXTiro2 = 150;
    int posXTiro3 = 150;
    int posXObst = rand()% 1100 + 850;
    int posXObst2 = rand()% 1200 + 900;
    int posXObst3 = rand()% 1000 + 830;
    int posXExplo = 0;

    //Declara e inicializa Variaveis com a posição Y dos objetos
    int posYBackGround=0;
    int posYNave= 150;
    int posYTiro = posYNave;
    int posYTiro1 = posYNave;
    int posYTiro2 = posYNave;
    int posYTiro3 = posYNave;
    int posYObst = rand() % 200 + 20;
    int posYObst2 = rand()% 380 + 250;
    int posYObst3 = rand()% 230 + 180;
    int posYExplo = 0;

    //Declara e inicializa Variaveis com a velocidade dos objetos
    float velNave= 5;
    float velTiro = 8;
    float velTiro1 = 8;
    float velTiro2 = 8;
    float velTiro3 = 8;
    float velObst  = 4;
    float velObst2 = 4;
    float velObst3 = 4;

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
            //Posicionamento do obst
            posXObst -= (velObst+8);
            if(posXObst<-50){
                posXObst = rand()% 1100 + 850;
                posYObst = rand()% 200 + 20;
            }
            //Posicionamento do obst2
            posXObst2 -= (velObst2+10);
            if(posXObst2<-50){
                posXObst2 = rand()% 1200 + 900;
                posYObst2 = rand() % 380 + 250;
            }

            //Posicionamento do obst3
            posXObst3 -= (velObst3+13);
            if(posXObst3<-50){
                posXObst3 = rand()% 1000 + 830;
                posYObst3 = rand()% 230 + 180;
            }
            /*posição tiro
            posXTiro += (velNave+3);
            if (posXTiro >= 300){
                posXTiro1 += (velNave+3);
            }
            if (posXTiro1>=450){
                posXTiro2 += (velNave+3);
            }
            if (posXTiro2>= 600){
                posXTiro3 += (velNave+3);
            }
            if (posXTiro3>=800){
                posXTiro2 += (velNave+3);
            }*/
            //Colisao
           // printf("Nave x %f - nave y %f - obst x %f - obst y %f\n", posXNave,posYNave,posXObst,posYObst);

            if (colisao(nave,posYNave,obst,posYObst)){
                printf("COLIDIU...");
            }
            if (colisao(nave,posYNave,obst2,posYObst2)){
                printf("COLIDIU...");
            }
            if (colisao(nave,posYNave,obst3,posYObst3)){
                printf("COLIDIU...");
            }

            /*if(tempoExplo<10){
                posXExplo -= velObst;
                tempoExplo++;
            }else{
                posXExplo = 900;
            }*/

            //Desenha objetos(com seu novo posicionamento) na tela
            al_draw_bitmap(backGround, posXBackGround, posYBackGround, 0);
            al_draw_bitmap(nave, posXNave, posYNave, 0);
            al_draw_bitmap(obst, posXObst, posYObst, 0);
            al_draw_bitmap(obst2, posXObst2, posYObst2, 0);
            al_draw_bitmap(obst3, posXObst3, posYObst3, 0);
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

            if(cima)posYNave-=5;
            if(baixo)posYNave+=5;
            if(freia)velNave-=0.1;
           // if (freia <=0)
            if(acelera)velNave+=0.1;

    }

    // Finaliza o timer, janela e fila_eventos
    al_destroy_timer(timer);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}
