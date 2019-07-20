//1.对消息帧中的全部字节相加（不包括起始“:”和结束符“CR-LF”，并把结果送入8位数据区，舍弃进位
//2.由0xFF减去最终的数据值，产生1的补码（即二进制反码）
//3.加“1”产生二进制补码

uint8_t LRC(uint8_t* Msg, uint16_t DataLen)
{
    uint8_t lrc = 0;

    while (DataLen--)
    {
        lrc += *(Msg++);
    }

    return ((uint8_t)(-((int8_t)lrc))); //返回二进制补码
}
