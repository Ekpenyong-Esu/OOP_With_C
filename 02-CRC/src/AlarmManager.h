//
// Created by mahon on 2/8/2024.
//

#ifndef INC_02_CRC_ALARMMANAGER_H
#define INC_02_CRC_ALARMMANAGER_H





typedef struct AlarmManager AlarmManager;
struct AlarmManager
{

};

void AlarmManager_Init(AlarmManager* const me);
void AlarmManager_Cleanup(AlarmManager* const me);
AlarmManager* AlarmManager_Create(void);
void AlarmManager_Destroy(AlarmManager* const me);

void AlarmManager_addAlarm(AlarmManager* const me, ErrorCodeType errCode);

#endif //INC_02_CRC_ALARMMANAGER_H
