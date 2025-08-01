//
// Created by mahon on 1/25/2024.
//

#ifndef REALTIME_STATICPRIORITY_MOTORDATA_H
#define REALTIME_STATICPRIORITY_MOTORDATA_H

#define RETRIGGER (2)
#define WAIT_FOREVER (0)
#define TRUE (1)
#define FALSE (0)
static int commandedPosition;
static int measuredPosition;

int getCmdPos(void);
int getMeasPos(void);
void setCmdPos(int x);
void setMeasPos(int x);

#endif //REALTIME_STATICPRIORITY_MOTORDATA_H
