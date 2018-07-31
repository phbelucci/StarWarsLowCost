#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_windows.h>
#include <stdbool.h>


#define FPS 60
#define TELA_LARGURA  800
#define TELA_ALTURA  400
#define TOLERANCIA 5
#define TEMPO_JOGO_SEGUNDOS 30


//--------------------------- PARAMETROS DO JOGO---------------------------------
    //declara o timer do programa
    ALLEGRO_TIMER *timer = NULL;

    // Variável representando a imagem
    ALLEGRO_BITMAP *backGround = NULL;
    ALLEGRO_BITMAP *nave = NULL;
    ALLEGRO_BITMAP *nave2 = NULL;
    ALLEGRO_BITMAP *nave3 = NULL;
    ALLEGRO_BITMAP *tiro = NULL;
    ALLEGRO_BITMAP *tiro1 = NULL;
    ALLEGRO_BITMAP *tiro2 = NULL;
    ALLEGRO_BITMAP *tiro3 = NULL;
    ALLEGRO_BITMAP *obst = NULL;
    ALLEGRO_BITMAP *obst2 = NULL;
    ALLEGRO_BITMAP *obst3 = NULL;
    ALLEGRO_BITMAP *explo = NULL;
    ALLEGRO_BITMAP *vilao = NULL;
    ALLEGRO_BITMAP *fogo = NULL;
    ALLEGRO_BITMAP *fumaca = NULL;
    ALLEGRO_BITMAP *menuInicial = NULL;
    ALLEGRO_BITMAP *play = NULL;
    ALLEGRO_BITMAP *vida1 = NULL;
    ALLEGRO_BITMAP *vida2 = NULL;
    ALLEGRO_BITMAP *vida3 = NULL;
    ALLEGRO_BITMAP *gameover = NULL;


    //Declara e inicializa Variaveis se controle do jogo
    bool sair = 0;
    bool pause = 0;
    int score = 0;
    int somaScore = 0;
    int tempJogo=0;
    int vidas = 3;
    int trocaNave = 3;

    //Declara e inicializa Variaveis com a posição X dos objetos


    int posXBackGround=0;
    int posXNave = 80;
    int posXTiro = 150;
    int posXTiro1 = 150;
    int posXTiro2 = 150;
    int posXTiro3 = 150;
    int posXObst = 1300;
    int posXObst2 = 1000;
    int posXObst3 = 800;
    int posXExploNave = 0;
    int posXExploObst = 0;
    int posXExploObst2 = 0;
    int posXExploObst3 = 0;
    int posXVilao = 900;
    int posXFogo = 25;
    int posXFumaca = 25;
    int posXVida1 = 750;
    int posXVida2 = 710;
    int posXVida3 = 670;
    int posXGo = 0;

    //Declara e inicializa Variaveis com a posição Y dos objetos
    int posYBackGround=0;
    int posYNave= 150;
    int posYTiro = 1800;
    int posYTiro1 = 150;
    int posYTiro2 = 1800;
    int posYTiro3 = 1800;
    int posYObst = 200;
    int posYObst2 = 300;
    int posYObst3 = 100;
    int posYExploNave = 1800;
    int posYExploObst = 0;
    int posYExploObst2 = 0;
    int posYExploObst3 = 0;
    int posYVida1 = 5;
    int posYVida2 = 5;
    int posYVida3 = 5;
    int posYGo = 0;

    //Angulo da nave
    float angNave= 2*ALLEGRO_PI;

    //Declara e inicializa Variaveis com a velocidade dos objetos
    float velNave= 5;
    float velTiro = 3;
    float velTiro1 = 1;
    float velTiro2 = 1;
    float velTiro3 = 1;
    float velObst  = 4;
    float velObst2 = 4;
    float velObst3 = 4;
    float velDesloc = 5;
    float velVilao = 3;


    //Declara e inicializa Variavel para contagem de tempo
    int tempExploNave = 999;
    int tempExploObst = 999;
    int tempExploObst2 = 999;
    int tempExploObst3 = 999;
    int tempPause = 999;

    //Declara e inicializa Variaveis de controle do teclado
    bool cima = 0;
    bool baixo = 0;
    bool freia = 0;
    bool acelera = 0;


    //Funcao de colisao entre dois objetos
    bool colisao(ALLEGRO_BITMAP *obj1, int posXObj1, int posYObj1, ALLEGRO_BITMAP *obj2,int posXObj2, int posYObj2){
    bool ok = false;

    int posX1Obj1 = posXObj1 + al_get_bitmap_width(obj1);
    int posY1Obj1 = posYObj1 + al_get_bitmap_height(obj1);
    int posX1Obj2 = posXObj2 + al_get_bitmap_width(obj2);
    int posY1Obj2 = posYObj2 + al_get_bitmap_height(obj2);

    if ( ( ( posYObj1>(posYObj2+TOLERANCIA))&&(posYObj1<(posY1Obj2-TOLERANCIA))) || ((posY1Obj1>(posYObj2+TOLERANCIA))&&(posY1Obj1<(posY1Obj2-TOLERANCIA)))){
        if ( ( ( posXObj1>(posXObj2+TOLERANCIA))&&(posXObj1<(posX1Obj2-TOLERANCIA))) || ((posX1Obj1>(posXObj2+TOLERANCIA))&&(posX1Obj1<(posX1Obj2-TOLERANCIA)))){
            ok = true;
        }
    }


    return ok;
}


    void rodaJogo(){

            //PROGRESSÃO
            if (score >= 10){
                velDesloc *= 1.1;
                velNave = velNave *1.1;
                score = 0;
            }

            //SISTEMA DE VIDAS
            if (vidas<3){
                posXVida1 = 1000;
                posYVida1 = 1000;
            }
            if (vidas<2){
                posXVida2 = 1000;
                posYVida2 = 1000;
            }
            if (vidas<1){
                posXVida3 = 1000;
                posYVida3 = 1000;
            }

            //TIROS

            posXTiro1 += 5;
            if (posXTiro1 <= 250){
                tiro1 = al_load_bitmap ("img/tiro.png");
                velTiro1 = (velTiro1+velNave);
            }
            posXTiro2 += 5;
            if (posXTiro2 <= 500){
                tiro2 = al_load_bitmap ("img/tiro.png");
                velTiro1 = (velTiro1+velNave);
            }


            //Posicionamento do obst
            posXObst -= (velObst+velNave);
            if (posXObst<-50){
                posXObst = (rand()% 1100) + 850;
                posYObst = (rand()% 120) + 20;
                velObst = rand()% 7 + 1;
                score ++;
                somaScore = somaScore + score;
                printf("%i\n", score);
            }
            //Posicionamento do obst2
            posXObst2 -= (velObst2+velNave);
            if (posXObst2<-50){
                posXObst2 = (rand()% 1200) + 900;
                posYObst2 = (rand() % 130) + 150;
                velObst2 = rand()% 7 + 1;
                score ++;
                somaScore = somaScore + score;
                printf ("%i\n", score);
            }

            //Posicionamento do obst3
            posXObst3 -= (velObst3+velNave);
            if (posXObst3<-50){
                posXObst3 = (rand()% 1000) + 830;
                posYObst3 = (rand()% 100) + 250;
                velObst3 = rand()% 7 + 1;
                score ++;
                somaScore = somaScore + score;
                printf ("%i\n", score);
            }

            if (colisao(nave,posXNave,posYNave,obst,posXObst,posYObst)){
                tempExploNave = 0;
                posXExploNave = posXNave;
                posYExploNave = posYNave;
                posYNave = 1800;
                posXNave = 1800;
                posXObst = (rand()% 1100) + 850;
                posYObst = (rand()% 120) + 20;
                backGround = al_load_bitmap("img/backgroundExplo.jpg");
                vidas --;
                trocaNave ++;
                printf ("%i", vidas);
                nave = al_load_bitmap("img/nave_colisao1.png");
                if (vidas <2){
                    nave = al_load_bitmap("img/nave_colisao2.png");
                }
            }
            if (colisao(nave,posXNave,posYNave,obst2,posXObst2,posYObst2)){
                tempExploNave = 0;
                posXExploNave = posXNave;
                posYExploNave = posYNave;
                posYNave = 1800;
                posXNave = 1800;
                posXObst2 = (rand()% 1200) + 900;
                posYObst2 = (rand() % 130) + 150;
                backGround = al_load_bitmap("img/backgroundExplo.jpg");
                vidas --;
                trocaNave ++;
                printf ("%i", vidas);
                nave = al_load_bitmap("img/nave_colisao1.png");
                if (vidas <2){
                    nave = al_load_bitmap("img/nave_colisao2.png");
                }
            }
            if (colisao(nave,posXNave,posYNave,obst3,posXObst3,posYObst3)){
                tempExploNave = 0;
                posXExploNave = posXNave;
                posYExploNave = posYNave;
                posYNave = 1800;
                posXNave = 1800;
                posXObst3 = (rand()% 1000) + 830;
                posYObst3 = (rand()% 100) + 250;
                backGround = al_load_bitmap("img/backgroundExplo.jpg");
                vidas --;
                trocaNave ++;
                printf ("%i", vidas);
                nave = al_load_bitmap("img/nave_colisao1.png");

                if (vidas <2){
                    nave = al_load_bitmap("img/nave_colisao2.png");
                }
            }


            if(tempExploNave<10){
                tempExploNave++;
            }else if(tempExploNave==10){

                posXExploNave = 1800;
                tempExploNave++;
                tempPause=0;
                posXObst = (rand()% 1100) + 850;
                posYObst = (rand()% 120) + 20;
                posXObst2 = (rand()% 1200) + 900;
                posYObst2 = (rand() % 130) + 150;
                posXObst3 = (rand()% 1000) + 830;
                posYObst3 = (rand()% 100) + 250;
                backGround = al_load_bitmap("img/background.jpg");
            }

            //TROCA DE NAVE
            if (trocaNave == 2){
                nave = nave2;
            }

            //LIMITE SUP E INF
            if (posYNave <= 10){
                posYNave = posYNave +10;
            }
            if (posYNave >=380){
                posYNave = posYNave-10;
            }

            tempJogo++;
            if(tempJogo>TEMPO_JOGO_SEGUNDOS*FPS){
                sair=1;
                printf("\n\n****************************");
                printf("\n****************************\n");
                printf("G A M E    O V E R  !  !  !");
                printf("\n\nPERDEU    PLAYBOY!   VAZA!!!");
                printf("\n****************************");
                printf("\n****************************\n\n\n\n");
            }

}


