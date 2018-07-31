#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <locale.h>

#define     FPS                     60
#define     TELA_LARGURA            800
#define     TELA_ALTURA             400
#define     TOLERANCIA              10
#define     TEMPO_JOGO_SEGUNDOS     60
#define     TEMPO_EXPLOSAO          10  //tempo em segundos = TEMPO_EXPLOSAO/60
#define     TELA_MENU               0
#define     TELA_ESCOLHA            1
#define     TELA_JOGO               2
#define     TELA_PAUSE              3
#define     TELA_RANKING            4


//--------------------------- PARAMETROS DO JOGO---------------------------------
//declara o timer do programa
ALLEGRO_TIMER *timer = NULL;


// Variável representando a imagem
ALLEGRO_BITMAP *backGround = NULL;
ALLEGRO_BITMAP *backGroundMenu = NULL;
ALLEGRO_BITMAP *backGroundEscolha = NULL;
ALLEGRO_BITMAP *backGroundRanking = NULL;
ALLEGRO_BITMAP *backGroundPause = NULL;
ALLEGRO_BITMAP *nave = NULL;
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
ALLEGRO_BITMAP *btPlay = NULL;
ALLEGRO_BITMAP *btExit = NULL;
ALLEGRO_BITMAP *vida1 = NULL;
ALLEGRO_BITMAP *vida2 = NULL;
ALLEGRO_BITMAP *vida3 = NULL;
ALLEGRO_BITMAP *plusTime = NULL;
ALLEGRO_FONT *textTime = NULL;
ALLEGRO_FONT *textRank = NULL;
ALLEGRO_FONT *textScore = NULL;


//Declara e inicializa Variaveis de controle do jogo

bool sair = 0;
bool pause = 0;
int score = 0;
int somaScore = 0;
int tempJogo=0;
int telaAtual=TELA_MENU;
int vidas = 3;
int trocaNave = 3;
int rTime = 0;
int gTime = 255;
int bTime = 255;
int progressao = 10;
char ranking[10][2];
char nomePlayer[50];
int scorePlayer;

//Declara e inicializa Variaveis com a posição X dos objetos


int posXBackGround=0;
int posXNave = 80;
int posXTiro = 150;
int posXTiro1 = 150;
int posXTiro2 = 150;
int posXTiro3 = 150;
int posXObst = 1300;
int posXObst2 = 1100;
int posXObst3 = 800;
int posXExploNave = 0;
int posXExploObst = 0;
int posXExploObst2 = 0;
int posXExploObst3 = 0;
int posXVilao = 900;
int posXFogo = 25;
int posXFumaca = 25;
int posXMouse = 999;
int posXMouseClick = 999;
int posXBtPlay = 90;
int posXBtExit = 290;
int posXVida1 = 750;
int posXVida2 = 710;
int posXVida3 = 670;
int posXTime = 20;
int posXplusTime = 100;

//Declara e inicializa Variaveis com a posição Y dos objetos
int posYBackGround=0;
int posYNave= 150;
int posYTiro = 1800;
int posYTiro1 = 1800;
int posYTiro2 = 1800;
int posYTiro3 = 1800;
int posYObst = 200;
int posYObst2 = 300;
int posYObst3 = 100;
int posYExploNave = 1800;
int posYExploObst = 0;
int posYExploObst2 = 0;
int posYExploObst3 = 0;
int posYVilao = 0;
int posYMouse = 999;
int posYMouseClick = 999;
int posYBtPlay = 190;
int posYBtExit = 190;
int posYVida1 = 5;
int posYVida2 = 5;
int posYVida3 = 5;
int posYTextTime = 10;
int posYplusTime = 999;

//Angulo da nave
float angNave= 2*ALLEGRO_PI;

//Declara e inicializa Variaveis com a velocidade dos objetos
float velNave= 5;
float velTiro = 8;
float velTiro1 = 8;
float velTiro2 = 8;
float velTiro3 = 8;
float velObst  = 4;
float velObst2 = 4;
float velObst3 = 4;
float velDesloc = 5;
float velVilao = 3;
float velFogo = 5;
float velPlusTime = 4;


//Declara e inicializa Variavel para contagem de tempo
int tempExploNave = 999;
int tempExploObst = 999;
int tempExploObst2 = 999;
int tempExploObst3 = 999;
int posColisao = 999;
int piscaNave=0;

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

int mouseClick(ALLEGRO_BITMAP *botao, int posXBotao, int posYBotao){
    int click=0;
    if((posXMouseClick>=posXBotao)&&(posXMouseClick<=(posXBotao + al_get_bitmap_width(botao)))){
        if((posYMouseClick>=posYBotao)&&(posYMouseClick<=(posYBotao + al_get_bitmap_height(botao)))){
            click=1;
            posXMouseClick=999;
            posYMouseClick=999;
        }
    }else{
        click=0;
        posXMouseClick=999;
        posYMouseClick=999;
    }

    return click;
}

