static uint16_t CrcValueCalc(const uint8_t* Data, int length)
{
    int i;
    uint16_t crcValue = 0xffff;

    while (length --)
    {
        crcValue ^= (uint16_t) * (Data ++);
        #if 0
        for (i = 7; i >= 0; i --)
        #else
        for (i = 0; i < 8; i++)
        #endif
        {
            crcValue = (crcValue & 0x0001) ? ((crcValue >> 1) ^ 0xa001) : (crcValue >> 1);
        }
    }

    return crcValue;
}