int main(void){
    //------------------------------------- inicializacao Bibl. ALLEGRO -------------------------------------
    // Inicializa a Allegro
    al_init();
    //------------------------------------- Variaveis para JANELAS/IMAGENS -------------------------------------
    // Variável representando a janela principal
    ALLEGRO_DISPLAY *janela = NULL;
    al_set_new_display_flags(ALLEGRO_RESIZABLE);

    //------------------------------------- Variaveis para ENVENTOS -------------------------------------
    //Variavel ponteiro para fila de enventos
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;


    //------------------------------------- inicializacao JANELAS e IMAGENS ---------------------------------
    // Inicializa o add-on para utilização de imagens
    al_init_image_addon();

    // Configura a janela
    janela = al_create_display(TELA_LARGURA, TELA_ALTURA);




    // Carrega o as imagens para o jogo
    play = al_create_bitmap(50,100);
    backGround = al_load_bitmap("img/background.jpg");
    nave = al_load_bitmap ("img/nave2 (2).png");
    tiro = al_load_bitmap ("img/tiro.png");


    tiro3 = al_load_bitmap ("img/tiro.png");
    obst = al_load_bitmap ("img/asteroide.png");
    obst2 = al_load_bitmap ("img/asteroide.png");
    obst3 = al_load_bitmap ("img/asteroide.png");
    explo = al_load_bitmap ("img/explo.png");
    fogo = al_load_bitmap("img/fogo.gif");
    vilao = al_load_bitmap("img/vilao.png");
    menuInicial = al_load_bitmap("img/menuInicial.jpg");
    vida1 = al_load_bitmap("img/vidasmall.png");
    vida2 = al_load_bitmap("img/vidasmall.png");
    vida3 = al_load_bitmap("img/vidasmall.png");
    gameover = al_load_bitmap("img/gameover.jpg");

    // Desenha as imagens na tela
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    al_draw_bitmap(menuInicial, 0, 0, 0);

    // Atualiza a tela
    al_flip_display();

    //------------------------------------- inicializacao EVENTOS---------------------------------
    //Inicializa variável timer com FPS definido
    timer = al_create_timer(1.0 / FPS);

    //inicializa addon do teclado
    al_install_keyboard();

    //inicializa o mouse
    al_install_mouse();

    //Inicializa variável fila de eventos
    fila_eventos = al_create_event_queue();

    //registra  timer e teclado na fila de eventos
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    //inicia a contagem do timer
    al_start_timer(timer);

    //Cria variavel para receber o tipo de evento detectado
    ALLEGRO_EVENT evento;




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

            if(pause){

            }else{
                rodaJogo();
            }


            if(tempPause<120){
                pause = 1;
                tempPause++;
            }else if(tempPause==120){
                tempPause=999;
                posXNave = 80;
                posYNave = 150;
                pause = 0;

            }


            //Desenha objetos(com seu novo posicionamento) na tela
            al_draw_bitmap(backGround, posXBackGround, posYBackGround, 0);
            al_draw_rotated_bitmap(nave, (al_get_bitmap_width(nave))/2, (al_get_bitmap_height(nave))/2, posXNave, posYNave,angNave,0);
            al_draw_bitmap(obst, posXObst, posYObst, 0);
            al_draw_bitmap(obst2, posXObst2, posYObst2, 0);
            al_draw_bitmap(obst3, posXObst3, posYObst3, 0);
            al_draw_bitmap(explo, posXExploNave, posYExploNave, 0);
            al_draw_bitmap(vida1,posXVida1,posYVida1,0);
            al_draw_bitmap(vida2,posXVida2,posYVida2,0);
            al_draw_bitmap(vida3,posXVida3,posYVida3,0);
            al_draw_bitmap(tiro1,posXTiro1,posYNave,0);
            al_draw_bitmap(tiro2,posXTiro1+300,posYNave,0);

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
	//********************************************angNave= 2*ALLEGRO_PI;********************************
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

            if(cima){
                posYNave-= velDesloc;
                angNave=(6.10865);
            }else if(baixo){
                posYNave+= velDesloc;
                angNave=(0.174533);
                //angNave=(ALLEGRO_PI/8);
            }else{
                angNave= 2*ALLEGRO_PI;
            }

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
