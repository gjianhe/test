static void ReceiveDataPrepare(uint8_t code dat)
{
    uint8_t check = 0, i = 0;
    static uint8_t state = 0;
    static uint8_t _data_cnt = 0;
    static uint8_t _data_len = 0;

    //第一个字节
    if (state == 0 && dat == CMD_HEAD)
    {
        state = 1;
        finger_rbuf[_data_cnt++] = dat;
    }
    //第二个字节
    else if (state == 1 && dat == CMD_MATCH)
    {
        state = 2;
        _data_len = 3;
        finger_rbuf[_data_cnt++] = dat;
    }
    //第三四五字节
    else if (state == 2 && _data_len > 0)   //数据
    {
        _data_len--;
        finger_rbuf[_data_cnt++] = dat;

        if (_data_len == 0)
        {
            state = 3;
        }
    }
    //第六字节
    else if (state == 3)
    {
        finger_rbuf[_data_cnt++] = dat;
        state = 4;
    }
    //第七字节
    else if (state == 4)
    {
        finger_rbuf[_data_cnt++] = dat;
        state = 5;
    }
    //第8字节
    else if (state == 5 && dat == CMD_TAIL)
    {
        finger_rbuf[_data_cnt++] = dat;
        state = 0;
        _data_cnt = 0;
        _data_len = 0;

        for (i = 0; i < 5; i++)
        {
            check ^= finger_rbuf[i + 1];
        }

        if (check == finger_rbuf[6])
        {
            ReceiveDataAnalyze((uint8_t code*)finger_rbuf);
        }
    }
    else
    {
        state = 0;
        _data_cnt = 0;
        _data_len = 0;
    }
}
