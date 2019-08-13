static uint8_t bit1_count(uint32_t ch)
{
    uint8_t cnt = 0;

    do
    {
        ch &= ch - 1;
        cnt++;
    } while (ch);

    return cnt;
}
