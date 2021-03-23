#ifndef _SCREEN_H_
#define _SCREEN_H_

typedef struct
{
    uint32_t second;
    uint32_t minute;
}Time_data_t;

typedef struct
{
    float dataSpeed;
    Time_data_t dataTime;
    float dataDistance;
    float dataCalo;
    uint8_t incline;
}dataUpdate;

void updateData(dataUpdate data);
void updateTime(uint32_t time);
void updateDistance(float dis);
void updateCalo(float cal);
void updateIncline(uint8_t incl);
void updateSpeed(float speed);

void mainScreen();

#endif /*_SCREEN_H_*/