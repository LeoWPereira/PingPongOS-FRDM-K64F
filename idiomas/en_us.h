/*
* Ping Pong OS
* en_us.h
* Projeto da disciplina Sistemas Operacionais - UTFPR - 2016.02
* Professor: Copetti
* Alunos: Leonardo Winter Pereira (leonardowinterpereira@gmail.com)
*         Lucas Zimmermann Cordeiro ()
*/

/////////////////////////////////////////////////////////////////////
//                      Diretivas de Compilacao                    //
/////////////////////////////////////////////////////////////////////

#ifndef __EN_US__
#define __EN_US__
#endif

/////////////////////////////////////////////////////////////////////
//                             Mensagens                           //
/////////////////////////////////////////////////////////////////////

#define ERR_ELEM_NAO_EXISTE                     "ERROR: Element does not exist"
#define ERR_ELEM_VAZIO                          "ERROR: Element is empty"
#define ERR_ELEM_OUTRA_FILA                     "ERROR: Element is already in another queue"
#define ERR_ELEM_NAO_PERTENCE_NA_FILA           "ERROR: Element does not belong to this queue"

#define ERR_FILA_VAZIA_OU_NAO_EXISTE            "ERROR: The queue does not exist or it is empty"

#define TASK_CONTEXT_INIT                       "task_init: initializing context"
#define TASK_CREATE                             "task_create: task created"
#define TASK_SWITCH                             "task_switch: switching context"
#define TASK_EXIT                               "task_exit: returning to main"
#define TASK_ID                                 "task_id: actual task's id"

#define ERR_STACK_INIT                          "ERROR: Stack creation"
