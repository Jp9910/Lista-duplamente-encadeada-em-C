#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* alteracao: adicionei as excessoes pra head sendo NULL no remove e no show. antes: 2112kb.*/

typedef struct lista {
    char nome[51];
    struct lista *prox, *ante;
} lista;

int test = 0;
lista* showA = NULL;
lista* show = NULL;
lista* showP = NULL;

lista* adicionarElemento(char *pessoa, lista* head);
lista* removerElemento(char *pessoa, lista* head);
int mostrar(char *pessoa, lista* head);

int main (int argc, char *argv[]){

    printf("1\n");
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    char comando[7], nomme[51];
    lista* HEAD = NULL;

    while(fscanf(input,"%s %[^\n]s",comando,nomme) != EOF)
    {
        if(!(strcmp("ADD",comando)))
        {
            HEAD = adicionarElemento(nomme, HEAD);
            if (test == 0)
            {
                fprintf(output,"[ERROR] ADD %s\n",nomme);
            } else {
                fprintf(output,"[ OK  ] ADD %s\n",nomme);test = 0;
                }
        }

        else if(!(strcmp("REMOVE",comando)))
        {
            HEAD = removerElemento(nomme, HEAD);
            if (test == 1)
            {
                fprintf(output,"[ERROR] REMOVE %s\n",nomme);
                test = 0;
            } else {
                fprintf(output,"[ OK  ] REMOVE %s\n",nomme);
                }
        }

        else if(!(strcmp("SHOW",comando)))
        {
            test = mostrar(nomme, HEAD);
            if(test == 1)
            {
                fprintf(output,"[ERROR] ?<-%s->?\n",nomme);
                test = 0;
            }
            else
            {
                fprintf(output, "[ OK  ] %s<-%s->%s\n",showA->nome,show->nome,showP->nome);
            }
        }
    }
    printf("2,");
    fclose(input);
    fclose(output);
    return 0;
}

lista * adicionarElemento(char* pessoa, lista* head)
{
    int i=0;
    lista* temp = NULL;
    lista* p = NULL;

        temp = (lista*)malloc(sizeof(lista));
        strcpy (temp->nome, pessoa);
        temp->prox = temp;
        temp->ante = temp;

        if(head == NULL)
        {
            head = temp;
            head->ante = head;
            head->prox = head;
            test = 1;
        }
        else
        {
            p = head;
            if(!(strcmp(p->nome, pessoa))){free(temp);return head;}
            while(p->prox != head)
            {
                if(!(strcmp(p->prox->nome, temp->nome)))
                {
                    i=1;
                    free(temp);
                    break;
                }
                p = p->prox;
            }
            if(i==0)
            {
                p->prox = temp;
                test = 1;
                temp->ante = p;
                temp->prox = head;
                head->ante = temp;
            }
        }
        return head;
}

lista* removerElemento(char* pessoa, lista* head)
{
    if(head == NULL){
        test = 1;
        return head;
    }
    lista* p = NULL;
    lista* liberar = NULL;
    lista* q = NULL;
    p=head;
    if(!(strcmp(pessoa,p->nome)))
    {
        if(p->prox == head)
        {
            head = NULL;
        }
        else
        {
            liberar = head;
            head = head->prox;
            if(head->prox == liberar)
            {
                head->prox = head;
                head->ante = head;
            }
            else
            {
                p = head;
                while(p->prox != liberar){
                    p = p->prox;
                }
                head->ante = p;
                p->prox = head;
                free(liberar);
            }
        }
    }
    else
    {
        while((strcmp(p->prox->nome,pessoa)))
        {
            if(p->prox == head)
            {
                test = 1;
                return head;
            }
            p = p->prox;
        }
        liberar = p->prox;
        if(liberar->prox == head)
        {
            p->prox=head;
            head->ante = p;
            free(liberar);
        }
        else
        {
        q = liberar->prox;
        p->prox = q;
        q->ante = p;
        free(liberar);
        }
    }
    return head;
}

int mostrar(char* pessoa, lista* head)
{
    if(head == NULL){
        return 1;
    }
    lista* p = NULL;
    p=head;
    while((strcmp(p->nome,pessoa)))
    {
        if(p->prox == head)
        {
            return 1;
        }
        p = p->prox;
    }
    showA = p->ante;
    show = p;
    showP = p->prox;
    return 0;
}
