/*
 *******************************************************************************
 * Project:       bdb_puzzle
 * Description:   blank.
 * Author:        103
 *                hf0bae103@hotmail.com
 * File:          main.h
 * Processor:     blank.
 * IDE:           CodeBlocks 16.01
 * Version:       170303t1535
 * Notes:         blank.
 *******************************************************************************
*/

#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include <stdlib.h>

#define BDB_PUZZLE_TASK_t_MIN 1
#define BDB_PUZZLE_TASK_t_MAX 5

#define PR__ printf

typedef struct
{
    int tick;
    unsigned int count;
    unsigned int return_id;
}BDB_PUZZLE_t;

typedef struct
{
    unsigned int id;
    int (*function)(unsigned int, int, int, void *);
    unsigned int now;
    unsigned int stay;
    unsigned int flag;
    int parameter_1;
    int parameter_2;
    void *parameter_3;
}BDB_PUZZLE_TASK_t;

extern BDB_PUZZLE_t bdb_puzzle_t;
extern BDB_PUZZLE_TASK_t bdb_puzzle_task_t[BDB_PUZZLE_TASK_t_MAX];

#endif /* __MAIN_H */

/* END OF FILE ****************************************************************/

