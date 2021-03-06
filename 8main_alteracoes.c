#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>
#include <locale.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdbool.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <locale.h>

#define     FPS                     60
#define     TELA_LARGURA            800
#define     TELA_ALTURA             600
#define     TOLERANCIA              20
#define     TEMPO_JOGO_SEGUNDOS     60
#define     TEMPO_EXPLOSAO          10  //tempo em segundos = TEMPO_EXPLOSAO/60
#define     TELA_MENU               0
#define     TELA_ESCOLHA            1
#define     TELA_JOGO               2
#define     TELA_PAUSE              3
#define     TELA_RANKING            4
#define     NUM_JOGADORES           10

//--------------------------- PARAMETROS DO JOGO---------------------------------

// Vari�vel representando a janela principal
ALLEGRO_DISPLAY *janela = NULL;

//declara o timer do programa
ALLEGRO_TIMER *timer = NULL;


// Vari�vel representando a imagem
ALLEGRO_BITMAP *backGround = NULL;
ALLEGRO_BITMAP *cenario1 = NULL;
ALLEGRO_BITMAP *cenario2 = NULL;
ALLEGRO_BITMAP *cenario3 = NULL;
ALLEGRO_BITMAP *backGroundMenu = NULL;
ALLEGRO_BITMAP *backGroundEscolha = NULL;
ALLEGRO_BITMAP *backGroundRanking = NULL;
ALLEGRO_BITMAP *backGroundPause = NULL;
ALLEGRO_BITMAP *nave[3][3];
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
ALLEGRO_BITMAP *btPlayAgain = NULL;
ALLEGRO_BITMAP *btQuit = NULL;
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
bool jogoSalvo = 0;
int score = 0;
int somaScore = 0;
int tempJogo=0;
int telaAtual=TELA_MENU;
int vidas = 3;
char nomePlayer[50]={"\t\tNOME PLAYER\n"};
int caracter=0;
int rTime = 0;
int gTime = 255;
int bTime = 255;
int progressao = 10;
int tipoNave = 0;
int estadoNave = 0;

//Declara e inicializa Variaveis com a posi��o X dos objetos
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
int posXBtPlay = 85;
int posXBtExit = 417;
int posXBtPlayAgain = 88;
int posXBtQuit = 238;
int posXVida1 = 580;
int posXVida2 = 630;
int posXVida3 = 680;
int posXTime = 20;
int posXplusTime = 100;

//Declara e inicializa Variaveis com a posi��o Y dos objetos
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
int posYBtPlay = 305;
int posYBtExit = 305;
int posYBtPlayAgain = 132;
int posYBtQuit = 132;
int posYVida1 = 5;
int posYVida2 = 5;
int posYVida3 = 5;
int posYTextTime = 10;
int posYplusTime = 999;

//Angulo da nave
float angNave= 2*ALLEGRO_PI;
float angObst= 0.0;
float angObst2= 0.0;
float angObst3 = 0.0;
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


void resetJogo(){
score = 0;
somaScore = 0;
tempJogo=0;
vidas = 3;

//Declara e inicializa Variaveis com a posi��o X dos objetos
posXBackGround=0;
posXNave = 80;
posXTiro = 150;
posXTiro1 = 150;
posXTiro2 = 150;
posXTiro3 = 150;
posXObst = 1300;
posXObst2 = 1100;
posXObst3 = 800;
posXExploNave = 0;
posXExploObst = 0;
posXExploObst2 = 0;
posXExploObst3 = 0;
posXVilao = 900;
posXFogo = 25;
posXFumaca = 25;
posXMouse = 999;
posXMouseClick = 999;
posXBtPlay = 133;
posXBtExit = 465;
posXBtPlayAgain = 88;
posXBtQuit = 238;
posXVida1 = 750;
posXVida2 = 710;
posXVida3 = 670;

//Declara e inicializa Variaveis com a posi��o Y dos objetos
posYBackGround=0;
posYNave= 150;
posYTiro = 1800;
posYTiro1 = 1800;
posYTiro2 = 1800;
posYTiro3 = 1800;
posYObst = 200;
posYObst2 = 300;
posYObst3 = 100;
posYExploNave = 1800;
posYExploObst = 0;
posYExploObst2 = 0;
posYExploObst3 = 0;
posYVilao = 0;
posYMouse = 999;
posYMouseClick = 999;
posYBtPlay = 265;
posYBtExit = 265;
posYBtPlayAgain = 132;
posYBtQuit = 132;
posYVida1 = 5;
posYVida2 = 5;
posYVida3 = 5;

//Angulo da nave
angNave= 2*ALLEGRO_PI;

//Declara e inicializa Variaveis com a velocidade dos objetos
velNave= 5;
velTiro = 8;
velTiro1 = 8;
velTiro2 = 8;
velTiro3 = 8;
velObst  = 4;
velObst2 = 4;
velObst3 = 4;
velDesloc = 5;
velVilao = 3;
velFogo = 5;

//Declara e inicializa Variavel para contagem de tempo
tempExploNave = 999;
tempExploObst = 999;
tempExploObst2 = 999;
tempExploObst3 = 999;
posColisao = 999;
piscaNave=0;
}


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

