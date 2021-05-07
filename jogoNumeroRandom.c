#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
	char nome[30];
	int tentativas;
	int numero;
} ranking;

// Funcaoo main
int main(){
	int n, x, limite_inferior, limite_superior, acertou, tentativas;
	int opcao;
	FILE *fp;
	ranking z, *rank;
	int ret = 1, flag, total = 0, pos = 0, op;

	// Loop principal

	do{

		printf("(1) - Jogar \n");
		printf("(2) - Ranking \n");
		printf("(3) - Sair \n");
		scanf("%i", &opcao);

		if (opcao == 1){

			char nome[30];

			printf("Digite seu nome: ");
			fflush(stdin);
			gets(nome);

			// Inicia o gerador de n�meros aleat�rios
			srand(time(NULL));

			// Inicaliza as vari�veis
			acertou = 0;			// Verifica se o jogador acertou o n�mero
			tentativas = 0;			// Total de tentativas
			limite_inferior = 0;	// Limite inferior
			limite_superior = 101;	// Limite superior
			n = (rand() % 100) + 1; // N�mero gerado aleatoriamente

			do{
				// Limpa a tela
				system("cls");

				// Imprime o total de tentativas e pede um n�mero ao jogador
				printf("Total de tentativas: %d\n", tentativas);
				printf("Digite um numero(Esta entre %d e %d): ", limite_inferior, limite_superior);
				scanf("%d", &x);

				// Aumenta em 1 o n�mero de tentativas
				tentativas++;

				// Verifica se o jogador ganhou ou diminui os limites ao redor do n�mero
				if (x > n){
					limite_superior = x;
				}
				else if (x < n){
					limite_inferior = x;
				}
				else{
					acertou = 1;
				}
			} while (!acertou);

			system("cls");
			printf("Parabens %s, o numero e: %d\n", nome, n);
			printf("Total de tentativas: %d\n", tentativas);

			fp = fopen("ranking.bin", "a+");
			strcpy(z.nome, nome);
			z.tentativas = tentativas;
			z.numero = n;
			fwrite(&z, sizeof(ranking), 1, fp);
			fclose(fp);
			getchar();
		}

		else if (opcao == 2){
			int a, b;
			system("cls");
			// Calcula Total
			fp = fopen("ranking.bin", "a+");
			while (ret == 1){

				ret = fread(&z, sizeof(ranking), 1, fp);

				if (ret == 1){
					total++;
				}
			}

			// Preenche Verto de Ranking
			rank = malloc((total + 1) * sizeof(ranking));

			rewind(fp);
			ret = 1;
			while (ret == 1){

				ret = fread(&z, sizeof(ranking), 1, fp);

				if (ret == 1){
					rank[pos] = z;
					pos++;
				}
			}
			fclose(fp);

			// Ordena
			for (a = 0; a < total; a++){
				for (b = a; b < total; b++){
					if (rank[a].tentativas > rank[b].tentativas){
						z = rank[a];
						rank[a] = rank[b];
						rank[b] = z;
					}
				}

				printf("\nNome:%s\t    Tentativa:%i\t  	  Numero:%i\n", rank[a].nome, rank[a].tentativas, rank[a].numero);
			}
		}

		else if (opcao == 3){
			system("cls");
			printf("Fim do programa");
		}

	} while (op != 3);

	return 0;
}
