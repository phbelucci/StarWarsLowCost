#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
#define     TELA_LARGURA            1920
#define     TELA_ALTURA             1080
#define     TOLERANCIA              50
#define     TEMPO_JOGO_SEGUNDOS     60
#define     TEMPO_EXPLOSAO          15  //tempo em segundos = TEMPO_EXPLOSAO/60
#define     TELA_MENU               0
#define     TELA_ESCOLHA            1
#define     TELA_JOGO               2
#define     TELA_PAUSE              3
#define     TELA_RANKING            4
#define     NUM_JOGADORES           10
#define     TAMANHO_NOME_PLAYER     10

//--------------------------- PARAMETROS DO JOGO---------------------------------

// Variável representando a janela principal
ALLEGRO_DISPLAY *janela = NULL;

//declara o timer do programa
ALLEGRO_TIMER *timer = NULL;


// Variável representando a imagem
ALLEGRO_BITMAP *backGround = NULL;
ALLEGRO_BITMAP *backGroundExplo = NULL;
ALLEGRO_BITMAP *backGroundCidade = NULL;
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
ALLEGRO_BITMAP *btNaveZero = NULL;
ALLEGRO_BITMAP *btNaveUm = NULL;
ALLEGRO_BITMAP *btNaveDois = NULL;
ALLEGRO_BITMAP *btCenarioEspaco = NULL;
ALLEGRO_BITMAP *btCenarioCidade = NULL;
ALLEGRO_BITMAP *btPlayJogo = NULL;
ALLEGRO_BITMAP *btPlayPause = NULL;
ALLEGRO_BITMAP *btExitPause = NULL;
ALLEGRO_BITMAP *vida1 = NULL;
ALLEGRO_BITMAP *vida2 = NULL;
ALLEGRO_BITMAP *vida3 = NULL;
ALLEGRO_BITMAP *plusTime = NULL;
ALLEGRO_BITMAP *plusScore = NULL;
ALLEGRO_FONT *textTime = NULL;
ALLEGRO_FONT *textRank = NULL;
ALLEGRO_FONT *textScoreJogo = NULL;
ALLEGRO_FONT *textNomePlayer = NULL;



//Declara e inicializa Variaveis de controle do jogo
bool sair = 0;
bool pause = 0;
bool jogoSalvo = 0;
int score = 0;
int somaScore = 0;
int tempJogo=0;
int telaAtual=TELA_MENU;
int vidas = 3;
char nomePlayer[TAMANHO_NOME_PLAYER]={"SEU NICK"};
int indexNome = -1;
int caracterPendente = 0;  // 0 - Não há letra a ser lida   e 1 - Letra  aguardando ser lida
char caracter='\0';    // Armazena o caractere digitado
bool teclaEnter = 0;
bool teclaApagar = 0;
int rTime = 0;
int gTime = 255;
int bTime = 255;
int progressao = 10;
int tipoNave = 0;
int estadoNave = 0;
int naveClick = 0;
int cenarioClick = 0;
int rankingScore[NUM_JOGADORES],i;
char rankingPlayers[NUM_JOGADORES][50];

//Declara e inicializa Variaveis com a posição X dos objetos
int posXBackGround=0;
int posXNave = 200;
int posXTiro = 150;
int posXTiro1 = 600;
int posXTiro2 = 150;
int posXTiro3 = 150;
int posXObst = 3000;
int posXObst2 = 2500;
int posXObst3 = 3300;
int posXExploNave = 0;
int posXExploObst = 4000;
int posXExploObst2 = 4000;
int posXExploObst3 = 40000;
int posXVilao = 900;
int posXFogo = 25;
int posXFumaca = 25;
int posXMouse = 4000;
int posXMouseClick = 4000;
int posXBtPlay = 495;
int posXBtExit = 1032;
int posXBtPlayAgain = 807;
int posXBtQuit = 1430;
int posXBtNaveZero = 303;
int posXBtNaveUm = 303;
int posXBtNaveDois = 303;
int posXBtCenarioEspaco = 1505;
int posXBtCenarioCidade = 1517;
int posXBtPlayJogo = 840;
int posXBtPlayPause = 248;
int posXBtExitPause = 1462;
int posXVida1 = 1600;
int posXVida2 = 1700;
int posXVida3 = 1800;
int posXTime = 20;
int posXplusTime = 4000;
int posXplusScore = 4000;

