#include "common-chax.h"
#include "random.h"

extern u16 *gRandStC;
static u16 *sRandStA = (u16 *)0x03000000;
int NextRN(void);

static int NextRNE(void)
{
    // This generates a pseudorandom string of 16 bits
    // In other words, a pseudorandom integer that can range from 0 to 65535

    u16 rn = (gRandStC[1] << 11) + (gRandStC[0] >> 5);

    // Shift state[2] one bit
    gRandStC[2] = gRandStC[2] << 1;

    // "carry" the top bit of state[1] to state[2]
    if (gRandStC[1] & 0x8000)
        gRandStC[2]++;

    rn ^= gRandStC[2];

    // Shifting the whole state 16 bits
    gRandStC[2] = gRandStC[1];
    gRandStC[1] = gRandStC[0];
    gRandStC[0] = rn;

    return rn;
}

void RandInitExt()
{
    int i;

    for(i = 0; i < 20; i++)
		NextRN();

	for( int i = 0; i < 3; i++ )
		gRandStC[i] = sRandStA[i];
}

int NextRNExts(int time)
{
    int ret;

    u16 bak[3] = {
        gRandStC[0],
        gRandStC[1],
        gRandStC[2]
    };

    while (time-- > 0)
        NextRNE();

    ret = NextRNE();

    gRandStC[0] = bak[0];
    gRandStC[1] = bak[1];
    gRandStC[2] = bak[2];

    return ret;
}

int RandNextExts(int max, int time)
{
    // take the next rn (range 0-0xFFFF) and convert it to a range 0-(max-1) value
    // NOTE: bugged due to rounding
    return NextRNExts(time) / (UINT16_MAX / max);
}


int RandNextExts_100(int time)
{
    // take the next rn (range 0-0xFFFF) and convert it to a range 0-(max-1) value
    // NOTE: bugged due to rounding
    return NextRNExts(time) / (UINT16_MAX / 100);
}

bool RandExtRoll2Rn(int threshold, int time)
{
    int rand;

    rand = RandNextExts_100(time);
    rand = rand + RandNextExts_100(time);
    rand = rand / 2;

    return (threshold > rand);
}
