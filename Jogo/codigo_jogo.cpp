#include <stdio.h> //Biblioteca utilizada para printar informacoes na tela.
#include <math.h> //Biblioteca utilizada para usar a funcao pow.
//Inclui a biblioteca conio2, utilizada para mudar a aparencia dos elementos da tela.
#include <conio2.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define QTD_NIVEIS 3 //Define a quantidade de niveis (1-99)

//Estrutura para controlar a posicao do jogador e dos ogros.
typedef struct
{
    int x,y,dir,x2,y2,x3,y3;
}POSICAO;

//Funcao Imprime_Mapa, que imprime constantemente o mapa do jogo na tela e limpa a tela com a funcao clrscr.
void Imprime_Mapa(char M[][27], POSICAO *jog, int *pontos, int *chaves, int *nivel, POSICAO o[], int *vidas){
    //Declaracao de variaveis
    int i, j;
    clrscr(); //Limpa a tela.
    M[jog->x][jog->y] = 'J';
    for(i=0; i<4; i++){
        M[o[i].x][o[i].y] = 'O';
    }
    for(i = 0; i < 11; i++) //For para percorrer as linhas.
    {
        printf("\n"); //Quebra linha utilizado para "trocar" de linha.
        for(j = 0 ; j < 27; j++){
            if(M[i][j] == '#'){ //Caso algum elemento da matriz seja #.
                textcolor(LIGHTGRAY); //Cor do texto ira ficar cinza claro.
                textbackground(LIGHTGRAY); //Cor do fundo do texto vai ficar cinza claro.
                cprintf(" %c",M[i][j]); //printa na tela a linha com a nova aparencia.
            }
            else if(M[i][j] == 'O'){ //Caso algum elemento da matriz seja O.
                textcolor(GREEN); //Cor do texto ira ficar verde.
                textbackground(GREEN); //Cor do fundo do texto vai ficar verde.
                cprintf(" %c",M[i][j]); //printa na tela a linha com a nova aparencia.
            }
            else if(M[i][j] == 'J'){ //Caso algum elemento da matriz seja J.
                textcolor(DARKGRAY); //Cor do texto ira ficar cinza escuro.
                textbackground(DARKGRAY); //Cor do fundo do texto vai ficar cinza escuro.
                cprintf(" %c",M[i][j]); //printa na tela a linha com a nova aparencia.
            }
            else if(M[i][j] == 'M'){ //Caso algum elemento da matriz seja M.
                textcolor(YELLOW); //Cor do texto ira ficar amarelo.
                textbackground(YELLOW); //Cor do fundo do texto vai ficar amarelo.
                cprintf(" %c",M[i][j]); //printa na tela a linha com a nova aparencia.
            }
            else if(M[i][j] == 'C'){ //Caso algum elemento da matriz seja C.
                textcolor(MAGENTA); //Cor do texto ira ficar magenta.
                textbackground(MAGENTA);  //Cor do fundo do texto vai ficar magenta.
                cprintf(" %c",M[i][j]); //printa na tela a linha com a nova aparencia.
            }
            else if(M[i][j] == 'A'){ //Caso algum elemento da matriz seja A.
                textcolor(CYAN); //Cor do texto ira ficar ciano.
                textbackground(CYAN); //Cor do fundo do texto vai ficar ciano.
                cprintf(" %c",M[i][j]); //printa na tela a linha com a nova aparencia.
            }
            else if(M[i][j] == 'D'){ //Caso algum elemento da matriz seja D.
                textcolor(RED); //Cor do texto ira ficar vermelho.
                textbackground(RED); //Cor do fundo do texto vai ficar vermelho.
                cprintf(" %c",M[i][j]); //printa na tela a linha com a nova aparencia.
            }
            else if(M[i][j] == 'B'){ //Caso algum elemento da matriz seja B.
                textcolor(BROWN); //Cor do texto ira ficar marrom.
                textbackground(BROWN); //Cor do fundo do texto vai ficar marrom.
                cprintf(" %c",M[i][j]); //printa na tela a linha com a nova aparencia.
            }
            else{ //Caso o elemento seja diferente dos outros
                textcolor(WHITE); //Cor do texto ira ficar branco.
                textbackground(WHITE); //Cor do fundo do texto vai ficar branco.
                cprintf(" %c",M[i][j]); //printa na tela a linha com a nova aparencia.
            }
        }
    }

    textbackground(BLACK); //Cor do fundo do texto ira ficar preto.
    textcolor(WHITE); //Cor do texto ira ficar branco.
    printf ("\n\nPontos: %d\t\tChaves: %d\t Nivel %d", *pontos, *chaves, *nivel-1); //Exibe os pontos, chaves e nivel atual na tela.
    printf("\n\n\nVIDAS: %d", *vidas);
    if (*chaves == 5) //Caso o jogador tenha mais do que 3 chaves.
    {
    	  textcolor(4);
        printf ("\n\tVOCE PASSOU DE NIVEL!!\t\t\n"); //Exibe mensagem dizendo que o jogador passou de nivel.
		    printf ("\tPressione a barra de espaco para mudar de nivel.\n");
	}
}