//Declara e inicializa Variaveis com a posição Y dos objetos
int posYBackGround=0;
int posYNave= 500;
int posYTiro = 1800;
int posYTiro1 = 500;
int posYTiro2 = 1800;
int posYTiro3 = 1800;
int posYObst = 300;
int posYObst2 = 500;
int posYObst3 = 800;
int posYExploNave = 3999;
int posYExploObst = 3000;
int posYExploObst2 = 3000;
int posYExploObst3 = 3000;
int posYVilao = 0;
int posYMouse = 4000;
int posYMouseClick = 4000;
int posYBtPlay = 560;
int posYBtExit = 560;
int posYBtPlayAgain = 110;
int posYBtQuit = 110;
int posYBtNaveZero = 85;
int posYBtNaveUm = 390;
int posYBtNaveDois = 690;
int posYBtCenarioEspaco = 160;
int posYBtCenarioCidade = 620;
int posYBtPlayJogo = 738;
int posYBtPlayPause = 283;
int posYBtExitPause = 280;
int posYVida1 = 20;
int posYVida2 = 20;
int posYVida3 = 20;
int posYTextTime = 20;
int posYplusTime = 2000;
int posYplusScore = 2000;

//Angulo da nave
float angNave= 2*ALLEGRO_PI;
float angObst= 0.0;
float angObst2= 0.0;
float angObst3 = 0.0;
float angPlusTime = 0.0;
float angPlusScore = 0.0;
//Declara e inicializa Variaveis com a velocidade dos objetos
float velNave= 10;
float velTiro = 8;
float velTiro1 = 8;
float velTiro2 = 8;
float velTiro3 = 8;
float velObst  = 4;
float velObst2 = 4;
float velObst3 = 4;
float velDesloc = 8;
float velVilao = 3;
float velFogo = 5;
float velPlusTime = 4;
float velPlusScore = 4;


//Declara e inicializa Variavel para contagem de tempo
int tempExploNave = 4000;
int tempExploObst = 4000;
int tempExploObst2 = 4000;
int tempExploObst3 = 4000;
int posColisao = 4000;
int piscaNave=0;

//Declara e inicializa Variaveis de controle do teclado
bool cima = 0;
bool baixo = 0;
bool freia = 0;
bool acelera = 0;


void resetJogo(){

    if (cenarioClick == 1){
        backGround = al_load_bitmap("img/back/1920/cenario/backgroundEspaco.jpg");
        backGroundExplo = al_load_bitmap("img/back/1920/cenario/backgroundEspacoExplo.jpg");
    }else if (cenarioClick ==2){
        backGround = al_load_bitmap("img/back/1920/cenario/backgroundCidade.jpg");
        backGroundExplo = al_load_bitmap("img/back/1920/cenario/backgroundCidadeExplo.jpg");
    }
    score = 0;
    somaScore = 0;
    tempJogo=0;
    vidas = 3;
    posColisao = 0;

    //Declara e inicializa Variaveis com a posição X dos objetos
    posXBackGround=0;
    posXNave = posXNave;
    posXObst = (rand()% TELA_LARGURA*1.5) + 2000;
    posXObst2 = (rand()% TELA_LARGURA*1.5) + 2000;
    posXObst3 = (rand()% TELA_LARGURA*1.5) + 2000;
    posXExploNave = 4000;
    posXExploObst = 4500;
    posXExploObst2 = 4500;
    posXExploObst3 = 4500;
    posXVilao = 900;
    posXFumaca = 25;
    posXFogo = 25;
    posXVida1 = 1600;
    posXVida2 = 1700;
    posXVida3 = 1800;

    //Declara e inicializa Variaveis com a posição Y dos objetos
    posYBackGround=0;
    posYObst = (rand()% 300) + 100;
    posYObst2 = (rand()% 600) + 350;
    posYObst3 = (rand()% 1000) + 400;
    posYExploNave = 4000;
    posYVida1 = 20;
    posYVida2 = 20;
    posYVida3 = 20;

    //Declara e inicializa Variaveis com a velocidade dos objetos
    velNave= 10;
    velObst  = 4;
    velObst2 = 4;
    velObst3 = 4;
    velDesloc = 8;
    velVilao = 3;
    velFogo = 5;

    //Declara e inicializa Variavel para contagem de tempo
    tempExploNave = 999;
    tempExploObst = 999;
    tempExploObst2 = 999;
    tempExploObst3 = 999;
    posColisao = 0;
    piscaNave=0;
}