int mousePosicao(ALLEGRO_BITMAP *botao, int posXBotao, int posYBotao){
    int posicao=0;
    if((posXMouse>=posXBotao)&&(posXMouse<=(posXBotao + al_get_bitmap_width(botao)))){
        if((posYMouse>=posYBotao)&&(posYMouse<=(posYBotao + al_get_bitmap_height(botao)))){
            posicao=1;
        }else{
            posicao=0;
        }
    }else{
        posicao=0;
    }
    return posicao;
}

int mouseClick(ALLEGRO_BITMAP *botao, int posXBotao, int posYBotao){
    int click=0;
    if((posXMouseClick>=posXBotao)&&(posXMouseClick<=(posXBotao + al_get_bitmap_width(botao)))){
        if((posYMouseClick>=posYBotao)&&(posYMouseClick<=(posYBotao + al_get_bitmap_height(botao)))){
            click=1;
            posXMouseClick=999;
            posYMouseClick=999;
        }else{
            click=0;
        }
    }else{
        click=0;
    }

    return click;
}

void telaMenu(){//----------------------------------------------------FUNCAO RESPONSALVEL PELO MENU
     al_draw_bitmap(btPlay, posXBtPlay, posYBtPlay, 0);
     al_draw_bitmap(btExit, posXBtExit, posYBtExit, 0);
     al_draw_bitmap(backGroundMenu, 0, 0, 0);

     if(mouseClick(btPlay, posXBtPlay, posYBtPlay)){
        telaAtual=TELA_ESCOLHA;
     }else if(mouseClick(btExit,posXBtExit,posYBtExit)){
         sair=1;
     }

     if(mousePosicao(btPlay, posXBtPlay, posYBtPlay)){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
        al_draw_bitmap(btPlay, posXBtPlay, posYBtPlay, 0);
     }else if(mousePosicao(btExit,posXBtExit,posYBtExit)){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
        al_draw_bitmap(btExit, posXBtExit, posYBtExit, 0);
     }else{
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
     }
}
void telaEscolha(){//----------------------------------------------------FUNCAO RESPONSALVEL PELO MENU
     //Monta a telaEscolha
     al_draw_bitmap(backGroundEscolha, 0, 0, 0);
     //al_draw_bitmap(cenario1, ((al_get_display_width(janela)/4)*1)-(al_get_bitmap_width(cenario1)/2), 200, 0);
     //al_draw_bitmap(cenario2, ((al_get_display_width(janela)/4)*2)-(al_get_bitmap_width(cenario2)/2), 200, 0);
     //al_draw_bitmap(cenario3, ((al_get_display_width(janela)/4)*3)-(al_get_bitmap_width(cenario3)/2), 200, 0);
     //al_draw_bitmap(nave[0][0], ((al_get_display_width(janela)/4)*1)-(al_get_bitmap_width(nave[0][0])/2), 150-(al_get_bitmap_height(nave[0][0])/2), 0);
     //al_draw_bitmap(nave[1][0], ((al_get_display_width(janela)/4)*2)-(al_get_bitmap_width(nave[1][0])/2), 150-(al_get_bitmap_height(nave[1][0])/2), 0);
     //al_draw_bitmap(nave[2][0], ((al_get_display_width(janela)/4)*3)-(al_get_bitmap_width(nave[2][0])/2), 150-(al_get_bitmap_height(nave[2][0])/2), 0);


     //Funcoes do mouse
     if(mousePosicao(nave[0][0], ((al_get_display_width(janela)/4)*1)-(al_get_bitmap_width(nave[0][0])/2),  150-(al_get_bitmap_height(nave[0][0])/2))){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
     }else if(mousePosicao(nave[1][0],((al_get_display_width(janela)/4)*2)-(al_get_bitmap_width(nave[1][0])/2), 150-(al_get_bitmap_height(nave[1][0])/2))){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
     }else if(mousePosicao(nave[2][0],((al_get_display_width(janela)/4)*3)-(al_get_bitmap_width(nave[2][0])/2), 150-(al_get_bitmap_height(nave[2][0])/2))){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
     }else if(mousePosicao(cenario1,((al_get_display_width(janela)/4)*1)-(al_get_bitmap_width(cenario1)/2), 200)){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
     }else if(mousePosicao(cenario2,((al_get_display_width(janela)/4)*2)-(al_get_bitmap_width(cenario2)/2), 200)){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
     }else if(mousePosicao(cenario3,((al_get_display_width(janela)/4)*3)-(al_get_bitmap_width(cenario3)/2), 200)){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
     }else{
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
     }


     if(mouseClick(nave[0][0], ((al_get_display_width(janela)/4)*1)-(al_get_bitmap_width(nave[0][0])/2),  150-(al_get_bitmap_height(nave[0][0])/2))){
        tipoNave=0;
        estadoNave=0;
     }else if(mouseClick(nave[1][0],((al_get_display_width(janela)/4)*2)-(al_get_bitmap_width(nave[1][0])/2), 150-(al_get_bitmap_height(nave[1][0])/2))){
        tipoNave=1;
        estadoNave=0;
     }else if(mouseClick(nave[2][0],((al_get_display_width(janela)/4)*3)-(al_get_bitmap_width(nave[2][0])/2), 150-(al_get_bitmap_height(nave[2][0])/2))){
        tipoNave=2;
        estadoNave=0;
     }else if(mouseClick(cenario1,((al_get_display_width(janela)/4)*1)-(al_get_bitmap_width(cenario1)/2), 200)){
        backGround = backGround;
     }else if(mouseClick(cenario2,((al_get_display_width(janela)/4)*2)-(al_get_bitmap_width(cenario2)/2), 200)){
        backGround = backGround;
     }else if(mouseClick(cenario3,((al_get_display_width(janela)/4)*3)-(al_get_bitmap_width(cenario3)/2), 200)){
        backGround = backGround;
     }

}
void telaPause(){//---------------------------------------------------FUNCAO RESPONSALVEL PELO PAUSE
    al_draw_bitmap(btPlay, posXBtPlay, posYBtPlay, 0);
    al_draw_bitmap(btExit, posXBtExit, posYBtExit, 0);
    al_draw_bitmap(backGroundMenu, 0, 0, 0);

    if(mouseClick(btPlay, posXBtPlay, posYBtPlay)){
        telaAtual=TELA_JOGO;
     }else if(mouseClick(btExit,posXBtExit,posYBtExit)){
         telaAtual=TELA_RANKING;
     }

     if(mousePosicao(btPlay, posXBtPlay, posYBtPlay)){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
     }else if(mousePosicao(btExit,posXBtExit,posYBtExit)){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
     }else{
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
     }

}

