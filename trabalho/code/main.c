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
	printf("5. Gerar arquivo .svg\n");
	printf("\n");
}

int main(int argc, char **argv)
{
	++argv, --argc;
	graph *descriptor = create();

	if (argc <= 0)
	{
		readTxt(descriptor);
	}

	else
	{
		readCsv(descriptor);
		link(descriptor);
		print(descriptor);
		saveTxt(descriptor);
	}
	plot(descriptor);

	int choice = 0;

    while(1)
    {
        limpar();
        menu();
        printf("Escolha uma funcionalidade: ");
        scanf("%i", &choice);
        limpar();

        switch(choice)
        {
            case 0:
				printf("Encerrando programa.");
				return 0;
            break;

            case 1:
				if(descriptor -> nodes)
				{
					printf("Erro: dados carregados anteriormente!");
				}

				else
				{
					readTxt(descriptor);
					printf("Dados carregados de .txt!");
				}
            break;

            case 2:
				if(descriptor -> nodes)
				{
					printf("Erro: dados carregados anteriormente!");
				}

				else
				{
					readCsv(descriptor);
					printf("Dados carregados de .csv!");
				}
            break;

            case 3:
				print(descriptor);
            break;

            case 4:
				saveTxt(descriptor);
				printf("Arquivo .txt gerado!");
            break;

            case 5:
				plot(descriptor);
				printf("Arquivo .dot gerado!");
            break;

            case 6:
				printf("A ser implementado!");
            break;

            default:
				printf("Funcionalidade desconhecida.");
            break;
        }
    }

	return 0;
}