void Carrega_mapa(char M[][27], int *nivel, POSICAO *j, int *chaves, POSICAO o[]){
  //Declaracao de variaveis.
  int i,k,l, cont_ogro=0, cont;
  FILE *arq; //Ponteiro para arquivo.
  char nome_mapa[10]; //Vetor utilizado para armazenar o nome padrao de arquivo.

    //Este bloco de comandos armazena o nome padrao de arquivo no vetor nome_mapa.
		nome_mapa[0] = 'm';
        nome_mapa[1] = 'a';
        nome_mapa[2] = 'p';
        nome_mapa[3] = 'a';
        nome_mapa[6] = '.';
        nome_mapa[7] = 't';
        nome_mapa[8] = 'x';
        nome_mapa[9] = 't';
        nome_mapa[10] = '\0';

        //If utilizado para realizar a consistencia de nomes a partir do nivel 10
        if (*nivel < 10){
            nome_mapa[4] = '0';
            nome_mapa[5] = *nivel + '0';
        }else{
            nome_mapa[4] = (*nivel/10) + '0';
            nome_mapa[5] = (*nivel%10) + '0';
        }

		arq = fopen(nome_mapa, "r"); //Abre o arquivo no modo de leitura.

		if(arq == NULL){ //Caso retorne NULL, ouve falha na abertura.
			printf("\nErro na abertura do arquivo. \n"); //Printf informando que ouve falha na abertura do arquivo.
		}
		while(!feof(arq)){ //Enquanto nao chegar no fim do arquivo.
			for(i = 0; i < 11; i++){ //For utilizado para percorrer as linhas.
	  			fscanf(arq,"%s", M[i]); //Ira armazenar o conteudo do arquivo na matriz M.
			}
		}
    //Bloco de comandos utilizado para percorrer a matriz procurando a posicao do jogador e do orgo.
		for (i=0; i<11; i++){
			for (k=0; k<27; k++){
				if (M[i][k]=='J'){ //Caso a posicao do jogador seja encontrada.
					j->x=i; //Ira atualizar o valor da posicao do jogador.
					j->y=k;
					j->x2=i;
					j->y2=k;

				}else if (M[i][k]=='O'){ //Caso a posicao do ogro seja encontrada.
					o[cont_ogro].x=i; //Ira atualizar o valor da posicao do ogro.
					o[cont_ogro].y=k;
					cont_ogro++; //Ira trocar para o proximo ogro.
				}
			}
		}

		fclose(arq); //Fecha o arquivo.
		*nivel = *nivel + 1; //Nivel recebe nivel+1.
		*chaves = 0; //Chaves recebe 0.
}