int abreArquivoDisco(char rankingPlayers[][50], int numJogadores, int score[]){
    FILE *arq;
    char texto[200];
    int result,i;

    printf("\nProcurando jogos salvos em Disco...");
    arq = fopen("savedGames/Jogos_Salvos.txt","r");
    if(arq == NULL) {
        printf("\nArquivo nao encontrado.\n    Criando novo arquivo...");
        //------------------------------------------------------------------------------------------
        for(i=0;i<NUM_JOGADORES;i++){
            strcpy(&rankingPlayers[i][0],"UNDEFINED PLAYER");
            score[i]=0;
        }
        arq = fopen("savedGames/Jogos_Salvos.txt","w");
        if(arq == NULL) {
            printf("Problemas na ABERTURA do arquivo linha 261\n");
        }
        result = fprintf(arq,"Posicao:\tPontuacao:\tNome:\n");
        if(result < 0)printf("Erro na escrita\n");
        for(i=0;i<NUM_JOGADORES;i++){
            result = fprintf(arq,"%i �\t\t",i+1);
            result = fprintf(arq,"%i\t\t",score[i]);
            result = fprintf(arq,"%s\n",rankingPlayers[i]);
            if(result < 0)printf("Erro na escrita\n");
        }
        fclose(arq);

        arq = fopen("savedGames/Jogos_Salvos.txt","r");
        if(arq == NULL) printf("\nErro ao abrir novo arquivo...");
        else printf("\nNovo Arquivo Criado com sucesso!!!");

        //------------------------------------------------------------------------------------------
    }
    fgets(texto,200,arq);//Le cabecaolho e descarta

    for(i=0;i<NUM_JOGADORES;i++){
        fscanf(arq,"%s", texto); //L� a posicao e descarta
        fscanf(arq,"%s", texto); //L� o "�" e descarta
        fscanf(arq,"%i", &score[i]); //L� a pontuacao e armazena
        fgets(&rankingPlayers[i],50,arq);  //L� o Nome do Player e armazena
    }

    fclose(arq);

    return 1;
}

