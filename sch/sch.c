#include "sch.h"


sTask SCH_tasks_G[SCH_MAX_TASKS];


void SCH_Tasks(void)
{
    unsigned char Index;

    for (Index = 0; Index < SCH_MAX_TASKS; Index++)
    {
        if (SCH_tasks_G[Index].RunMe > 0)
        {
            (*SCH_tasks_G[Index].pTask)();
            SCH_tasks_G[Index].RunMe -= 1;

            if (SCH_tasks_G[Index].Period == 0)
            {
                SCH_Delete_Task(Index);
            }
        }
    }
}


unsigned char SCH_Add_Task(void (*pFun)(void),
                           const unsigned short Delay,
                           const unsigned short Period)
{
    unsigned char Index = 0;

    while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS))
    {
        Index++;
    }

    if (Index == SCH_MAX_TASKS)
    {
        return SCH_MAX_TASKS;
    }

    SCH_tasks_G[Index].pTask = pFun;
    SCH_tasks_G[Index].Delay = Delay;
    SCH_tasks_G[Index].Period = Period;
    SCH_tasks_G[Index].RunMe = 0;
    return Index;
}


void SCH_Delete_Task(const unsigned char Task_Index)
{
    unsigned char Index = 0;
    
    if (SCH_tasks_G[Index].pTask != 0)
    {
        SCH_tasks_G[Index].pTask = 0;
        SCH_tasks_G[Index].Delay = 0;
        SCH_tasks_G[Index].Period = 0;
        SCH_tasks_G[Index].RunMe = 0;
    }
}


void SCH_Update(void)
{
    unsigned char Index;

    for (Index = 0; Index < SCH_MAX_TASKS; Index++)
    {
        if (SCH_tasks_G[Index].pTask)
        {
            if (SCH_tasks_G[Index].Delay == 0)
            {
                SCH_tasks_G[Index].RunMe += 1;

                if (SCH_tasks_G[Index].Period)
                {
                    SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
                }
            }
            else
            {
                SCH_tasks_G[Index].Delay -= 1;
            }
        }
    }
}


