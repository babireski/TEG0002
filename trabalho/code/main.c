#include "functions.h"

void clean()
{
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #endif
}

void wait()
{
    printf("\n");
    printf("\n");
    printf("Pressione qualquer tecla para continuar. ");
    getchar();
    getchar();
}

void menu()
{
	printf("0. Encerrar programa\n");
	printf("1. Ler dados de arquivo .txt\n");
	printf("2. Ler dados de arquivo .csv\n");
	printf("3. Imprimir grafo no terminal\n");
	printf("4. Gerar arquivo .txt\n");
	printf("5. Gerar arquivo .dot\n");
	printf("6. Gerar arquivo .svg\n");
	printf("\n");
}

int main()
{
	graph *descriptor = create();

	int choice = 0;

    while(1)
    {
        clean();
        menu();
        printf("Escolha uma funcionalidade: ");
        scanf("%i", &choice);
        clean();

        switch(choice)
        {
            case 0:
				printf("Encerrando programa.\n");
				destroy(descriptor);
				return 0;
            break;

            case 1:
				if(descriptor -> nodes)
				{
					printf("Erro: dados carregados anteriormente!");
					wait();
				}

				else
				{
					readTxt(descriptor);
					printf("Dados carregados de .txt!");
					wait();
				}
            break;

            case 2:
				if(descriptor -> nodes)
				{
					printf("Erro: dados carregados anteriormente!");
					wait();
				}

				else
				{
					readCsv(descriptor);
					link(descriptor);
					printf("Dados carregados de .csv!");
					wait();
				}
            break;

            case 3:
				if(descriptor -> nodes)
				{
					print(descriptor);
					wait();
				}

				else
				{
					printf("Erro: dados ainda precisam ser carregados!");
				}

				wait();
            break;

            case 4:
				saveTxt(descriptor);
				printf("Arquivo .txt gerado!");
				wait();
            break;

            case 5:
				graphviz(descriptor);
				printf("Arquivo .dot gerado!");
				wait();
            break;

            case 6:
				plot();
				printf("Arquivo .svg gerado!");
				wait();
            break;

            default:
				printf("Funcionalidade desconhecida.");
				wait();
            break;
        }
    }

	return 0;
}