int SalvaArquivoDisco(char rankingPlayers[][50], int numJogadores, int score[]){

    FILE *arq;
    int result,i;

    arq = fopen("savedGames/Jogos_Salvos.txt","w");
    if(arq == NULL) {
        printf("Problemas na ABERTURA do arquivo\n");
    }
    printf("\nSalvando os dados...");
    result = fprintf(arq,"Posicao:\tPontuacao:\tNome:\n");
    if(result < 0)printf("Erro na escrita\n");
    for(i=0;i<NUM_JOGADORES;i++){
        result = fprintf(arq,"%i �\t\t",i+1);
        result = fprintf(arq,"%i",score[i]);
        result = fprintf(arq,"%s\n",rankingPlayers[i]);
    }
    if(result < 0)printf("Erro na escrita\n");
    else printf("\n   Dados salvos com Sucesso!!!...");
    fclose(arq);

    return 1;
}

void telaRanking(){//-------------------------------------------------FUNCAO RESPONSALVEL PELO RANKING
    int rankingScore[NUM_JOGADORES],i;
    char rankingPlayers[NUM_JOGADORES][50], rankingFormatado[NUM_JOGADORES][80];

    if(!jogoSalvo){
        jogoSalvo = abreArquivoDisco(rankingPlayers,NUM_JOGADORES,rankingScore);

        for(i=0;i<NUM_JOGADORES;i++){
            if(rankingScore[i]==0){
                strcpy(&rankingPlayers[i],nomePlayer);
                rankingScore[i] = somaScore;
                break;
            }

        }
         if(i>=NUM_JOGADORES)printf("\n\n ***  Memoria cheia!!\n\nDelete os arquivos salvos!! ***\n\n");

        jogoSalvo = SalvaArquivoDisco(rankingPlayers,NUM_JOGADORES,rankingScore);
    }

    al_draw_bitmap(btPlayAgain, posXBtPlayAgain, posYBtPlayAgain, 0);
    al_draw_bitmap(btQuit, posXBtQuit, posYBtQuit, 0);
    al_draw_bitmap(backGroundRanking, 0, 0, 0);
    //SCORE FINAL
    al_draw_textf(textRank, al_map_rgb(255, 255, 0), 85, 250, ALLEGRO_ALIGN_LEFT, "%i",somaScore*progressao);

    //RANKING PLAYERS
    al_draw_textf(textRank, al_map_rgb(255, 255, 0), 450, 250, ALLEGRO_ALIGN_LEFT, "PLAYER 1: %i",somaScore*progressao);
    al_draw_textf(textRank, al_map_rgb(255, 255, 0), 450, 300, ALLEGRO_ALIGN_LEFT, "PLAYER 2: %i",somaScore*progressao);
    al_draw_textf(textRank, al_map_rgb(255, 255, 0), 450, 350, ALLEGRO_ALIGN_LEFT, "PLAYER 3: %i",somaScore*progressao);
    al_draw_textf(textRank, al_map_rgb(255, 255, 0), 450, 400, ALLEGRO_ALIGN_LEFT, "PLAYER 4: %i",somaScore*progressao);
    al_draw_textf(textRank, al_map_rgb(255, 255, 0), 450, 450, ALLEGRO_ALIGN_LEFT, "PLAYER 5: %i",somaScore*progressao);

    if(mouseClick(btPlayAgain, posXBtPlayAgain, posYBtPlayAgain)){
        telaAtual=TELA_MENU;
        jogoSalvo = 0;
        resetJogo();
     }else if(mouseClick(btQuit,posXBtQuit,posYBtQuit)){
         sair=1;
         jogoSalvo = 0;
     }

     if(mousePosicao(btPlayAgain, posXBtPlayAgain, posYBtPlayAgain)){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
     }else if(mousePosicao(btQuit,posXBtQuit,posYBtQuit)){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
     }else{
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
     }

}

