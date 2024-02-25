//
// Created by mahon on 2/3/2024.
//

#ifndef OWNSHIPATTITUDE_ALARMMANAGER_H
#define OWNSHIPATTITUDE_ALARMMANAGER_H

typedef struct AlarmManager AlarmManager;
struct AlarmManager
{

};

void AlarmManager_Init(AlarmManager* const me);
void AlarmManager_Cleanup(AlarmManager* const me);
AlarmManager* AlarmManager_Create(void);
void AlarmManager_Destroy(AlarmManager* const me);

#endif //OWNSHIPATTITUDE_ALARMMANAGER_H
