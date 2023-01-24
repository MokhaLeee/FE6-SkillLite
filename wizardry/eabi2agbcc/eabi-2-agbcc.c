#include "common-chax.h"

#ifndef SItype
typedef __signed__ long int SItype;
#endif

SItype __divsi3(SItype a, SItype b);

SItype __aeabi_idiv(SItype a, SItype b)
{
  return __divsi3(a, b);
}
