/*
* Ping Pong OS
* queue.c
* Projeto da disciplina Sistemas Operacionais - UTFPR - 2016.02
* Professor: Copetti
* Alunos: Leonardo Winter Pereira (leonardowinterpereira@gmail.com)
*         Lucas Zimmermann Cordeiro ()
*/

/////////////////////////////////////////////////////////////////////
//                      Diretivas de Compilacao                    //
/////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"
#include IDIOMA_ATUAL
#include <config/config.h>

/////////////////////////////////////////////////////////////////////
//                              DEFINEs                            //
/////////////////////////////////////////////////////////////////////

#define FILA_VAZIA              0
#define TAM_MIN_FILA            1

#define TRUE					1
#define FALSE					0

/////////////////////////////////////////////////////////////////////
//                           Prototipacoes                         //
/////////////////////////////////////////////////////////////////////

int esta_na_fila(queue_t *queue, queue_t *elem);

/////////////////////////////////////////////////////////////////////
//                    Funcoes definidas em queue.h                 //
/////////////////////////////////////////////////////////////////////

void queue_append (queue_t **queue, queue_t *elem)
{
    if (*queue)
    {
        if (elem) // Verifica a existência do elemento elem
        {
            if (elem->prev || elem->next) // Se o elemento ja estiver em outra fila, aborta a operacao
                printf("\n%s\n", ERR_ELEM_OUTRA_FILA);
            
            else
            {
                elem->next = *queue; // Elemento->"Esquerda" recebe o primeiro elemento da fila
                elem->prev = (*queue)->prev; // Elemento->"Direita" recebe o ex-ultimo elemento da fila
                
                (*queue)->prev->next = elem; // O novo penultimo ponteiro aponta para o Elemento (que agora e o ultimo)

                (*queue)->prev = elem; // O elemento anexado se torna o ultimo da fila
            }
        }
        else
            printf("\n%s\n", ERR_ELEM_VAZIO);
    }

    else // Se a fila estiver vazia e inserido o primeiro elemento
    {
        // O elemento vai apontar para ele mesmo, em todas as direcoes
        elem->next = elem;
        elem->prev = elem;
        
        *queue = elem;
    }
}

queue_t *queue_remove (queue_t **queue, queue_t *elem)
{
    queue_t *inicio         = NULL;
    queue_t *apontador_elem = NULL;

    if (*queue) // A fila nao pode estar vazia
    {
            if (elem) // O elemento deve existir
            {
                   if(esta_na_fila(*queue, elem)) // O elemento deve estar na fila
                   {
                        if(queue_size(*queue) > TAM_MIN_FILA) // Evita acesso indevido e� memoria
                        {
                               /*
                               * Se o elemento a ser deletado for igual ao primeiro,
                               * o inicio recebe o proximo (o 2o, se ele existir)
                               */
                               if ((*queue) != elem)
                                   inicio = *queue;
                               
                               else
                                   inicio = (*queue)->next;

                               // Percorre a fila ate encontrar o elemento
                               while((*queue) != elem)
                                   (*queue) = (*queue)->next;

                               // Quando encontrar troca os ponteiros para tira-lo da fila
                               (*queue)->prev->next = (*queue)->next;
                               (*queue)->next->prev = (*queue)->prev;

                               apontador_elem = (*queue);

                               (*queue)= (*queue)->next;

                               // Como ele está fora da fila, ele nao aponta para ninguem
                               apontador_elem->prev = NULL;
                               apontador_elem->next = NULL;

                               // Volta ao inicio da fila
                                while(*queue != inicio)
                                   *queue =(*queue)->next;
                        }
                        
                        else // Quando so restar 1 elemento na fila
                        {
                            apontador_elem = (*queue);
                            
                            apontador_elem->prev = NULL;
                            apontador_elem->next = NULL;
                            
                            (*queue) = NULL;
                        }
                        
                        return apontador_elem;

                    }

                    else
                    {
                        printf("\n%s\n", ERR_ELEM_NAO_PERTENCE_NA_FILA);
                        
                        return NULL;
                    }
            }
            
            else
            {
                printf("\n%s\n", ERR_ELEM_NAO_EXISTE);
                
                return NULL;
            }
    }

    else
    {
        printf("\n%s\n", ERR_FILA_VAZIA_OU_NAO_EXISTE);
        
        return NULL;
    }
}

int queue_size (queue_t *queue)
{
    queue_t *aux; // Auxiliar usado para percorrer a fila

    int tamanho = 0;

    if(queue) // A fila nao deve estar vazia
    {
        aux = queue;
        
        do
        {
            tamanho++;
            
            aux = aux->next;
        } while (aux != queue) ; // Acaba quando o auxiliar chega novamente ao inicio da fila
        
        return tamanho; /*Retorna a qtd de elementos (tamanho)*/
    }

    else
        return FILA_VAZIA;
}

void queue_print (char *name, queue_t *queue, void print_elem (void*))
{
    int cont;

    queue_t *aux; // Auxiliar usado para percorrer a fila

    aux = queue; // O auxiliar recebe a fila

    printf("%s:[", name);

    print_elem (queue); // Imprime somente o primeiro elemento
    
    printf(""); // ***********

    for (cont = 0; cont < queue_size(queue) - 1; cont++) // Imprime o resto dos elementos
    {
        printf(" ");
        
        print_elem(aux->next); /*Imprime o proximo elemento*/
        
        printf(""); // **********
        
        aux = aux->next;
    }

    printf("]\n");
}

/////////////////////////////////////////////////////////////////////
//                   Funcoes definidas pelos alunos                //
/////////////////////////////////////////////////////////////////////

int esta_na_fila(queue_t *queue, queue_t *elem)
{
    queue_t *aux;

    aux = queue; // Uma variavel auxiliar recebe a fila
    
    do
    {
        if (aux == elem)
           return TRUE; // Achando o elemento, retorna true
        
        aux = aux->prev; // Percorre a fila
    } while (aux != queue); // Ate voltar ao inicio da fila

    return FALSE; // Não achando o elemento, retorna false
}
