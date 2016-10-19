/*
* Ping Pong OS
* task.h
* Projeto da disciplina Sistemas Operacionais - UTFPR - 2016.02
* Professor: Copetti
* Alunos: Leonardo Winter Pereira (leonardowinterpereira@gmail.com)
*         Lucas Zimmermann Cordeiro ()
*/

/*
 * Esse arquivo, ao contrario do explicado no PDF da pratica,
 * foi separado em cada uma das sub-atividades, para facilitar o entendimento
 * do SO!
 * Esse arquivo e a referencia apenas para as funcoes e a estrutura das tasks
 */

// ucontext somente disponivel no LINUX

#ifndef __TASK_H__
#define __TASK_H__

//////////////////////////////////////////////////////////////////
// 							DEPENDENCIAS						//
//////////////////////////////////////////////////////////////////

#include <config/includes.h>

//////////////////////////////////////////////////////////////////
// 								STRUCTS							//
//////////////////////////////////////////////////////////////////
typedef struct task_t
{
	struct task_t *prev, *next;

	int tid;
	int prioridadeEstatica ;
	int prioridadeDinamica ;

	ucontext_t context;
} task_t;

//////////////////////////////////////////////////////////////////
// 						PROTOTIPOS DE FUNCOES					//
//////////////////////////////////////////////////////////////////

void task_init ();

int task_create (task_t * task, void (*start_routine)(void *),  void * arg);

int task_switch (task_t *task);

void task_exit (int exit_code);

int task_id ();

void task_yield();

task_t* scheduler(void* arg);

void dispatcher_body(void* arg);

void print_queue (void * task);

int task_nice (int nice_level);

#endif
