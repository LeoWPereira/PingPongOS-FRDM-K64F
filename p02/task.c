/*
* Ping Pong OS
* task.c
* Projeto da disciplina Sistemas Operacionais - UTFPR - 2016.02
* Professor: Copetti
* Alunos: Leonardo Winter Pereira (leonardowinterpereira@gmail.com)
*         Lucas Zimmermann Cordeiro ()
*/

#include <config/includes.h>

#include <p00/queue.h>

#include <config/config.h>
#include IDIOMA_ATUAL

#define STACKSIZE 32768

<<<<<<< HEAD
task_t* tarefaAtual;
task_t* tarefaQueue;

task_t tarefa_main;
task_t dispatcher;
=======
task_t *tarefaAtual;
task_t task_main;
>>>>>>> 308cce4eb64f954b35550efd3b3513f15d14d271

int id = 0;

/**=================================================================================**/

void task_init ()
{
<<<<<<< HEAD
	tarefaQueue = NULL;
=======
    /** Esta funcao inicializa as estruturas necessarias para a execucao das tarefas.
    Por enquanto, contem apenas algumas inicializacoes de variaveis da biblioteca **/
>>>>>>> 308cce4eb64f954b35550efd3b3513f15d14d271

	tarefa_main.tid = id;

	getcontext(&tarefa_main.context);

	tarefaAtual = &tarefa_main;

<<<<<<< HEAD
	// desativa o buffer da saida padrao (stdout), usado pela função printf
	setvbuf (stdout, 0, _IONBF, 0) ;

	#ifdef DEBUG
		printf ("task_init: inicializou a tarefa %d\n", tarefaAtual->tid) ;
	#endif

	id++ ;
=======
    setvbuf (stdout, 0, _IONBF, 0) ; // desativa o buffer da saida padrao (stdout), usado pela funcao printf

    #ifdef DEBUG
        printf ("%s %d\n", TASK_CONTEXT_INIT, tarefaAtual->tid);
    #endif
>>>>>>> 308cce4eb64f954b35550efd3b3513f15d14d271

	task_create(&dispatcher, dispatcher_body, NULL);
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

    task_t *aux;

    getcontext(&task->context);

    stack = malloc (STACKSIZE);

    //deve-se alocar um novo espaço na fila para esse contexto e atribuir
	//seu endereço para contexto->uc_stack e definir um sucessor para o
	//contexto e atribuir seu endereço para contexto->uc_link
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

    task->tid = id;

    makecontext (&(task->context),
    			(void*)(*start_routine),
				1,
				arg);

    // na primeira execução desta função, que será o dispatcher que executará, não vai adicionar na fila, pois para adicionar deve entrar no else
	if (task->tid > 1)
	{
		queue_append ((queue_t **) &tarefaQueue, (queue_t *) task);

<<<<<<< HEAD
		// adiciona a tarefa (que não é o dispatcher) na fila de tarefas prontas
=======
    #ifdef DEBUG
        printf ("%s %d\n", TASK_CREATE, task->tid);
    #endif
>>>>>>> 308cce4eb64f954b35550efd3b3513f15d14d271

		task->prioridadeDinamica = 0;
		task->prioridadeEstatica = 0;
		// prioridade estatica e dinamica 0 na tarefa ao ser criada (default)
	}

	#ifdef DEBUG
		printf ("task_create: criou tarefa %d\n", task->tid) ;

		queue_print ("Elementos da fila:  ", (queue_t*) tarefaQueue, print_queue);

		printf ("\n\n") ;
	#endif

	id++;

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
<<<<<<< HEAD
    	printf ("task_switch: trocando contexto de %d para %d\n", aux->tid, task->tid) ;
=======
        printf ("%s de %d para %d\n", TASK_SWITCH, aux->tid, task->tid) ;
>>>>>>> 308cce4eb64f954b35550efd3b3513f15d14d271
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

<<<<<<< HEAD
	#ifdef DEBUG
		printf ("task_exit: encerrou a tarefa %d\n", tarefaAtual->tid) ;
	#endif

	// quando dispatcher encerra, volta pra main
	if (tarefaAtual->tid == 1)
		task_switch (&tarefa_main);

	// quando uma tarefa encerra, volta para o dispatcher
	else
	{
		// remove da fila a tarefa que encerrou
		queue_remove ((queue_t **) &tarefaQueue, (queue_t *) tarefaAtual) ;

		#ifdef DEBUG
			queue_print ("Elementos da fila:  ", (queue_t*) tarefaQueue, print_queue);
=======
    #ifdef DEBUG
        printf ("%s\n", TASK_EXIT);
    #endif
>>>>>>> 308cce4eb64f954b35550efd3b3513f15d14d271

			printf ("\n\n") ;
		#endif

		// volta pro dispatcher
		task_switch(&dispatcher);
	}
}

/**=================================================================================**/

int task_id ()
{
    /** retorno: Identificador numerico (ID) da tarefa corrente,
    que devera ser 0 para main, ou um valor positivo para as demais tarefas.
    Esse identificador e unico: nao existem duas tarefas com o mesmo ID.**/

    #ifdef DEBUG
<<<<<<< HEAD
    	printf ("task_id: id da tarefa atual: %d\n", tarefaAtual->tid);
=======
        printf ("%s: %d\n", TASK_ID, tarefaAtual->tid);
>>>>>>> 308cce4eb64f954b35550efd3b3513f15d14d271
    #endif

    return tarefaAtual->tid;
}