int MovimentacaoOgro(char M[][27], POSICAO *j, POSICAO o[], char anterior[], int i, int *vidas){
    int t;
    //Aqui guarda a posicao atual do ogro antes de se mover nas variaveis x2 e y2 da struct posicao
    o[i].y2 = o[i].y;
    o[i].x2 = o[i].x;
    //Verifica qual é o caractere que estava "em baixo" do ogro e faz a matriz na posiçao do ogro antes de se mover receber ele
    if(anterior[i] == 'K'){
        M[o[i].x2][o[i].y2] = 'K';
    }
    if(anterior[i] == 'M'){
        M[o[i].x2][o[i].y2] = 'M';
    }
    if(anterior[i] == 'A'){
        M[o[i].x2][o[i].y2] = 'A';
    }
    if(anterior[i] == 'C'){
        M[o[i].x2][o[i].y2] = 'C';
    }
    if(anterior[i] == 'B'){
        M[o[i].x2][o[i].y2] = 'B';
    }
    //Aqui o ogro se move normalmente através da struct se não há parede, porta desativada ou outro ogro.
    switch(o[i].dir){
        case 0 :
                if(M[o[i].x-1][o[i].y] != '#' && M[o[i].x-1][o[i].y] != 'D' && M[o[i].x-1][o[i].y] != 'O'){
                    o[i].x = o[i].x - 1;
                }
                else{
                    t = 1;
                }
            break;
        case 1:
                if(M[o[i].x][o[i].y+1] != '#' && M[o[i].x][o[i].y+1] != 'D' && M[o[i].x+1][o[i].y] != 'O'){
                    t = 1;
                }
                else{
                    t = 1;
                }
            break;
        case 2:
                if(M[o[i].x+1][o[i].y] != '#' && M[o[i].x+1][o[i].y] != 'D' && M[o[i].x+1][o[i].y] != 'O'){
                    o[i].x = o[i].x + 1;
                }
                else{
                    t = 1;
                }
            break;
        case 3:anterior[i] = M[o[i].x][o[i].y];
                if(M[o[i].x][o[i].y-1] != '#' && M[o[i].x][o[i].y-1] != 'D' && M[o[i].x-1][o[i].y] != 'O'){
                    o[i].y = o[i].y - 1;
                }
                else{
                    t = 1;
                }
            break;
    }
    //Depois q ele se move, a variavel anterior recebe o caractere que está na posiçao da matriz para onde o ogro irá
    anterior[i] = M[o[i].x][o[i].y];
    //Se o ogro encontra o jogador, a vida diminui em 1 e o jogador volta para a posicao inicial
    if(o[i].x == j->x && o[i].y == j->y){
        *vidas = *vidas - 1;
        j->x = j->x2;
        j->y = j->y2;
    }

    return t;
}

