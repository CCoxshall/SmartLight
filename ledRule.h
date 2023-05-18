#include "rgb.h"
#include "croncpp.h"

typedef struct ledRule 
{
    cron::cronexpr Cron;
    uint64_t TransitionTimeMs;
    TransitionType TransitionType;
    unsigned char Brightness;
    rgb Colour;
};

typedef enum TransitionType
{
    Brightness,
    Colour,
    Both
};