void task_yield ()
{
	task_t* auxTask; // auxiliar para identificar a task atual
	task_t* auxQueue; // auxiliar para poder varrer a fila, se usasse o próprio taskQueue para varrer, perderia o primeiro elemento da fila

	auxQueue = tarefaQueue;

	int tamFila = queue_size ((queue_t *) tarefaQueue);

	// busca o task atual na fila se nao for a main
	if (tarefaAtual->tid > 1)
	{
		do
		{
			if (tarefaAtual->tid == auxQueue->tid)
			{
				auxTask = auxQueue;

				tamFila = 0; 	// só para poder sair do do while
			}

			auxQueue = auxQueue->next;

			tamFila--;

		} while (tamFila > 0);

		// se nao for a main, vai remover o task original que por enquanto é o primeiro da fila, e insere de volta na fila (sempre no final)
		queue_remove ((queue_t **) &tarefaQueue, (queue_t *) tarefaAtual);
		queue_append ((queue_t **) &tarefaQueue, (queue_t *) tarefaAtual);

		auxQueue = tarefaQueue;

		#ifdef DEBUG
			queue_print ("Elementos da fila (remove/append):  \n", (queue_t*) tarefaQueue, print_queue);
		#endif
	}

	// se for a main, nao vai estar na fila, por isso nao tá no if acima, entao o auxiliar do task só vai receber o taskAtual (que já é a main)
	else
		auxTask = tarefaAtual;

	// quando chama task_yield, deve ir para o dispatcher sempre, então será o taskAtual
	tarefaAtual = &dispatcher;

	#ifdef DEBUG
		printf ("task_yield: a tarefa %d liberou o processador\n\n\n", auxTask->tid) ;
	#endif

	// Precisa de aux pq tem que sempre atualizar o taskAtual, mas como você quer passar como parametro no swapcontext() o parametro atual, se passar o taskAtual vai acabar passando o proprio task, então precisa de um auxiliar que vai ser a tarefa original, antes de trocar de contexto.

	if (swapcontext(&auxTask->context, &dispatcher.context) == -1)
	{
		perror("Erro na liberaçao do processador.\n");

		return ;
	}
}

task_t* scheduler (void* arg)
{
	int tam = queue_size ((queue_t *) tarefaQueue);

	task_t* auxQueue;
	task_t* auxTask;

	auxQueue = tarefaQueue;
	auxTask = tarefaQueue;

	// varre a fila inteira e acha o menor valor de prioridade
	do
	{
		// começa verificando a prioridade do primeiro da fila e vai indo até o final dela, procurando o menor valor e atribuindo a auxTask, quando chega ao final, auxTask terá o menor valor
		if (auxQueue->prioridadeDinamica < auxTask->prioridadeDinamica)
			auxTask = auxQueue;

		auxQueue = auxQueue->next;

	} while (auxQueue != tarefaQueue);

	#ifdef DEBUG
		printf ("Proxima tarefa:  %d\n", auxTask->tid);
	#endif

	auxQueue = tarefaQueue;

	// aumentando prioridade de todas as tarefas
	do
	{
		// não diminui prioridade da tarefa em questão (que é o auxTask)
		if (auxQueue != auxTask)
			auxQueue->prioridadeDinamica--;

		else
			auxQueue->prioridadeDinamica = auxQueue->prioridadeEstatica ;

		#ifdef DEBUG
			printf ("scheduler: Tarefa %d, prioridade %d\n", auxQueue->tid, auxQueue->prioridadeDinamica);
		#endif

		auxQueue = auxQueue->next;
		tam--;

	} while (tam > 0);

	return auxTask;
}

void dispatcher_body (void* arg)
{
	task_t* proximo;

	// se o numero de tarefas for maior que zero
	while (queue_size ((queue_t *) tarefaQueue) > 0)
	{
		proximo = scheduler(NULL);

		if(proximo)
			task_switch(proximo); // transfere controle para a tarefa "next"
	}

	task_exit(0); // // encerra dispatcher e volta pra main
}

void print_queue (void * task)
{
	task_t *elem = task;

	if (!elem)
		return ;

	if (elem->prev)
		printf (" %d", elem->prev->tid) ;

	else
		printf ("*") ;

	printf ("<%d>", elem->tid) ;

	if (elem->next)
		printf ("%d", elem->next->tid) ;

	else
		printf ("*") ;
}

int task_nice (int nice_level)
{
	int prioridade = tarefaAtual->prioridadeEstatica ;

	if (((prioridade + nice_level) <= 20 ) && ((prioridade + nice_level) >= -20))
	{
		tarefaAtual->prioridadeEstatica = nice_level ;
		tarefaAtual->prioridadeDinamica = nice_level ;

		#ifdef DEBUG
			printf ("task_nice: Tarefa %d, prioridade %d\n", tarefaAtual->tid, tarefaAtual->prioridadeDinamica) ;
		#endif

		return prioridade;
	}

	else
	{
		printf("A prioridade ficou fora do intervalo -20 a 20\n");

		return 0 ;
	}
}

