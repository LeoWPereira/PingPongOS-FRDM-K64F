/*
* Ping Pong OS
* task.c
* Projeto da disciplina Sistemas Operacionais - UTFPR - 2016.02
* Professor: Copetti
* Alunos: Leonardo Winter Pereira (leonardowinterpereira@gmail.com)
*         Lucas Zimmermann Cordeiro ()
*/

#include <stdio.h>
#include <stdlib.h>

#include "task.h"

#include <config/config.h>
#include IDIOMA_ATUAL

#define STACKSIZE 32768

task_t *tarefaAtual;
task_t task_main;

int id = 0;

/**=================================================================================**/

void task_init ()
{
    /** Esta funcao inicializa as estruturas necessarias para a execucao das tarefas.
    Por enquanto, contem apenas algumas inicializacoes de variaveis da biblioteca **/

	tarefaAtual = &task_main;

	getcontext (&tarefaAtual->context);

	tarefaAtual->next = NULL;
	tarefaAtual->prev = NULL;

    setvbuf (stdout, 0, _IONBF, 0) ; // desativa o buffer da saida padrao (stdout), usado pela funcao printf

    #ifdef DEBUG
        printf ("%s %d\n", TASK_CONTEXT_INIT, tarefaAtual->tid);
    #endif

    tarefaAtual->tid = id++;
}

/**=================================================================================**/

int task_create (task_t * task, void (*start_routine)(void *),  void * arg)
{
    /** Atencao: deve ser previsto um descritor de tarefa que aponte para o programa principal
    (que exercera a mesma funcao da variavel ContextMain no programa task.c) **/
   
    /* task: estrutura que referencia a tarefa criada
    start_routine: funcao que sera executada pela tarefa
    arg: parametro a passar para a tarefa que esta sendo criada
    retorno: o ID da task ou valor negativo, se houver erro */

    char* stack;

    getcontext(&task->context);

    stack = malloc (STACKSIZE);

    if (stack)
    {
        task->context.uc_stack.ss_sp = stack ;
        task->context.uc_stack.ss_size = STACKSIZE;
        task->context.uc_stack.ss_flags = 0;
        task->context.uc_link = 0;
    }
    else
    {
        perror ("%s: ", ERR_STACK_INIT);

        return -1;
    }

    makecontext (&(task->context),
    			(void*)(*start_routine),
				1,
				arg);

    task->tid = id++;
	task->prev = NULL;
	task->next = NULL;

    #ifdef DEBUG
        printf ("%s %d\n", TASK_CREATE, task->tid);
    #endif

    return tarefaAtual->tid;
}

/**=================================================================================**/

int task_switch (task_t *task)
{
    /** Esta e a operacao basica de troca de contexto, que encapsula a funcao swapcontext.
    Ela sera chamada sempre que for necessaria uma troca de contexto **/
    /* task: tarefa que ira assumir o processador
    retorno: valor negativo se houver erro, ou zero */

    task_t *aux;

    aux = tarefaAtual;
    tarefaAtual = task;

    if ((!aux) || tarefaAtual != task)
        return -1;

    #ifdef DEBUG
        printf ("%s de %d para %d\n", TASK_SWITCH, aux->tid, task->tid) ;
    #endif

    swapcontext( &(aux->context), &(task->context) );

    return 0;
}

/**=================================================================================**/

void task_exit (int exit_code)
{
    /** Quando uma tarefa encerra, o controle deve retornar a tarefa main.
    Esta chamada sera implementada usando task_switch **/
    /* exit_code : codigo de termino devolvido pela tarefa corrente
    (ignorar este parametro por enquanto, pois ele somente sera usado mais tarde) */

    #ifdef DEBUG
        printf ("%s\n", TASK_EXIT);
    #endif

    task_switch(&task_main);
}

/**=================================================================================**/

int task_id ()
{
    /** retorno: Identificador numerico (ID) da tarefa corrente,
    que devera ser 0 para main, ou um valor positivo para as demais tarefas.
    Esse identificador e unico: nao existem duas tarefas com o mesmo ID.**/

    #ifdef DEBUG
        printf ("%s: %d\n", TASK_ID, tarefaAtual->tid);
    #endif

    return tarefaAtual->tid;
}
