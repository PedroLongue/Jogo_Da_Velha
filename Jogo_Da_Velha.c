#include <stdio.h>
#include <stdlib.h>

void inicia(char game[][3]){
	int i, j;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			game[i][j] = ' ';
		}
	}
}

int valido(char coordenada){
    if(coordenada == 'x' || coordenada == 'o')
        return 1;
    else
        return 0;
}

int pertinente(int x, int y) {
    if(x >= 0 && x < 3) {
        if(y >= 0 && y < 3)
            return 1;
    }
    return 0;
}

int vazio(int x, int y, char game[][3]) {//verficar se a posicao desejada esta vazia
    if(game[x][y] != 'x' && game[x][y] != 'o')
        return 1;
    return 0;
}

int linhas(char game[][3]) {
    int i, j, igual = 1;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 2; j++) {
            if(valido(game[i][j]) && game[i][j] == game[i][j+1])
                igual++;
        }
        if(igual == 3)
            return 1;
        igual = 1;
    }
    return 0;
}

int colunas(char game[][3]) {
    int i, j, igual = 1;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 2; j++) {
            if(valido(game[j][i]) && game[j][i] == game[j+1][i])
                igual++;
        }
        if(igual == 3)
            return 1;
        igual = 1;
    }
    return 0;
}

int diagp(char game[][3]) {
    int i, igual = 1;
    for(i = 0; i < 2; i++) {
        if(valido(game[i][i]) && game[i][i] == game[i+1][i+1])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}

int diags(char game[][3]) {
    int i, igual = 1;
    for(i = 0; i < 2; i++) {
        if(valido(game[i][3-i-1]) && game[i][3-i-1] == game[i+1][3-i-2])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}

void imprime(char game[][3]) {
    int lin, col;
    printf("\n\t    0  1  2\n");
    for(lin = 0; lin < 3; lin++) {
        printf("\t%d ", lin);
        for(col = 0; col < 3; col++) {
            if(col < 2)
                printf(" %c |", game[lin][col]);
            else
                printf(" %c ", game[lin][col]);
        }
        if(lin < 2)
            printf("\n\t   ---------\n");
    }
}
void jogo(char game[][3], char jogador1[], char jogador2[]){
	int y, x, z, pos = 1, simbolo = 1, num_jogadas = 0, vitorias = 0;
	do {
        do {
            imprime(game);
            printf("\nDigite a coordenada (linha e coluna): ");
            scanf("%d%d", &x, &y);
            z = pertinente(x, y);
            if(z == 1)
                z += vazio(x, y, game);
        } while(z != 2);
        if(simbolo == 1)
            game[x][y] = 'x';
        else
            game[x][y] = 'o';
            
        num_jogadas++;
        simbolo++;
        
        if(simbolo == 3)
            simbolo = 1;
        vitorias += linhas(game);
        vitorias += colunas(game);
        vitorias += diagp(game);
        vitorias += diags(game);
    } while(vitorias== 0 && num_jogadas < 9);
    if(vitorias != 0) {
        imprime(game);
        if(simbolo - 1 == 1)
            printf("\nParabens %s!!! Voce venceu.\n", jogador1);
        else
            printf("\nParabens %s!!! Voce venceu.\n", jogador2);
    } else
        printf("DEU VELHA :( \n\n");
}

int main(){
	char jogador1[20], jogador2[20], game[3][3];
	int esc;
	
	printf("REGRAS: \n");
	printf("Eh necessario que cada jogador realize sua jogada de forma intercalada.\nJogador 1(x).\nJogador 2(o).");
	printf("\n\n");
	printf("Jogador 1, informe seu nome: ");
	scanf (" %[^\n]", jogador1);
	printf("Jogador 2, informe seu nome: ");
	scanf (" %[^\n]", jogador2);
	
	do{
		inicia(game);
		jogo(game, jogador1, jogador2);
		printf("Deseja jogar novamente?\n[1]Sim\n[2]Nao\n");
		scanf ("%d", &esc);
	}while(esc == 1);
	
	return 0;
}