//Funcao de colisao entre dois objetos
bool colisao(ALLEGRO_BITMAP *obj1, int posXObj1, int posYObj1, ALLEGRO_BITMAP *obj2,int posXObj2, int posYObj2){
    bool ok = false;
    int posX1Obj1 = posXObj1 + al_get_bitmap_width(obj1);
    int posY1Obj1 = posYObj1 + al_get_bitmap_height(obj1);
    int posX1Obj2 = posXObj2 + al_get_bitmap_width(obj2);
    int posY1Obj2 = posYObj2 + al_get_bitmap_height(obj2);

    if ( ( ( posXObj1>(posXObj2+TOLERANCIA))&&(posXObj1<(posX1Obj2-TOLERANCIA))) || ((posX1Obj1>(posXObj2+TOLERANCIA))&&(posX1Obj1<(posX1Obj2-TOLERANCIA)))){
        if ( ( ( posYObj1>(posYObj2+TOLERANCIA))&&(posYObj1<(posY1Obj2-TOLERANCIA))) || ((posY1Obj1>(posYObj2+TOLERANCIA))&&(posY1Obj1<(posY1Obj2-TOLERANCIA)))){
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
            posXMouseClick=4000;
            posYMouseClick=4000;
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
     al_draw_textf(textNomePlayer, al_map_rgb(255, 255, 0), 970, 631, ALLEGRO_ALIGN_CENTER, "%s",nomePlayer);

     if(indexNome==0){
        strcpy(nomePlayer,"SEU NICK");
     }
     if(caracterPendente){
        if(indexNome<0){
            indexNome = 0;
            strcpy(nomePlayer," ");
        }
        if(teclaApagar){
            indexNome--;
            caracter=' ';
        }
        if(indexNome<TAMANHO_NOME_PLAYER-1){
            nomePlayer[indexNome]=caracter;
            indexNome++;
            nomePlayer[indexNome] = '\0';
        }
        if(teclaApagar){
            indexNome--;
        }
        caracterPendente=0;
     }

     //Funcoes do mouse
     if(mousePosicao(btNaveZero, posXBtNaveZero, posYBtNaveZero)){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
        al_draw_bitmap(btNaveZero,posXBtNaveZero, posYBtNaveZero, 0);
     }else if(mousePosicao(btNaveUm, posXBtNaveUm, posYBtNaveUm)){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
        al_draw_bitmap(btNaveUm,posXBtNaveUm, posYBtNaveUm, 0);
     }else if(mousePosicao(btNaveDois, posXBtNaveDois, posYBtNaveDois)){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
        al_draw_bitmap(btNaveDois,posXBtNaveDois, posYBtNaveDois, 0);
     }else if(mousePosicao(btCenarioEspaco,posXBtCenarioEspaco, posYBtCenarioEspaco)){
        al_draw_bitmap(btCenarioEspaco, posXBtCenarioEspaco, posYBtCenarioEspaco, 0);
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
     }else if(mousePosicao(btCenarioCidade, posXBtCenarioCidade, posYBtCenarioCidade)){
        al_draw_bitmap(btCenarioCidade, posXBtCenarioCidade, posYBtCenarioCidade,0);
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
     }else if (mousePosicao(btPlayJogo, posXBtPlayJogo, posYBtPlayJogo)){
        al_draw_bitmap(btPlayJogo, posXBtPlayJogo, posYBtPlayJogo, 0);
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
     } else{
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
     }


     if(mouseClick(btNaveZero, posXBtNaveZero, posYBtNaveZero)){
        tipoNave=0;
        estadoNave=0;
        naveClick = 1;
     }else if(mouseClick(btNaveUm, posXBtNaveUm, posYBtNaveUm)){
        tipoNave=1;
        estadoNave=0;
        naveClick = 2;
     }else if(mouseClick(btNaveDois, posXBtNaveDois, posYBtNaveDois)){
        tipoNave=2;
        estadoNave=0;
        naveClick = 3;
     }else if(mouseClick(btCenarioEspaco, posXBtCenarioEspaco, posYBtCenarioEspaco)){
        cenarioClick = 1;
     }else if(mouseClick(btCenarioCidade, posXBtCenarioCidade, posYBtCenarioCidade)){
        cenarioClick = 2;
        rTime = 0;
        gTime = 0;
        bTime = 100;

     }else if(mouseClick(btPlayJogo, posXBtPlayJogo, posYBtPlayJogo)){
        if ((cenarioClick == 1)||(cenarioClick == 2)){
            resetJogo();
            telaAtual = TELA_JOGO;
        }else al_show_native_message_box(janela,"ATENCAO","DEIXE DE PREGUICA,\nESCOLHA UM CENARIO!","",NULL,ALLEGRO_MESSAGEBOX_WARN);
     }

     if (naveClick == 1){
        al_draw_bitmap(btNaveZero, posXBtNaveZero, posYBtNaveZero,0);
     } else if (naveClick == 2) {
        al_draw_bitmap(btNaveUm, posXBtNaveUm, posYBtNaveUm,0);
     } else if (naveClick == 3){
        al_draw_bitmap(btNaveDois, posXBtNaveDois, posYBtNaveDois,0);
     }
     if (cenarioClick == 1){
        al_draw_bitmap(btCenarioEspaco, posXBtCenarioEspaco, posYBtCenarioEspaco,0);
     } else if (cenarioClick == 2){
        al_draw_bitmap(btCenarioCidade, posXBtCenarioCidade, posYBtCenarioCidade,0);
     }

}
void telaPause(){//---------------------------------------------------FUNCAO RESPONSALVEL PELO PAUSE
    al_draw_bitmap(backGroundPause, 0, 0, 0);



    if(mouseClick(btPlayPause, posXBtPlayPause, posYBtPlayPause)){
        telaAtual = TELA_JOGO;
     }else if(mouseClick(btExitPause,posXBtExitPause,posYBtExitPause)){
         telaAtual = TELA_RANKING;
     }

     if(mousePosicao(btPlayPause, posXBtPlayPause, posYBtPlayPause)){
        al_draw_bitmap(btPlayPause, posXBtPlayPause, posYBtPlayPause, 0);
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
     }else if(mousePosicao(btExitPause,posXBtExitPause,posYBtExitPause)){
        al_draw_bitmap(btExitPause, posXBtExitPause, posYBtExitPause, 0);
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
     }else{
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
     }

}

int abreArquivoDisco(char rankingPlayersArq[][50], int numJogadores, int scoreArq[]){
    FILE *arq;
    char texto[200];
    int result,i;

    printf("\nProcurando jogos salvos em Disco...");
    arq = fopen("savedGames/Jogos_Salvos.txt","r");
    if(arq == NULL) {
        printf("\nArquivo nao encontrado.\n    Criando novo arquivo...");
        //------------------------------------------------------------------------------------------
        for(i=0;i<NUM_JOGADORES;i++){
            strcpy(&rankingPlayersArq[i][0],"[VAZIO]");
            scoreArq[i]=0;
        }
        arq = fopen("savedGames/Jogos_Salvos.txt","w");
        if(arq == NULL) {
            printf("Problemas na ABERTURA do arquivo linha 261\n");
        }
        result = fprintf(arq,"Posicao:\tPontuacao:\tNome:\n");
        if(result < 0)printf("Erro na escrita\n");
        for(i=0;i<NUM_JOGADORES;i++){
            result = fprintf(arq,"%i º\t\t",i+1);
            result = fprintf(arq,"%i\t\t",scoreArq[i]);
            result = fprintf(arq,"%s\n",rankingPlayersArq[i]);
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
        fscanf(arq,"%s", texto); //Lê a posicao e descarta
        fscanf(arq,"%s", texto); //Lê o "º" e descarta
        fscanf(arq,"%i", &scoreArq[i]); //Lê a pontuacao e armazena
        fgets(&rankingPlayersArq[i],50,arq);  //Lê o Nome do Player e armazena
    }

    fclose(arq);

    return 1;
}

int SalvaArquivoDisco(char rankingPlayersArq[][50], int numJogadores, int scoreArq[]){

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
        result = fprintf(arq,"%i º\t\t",i+1);
        result = fprintf(arq,"%i",scoreArq[i]);
        result = fprintf(arq,"%s\n",rankingPlayersArq[i]);
    }
    if(result < 0)printf("Erro na escrita\n");
    else printf("\n   Dados salvos com Sucesso!!!...");
    fclose(arq);

    return 1;
}

void telaRanking(){//-------------------------------------------------FUNCAO RESPONSALVEL PELO RANKING
    char txtF[TAMANHO_NOME_PLAYER]; // Recebe Texto Formatado

    if(!jogoSalvo){
        // ABRE OU CRIA UM AQUIVO E COPIA VALORES SALVOS PARA OS ARRAYS DE NOME E PONTUACAO
        jogoSalvo = abreArquivoDisco(rankingPlayers,NUM_JOGADORES,rankingScore);
        // INSERE OS DADOS DO ÚLTIMO JOGO REALIZADO NO PRIMEIRO ESPAÇO DISPONIVEL DOS ARRAYS
        for(i=0;i<NUM_JOGADORES;i++){
            if(rankingScore[i]==0){
                strcpy(&rankingPlayers[i],"\t\t");
                strcat(&rankingPlayers[i],&nomePlayer);
                strcat(&rankingPlayers[i],"\n");
                rankingScore[i] = somaScore*progressao;
                break;
            }
        }
        //SE NÃO HÁ ESPAÇO DISPONÍVEL NOS ARRAYS, INSERE DADOS DO ÚLTIMO JOGO NA ÚLTIMA LINHA DOS ARRAYS
        if(i>=NUM_JOGADORES){
            strcpy(&rankingPlayers[NUM_JOGADORES-1],"\t\t");
            strcat(&rankingPlayers[NUM_JOGADORES-1],&nomePlayer);
            strcat(&rankingPlayers[NUM_JOGADORES-1],"\n");
            rankingScore[NUM_JOGADORES-1] = somaScore*progressao;
        }

        //ORDENA OS ARRAYS DA MAIOR PARA A MENOR PONTUAÇÃO (DE CIMA PARA BAIXO RESPECTIVAMENTE)
            //IMPLEMENTAR AQUI ALGORITMO QUE ORDENA O ARRAY rankingScore[]
            //OBS: A CADA POSIÇÃO TROCADA NO rankingScore[], TROCAR A POSIÇÃO CORRESPONDENTE NO rankingPlayers[]

        //SALVA ARRAYS ATUALIZADOS NO ARQUIVO
        jogoSalvo = SalvaArquivoDisco(rankingPlayers,NUM_JOGADORES,rankingScore);
    }

    al_draw_bitmap(backGroundRanking, 0, 0, 0);

    //SCORE FINAL
    al_draw_textf(textScoreJogo, al_map_rgb(255, 255, 0), 270, 65, ALLEGRO_ALIGN_LEFT, "%i",somaScore*progressao);
    //RANKING PLAYERS
    int posYTextRanking = 180;
    for(i=0;i<NUM_JOGADORES;i++){
        strcpy(txtF, &rankingPlayers[i][2]);
        txtF[strlen(txtF)-1]='\0';
        txtF[TAMANHO_NOME_PLAYER-1]='\0';
        al_draw_text(textRank, al_map_rgb(255, 255, 0), 270, posYTextRanking, ALLEGRO_ALIGN_LEFT, txtF);
        al_draw_textf(textRank, al_map_rgb(255, 255, 0), 620, posYTextRanking, ALLEGRO_ALIGN_RIGHT, "%i", rankingScore[i]);
        posYTextRanking += 60;
    }

    if(mouseClick(btPlayAgain, posXBtPlayAgain, posYBtPlayAgain)){
        naveClick = 0;
        cenarioClick = 0;
        jogoSalvo = 0;
        strcpy(nomePlayer,"SEU NICK");
        indexNome = -1;
        telaAtual=TELA_MENU;
     }else if(mouseClick(btQuit,posXBtQuit,posYBtQuit)){
         jogoSalvo = 0;
         sair=1;
     }

     if(mousePosicao(btPlayAgain, posXBtPlayAgain, posYBtPlayAgain)){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
        al_draw_bitmap(btPlayAgain, posXBtPlayAgain, posYBtPlayAgain, 0);
     }else if(mousePosicao(btQuit,posXBtQuit,posYBtQuit)){
        al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
        al_draw_bitmap(btQuit, posXBtQuit, posYBtQuit, 0);
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
            if(posYNave!=500){
                posYNave=500;
                posXNave=150;
                angNave= 2*ALLEGRO_PI;
            }else{
                posYNave=4800;
            }
            piscaNave=0;
        }
        posColisao++;
    }else if(posColisao==120){//-------------------------------------RETOMADA DO JOGO APOS COLISAO
        posColisao=4000;
        posXNave = 150;
        posYNave = 500;

    }else{//----------------------------------------------------------ROTINA DO JOGO ATIVO
        //------------------------------------------------------------TRATAMENTO DA PROGRESSÃO DE VELOCIDADE DO JOGO
        //PROGRESSÃO
        if (score >= 10){
            velDesloc *= 1.1;
            velNave = velNave *1.1;
            progressao += 10;
            score = 0;
        }

        //------------------------------------------------------------SISTEMA DE VIDAS
            if (vidas<3){
                posXVida1 = 4000;
                posYVida1 = 4000;
            }
            if (vidas<2){
                posXVida2 = 4000;
                posYVida2 = 4000;
            }
            if (vidas<1){
                posXVida3 = 4000;
                posYVida3 = 4000;
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
        angPlusTime += (0.0349066)*2;
        posXplusTime -= (velPlusTime+velNave);
        if (posXplusTime <= -50){
            posYplusTime = (rand()% TELA_ALTURA-100) + 100;
            posXplusTime = (rand()% TELA_LARGURA*1.5) + 2000;
            velPlusTime = (rand()% 2) + 1;
        }
        //Posicionamento PlusScore
        angPlusScore += (0.0349066)*2;
        posXplusScore -= (velPlusScore+velNave);
        if (posXplusScore <= -50){
            posYplusScore = (rand()% TELA_ALTURA-100) + 100;
            posXplusScore = (rand()% TELA_LARGURA*1.5) + 2000;
            velPlusScore = (rand()% 2) + 1;
        }
        //Posicionamento do obst
        angObst+=0.0349066;
        posXObst -= (velObst+velNave);
        if(posXObst<-50){
            posXObst = (rand()% TELA_LARGURA*1.5) + 2000;
            posYObst = (rand()% 300) + 100;
            velObst = rand()% 7 + 1;
            score ++;
            somaScore ++;
            printf("SomaScore:%i\n", somaScore);
        }
        //Posicionamento do obst2
        angObst2-=0.0349066;
        posXObst2 -= (velObst2+velNave);
        if(posXObst2<-50){
            posXObst2 = (rand()% TELA_LARGURA*1.5) + 2000;
            posYObst2 = (rand()% 600) + 350;
            velObst2 = rand()% 7 + 1;
            score ++;
            somaScore ++;
            printf ("SomaScore:%i\n", somaScore);
        }
        //Posicionamento do obst3
        angObst3+=0.0349066;
        posXObst3 -= (velObst3+velNave);
        if(posXObst3<-50){
            posXObst3 = (rand()% TELA_LARGURA*1.5) + 2000;
            posYObst3 = (rand()% TELA_ALTURA-100) + 600;
            velObst3 = rand()% 7 + 1;
            score ++;
            somaScore ++;
            printf ("SomoScore:%i\n", somaScore);
        }

        //------------------------------------------------------------TRATAMENTO DAS COLISÕES
        if (colisao(nave[tipoNave][estadoNave],posXNave,posYNave,obst,posXObst,posYObst)){
            tempExploNave = 0;
            posXExploNave = posXNave;
            posYExploNave = posYNave-(al_get_bitmap_height(explo)-al_get_bitmap_height(nave[tipoNave][estadoNave]))/2;
            posYNave = 6000;
            posXNave = 6000;
            posXObst = (rand()% TELA_LARGURA*1.5) + 2000;
            posYObst = (rand()% 400) + 100;
            posXplusTime = (rand()% TELA_LARGURA*1.5) + 2000;
            vidas --;
            posXplusTime = 5000;
            posXplusScore = 5500;
            estadoNave++;
            if(estadoNave>2)estadoNave=2;
        }
        if (colisao(nave[tipoNave][estadoNave],posXNave,posYNave,obst2,posXObst2,posYObst2)){
            tempExploNave = 0;
            posXExploNave = posXNave;
            posYExploNave = posYNave-(al_get_bitmap_height(explo)-al_get_bitmap_height(nave[tipoNave][estadoNave]))/2;
            posYNave = 6500;
            posXNave = 7000;
            posXObst2 = (rand()% TELA_LARGURA*1.5) + 2000;
            posYObst2 = (rand()% 800) + 450;
            posXplusTime = (rand()% TELA_LARGURA*1.5) + 2000;
            vidas --;
            posXplusTime = 5000;
            posXplusScore = 5500;
            estadoNave++;
            if(estadoNave>2)estadoNave=2;
        }
        if (colisao(nave[tipoNave][estadoNave],posXNave,posYNave,obst3,posXObst3,posYObst3)){
            tempExploNave = 0;
            posXExploNave = posXNave;
            posYExploNave = posYNave-(al_get_bitmap_height(explo)-al_get_bitmap_height(nave[tipoNave][estadoNave]))/2;
            posYNave = 1800;
            posXNave = 1800;
            posXObst3 = (rand()% TELA_LARGURA*1.5) + 2000;
            posYObst3 = (rand()% TELA_ALTURA-al_get_bitmap_height(obst3)) + 700;
            posXplusTime = (rand()% TELA_LARGURA*1.5) + 2000;
            vidas --;
            posXplusTime = 5000;
            posXplusScore = 5500;
            estadoNave++;
            if(estadoNave>2)estadoNave=2;
        }

        if (colisao(nave[tipoNave][estadoNave],posXNave,posYNave,plusTime,posXplusTime,posYplusTime)){
            tempJogo = tempJogo - 120;
            posYplusTime = (rand()% 1000) + 100;
            posXplusTime = (rand()% TELA_LARGURA*1.5) + 2000;
        }

        if (colisao(nave[tipoNave][estadoNave],posXNave,posYNave,plusScore,posXplusScore,posYplusScore)){
            somaScore += 2;
            posYplusScore = (rand()% 1000) + 100;
            posXplusScore = (rand()% TELA_LARGURA*1.5) + 2000;
        }

        //------------------------------------------------------------TRATAMENTO DAS EXPLOSÕES
        if(tempExploNave<TEMPO_EXPLOSAO){
            posXExploNave -= velNave;
            tempExploNave++;
        }else if(tempExploNave==TEMPO_EXPLOSAO){
            posXExploNave = 5000;
            tempExploNave++;
            posColisao=0;
            posXObst = (rand()% TELA_LARGURA*1.5) + 2000;
            posYObst = (rand()% 300) + 50;
            posXObst2 = (rand()% TELA_LARGURA*1.5) + 2000;
            posYObst2 = (rand() % 600) + 320;
            posXObst3 = (rand()% TELA_LARGURA*1.5) + 2000;
            posYObst3 = (rand()% 1000) + 680;
            if (vidas<0){
                telaAtual = TELA_RANKING;
            }
        }

        //------------------------------------------------------------LIMITE SUP E INF
        if (posYNave <= al_get_bitmap_height(nave[tipoNave][estadoNave])/2){
            posYNave = al_get_bitmap_height(nave[tipoNave][estadoNave])/2;
        }
        if (posYNave >= TELA_ALTURA-al_get_bitmap_height(nave[tipoNave][estadoNave])/2){
            posYNave =  TELA_ALTURA-al_get_bitmap_height(nave[tipoNave][estadoNave])/2;
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
    if(tempExploNave>=TEMPO_EXPLOSAO)al_draw_bitmap(backGround, posXBackGround, posYBackGround, 0);
    else al_draw_bitmap(backGroundExplo, posXBackGround, posYBackGround, 0);
    al_draw_rotated_bitmap(nave[tipoNave][estadoNave], (al_get_bitmap_width(nave[tipoNave][estadoNave]))/2, (al_get_bitmap_height(nave[tipoNave][estadoNave]))/2, posXNave, posYNave,angNave,0);
    //al_draw_rotated_bitmap(obst, (al_get_bitmap_width(obst))/2, (al_get_bitmap_height(obst))/2, posXObst, posYObst,angObst,0);
    //al_draw_rotated_bitmap(obst2, (al_get_bitmap_width(obst2))/2, (al_get_bitmap_height(obst2))/2, posXObst2, posYObst2,angObst2,0);
    //al_draw_rotated_bitmap(obst3, (al_get_bitmap_width(obst3))/2, (al_get_bitmap_height(obst3))/2, posXObst3, posYObst3,angObst3,0);
    al_draw_bitmap(obst, posXObst, posYObst,0);
    al_draw_bitmap(obst2, posXObst2, posYObst2,0);
    al_draw_bitmap(obst3, posXObst3, posYObst3,0);
    al_draw_bitmap(explo, posXExploNave, posYExploNave, 0);
    al_draw_bitmap(vida1,posXVida1,posYVida1,0);
    al_draw_bitmap(vida2,posXVida2,posYVida2,0);
    al_draw_bitmap(vida3,posXVida3,posYVida3,0);
    //al_draw_bitmap(vilao, posXVilao, posYVilao, 0);
   // al_draw_rotated_bitmap(plusTime, (al_get_bitmap_width(plusTime))/4, (al_get_bitmap_height(plusTime))/4, posXplusTime, posYplusTime,angPlusTime,0);
    //al_draw_rotated_bitmap(plusScore, (al_get_bitmap_width(plusScore))/4, (al_get_bitmap_height(plusScore))/5, posXplusScore, posYplusScore,angPlusScore,0);
    al_draw_bitmap(plusScore, posXplusScore, posYplusScore,0);
    al_draw_bitmap(plusTime, posXplusTime, posYplusTime,0);
    al_draw_textf(textScoreJogo, al_map_rgb(rTime, gTime, bTime), 500, 10, ALLEGRO_ALIGN_LEFT, "SCORE: %i",somaScore*progressao);
    al_draw_textf(textTime, al_map_rgb(rTime, gTime, bTime), 20 , 10, ALLEGRO_ALIGN_LEFT, "TIME: %i",TEMPO_JOGO_SEGUNDOS - (tempJogo/FPS));
    if (ALLEGRO_KEY_SPACE){
        al_draw_bitmap(tiro1, posXTiro1, posYTiro1,0);
    }

}

int main(void){
    //------------------------------------- inicializacao Bibl. ALLEGRO -------------------------------------
    // Inicializa a Allegro
    al_init();

    //------------------------------------- Variaveis para ENVENTOS -------------------------------------
    //Variavel ponteiro para fila de enventos
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

    //------------------------------------- inicializacao JANELAS e IMAGENS ---------------------------------
    // Inicializa o add-on para utilização de imagens
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();


    // Configura a janela

    ALLEGRO_MONITOR_INFO info;

	int res_x_comp, res_y_comp;

	al_get_monitor_info(0, &info);

	res_x_comp = info.x2 - info.x1;
	res_y_comp = info.y2 - info.y1;

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	janela = al_create_display(res_x_comp, res_y_comp);
	printf("\nx_comp: %i    y_comp: %i", res_x_comp, res_y_comp);

	float red_x = res_x_comp / (float) TELA_LARGURA;
	float red_y = res_y_comp / (float) TELA_ALTURA;

	ALLEGRO_TRANSFORM transformar;

	al_identity_transform(&transformar);
	al_scale_transform(&transformar, red_x, red_y);
	al_use_transform(&transformar);

    // Carrega as imagens para o jogo
    backGround =            al_load_bitmap("img/back/1920/cenario/backGroundEspaco.jpg");
    backGroundCidade =      al_load_bitmap("img/back/1920/cenario/backGroundCidade.jpg");
    backGroundMenu =        al_load_bitmap("img/back/1920/menuInicial/menuInicial1920.jpg");
    backGroundEscolha =     al_load_bitmap("img/back/1920/telaEscolha/telaEscolha1920.jpg");
    backGroundPause =       al_load_bitmap("img/back/1920/telaPause/telaPause.jpg");
    backGroundRanking =     al_load_bitmap("img/back/1920/telaRanking/telaRanking.jpg");
    nave[0][0] =            al_load_bitmap("img/naves/naveZeroEstadoZero.png");
    nave[0][1] =            al_load_bitmap("img/naves/naveZeroEstadoUm.png");
    nave[0][2] =            al_load_bitmap("img/naves/naveZeroEstadoDois.png");
    nave[1][0] =            al_load_bitmap("img/naves/naveUmEstadoZero.png");
    nave[1][1] =            al_load_bitmap("img/naves/naveUmEstadoZero.png");
    nave[1][2] =            al_load_bitmap("img/naves/naveUmEstadoZero.png");
    nave[2][0] =            al_load_bitmap("img/naves/naveDoisEstadoZero.png");
    nave[2][1] =            al_load_bitmap("img/naves/naveDoisEstadoZero.png");
    nave[2][2] =            al_load_bitmap("img/naves/naveDoisEstadoZero.png");
    btNaveZero =            al_load_bitmap("img/back/1920/telaEscolha/botaoInversoNaveZero.png");
    btNaveUm =              al_load_bitmap("img/back/1920/telaEscolha/botaoInversoNaveUm.png");
    btNaveDois =            al_load_bitmap("img/back/1920/telaEscolha/botaoInversoNaveDois.png");
    btCenarioEspaco =       al_load_bitmap("img/back/1920/telaEscolha/botaoInversoCenarioEspaco.png");
    btCenarioCidade =       al_load_bitmap("img/back/1920/telaEscolha/botaoInversoCenarioCidade.png");
    btPlayJogo =            al_load_bitmap("img/back/1920/telaEscolha/botaoInversoPlayJogo.png");
    obst =                  al_load_bitmap("img/asteroide.png");
    obst2 =                 al_load_bitmap("img/asteroide.png");
    obst3 =                 al_load_bitmap("img/asteroide.png");
    explo =                 al_load_bitmap("img/explo.png");
    fogo =                  al_load_bitmap("img/fogo_small.png");
    //vilao =               al_load_bitmap("img/vilao.png");
    btPlay =                al_load_bitmap("img/back/1920/menuInicial/botaoInversoPlay.png");
    btExit =                al_load_bitmap("img/back/1920/menuInicial/botaoInversoExit.png");
    btPlayAgain =           al_load_bitmap("img/back/1920/telaRanking/botaoInversoPlayAgain.png");
    btQuit =                al_load_bitmap("img/back/1920/telaRanking/botaoInversoQuit.png");
    btPlayPause =           al_load_bitmap("img/back/1920/telaPause/botaoInversoPlayPause.png");
    btExitPause =           al_load_bitmap("img/back/1920/telaPause/botaoInversoExitPause.png");
    vida1 =                 al_load_bitmap("img/vidasmall.png");
    vida2 =                 al_load_bitmap("img/vidasmall.png");
    vida3 =                 al_load_bitmap("img/vidasmall.png");
    plusTime =              al_load_bitmap("img/plusTime.png");
    plusScore =             al_load_bitmap("img/plusScore.png");
    tiro1   =               al_load_bitmap("img/tiroUm.png");
    textTime =              al_load_font("fonte/alarm_clock/alarm_clock.ttf", 80, ALLEGRO_TTF_NO_KERNING);
    textRank =              al_load_font("fonte/alarm_clock/alarm_clock.ttf", 40, ALLEGRO_TTF_NO_KERNING);
    textScoreJogo =         al_load_font("fonte/alarm_clock/alarm_clock.ttf", 80, ALLEGRO_TTF_NO_KERNING);
    textNomePlayer =        al_load_font("fonte/alarm_clock/alarm_clock.ttf", 100, ALLEGRO_TTF_NO_KERNING);


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
                    sair=1;
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
            case ALLEGRO_KEY_BACKSPACE:
            teclaApagar = 1;
            break;
            case ALLEGRO_KEY_ENTER:
            teclaEnter = 1;
            break;
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
                case ALLEGRO_KEY_BACKSPACE:
                teclaApagar = 0;
                break;
                case ALLEGRO_KEY_ENTER:
                teclaEnter = 0;
                break;
            }

        }
        //****************************************************************************
        //se o evento for uma tecla de texto...
        //https://www.rafaeltoledo.net/tutorial-allegro-5-14-entrada-de-texto/
        //****************************************************************************
        else if (evento.type == ALLEGRO_EVENT_KEY_CHAR){
            caracter = (char)evento.keyboard.unichar;
            if((caracter >= 97)&&(caracter <= 122))caracter-=32;
            if((isalnum((int)caracter))||(caracter==8)||(caracter==32))caracterPendente = 1;
            printf("\n%c", caracter);

        }

        //****************************************************************************
        // Se o evento foi de movimentação do mouse
        //****************************************************************************
        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
            posXMouse = evento.mouse.x/red_x;
            posYMouse = evento.mouse.y/red_y;
            //printf("\n X do Mouse = %i", posXMouse);
            //printf("\n Y do Mouse = %i", posYMouse);
        }

        // Ou se o evento foi um clique do mouse
        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            posXMouseClick = evento.mouse.x/red_x;
            posYMouseClick = evento.mouse.y/red_y;
            printf("\n X do Click = %i", posXMouseClick);
            printf("\n Y do Click = %i", posYMouseClick);

        }

        //****************************************************************************
        //se o evento for Fechar Janela...
        //****************************************************************************
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                sair=1;
        }

        //if(sair){
           //int resp = al_show_native_message_box(janela,"Fechar","Seus dados serao perdidos\nDeseja realmente sair do programa?","",NULL,ALLEGRO_MESSAGEBOX_YES_NO);
            //if (resp)sair=1;
            //else sair=0;
       // }
    }//Fecha while(sair)

    // Finaliza o timer, janela e fila_eventos
    al_destroy_timer(timer);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}//Fecha void main()
