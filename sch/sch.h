#ifndef __SCH_H
#define __SCH_H

typedef struct
{
    void (*pTask)(void);
    unsigned short Delay;
    unsigned short Period;
    unsigned char RunMe;
} sTask;


#define SCH_MAX_TASKS   (2)

extern void SCH_Tasks(void);
extern void SCH_Delete_Task(const unsigned char Task_Index);
extern void SCH_Update(void);
extern unsigned char SCH_Add_Task(void (*pFun)(void),
                                  const unsigned short Delay,
                                  const unsigned short Period);

#endif

