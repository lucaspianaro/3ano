#include <stdio.h>
#include <stdlib.h>
 
void worstfit(int b, int p, int blocos[],int processo[]) 
{ 
	int max_sort(int blocos[], int b) 
	{ 
		int temp,i,j; 
		for(i=0; i<b;i++) 
		{ 
			for(j=i+1;j<b;j++) 
			{ 
				if(blocos[i]<blocos[j]) 
				{ 
					temp=blocos[i]; 
					blocos[i]=blocos[j]; 
					blocos[j]=temp; 
				} 
			} 
		} 
	} 
 
	int flag,i,j,temp_blocos[30]; 
	for(i=0;i<b;i++) 
	{ 
		temp_blocos[i]=blocos[i]; 
	} 
	printf("\nWorst Fit:\n"); 
	for(i=0;i<p;i++) 
	{ 
		max_sort(temp_blocos,b); 
		flag=-1; 
		for(j=0;j<b;j++) 
		{ 
			if(temp_blocos[j]>=processo[i]) 
			{ 
				if(flag==-1)
				{ 
					flag=j; 
				} 
			} 
		} 
		if (flag!= -1) 
		{ 
			printf("\nO processo de tamanho %dKB foi alocado no bloco %dKB\n",processo[i], temp_blocos[flag] );  
			temp_blocos[flag] -= processo[i]; 
			printf("Tamanho do buraco depois de alocar o processo: %dKB\n",temp_blocos[flag]); 
 
		} 
		else
		{ 
			printf("\nO processo de tamanho %dKB esta em estado de espera\n",processo[i]); 
		} 
	} 
} 


void firstfit(int b, int p, int blocos[],int processo[]) 
{ 
	int flag,i,j,temp_blocos[30]; 
	for(i=0;i<b;i++) 
	{ 
		temp_blocos[i]=blocos[i]; 
	} 
	printf("\nFirst Fit:\n"); 
	for(i=0;i<p;i++) 
	{ 
		flag=-1; 
		for(j=0;j<b;j++) 
		{ 
			if(temp_blocos[j]>=processo[i]) 
			{ 
				if(flag==-1)
				{ 
					flag=j; 
				} 
			} 
		} 
		if (flag!= -1) 
		{ 
			printf("\nO processo de tamanho %dKB foi alocado no bloco %dKB\n",processo[i], temp_blocos[flag] ); 
			temp_blocos[flag] -= processo[i]; 
			printf("Tamanho do buraco depois de alocar o processo: %dKB\n",temp_blocos[flag]);  
 
		} 
		else
		{ 
			printf("\nO processo de tamanho %dKB esta em estado de espera\n",processo[i]); 
		} 
	} 
} 


void bestfit(int b, int p, int blocos[],int processo[]) 
{ 
	int asc_sort(int blocos[], int b) 
	{ 
		int temp,i,j; 
		for(i=0; i<b;i++) 
		{ 
			for(j=i+1;j<b;j++) 
			{ 
				if(blocos[i]>blocos[j]) 
				{ 
					temp=blocos[i]; 
					blocos[i]=blocos[j]; 
					blocos[j]=temp; 
				} 
			} 
		} 
	} 
 
	int flag,i,j,temp_blocos[30]; 
	for(i=0;i<b;i++) 
	{ 
		temp_blocos[i]=blocos[i]; 
	} 
	printf("\nBest Fit:\n"); 
	for(i=0;i<p;i++) 
	{ 
		asc_sort(temp_blocos,b); 
		flag=-1; 
		for(j=0;j<b;j++) 
		{ 
			if(temp_blocos[j]>=processo[i]) 
			{ 
				if(flag==-1)
				{ 
					flag=j; 
				} 
			} 
		} 
		if (flag!= -1) 
		{ 
			printf("\nO processo de tamanho %dKB foi alocado no bloco %dKB\n",processo[i], temp_blocos[flag] ); 
			temp_blocos[flag] -= processo[i]; 
			printf("Tamanho do buraco depois de alocar o processo: %dKB\n",temp_blocos[flag]); 
 
		} 
		else
		{ 
			printf("\nO processo de tamanho %dKB esta em estado de espera\n",processo[i]); 
		} 
	} 
}

void circularfit(int b, int p, int blocos[],int processo[]) 
{ 
    int flag,i,j,temp_blocos[30]; 
    for(i=0;i<b;i++) 
    { 
        temp_blocos[i]=blocos[i]; 
    } 
    printf("\nCircular Fit:\n"); 
    for(i=0;i<p;i++) 
    { 

        for(j=0;j<b;j++) 
        { 
            if(temp_blocos[j]>=processo[i]) 
            { 
                if(flag==-1)
                { 
                    flag=j; 
                } 
            } 
        } 
        if (flag!= -1) 
        { 
            printf("\nO processo de tamanho %dKB foi alocado no bloco %dKB\n",processo[i], temp_blocos[flag] ); 
            temp_blocos[flag] -= processo[i]; 
            printf("Tamanho do buraco depois de alocar o processo: %dKB\n",temp_blocos[flag]);
 
        } 
        else
        { 
            printf("\nO processo de tamanho %dKB esta em estado de espera\n",processo[i]); 
        } 
    } 
}

void insert()
{
	int choice,b,p,blocos[30],processos[30],i,j; 
	printf("\nQuantidade de blocos:"); 
	scanf("%d",&b); 
	for(i=0;i<b;i++) 
	{ 
		printf("\n\tTamanho do bloco %d em KB:",i+1); 
		scanf("%d",&blocos[i]); 
	} 
	printf("\nQuantidade de processos:"); 
	scanf("%d",&p); 
	for(i=0;i<p;i++) 
	{ 
		printf("\n\tTamanho do processo %d em KB:",i+1); 
		scanf("%d",&processos[i]); 
	} 
 
	printf("\nEscolha um algoritmo:"); 
	printf("\n1.Best fit\n2.First Fit\n3.Worst Fit\n4.Todos juntos\n\n5.Sair"); 
	do{ 
		printf("\nSua opcao:"); 
		scanf("%d",&choice); 
		printf("\n"); 
		if(choice == 1) 
		{ 
			bestfit(b,p,blocos,processos); 
		} 
		if(choice==2) 
		{ 
			firstfit(b,p,blocos,processos); 
		} 
		if(choice==3) 
		{ 
			worstfit(b,p,blocos,processos); 
		}
		if(choice==4) 
		{
			bestfit(b,p,blocos,processos);
			firstfit(b,p,blocos,processos);  
			worstfit(b,p,blocos,processos);
			circularfit(b,p,blocos,processos);
		} 
	}while(choice<=4);
}

void interface()
{
    int input;

    printf("--------------------------------\n");
    printf("     Alocacao de Processos      \n");
    printf("--------------------------------\n\n");
    printf("[1] Inserir processo\n");
    printf("[2] Remover processo\n");
    printf("[3] Listar estado das memorias\n");
    printf("[4] Finalizar aplicacao\n");
    printf("\nDigite uma opcao:");
    scanf("%d", &input);

    switch (input)
    {
    case 1:
      insert();
      interface();
      break;
    case 2:
      printf("Removeu");
      break;
    case 3:
      printf("Listou");
      break;
    case 4:
      printf("Finalizou");
      break;
    }
}

int main() 
{
	interface();
	return 0; 
}
