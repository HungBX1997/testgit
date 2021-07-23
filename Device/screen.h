#ifndef _SCREEN_H_
#define _SCREEN_H_

typedef struct
{
    uint32_t Second;
    uint32_t Minute;
}Time_data_t;

typedef struct
{
    float DataSpeed;
    Time_data_t DataTime;
    float DataDistance;
    float DataCalo;
    uint8_t Incline;
}dataUpdate;

void updateData(dataUpdate Data);
void updateTime(uint32_t Time);
void updateDistance(float Dis);
void updateCalo(float Cal);
void updateIncline(uint8_t Incl);
void updateSpeed(float Speed);

void mainScreen();

#endif /*_SCREEN_H_*/