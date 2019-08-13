static void ReceiveDataAnalyze(uint8_t code* buf)
{
    switch (buf[1])
    {
        case 0x0C: //比对1:N
			//buf[4]是用户权限，有效范围是1～3
            if (buf[4] >= 1 && buf[4] <= 3)
            {
				//buf[2]是用户号高位，buf[3]是用户号低位
                USERID = (uint16_t)(buf[2] << 8) | buf[3];
            }
            else
            {
                USERID = 0;
            }
            
            break;

        default:
            break;
    }
}

static void ReceiveDataPrepare(uint8_t code dat)
{
    uint8_t check = 0, i = 0;
    static uint8_t state = 0;
    static uint8_t _data_cnt = 0;
    static uint8_t _data_len = 0;

    //第一个字节0xF5
    if (state == 0 && dat == 0xF5)
    {
        state = 1;
        finger_rbuf[_data_cnt++] = dat;
    }
    //第二个字节CMD
    else if (state == 1)
    {
        state = 2;
        _data_len = 3;
        finger_rbuf[_data_cnt++] = dat;
    }
    //第三四五字节Q1,Q2,Q3
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
    //第七字节CHK
    else if (state == 4)
    {
        finger_rbuf[_data_cnt++] = dat;
        state = 5;
    }
    //第8字节0xF5
    else if (state == 5 && dat == 0xF5)
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