void telaMenu(){//----------------------------------------------------FUNCAO RESPONSALVEL PELO MENU
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
     al_draw_bitmap(btPlay, 90, 275, 0);
     al_draw_bitmap(btExit, 424, 275, 0);
     al_draw_bitmap(backGroundMenu, 50, 0, 0);

     if(mouseClick(btPlay, posXBtPlay, posYBtPlay)){
        telaAtual=TELA_ESCOLHA;

     }else if(mouseClick(btExit,posXBtExit,posYBtExit)){
         sair=1;
     }
}
void telaEscolha(){//----------------------------------------------------FUNCAO RESPONSALVEL PELO MENU
     al_draw_bitmap(backGroundEscolha, 50, 0, 0);
     al_set_new_display_flags(ALLEGRO_RESIZABLE);

}
void telaPause(){//---------------------------------------------------FUNCAO RESPONSALVEL PELO PAUSE
    al_draw_bitmap(backGroundPause, 0, 0, 0);
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
}
void telaRanking(){//-------------------------------------------------FUNCAO RESPONSALVEL PELO RANKING
    al_draw_bitmap(backGroundRanking, 50, 0, 0);
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    //SCORE FINAL
    al_draw_textf(textRank, al_map_rgb(255, 255, 0), 85, 250, ALLEGRO_ALIGN_LEFT, "%i",somaScore*progressao);
    //RANKING PLAYERS
    al_draw_textf(textRank, al_map_rgb(255, 255, 0), 410, 140, ALLEGRO_ALIGN_LEFT, "PLAYER 1: %i",somaScore*progressao);
    al_draw_textf(textRank, al_map_rgb(255, 255, 0), 410, 190, ALLEGRO_ALIGN_LEFT, "PLAYER 2: %i",somaScore*progressao);
    al_draw_textf(textRank, al_map_rgb(255, 255, 0), 410, 240, ALLEGRO_ALIGN_LEFT, "PLAYER 3: %i",somaScore*progressao);
    al_draw_textf(textRank, al_map_rgb(255, 255, 0), 410, 290, ALLEGRO_ALIGN_LEFT, "PLAYER 4: %i",somaScore*progressao);
    al_draw_textf(textRank, al_map_rgb(255, 255, 0), 410, 340, ALLEGRO_ALIGN_LEFT, "PLAYER 5: %i",somaScore*progressao);

}

