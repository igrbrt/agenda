#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct agenda{
    char nome[128];
    int tel;
    struct agenda *prox;
}agenda;

void cadastrar(agenda*);
void inserir(agenda*);
void mostrar(agenda*);
void salvar();
void listar();

agenda *inicio=NULL;

int main(){
    char op;
    agenda *c;
    while(1){
    printf("(C)adastrar\n(M)ostrar\n(L)istar salvos\n(S)alvar\n(F)echar\n\n->");
    op=getchar();
    switch(op){
        case 'c': c=(agenda*)malloc(sizeof(agenda));
                  cadastrar(c);
                  inserir(c);
                  break;
        case 'm': putchar('\n');
                  mostrar(inicio);
                  sleep(2);
                  break;
        case 's': salvar();
                  puts("Salvo com sucesso!"); sleep(2);
                  break;
        case 'l': listar();sleep(2);
                  break;
        case 'f': exit(0);
        default : puts("Opcao invalida"); sleep(2);
    }
    __fpurge(stdin);
    system("clear");
    }
    return 0;
}

void cadastrar(agenda *novo){
    printf("Nome: ");
    __fpurge(stdin);
    fgets(novo->nome,128,stdin);
    printf("Telefone: ");
    scanf("%d",&novo->tel);
    printf("\nCadastrado !\n");
    sleep(2);
}

void inserir(agenda *novo){
    agenda *aux,*aux2;
    if(inicio==NULL)
        inicio=novo;
    else{
        if(strcmp(novo->nome,inicio->nome)<0){
            novo->prox=inicio;
            inicio=novo;
        }
        else{
            aux2=inicio->prox;
            aux=inicio;
            while(aux->prox!=NULL && strcmp(novo->nome,aux2->nome)>0){
                aux=aux->prox;
                aux2=aux2->prox;
            }
            aux->prox=novo;
            novo->prox=aux2;
        }
    }
}

void mostrar(agenda *aux){
    printf("Nome: %s",aux->nome);
    printf("Telefone: %d",aux->tel);
    printf("\n\n");
    if(aux->prox!=NULL)
        mostrar(aux->prox);
}

void listar(){
    FILE *fp;
    agenda *aux;
    fp=fopen("agenda.txt","r");
    while(fscanf(fp,"%s %d",aux->nome,&aux->tel)!=EOF){
        printf("%s\n",aux->nome);
        printf("%d\n\n",aux->tel);
    }
    fclose(fp);
}

void salvar(){
    agenda *aux=inicio;
    FILE *fp;
    fp=fopen("agenda.txt","a");
    while(aux->prox!=NULL){
        fprintf(fp,"%s\n%d\n\n",aux->nome,aux->tel);
        aux=aux->prox;
    }
    fprintf(fp,"%s\n%d\n\n",aux->nome,aux->tel);
    fclose(fp);
}
