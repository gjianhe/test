uint16_t CRC16(uint8_t* Msg, uint16_t DataLen)
{
    int i;
    uint16_t RegCRC = 0xFFFF;

    while (DataLen--)
    {
        RegCRC ^= *(Msg++);

        for (i = 0; i < 8; i++)
        {
            RegCRC = (RegCRC & 0x0001) ? (RegCRC >> 1 ^ 0xA001) : (RegCRC >>= 1);
        }
    }

    return RegCRC;
}
