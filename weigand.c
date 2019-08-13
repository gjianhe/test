

static volatile uint8_t bitcount = 0;
static volatile uint32_t cardtemp = 0;
static volatile uint32_t lastwiegand = 0;

uint32_t CARDID = 0;

void wiegand26_readd0(void)
{
    bitcount++;
    cardtemp <<= 1;
    lastwiegand = gettick();
}

void wiegand26_readd1(void)
{
    bitcount++;
    cardtemp |= 1;
    cardtemp <<= 1;
    lastwiegand = gettick();
}

void wiegand26_conversion(void)
{
    uint32_t systick = gettick();

    if ((sysTick - lastwiegand) > 25)
    {
        if (bitcount == 26)
        {
            //cardtemp >>= 1;
            CARDID = (cardtemp & 0x1FFFFFE) >> 1;
            bitcount = 0;
            cardtemp = 0;
        }
    }
    else
    {
        lastwiegand = systick;
        bitcount = 0;
        cardtemp = 0;
    }
}