void telaJogo(){//----------------------------------------------------FUNCAO RESPONSALVEL PELO JOGO

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
        //------------------------------------------------------------TRATAMENTO DA PROGRESS�O DE VELOCIDADE DO JOGO
        //PROGRESS�O
        if (score >= 10){
            velDesloc *= 1.1;
            velNave = velNave *1.1;
            progressao += 10;
            score = 0;
        }

        //------------------------------------------------------------SISTEMA DE VIDAS
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
        //------------------------------------------------------------TRATAMENTO DAS POSI��ES E VELOCIDADES(TODOS OS OBJETOS)
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
            posYObst2 = (rand() % 300) + 150;
            velObst2 = rand()% 7 + 1;
            score ++;
            somaScore ++;
            printf ("SomaScore:%i\n", somaScore);
        }
        //Posicionamento do obst3
        posXObst3 -= (velObst3+velNave);
        if(posXObst3<-50){
            posXObst3 = (rand()% 1000) + 830;
            posYObst3 = (rand()% 550) + 250;
            velObst3 = rand()% 7 + 1;
            score ++;
            somaScore ++;
            printf ("SomoScore:%i\n", somaScore);
        }


        //------------------------------------------------------------TRATAMENTO DAS COLIS�ES
        if (colisao(nave[tipoNave][estadoNave],posXNave,posYNave,obst,posXObst,posYObst)){
            tempExploNave = 0;
            posXExploNave = posXNave;
            posYExploNave = posYNave;
            posYNave = 1800;
            posXNave = 1800;
            posXObst = (rand()% 1100) + 850;
            posYObst = (rand()% 120) + 20;
            backGround = al_load_bitmap("img/backgroundExplo.jpg");
            vidas --;
            posXplusTime = 999;
            estadoNave++;
            if(estadoNave>2)estadoNave=2;
        }
        if (colisao(nave[tipoNave][estadoNave],posXNave,posYNave,obst2,posXObst2,posYObst2)){
            tempExploNave = 0;
            posXExploNave = posXNave;
            posYExploNave = posYNave;
            posYNave = 1800;
            posXNave = 1800;
            posXObst2 = (rand()% 1200) + 900;
            posYObst2 = (rand() % 130) + 150;
            backGround = al_load_bitmap("img/backgroundExplo.jpg");
            vidas --;
            posXplusTime = 999;
            estadoNave++;
            if(estadoNave>2)estadoNave=2;
        }
        if (colisao(nave[tipoNave][estadoNave],posXNave,posYNave,obst3,posXObst3,posYObst3)){
            tempExploNave = 0;
            posXExploNave = posXNave;
            posYExploNave = posYNave;
            posYNave = 1800;
            posXNave = 1800;
            posXObst3 = (rand()% 1000) + 830;
            posYObst3 = (rand()% 100) + 250;
            backGround = al_load_bitmap("img/backgroundExplo.jpg");
            vidas --;
            posXplusTime = 999;
            estadoNave++;
            if(estadoNave>2)estadoNave=2;
        }

        //------------------------------------------------------------TRATAMENTO DAS EXPLOS�ES
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
            backGround = al_load_bitmap("img/background.jpg");
        }
        if (colisao(nave[tipoNave][estadoNave],posXNave,posYNave,plusTime,posXplusTime,posYplusTime)){
            tempJogo = tempJogo - 120;
            posXplusTime = 999;
            posYplusTime = (rand()% 20) + 300;
            posXplusTime = (rand()% 1700) + 1300;
        }

        //------------------------------------------------------------LIMITE SUP E INF
        if (posYNave <= 10){
            posYNave = posYNave + 20;
        }
        if (posYNave >=550){
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
    al_draw_rotated_bitmap(nave[tipoNave][estadoNave], (al_get_bitmap_width(nave[tipoNave][estadoNave]))/2, (al_get_bitmap_height(nave[tipoNave][estadoNave]))/2, posXNave, posYNave,angNave,0);
    angObst+=0.0349066;
    angObst2-=0.0349066;
    angObst3+=0.0349066;
    al_draw_rotated_bitmap(obst, (al_get_bitmap_width(obst))/2, (al_get_bitmap_height(obst))/2, posXObst, posYObst,angObst,0);
    al_draw_rotated_bitmap(obst2, (al_get_bitmap_width(obst2))/2, (al_get_bitmap_height(obst2))/2, posXObst2, posYObst2,angObst2,0);
    al_draw_rotated_bitmap(obst3, (al_get_bitmap_width(obst3))/2, (al_get_bitmap_height(obst3))/2, posXObst3, posYObst3,angObst3,0);
    al_draw_bitmap(explo, posXExploNave, posYExploNave, 0);
    al_draw_bitmap(vida1,posXVida1,posYVida1,0);
    al_draw_bitmap(vida2,posXVida2,posYVida2,0);
    al_draw_bitmap(vida3,posXVida3,posYVida3,0);
    al_draw_bitmap(vilao, posXVilao, posYVilao, 0);
    al_draw_bitmap(plusTime,posXplusTime,posYplusTime,0);
    al_draw_textf(textScore, al_map_rgb(rTime, gTime, bTime), 250, 10, ALLEGRO_ALIGN_LEFT, "SCORE: %i",somaScore*progressao);
    al_draw_textf(textTime, al_map_rgb(rTime, gTime, bTime), 10 , 10, ALLEGRO_ALIGN_LEFT, "TIME: %i",TEMPO_JOGO_SEGUNDOS - (tempJogo/FPS));
}

