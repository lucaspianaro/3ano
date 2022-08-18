#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

//variaveis processo
typedef struct{
    int pid;
    int carga;
    int chegada;
} PROCESSO;

//variaveis listagem processo
typedef struct{
    PROCESSO* lista;
    int tam;
} LISTARPROCESSO;

//variaveis processo
typedef struct{
    int* lista;
    int tam;
} LISTA;

//criar nova lista
void insereArrayInt(LISTA* x, int item){
    LISTA novaLista;
    novaLista.tam = x->tam+1;
    novaLista.lista = realloc(x->lista, novaLista.tam * sizeof (int));

    if (novaLista.lista!=NULL) {
        novaLista.lista[novaLista.tam-1]= item;
        x->lista= novaLista.lista;
        x->tam= novaLista.tam;
    }
}

//lista de processos
PROCESSO processosProntos[] = {
    { .pid = 1001, .carga = 18, .chegada = 0},
    { .pid = 1102, .carga = 4, .chegada = 0 },
    { .pid = 1003, .carga = 22, .chegada = 0 },
    { .pid = 1014, .carga = 3, .chegada = 3 },
    { .pid = 1061, .carga = 8, .chegada = 3 },
    { .pid = 1002, .carga = 7, .chegada = 15 },
    { .pid = 1203, .carga = 2, .chegada = 15 },
    { .pid = 1304, .carga = 13, .chegada = 15 },
};

//inserir processos
void insereProcessos(LISTARPROCESSO* x, PROCESSO item){
    LISTARPROCESSO novaLista;
    novaLista.tam=x->tam+1;
    novaLista.lista=realloc(x->lista, novaLista.tam * sizeof (PROCESSO));

    if (novaLista.lista!=NULL) {
        novaLista.lista[novaLista.tam-1]=item;
        x->lista=novaLista.lista;
        x->tam=novaLista.tam;
    }
}

int originalTam = (int) (sizeof(processosProntos) / sizeof(PROCESSO));
int cargaExecutada=0;
int transicoes=0;

//iniciar processos
void inicializaProcesso(LISTARPROCESSO* processos, int length){
    processos->tam=length;
    processos->lista=malloc(processos->tam * sizeof (PROCESSO));
    processos->lista[0]= (PROCESSO) processosProntos[0];
    
    if(!processos->lista) return;
    int i=1;
    for(i; i<originalTam; i++) 
	insereProcessos(processos, processosProntos[i]);
}

//inicia processo prontos
void inicializaProntos(LISTA* prontos, int length, int first){
    prontos->tam=length;
    prontos->lista=malloc(prontos->tam * sizeof (int));
    
    if(!prontos->lista) return;
    prontos->lista[0] = first;
}

//imprime processos
void listarProcessos(LISTARPROCESSO processos){
    int i=0;
    for(i; i<processos.tam; i++){
        printf("PID: %i Carga: %i Chegada: %i \n", processos.lista[i].pid, processos.lista[i].carga, processos.lista[i].chegada);
    }
    printf("\n");
}

//executar
void executar(int quantum){
    LISTARPROCESSO processos;
    LISTA prontos;
    int emExe = -1, i;

    inicializaProcesso(&processos, 1);
    inicializaProntos(&prontos, 1, emExe);
    listarProcessos(processos);

    for ( i = 0; i<processos.tam; i++) {
        PROCESSO processo=processos.lista[i];

        transicoes++;
        emExe=processo.pid;

        int cargaDiferenca=processo.carga - quantum;
        cargaExecutada+=(cargaDiferenca>0 ? quantum : cargaDiferenca+quantum);
        processo.carga -= quantum;

        int proximoLog = -1;
        if(i < processos.tam-1){
            proximoLog = processos.lista[i+1].pid;
        }

        printf("Executando: %i Proximo: %i Prontos:", emExe, proximoLog);
        imprimeProntos(prontos);

        if (cargaDiferenca>0) {
            insereProcessos(&processos, processo);
        }
        else {
            if (prontos.tam==1 && prontos.lista!=NULL && prontos.lista[0]==-1) {
                prontos.lista[0]=emExe;
            }else insereArrayInt(&prontos, emExe);
        }
    }

	printf("\n");
    imprimirStatus();
}

//imprime prontos
void imprimeProntos(LISTA r) {
    int i = 0;
    for(i; i<r.tam; i++) {
        if(i==r.tam - 1)printf("%i", r.lista[i]);
        else printf("%i,", r.lista[i]);
    }
    printf("\n");
}

//imprime status
void imprimirStatus() {
    int total = transicoes + cargaExecutada;

    printf("Transicoes: %i\nCarga executada: %i\nTotal: %i\n", transicoes, cargaExecutada, total);
    printf("Vazio: %.3f%\n", ((float)originalTam / total));
    printf("CPU: %.3f\n", (((float)total - transicoes) / total) * 100);
    printf("Tempo de resposta: %.3f\n", ((float) total / originalTam));
    
    printf("\n");
}

void inicializaProntos(LISTA* prontos, int length, int first);
void inicializaProcesso(LISTARPROCESSO* processos, int length);
void listarProcessos(LISTARPROCESSO processos);
void executar(int quantum);
void imprimirStatus();

int main(){
    executar(4);
    return 0;
}
