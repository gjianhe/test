#include "hsch.h"


sTask hSCH_tasks_G[HSCH_MAX_TASKS];



void hSCH_Tasks(void)
{
    unsigned char Index;

    for (Index = 0; Index < HSCH_MAX_TASKS; Index++)
    {
        // 判断是否有任务需要运行并且该任务是合作式任务
        if (hSCH_tasks_G[Index].RunMe > 0 && hSCH_tasks_G[Index].Co_op)
        {
            hSCH_tasks_G[Index].RunMe -= 1;
            (*hSCH_tasks_G[Index].pTask)();

            if (hSCH_tasks_G[Index].Period == 0)
            {
                hSCH_Delete_Task(Index);
            }
        }
    }
}

unsigned char hSCH_Add_Task(void (*pFun)(void),
                            const unsigned short Delay,
                            const unsigned short Period,
                            const unsigned char Co_op)
{
    unsigned char Index = 0;

    while ((hSCH_tasks_G[Index].pTask != 0) && (Index < HSCH_MAX_TASKS))
    {
        Index++;
    }

    if (Index == HSCH_MAX_TASKS)
    {
        return HSCH_MAX_TASKS;
    }

    hSCH_tasks_G[Index].pTask = pFun;
    hSCH_tasks_G[Index].Delay = Delay;
    hSCH_tasks_G[Index].Period = Period;
    hSCH_tasks_G[Index].RunMe = 0;
    hSCH_tasks_G[Index].Co_op = Co_op;
    //
    return Index;
}

void hSCH_Delete_Task(const unsigned char Task_Index)
{
    unsigned char Index = 0;

    if (hSCH_tasks_G[Index].pTask != 0)
    {
        hSCH_tasks_G[Index].pTask = 0;
        hSCH_tasks_G[Index].Delay = 0;
        hSCH_tasks_G[Index].Period = 0;
        hSCH_tasks_G[Index].RunMe = 0;
        hSCH_tasks_G[Index].Co_op = 0;
    }
}

void hSCH_Update(void)
{
    unsigned char Index;

    for (Index = 0; Index < HSCH_MAX_TASKS; Index++)
    {
        if (hSCH_tasks_G[Index].pTask)
        {
            if (hSCH_tasks_G[Index].Delay == 0)
            {
                if (hSCH_tasks_G[Index].Co_op)  // 合作式任务
                {
                    hSCH_tasks_G[Index].RunMe += 1;
                }
                else    // 抢占式任务
                {
                    (*hSCH_tasks_G[Index].pTask)();
                }

                if (hSCH_tasks_G[Index].Period)
                {
                    // 重复性任务
                    hSCH_tasks_G[Index].Delay = hSCH_tasks_G[Index].Period;
                }
                else
                {
                    // 非重复性任务
                    if (!hSCH_tasks_G[Index].Co_op)
                    {
                        // 抢占式任务在这边删除，合作式任务在hSCH_Tasks中删除
                        hSCH_Delete_Task(Index);
                    }
                }
            }
            else
            {
                hSCH_tasks_G[Index].Delay -= 1;
            }
        }
    }
}