//Funcao menu, ira controlar o menu principal do jogo.
void Menu(char M[][27], POSICAO *j, int *chaves, int *nivel, int *pontos, int *fim, POSICAO o[]){
    //Declaracao de variaveis.
    int verdade = 0; //Ira ser utilizada pra pausar o jogo quando o menu for aberto.
    int teste,i,k;
    int h = 0;
    char tecla; //Ira armazenar a tecla que o usuario inserir.
    FILE *arq; //Ponteiro para arquivo.


    //Este bloco de comandos faz a interface do menu, tornando-a mais acessivel ao jogador.
    textbackground(LIGHTGRAY);
    printf("\n\n\n                                                       ");
    textbackground(DARKGRAY);
    printf("\n                                                       ");
    printf("\n                       ");
    printf("MENU");
    printf("                            ");
    printf("\n                  ");
    printf("(N) Novo jogo");
    printf("                        ");
    printf("\n                  ");
    printf("(C) Carregar jogo");
    printf("                    ");
    printf("\n                  ");
    printf("(S) Salvar jogo");
    printf("                      ");
    printf("\n                  ");
    printf("(Q) Sair do jogo");
    printf("                     ");
    printf("\n                  ");
    printf("(V) Voltar");
    printf("                           ");
    textbackground(DARKGRAY);
    printf("\n                                                       ");
    textbackground(LIGHTGRAY);
    printf("\n                                                       ");
    textbackground(BLACK);

    //Enquanto o menu estiver aberto, o jogo ira ficar pausado.
    while(verdade != 1){ //Menu ficara aberto enquanto a variavel verdade for diferente de 1.
        while(teste != ' '){ //Enquanto o teste for diferente de espaco
            if(_kbhit()){
                tecla = getch(); //Ira ler oque o jogador digitar e armazenar na variavel tecla
                teste = ' '; //Apos isso, teste recebera espaco
            }
        }
        if(tecla == 'N' || tecla == 'n'){ //Caso o usuario digite N.
            //Um novo jogo sera iniciado.
            *nivel = 1; //Nivel voltara para 1.
            *pontos = 0; //Pontos voltara para 0.
            *chaves = 0; //Chaves voltara para 0.
            Carrega_mapa(M, nivel,j,chaves,o); //Chama a funcao Carrega_mapa, para carregar o mapa novamente.
            printf("\nUm novo jogo sera iniciado.\n"); //Printf informando o usuario que um novo jogo sera iniciado.
            Sleep(1000); //Sleep utilizado apenas para dar tempo do jogador ler a mensagem
            verdade = 1; //Verdade recebe 1, para sair do while.
        }
        else if(tecla == 'C' || tecla == 'c'){ //Caso o usuario digite C.
            arq = fopen("jogosalvo.txt","r"); //Abre um arquivo chamado jogosalvo.
            if(arq == NULL){ //Caso retorne NULL, ouve falha na abertura do arquivo.
                printf("\nNao existe um jogo salvo. \n"); //Printf informando que ouve falha na abertura
            }
            else{ //Senao
               while(!feof(arq)){ //Enquanto nao chegar no fim do arquivo.
                    for(i = 0; i < 11; i++){ //Ira percorrer as linhas.
                        fscanf(arq,"%s", M[i]); //Ira armazenar ela no matriz.
                    }
                }
                fclose(arq); //Fecha o arquivo.

                //Este bloco de comandos ira procurar o jogador na matriz, e atualizar a sua posicao.
                for (i=0; i < 11; i++){
                    for(k=0; k < 27; k++){
                        if(M[i][k] == 'J'){
                            j->x=i;
                            j->y=k;
                        }
                    }
                }
                //Printf informando que o jogo foi carregado com sucesso.
                printf("\nJogo salvo carregado com sucesso.\n");
                Sleep(1000); //Sleep utilizado apenas para dar tempo do jogador ler a mensagem
                verdade = 1; //Verdade recebe 1, para sair do while.
            }

        }
        else if(tecla == 'S' || tecla == 's'){ //Caso o usuario digite S.
            arq = fopen("jogosalvo.txt","w"); //Cria um arquivo novo chamado jogo salvo.
            if(arq == NULL){ //Caso retorne NULL, ouve falha na criacao do arquivo.
                printf("\nErro no salvamento. \n"); //Printf informando que ouve falha na criacao.
            }
            else{ //Caso nao ouve falha.
                for (i = 0; i < 11; i++){
                    putc('\n',arq); //Coloca uma quebra linha no arquivo.
                    for(k = 0; k < 27; k++){
                        putc(M[i][k],arq); //Coloque caractere por caractere no arquivo.
                    }
                }
                fclose(arq); //Fecha o arquivo.
                //Printf informando que o jogo foi salvo com sucesso.
                printf("\nJogo salvo com sucesso.\n");
            }
            teste = 'b'; //Teste recebe b, um valor aleatorio, apenas para continuar com o menu aberto.
        }
        else if(tecla == 'V' || tecla == 'v' || tecla == 9){ //Caso o usuario digite V.
            verdade = 1; //Verdade ira receber 1 e o menu ira fechar.
        }
        else if(tecla == 'Q' || tecla == 'q'){ //Caso o usuario digite Q, o jogo ira finalizar.
            printf("\nO jogo sera finalizado. \n"); //Printf informando o jogador.
            *fim = 1; //Fim ira receber 1.
            verdade = 1; //Verdade ira receber 1, para fechar o menu.
        }
        else{ //Caso seja pressionada outra tecla.
            printf("\nTecla invalida.\n"); //Printf informando que a tecla eh invalida.
            teste = 'b'; //Teste recebe b, um valor aleatorio, apenas para continuar com o menu aberto.
        }
    }
}

