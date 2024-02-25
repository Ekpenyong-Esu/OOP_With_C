//
// Created by mahon on 2/3/2024.
//

#ifndef ANDSTATE_DECOMPBUILDER_H
#define ANDSTATE_DECOMPBUILDER_H

typedef struct DecompBuilder DecompBuilder;
struct DecompBuilder
{

};

void DecompBuilder_Init(DecompBuilder* const me);
void DecompBuilder_Cleanup(DecompBuilder* const me);
DecompBuilder * DecompBuilder_Create(void);
void DecompBuilder_Destroy(DecompBuilder* const me);

#endif //ANDSTATE_DECOMPBUILDER_H