void telaJogo(){//----------------------------------------------------FUNCAO RESPONSALVEL PELO JOGO

    setlocale(LC_ALL,"portuguese");

    //POSICIONAMENTO
    if(posColisao<120){//---------------------------------------------PAUSA APOS OCORRENCIA DE COLISAO(JOGO INATIVO)
        //------------------------------------------------------------MANTEM BACKGROUND EM MOVIMENTO
        posXBackGround -= velNave;
        if(posXBackGround<=(TELA_LARGURA*-2)){
            posXBackGround=0;
        }
        //------------------------------------------------------------PISCA NAVE ENQUANTO AGUARDA RETOMADA DO JOGO
        piscaNave++;
        if(piscaNave>=(120/20)){
            if(posYNave!=150){
                posYNave=150;
                posXNave=80;
                angNave= 2*ALLEGRO_PI;
            }else{
                posYNave=999;
            }
            piscaNave=0;
        }
        posColisao++;
    }else if(posColisao==120){//-------------------------------------RETOMADA DO JOGO APOS COLISAO
        posColisao=999;
        posXNave = 80;
        posYNave = 150;

    }else{//----------------------------------------------------------ROTINA DO JOGO ATIVO
        //------------------------------------------------------------TRATAMENTO DA PROGRESSÃO DE VELOCIDADE DO JOGO
        //PROGRESSÃO

        printf ("\n%i", posXplusTime);
        printf("\n%i", posYplusTime);
        if (score >= 10){
            velDesloc *= 1.15;
            velNave = velNave *1.15;
            progressao += 10;
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
            if (vidas<0){
                telaAtual = TELA_RANKING;
            }
        //------------------------------------------------------------TRATAMENTO DAS POSIÇÕES E VELOCIDADES(TODOS OS OBJETOS)
        //Posicionamento do background (VELOCIDADE DA NAVE)
        posXBackGround -= velNave;
        if(posXBackGround<=(TELA_LARGURA*-2)){
            posXBackGround=0;
        }
         //Posicionamento Vilao
        posXVilao -= velVilao;
        if(posXObst<-50){
            posXVilao -- ;
        }
        //Posicionamento PlusTime
        posXplusTime -= (velPlusTime+velNave);
        if (posXplusTime <= -50){
            posYplusTime = (rand()% 300) + 20;
            posXplusTime = (rand()% 1700) + 1300;
            velPlusTime = (rand()% 2) + 1;
        }

        //Posicionamento do obst
        posXObst -= (velObst+velNave);
        if(posXObst<-50){
            posXObst = (rand()% 1100) + 850;
            posYObst = (rand()% 120) + 20;
            velObst = rand()% 7 + 1;
            score ++;
            somaScore ++;
            printf("SomaScore:%i\n", somaScore);
        }
        //Posicionamento do obst2
        posXObst2 -= (velObst2+velNave);
        if(posXObst2<-50){
            posXObst2 = (rand()% 1200) + 900;
            posYObst2 = (rand() % 130) + 150;
            velObst2 = rand()% 7 + 1;
            score ++;
            somaScore ++;
            printf ("SomaScore:%i\n", somaScore);
        }
        //Posicionamento do obst3
        posXObst3 -= (velObst3+velNave);
        if(posXObst3<-50){
            posXObst3 = (rand()% 1000) + 830;
            posYObst3 = (rand()% 100) + 250;
            velObst3 = rand()% 7 + 1;
            score ++;
            somaScore ++;
            printf ("SomoScore:%i\n", somaScore);
        }


        //------------------------------------------------------------TRATAMENTO DAS COLISÕES
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
            posXplusTime = 999;
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
            posXplusTime = 999;
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
            posXplusTime = 999;
            printf ("%i", vidas);
            nave = al_load_bitmap("img/nave_colisao1.png");
            if (vidas <2){
                nave = al_load_bitmap("img/nave_colisao2.png");
            }

        }
        if (colisao(nave,posXNave,posYNave,plusTime,posXplusTime,posYplusTime)){
            tempJogo = tempJogo - 120;
            posXplusTime = 999;
            posYplusTime = (rand()% 20) + 300;
            posXplusTime = (rand()% 1700) + 1300;


        }

        //------------------------------------------------------------TRATAMENTO DAS EXPLOSÕES
        if(tempExploNave<TEMPO_EXPLOSAO){
            tempExploNave++;
        }else if(tempExploNave==TEMPO_EXPLOSAO){
            posXExploNave = 1800;
            tempExploNave++;
            posColisao=0;
            posXObst = (rand()% 1100) + 850;
            posYObst = (rand()% 120) + 20;
            posXObst2 = (rand()% 1200) + 900;
            posYObst2 = (rand() % 130) + 150;
            posXObst3 = (rand()% 1000) + 830;
            posYObst3 = (rand()% 100) + 250;
            backGround = al_load_bitmap("img/background1.jpg");
        }

        //------------------------------------------------------------LIMITE SUP E INF
        if (posYNave <= 0){
            posYNave = posYNave + 20;
        }
        if (posYNave >=360){
            posYNave = posYNave -10;
        }

        //------------------------------------------------------------CONTROLES DO TECLADO
        if(cima){
            posYNave-= velDesloc;
            angNave=(6.10865);
        }else if(baixo){
            posYNave+= velDesloc;
            angNave=(0.174533);
        }else{
            angNave= 2*ALLEGRO_PI;
        }
        if(freia){
            velNave-=0.1;
            if (velNave <=1)velNave=1;
        }
        if(acelera)velNave+=0.1;

        //------------------------------------------------------------CONTROLA TEMPO DE JOGO
        tempJogo++;
        if(tempJogo>TEMPO_JOGO_SEGUNDOS*FPS){
            telaAtual=TELA_RANKING;
        }
    }

    //------------------------------------------------------------Desenha/Atualiza objetos na tela
    al_draw_bitmap(backGround, posXBackGround, posYBackGround, 0);
    al_draw_rotated_bitmap(nave, (al_get_bitmap_width(nave))/2, (al_get_bitmap_height(nave))/2, posXNave, posYNave,angNave,0);
    al_draw_bitmap(obst, posXObst, posYObst, 0);
    al_draw_bitmap(obst2, posXObst2, posYObst2, 0);
    al_draw_bitmap(obst3, posXObst3, posYObst3, 0);
    al_draw_bitmap(explo, posXExploNave, posYExploNave, 0);
    al_draw_bitmap(vida1,posXVida1,posYVida1,0);
    al_draw_bitmap(vida2,posXVida2,posYVida2,0);
    al_draw_bitmap(vida3,posXVida3,posYVida3,0);
    al_draw_bitmap(plusTime,posXplusTime,posYplusTime,0);
    al_draw_textf(textScore, al_map_rgb(rTime, gTime, bTime), 250, 10, ALLEGRO_ALIGN_LEFT, "SCORE: %i",somaScore*progressao);
    al_draw_textf(textTime, al_map_rgb(rTime, gTime, bTime), 10 , 10, ALLEGRO_ALIGN_LEFT, "TIME: %i",TEMPO_JOGO_SEGUNDOS - (tempJogo/FPS));


}