char MovimentacaoEcolisao(char M[][27], POSICAO *j, char tecla, int *pontos, int *chaves, int *nivel, int *fim, POSICAO o[], int *vidas, char *anterior){
  //Declaracao de variaveis.
    int  i, m, k;
    j->x3 = j->x;
    j->y3 = j->y;
    if(*anterior == 'B'){
        M[j->x3][j->y3] = 'B';
    }
    if(*anterior == 'A'){
        M[j->x3][j->y3] = 'A';
    }
    if(*anterior == 'K'){
        M[j->x3][j->y3] = 'K';
    }
    if(tecla == 'w' || tecla == 'W' || tecla == 72){
        if(M[j->x-1][j->y] != '#' && M[j->x-1][j->y] != 'D'){// colisao para parede ou porta fechada
            j->x = j->x - 1;
            if(M[j->x][j->y] == 'M'){// sistema de moeda
                *anterior = 'K';
                *pontos = *pontos + 10;
            }
            else if(M[j->x][j->y] == 'C')
            {
                *anterior = 'K';
                *chaves = *chaves + 1;
            }
            else if(M[j->x][j->y] == 'B'){
                *anterior = 'B';
            }
            else if(M[j->x][j->y] == 'A'){
                *anterior = 'A';
            }
            else{
                *anterior = 'K';
            }
        }
    }
    else if(tecla == 's' || tecla == 'S' || tecla == 80){
        if(M[j->x+1][j->y] != '#' && M[j->x+1][j->y] != 'D'){// colisao para parede ou porta fechada
            j->x = j->x + 1;
            if(M[j->x][j->y] == 'M'){// sistema de moeda
                *anterior = 'K';
                *pontos = *pontos + 10;
            }
            else if(M[j->x][j->y] == 'C')
            {
                *anterior = 'K';
                *chaves = *chaves + 1;
            }
            else if(M[j->x][j->y] == 'B'){
                *anterior = 'B';
            }
            else if(M[j->x][j->y] == 'A'){
                *anterior = 'A';
            }
            else{
                *anterior = 'K';
            }
        }
    }
    else if(tecla == 'a' || tecla == 'A' || tecla == 75){
        if(M[j->x][j->y-1] != '#' && M[j->x][j->y-1] != 'D'){// colisao para parede ou porta fechada
            j->y = j->y - 1;
            if(M[j->x][j->y] == 'M'){// sistema de moeda
                *anterior = 'K';
                *pontos = *pontos + 10;
            }
            else if(M[j->x][j->y] == 'C')
            {
                *anterior = 'K';
                *chaves = *chaves + 1;
            }
            else if(M[j->x][j->y] == 'B'){
                *anterior = 'B';
            }
            else if(M[j->x][j->y] == 'A'){
                *anterior = 'A';
            }
            else{
                *anterior = 'K';
            }
        }
    }
    else if(tecla == 'd' || tecla == 'D' || tecla == 77){
        if(M[j->x][j->y+1] != '#' && M[j->x][j->y+1] != 'D'){// colisao para parede ou porta fechada
            j->y = j->y + 1;
            if(M[j->x][j->y] == 'M'){// sistema de moeda
                *anterior = 'K';
                *pontos = *pontos + 10;
            }
            else if(M[j->x][j->y] == 'C')
            {
                *anterior = 'K';
                *chaves = *chaves + 1;
            }
            else if(M[j->x][j->y] == 'B'){
                *anterior = 'B';
            }
            else if(M[j->x][j->y] == 'A'){
                *anterior = 'A';
            }
            else{
                *anterior = 'K';
            }
        }
    }
    else if(tecla == 'b' || tecla == 'B')//sistema de alavanca
    {
          if (M[j->x-1][j->y] == 'B' || M[j->x+1][j->y] == 'B' || M[j->x][j->y-1] == 'B' || M[j->x][j->y+1] == 'B')
          {
            for (k=0; k<11; k++)
            {
                for (m=0; m<27; m++)
                {
                  if (M[k][m] == 'D')
                      M[k][m] = 'A';
                      else if (M[k][m] == 'A')
                          M[k][m] = 'D';
                }
            }
          }
      }
      else if (tecla == 9){ //Caso seja pressionado a tecla TAB. ira abrir o menu.
          Menu(M, j,chaves,nivel,pontos,fim, o); //Chama a funcao menu.
      }
      else if (tecla == ' ') //Caso seja pressionado a tecla de espaço, passa de nivel se tiver mais q 4 chaves
      {
      	if (*chaves < 4)
      	{
      		tecla = 'c';
		}
	  }
    for(i=0;i<4;i++){
        if(o[i].x == j->x && o[i].y == j->y){
            *vidas = *vidas - 1;
            j->x = j->x2;
            j->y = j->y2;
        }
    }
	return tecla; //Retorna a variavel tecla.
}


