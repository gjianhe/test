#include <stdio.h>
#include <math.h>
#define PI 3.14159

#define F 60    /* 频率 */

int main(void)
{
    FILE* fp;
    int i;
    int arr[101];

    /* 新建文件 */
    fp = fopen("out.txt", "w");

    /* 计算，*1000000是把时间换算成微秒，+0.5四舍五入 */
    for (i = 0; i < 101; i++)
    {
        arr[i] = (1.0 / (F * 2) - (acos(1.0 - i / 50.0) / (2 * F * PI))) * 1000000 + 0.5;
    }

    /* 输出到文件 */
    fprintf(fp, "arr[]={");

    for (i = 0; i < 101; i++)
    {
        /* 每10个换行 */
        if (i % 10 == 0)
        {
            fprintf(fp, "\n");
        }

        fprintf(fp, "%-5d,", arr[i]);
    }

    fprintf(fp, "\n}");

    fclose(fp);

    return 0;
}
