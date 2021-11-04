#ifndef __HSCH_H
#define __HSCH_H

typedef struct
{
    void (*pTask)(void);    // 任务指针
    unsigned short Delay;   // 0，首次立马运行，非0，间隔Delay再运行第一次
    unsigned short Period;  // 0，单次任务，非0，任务周期运行单位
    unsigned char RunMe;
    unsigned char Co_op;    // 任务类型，1合作式，0抢占式(在中断中运行)
} sTask;


#define HSCH_MAX_TASKS   (1)    // 任务总个数


extern void hSCH_Update(void);
extern void hSCH_Tasks(void);
extern void hSCH_Delete_Task(const unsigned char Task_Index);
extern unsigned char hSCH_Add_Task(void (*pFun)(void),
                                   const unsigned short Delay,
                                   const unsigned short Period,
                                   const unsigned char Co_op
                                   );


#endif