int main(void){
    //------------------------------------- inicializacao Bibl. ALLEGRO -------------------------------------
    // Inicializa a Allegro
    al_init();

    //------------------------------------- Variaveis para ENVENTOS -------------------------------------
    //Variavel ponteiro para fila de enventos
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

    //------------------------------------- inicializacao JANELAS e IMAGENS ---------------------------------
    // Inicializa o add-on para utiliza��o de imagens
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // Configura a janela

    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    janela = al_create_display(TELA_LARGURA, TELA_ALTURA);

    // Carrega as imagens para o jogo
    backGround = al_load_bitmap("img/background.jpg");
    backGroundMenu = al_load_bitmap("img/menuInicial.jpg");
    backGroundEscolha = al_load_bitmap("img/backgroundEscolha.jpg");
    backGroundPause = al_load_bitmap("img/telaPause.jpg");
    backGroundRanking = al_load_bitmap("img/gameover.jpg");
    nave[0][0] = al_load_bitmap ("img/naveGenerica0_0.png");
    nave[0][1] = al_load_bitmap ("img/naveGenerica0_1.png");
    nave[0][2] = al_load_bitmap ("img/naveGenerica0_2.png");
    nave[1][0] = al_load_bitmap ("img/naveDarth1_0.png");
    nave[1][1] = al_load_bitmap ("img/naveDarth1_1.png");
    nave[1][2] = al_load_bitmap ("img/naveDarth1_2.png");
    nave[2][0] = al_load_bitmap ("img/naveHomer2_0.png");
    nave[2][1] = al_load_bitmap ("img/naveHomer2_1.png");
    nave[2][2] = al_load_bitmap ("img/naveHomer2_2.png");
    obst = al_load_bitmap ("img/asteroide.png");
    obst2 = al_load_bitmap ("img/asteroide.png");
    obst3 = al_load_bitmap ("img/asteroide.png");
    explo = al_load_bitmap ("img/explo.png");
    fogo = al_load_bitmap("img/fogo_small.png");
    vilao = al_load_bitmap("img/vilao.png");
    btPlay = al_load_bitmap("img/botaoInversoPlay.png");
    btExit = al_load_bitmap("img/botaoInversoExit.png");
    btPlayAgain = al_load_bitmap("img/boteosRanking.jpg");
    btQuit = al_load_bitmap("img/boteosRanking.jpg");
    vida1 = al_load_bitmap("img/vidasmall.png");
    vida2 = al_load_bitmap("img/vidasmall.png");
    vida3 = al_load_bitmap("img/vidasmall.png");
    cenario1 = al_load_bitmap("img/cenario1.jpg");
    cenario2 = al_load_bitmap("img/cenario2.jpg");
    cenario3 = al_load_bitmap("img/cenario3.jpg");
    textTime = al_load_font("fonte/alarm_clock/alarm_clock.ttf", 25, ALLEGRO_TTF_NO_KERNING);
    textRank = al_load_font("fonte/alarm_clock/alarm_clock.ttf", 50, ALLEGRO_TTF_NO_KERNING);
    textScore = al_load_font("fonte/alarm_clock/alarm_clock.ttf", 25, ALLEGRO_TTF_NO_KERNING);
    plusTime = al_load_bitmap("img/plusTime.png");

    //------------------------------------- inicializacao EVENTOS---------------------------------
    //Inicializa vari�vel timer com FPS definido
    timer = al_create_timer(1.0 / FPS);

    //inicializa addon do teclado
    al_install_keyboard();

    //inicializa addon do mouse
    al_install_mouse();

    // Atribui o cursor padr�o do sistema para ser usado
    al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    //Inicializa vari�vel fila de eventos
    fila_eventos = al_create_event_queue();

    //registra  timer, teclado e mouse na fila de eventos
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

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
                    sair=1;
                    break;
                    case TELA_ESCOLHA:
                    telaAtual=TELA_JOGO;
                    break;
                    case TELA_JOGO:
                    telaAtual=TELA_PAUSE;
                    break;
                    case TELA_PAUSE:
                    telaAtual=TELA_JOGO;
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
        //se o evento for uma tecla de texto...
        //https://www.rafaeltoledo.net/tutorial-allegro-5-14-entrada-de-texto/
        //****************************************************************************
	/*  if (evento.type == ALLEGRO_EVENT_KEY_CHAR){
            nomePlayer[caracter]=evento.keyboard.unichar;
            caracter++;
            nomePlayer[caracter]='\0';
            system("cls");
            printf("%s",nomePlayer);
         }
    */


        //****************************************************************************
        // Se o evento foi de movimenta��o do mouse
        //****************************************************************************
        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
            posXMouse = evento.mouse.x;
            posYMouse = evento.mouse.y;
            //printf("\n X do Mouse = %i", posXMouse);
            //printf("\n Y do Mouse = %i", posYMouse);
        }

        // Ou se o evento foi um clique do mouse
        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            posXMouseClick = evento.mouse.x;
            posYMouseClick = evento.mouse.y;
            printf("\n X do Click = %i", posXMouseClick);
            printf("\n Y do Click = %i", posYMouseClick);
        }

        //****************************************************************************
        //se o evento for Fechar Janela...
        //****************************************************************************
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                sair=1;
        }

        if(sair){
            int resp = al_show_native_message_box(janela,"Fechar","Seus dados serao perdidos\nDeseja realmente sair do programa?","",NULL,ALLEGRO_MESSAGEBOX_YES_NO);
            if (resp)sair=1;
            else sair=0;
        }
    }//Fecha while(sair)

    // Finaliza o timer, janela e fila_eventos
    al_destroy_timer(timer);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}//Fecha void main()
