/*
 *******************************************************************************
 * Project:       bdb_puzzle
 * Description:   blank.
 * Author:        103
 *                hf0bae103@hotmail.com
 * File:          main.c
 * Processor:     blank.
 * IDE:           CodeBlocks 16.01
 * Version:       170303t1535
 * Notes:         blank.
 *******************************************************************************
*/

#include "main.h"

BDB_PUZZLE_t bdb_puzzle_t;
BDB_PUZZLE_TASK_t bdb_puzzle_task_t[BDB_PUZZLE_TASK_t_MAX];

static void bdb_puzzle(void);
static void bdb_puzzle_task_insert(int (*function)(unsigned int, int, int, void *), unsigned int stay, unsigned int flag, int parameter_1, int parameter_2, void *parameter_3);
static unsigned int bdb_puzzle_task_clear(unsigned int count);
static void bdb_puzzle_task_state(void);

int task_template(unsigned int flag, int parameter_1, int parameter_2, void *parameter_3);

int main()
{
    bdb_puzzle_task_insert(task_template, 10, 0, -10, 10, NULL);

    bdb_puzzle_task_state();

    for(;;)
    {
        bdb_puzzle();

        bdb_puzzle_t.tick++;
    }

    return 0;
}

/*
 * bdb_puzzle()
 * Description:   blank.
 * Parameter:     none.
 * Return:        none.
 * Notes:         blank.
*/
static void bdb_puzzle(void)
{
    unsigned int now = 0;
    unsigned int stay = 0;
    int return_value = 0;

    if(bdb_puzzle_task_t[bdb_puzzle_t.count].id != 0)
    {
        now = bdb_puzzle_t.tick;

        if(now > bdb_puzzle_task_t[bdb_puzzle_t.count].now)
        {
            stay = now - bdb_puzzle_task_t[bdb_puzzle_t.count].now;
        }
        else
        {
            stay = bdb_puzzle_task_t[bdb_puzzle_t.count].now - now;
        }

        if(stay >= bdb_puzzle_task_t[bdb_puzzle_t.count].stay)
        {
            return_value = bdb_puzzle_task_t[bdb_puzzle_t.count].function(bdb_puzzle_task_t[bdb_puzzle_t.count].flag, bdb_puzzle_task_t[bdb_puzzle_t.count].parameter_1, bdb_puzzle_task_t[bdb_puzzle_t.count].parameter_2, bdb_puzzle_task_t[bdb_puzzle_t.count].parameter_3);

            // 임시
            return_value = (return_value == 0) ? 0 : return_value;

            bdb_puzzle_t.return_id = bdb_puzzle_task_clear(bdb_puzzle_t.count);
        }
    }

# if 0
// 2016년 10월 20일
// STM32F407VGT7에서 구문 실행 시 오동작
    bdb_puzzle_t.count >= BDB_PUZZLE_TASK_t_MAX ? bdb_puzzle_t.count = 0 : bdb_puzzle_t.count++;
# else
// 2016년 10월 20일
// STM32F407VGT7에서 구문 실행 시 정상 동작
    bdb_puzzle_t.count++;

    if(bdb_puzzle_t.count >= BDB_PUZZLE_TASK_t_MAX)
    {
            bdb_puzzle_t.count = 0;
    }
#endif
}

/*
 * bdb_puzzle_task_insert()
 * Description:   blank.
 * Parameter:     none.
 * Return:        none.
 * Notes:         blank.
*/
static void bdb_puzzle_task_insert(int (*function)(unsigned int, int, int, void *), unsigned int stay, unsigned int flag, int parameter_1, int parameter_2, void *parameter_3)
{
    unsigned int count;

    for(count = BDB_PUZZLE_TASK_t_MIN; count < BDB_PUZZLE_TASK_t_MAX; count++)
    {
        if(bdb_puzzle_task_t[count].id == 0)
        {
            break;
        }
    }

    bdb_puzzle_task_t[count].id = count;
    bdb_puzzle_task_t[count].function = function;
    bdb_puzzle_task_t[count].now = bdb_puzzle_t.tick;
    bdb_puzzle_task_t[count].stay = stay;
    bdb_puzzle_task_t[count].flag = flag;
    bdb_puzzle_task_t[count].parameter_1 = parameter_1;
    bdb_puzzle_task_t[count].parameter_2 = parameter_2;
    bdb_puzzle_task_t[count].parameter_3 = parameter_3;
}

/*
 * bdb_puzzle_task_clear()
 * Description:   blank.
 * Parameter:     none.
 * Return:        none.
 * Notes:         blank.
*/
static unsigned int bdb_puzzle_task_clear(unsigned int count)
{
    bdb_puzzle_task_t[count].id = 0;
    bdb_puzzle_task_t[count].function = 0;
    bdb_puzzle_task_t[count].now = 0;
    bdb_puzzle_task_t[count].stay = 0;
    bdb_puzzle_task_t[count].flag = 0;
    bdb_puzzle_task_t[count].parameter_1 = 0;
    bdb_puzzle_task_t[count].parameter_2 = 0;
    bdb_puzzle_task_t[count].parameter_3 = 0;

    return count;
}

/*
 * bdb_puzzle_task_state()
 * Description:   blank.
 * Parameter:     none.
 * Return:        none.
 * Notes:         blank.
*/
static void bdb_puzzle_task_state(void)
{
    unsigned int count;
    int return_value = 0;

    PR__("----- bdb_puzzle_task_state -----\n\r");

    for(count = BDB_PUZZLE_TASK_t_MIN; count < BDB_PUZZLE_TASK_t_MAX; count++)
    {
        if(bdb_puzzle_task_t[count].id != 0)
        {
            PR__("[%d: %d]", count, bdb_puzzle_task_t[count].stay);
            return_value = bdb_puzzle_task_t[count].function(1, 0, 0, 0);

            PR__("(%d)(%d)(0x%p)\n\r", bdb_puzzle_task_t[count].parameter_1, bdb_puzzle_task_t[count].parameter_2, bdb_puzzle_task_t[count].parameter_3);
        }

        // 임시
        return_value = (return_value == 0) ? 0 : return_value;
    }
}

/*
 * task_template()
 * Description:   blank.
 * Parameter:     none.
 * Return:        none.
 * Notes:         blank.
*/
int task_template(unsigned int flag, int parameter_1, int parameter_2, void *parameter_3)
{
    unsigned err = 0;

    switch(flag)
    {
        case 1:
            PR__(" %s ", __func__);
            goto task_template_EXIT;
            return 0;
        default:
            break;
    }

task_template_EXIT:
    return err;
}

/* END OF FILE ****************************************************************/

