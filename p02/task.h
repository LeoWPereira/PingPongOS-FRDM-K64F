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
#include <ucontext.h>

typedef struct task_t
{
	struct task_t *prev, *next;
	int tid;
	ucontext_t context;
} task_t;

void task_init ();

int task_create (task_t * task, void (*start_routine)(void *),  void * arg);

int task_switch (task_t *task);

void task_exit (int exit_code);

int task_id ();
