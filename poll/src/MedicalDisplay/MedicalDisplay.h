//
// Created by mahon on 1/13/2024.
//

#ifndef POLL_MEDICALDISPLAY_H
#define POLL_MEDICALDISPLAY_H


typedef struct MedicalDisplay MedicalDisplay;
struct MedicalDisplay
{

};

void MedicalDisplay_Init(MedicalDisplay* const me);
void MedicalDisplay_Cleanup(MedicalDisplay* const me);

MedicalDisplay* MedicalDisplay_Create(void);
void MedicalDisplay_Destroy(MedicalDisplay* me);

void MedicalDisplay_showO2Concentration(MedicalDisplay* const me, int data);
void MedicalDisplay_showGasFlow(MedicalDisplay* const me, int data);
void MedicalDisplay_showGasFlowStatus(MedicalDisplay* const me, int state);
void MedicalDisplay_showCircuitPressure(MedicalDisplay* const me, int data);



#endif //POLL_MEDICALDISPLAY_H