int main(void){
    //------------------------------------- inicializacao Bibl. ALLEGRO -------------------------------------
    // Inicializa a Allegro
    al_init();

    //------------------------------------- Variaveis para JANELAS/IMAGENS -------------------------------------
    // Variável representando a janela principal
    ALLEGRO_DISPLAY *janela = NULL;


    //------------------------------------- Variaveis para ENVENTOS -------------------------------------
    //Variavel ponteiro para fila de enventos
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

    //------------------------------------- inicializacao JANELAS e IMAGENS ---------------------------------
    // Inicializa o add-on para utilização de imagens
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // Configura a janela
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    janela = al_create_display(TELA_LARGURA, TELA_ALTURA);

    // Carrega as imagens para o jogo
    backGround = al_load_bitmap("img/background1.jpg");
    backGroundMenu = al_load_bitmap("img/menuInicial.jpg");
    backGroundEscolha = al_load_bitmap("img/background1.jpg");
    backGroundPause = al_load_bitmap("img/background1.jpg");
    backGroundRanking = al_load_bitmap("img/gameover.jpg");
    nave = al_load_bitmap ("img/nave2 (2).png");
    tiro = al_load_bitmap ("img/tiro.png");
    tiro1 = al_load_bitmap ("img/tiro.png");
    tiro2 = al_load_bitmap ("img/tiro.png");
    tiro3 = al_load_bitmap ("img/tiro.png");
    obst = al_load_bitmap ("img/asteroide.png");
    obst2 = al_load_bitmap ("img/asteroide.png");
    obst3 = al_load_bitmap ("img/asteroide.png");
    explo = al_load_bitmap ("img/explo.png");
    fogo = al_load_bitmap("img/fogo_small.png");
    vilao = al_load_bitmap("img/vilao.png");
    btPlay = al_load_bitmap("img/btPlay.jpg");
    btExit = al_load_bitmap("img/btExit.jpg");
    vida1 = al_load_bitmap("img/vidasmall.png");
    vida2 = al_load_bitmap("img/vidasmall.png");
    vida3 = al_load_bitmap("img/vidasmall.png");
    textTime = al_load_font("fonte/alarm_clock/alarm_clock.ttf", 25, ALLEGRO_TTF_NO_KERNING);
    textRank = al_load_font("fonte/alarm_clock/alarm_clock.ttf", 35, ALLEGRO_TTF_NO_KERNING);
    textScore = al_load_font("fonte/alarm_clock/alarm_clock.ttf", 25, ALLEGRO_TTF_NO_KERNING);
    plusTime = al_load_bitmap("img/plusTime.png");

    //------------------------------------- inicializacao EVENTOS---------------------------------
    //Inicializa variável timer com FPS definido
    timer = al_create_timer(1.0 / FPS);

    //inicializa addon do teclado
    al_install_keyboard();

    //inicializa addon do mouse
    al_install_mouse();

    // Atribui o cursor padrão do sistema para ser usado
    al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    //Inicializa variável fila de eventos
    fila_eventos = al_create_event_queue();

    //registra  timer, teclado e mouse na fila de eventos
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_mouse_event_source());

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

            if(telaAtual==TELA_MENU){
                telaMenu();
            }else if (telaAtual==TELA_ESCOLHA){
                telaEscolha();
            }else if(telaAtual==TELA_JOGO){
                telaJogo();
            }else if(telaAtual == TELA_PAUSE){
                telaPause();
            }else if(telaAtual == TELA_RANKING){
                telaRanking();
            }

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
                switch(telaAtual){
                    case TELA_MENU:
                    telaAtual=TELA_ESCOLHA;
                    break;
                    case TELA_ESCOLHA:
                    telaAtual=TELA_JOGO;
                    break;
                    case TELA_JOGO:
                    telaAtual=TELA_PAUSE;
                    break;
                    case TELA_PAUSE:
                    telaAtual=TELA_RANKING;
                    break;
                    case TELA_RANKING:
                    sair = 1;
                    break;
                }
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

        //****************************************************************************
        // Se o evento foi de movimentação do mouse
        //****************************************************************************
        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
            posXMouse = evento.mouse.x;
            posYMouse = evento.mouse.y;
            //printf("\n X do Mouse = %i", posXMouse);
            //printf("\n Y do Mouse = %i", posYMouse);
        }
        else{
            posXMouse = 999;
            posYMouse = 999;
        }

        // Ou se o evento foi um clique do mouse
        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            posXMouseClick = evento.mouse.x;
            posYMouseClick = evento.mouse.y;
            printf("\n X do Click = %i", posXMouseClick);
            printf("\n Y do Click = %i", posYMouseClick);
        }
    }

    // Finaliza o timer, janela e fila_eventos
    al_destroy_timer(timer);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}
