/*
* Ping Pong OS
* pt_br.h
* Projeto da disciplina Sistemas Operacionais - UTFPR - 2016.02
* Professor: Copetti
* Alunos: Leonardo Winter Pereira (leonardowinterpereira@gmail.com)
*         Lucas Zimmermann Cordeiro ()
*/

/////////////////////////////////////////////////////////////////////
//                      Diretivas de Compilacao                    //
/////////////////////////////////////////////////////////////////////

#ifndef __PT_BR__
#define __PT_BR__
#endif

/////////////////////////////////////////////////////////////////////
//                             Mensagens                           //
/////////////////////////////////////////////////////////////////////

#define ERR_ELEM_NAO_EXISTE                     "ERRO: O elemento nao existe"
#define ERR_ELEM_VAZIO                          "ERRO: O elemento esta vazio"
#define ERR_ELEM_OUTRA_FILA                     "ERRO: O elemento ja esta em uma fila"
#define ERR_ELEM_NAO_PERTENCE_NA_FILA           "ERRO: O elemento nao pertence a esta fila"

#define ERR_FILA_VAZIA_OU_NAO_EXISTE            "ERRO: A fila nao existe ou esta vazia"

#define TASK_CONTEXT_INIT                       "task_init: inicializando no contexto"
#define TASK_CREATE                             "task_create: criou tarefa"
#define TASK_SWITCH                             "task_switch: trocando contexto"
#define TASK_EXIT                               "task_exit: voltando para main"
#define TASK_ID                                 "task_id: id da tarefa atual"

#define ERR_STACK_INIT                          "ERRO: Criacao da pilha"