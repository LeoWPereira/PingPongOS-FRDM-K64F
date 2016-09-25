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

#define STACKSIZE 32768

task_t *tarefaAtual;
task_t task_main;
int id = 0;

/**=================================================================================**/

void task_init ()
{
    /** Esta funcao inicializa as estruturas necessarias para a execu��o das tarefas.
    Por enquanto, contem apenas algumas inicializacoes de variaveis da biblioteca **/
    /* desativa o buffer da saida padrao (stdout), usado pela fun��o printf */

	tarefaAtual = &task_main;

	getcontext (&tarefaAtual->context);

	tarefaAtual->next = NULL;
	tarefaAtual->prev = NULL;

    setvbuf (stdout, 0, _IONBF, 0) ;

    #ifdef DEBUG
    printf ("task_init: inicializando no contexto %d\n", current->id);
    #endif

    tarefaAtual->tid = id++;
}

/**=================================================================================**/

int task_create (task_t * task, void (*start_routine)(void *),  void * arg)
{
    /** Aten��o: deve ser previsto um descritor de tarefa que aponte para o programa principal
    (que exercer� a mesma fun��o da vari�vel ContextMain no programa pingpong.c) **/
   /* task: estrutura que referencia a tarefa criada
    start_routine: fun��o que ser� executada pela tarefa
    arg: par�metro a passar para a tarefa que est� sendo criada
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
        perror ("Erro na cria��o da pilha: ");

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
    printf ("task_create: criou tarefa %d\n", task->id);
    #endif

    return tarefaAtual->tid;
}

/**=================================================================================**/

int task_switch (task_t *task)
{
    /** Esta e a opera��o basica de troca de contexto, que encapsula a funcao swapcontext.
    Ela sera chamada sempre que for necessaria uma troca de contexto **/
    /* task: tarefa que ira assumir o processador
    retorno: valor negativo se houver erro, ou zero */

    task_t *aux;

    aux = tarefaAtual;
    tarefaAtual = task;

    if ((!aux) || tarefaAtual != task)
        return -1;

    #ifdef DEBUG
    printf ("task_switch: trocando contexto de %d para %d\n", aux->id, task->id) ;
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
    printf ("task_exit: voltando para main\n");
    #endif

    task_switch(&task_main);
}

/**=================================================================================**/

int task_id ()
{
    /** retorno: Identificador numerico (ID) da tarefa corrente,
    que devera ser 0 para main, ou um valor positivo para as demais tarefas.
    Esse identificador e �nico: nao existem duas tarefas com o mesmo ID.**/

    #ifdef DEBUG
    printf ("task_id: id da tarefa atual: %d\n", current->id);
    #endif

    return tarefaAtual->tid;
}