int main(){
  //Declaracao de variaveis.
	char nome_mapa[265]; //Variavel que ira armazenar o nome do mapa.
    char M[11][27], controle; //Matriz que ira representar o mapa
    int pontos, chaves, nivel, dir;
    int fim = 0; //Variavel fim, utilizada para terminar o jogo.
    char teste, anterior[4], anterior2='K';
    pontos = 0; //Variavel pontos, utilizada para contabilizar os pontos do jogador.
    chaves = 0; //Variavel chaves, utilizada para contabilizar as chaves que o jogador pegou.
    nivel = 1; //Variavel nivel, para exibir na tela o nivel em que o jogador esta.
    POSICAO j; //variavel do tipo POSICAO, para indicar a posicao do jogador.
    POSICAO o[4]; //Vetor do tipo POSICAO, para indicar a posicao do ogro.
    int vidas=3; //Variavel vidas, para indicar a vida atual do jogador. (Max:3)
    clock_t t; //Variavel que armazena o tempo de execucao do codigo

    for (int i=0; i<QTD_NIVEIS; i++){
		Carrega_mapa(M, &nivel, &j, &chaves,o);
    	Imprime_Mapa(M, &j, &pontos, &chaves, &nivel,o,&vidas);

        for(int i=0; i<4; i++){
            o[i].dir = rand() % 4;
            //Primeiro a posição "em baixo" do ogro recebe o caractere espaço
            anterior[i] = 'K';
        }

		while(teste != ' ' && vidas > 0){
            if(_kbhit()){
                controle = getch();
                teste = MovimentacaoEcolisao(M, &j, controle, &pontos, &chaves, &nivel, &fim, o, &vidas, &anterior2);
                Imprime_Mapa(M, &j, &pontos, &chaves, &nivel, o, &vidas);
            }
            else{
                for(int i=0; i<4; i++){
                    if(MovimentacaoOgro(M,&j,o,anterior,i, &vidas) == 1){
                        o[i].dir = rand() % 4;
                    }
                }
                t = clock() + 1000;
                Imprime_Mapa(M, &j, &pontos, &chaves, &nivel, o, &vidas);
            }
            do{
                if(_kbhit()){
                    controle = getch();
                    teste = MovimentacaoEcolisao(M, &j, controle, &pontos, &chaves, &nivel, &fim, o, &vidas, &anterior2);
                    Imprime_Mapa(M, &j, &pontos, &chaves, &nivel, o, &vidas);
                }
            }while(clock() < t);
            if(fim == 1){ //Caso fim receba 1 em algum momento, o jogo sera finalizado.
                printf("\n\nO jogo foi finalizado."); //Printf informando que o jogo foi finalizado.
                return 0; //Fim do programa.
            }

    	}
    	controle = 'c';
    	teste = 'c';
    	if(vidas == 0){
            printf("\n\t\tVoce perdeu.\n");
            return 0;
    	}

	}

	printf ("\n\t\tParabens voce ganhou!\n"); //Printf informando que o usuario ganhou.
    return 0; //Fim do programa.
}
