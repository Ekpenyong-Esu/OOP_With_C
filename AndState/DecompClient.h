//
// Created by mahon on 2/3/2024.
//

#ifndef ANDSTATE_DECOMPCLIENT_H
#define ANDSTATE_DECOMPCLIENT_H

typedef struct DecompClient DecompClient;
struct DecompClient
{

};

void DecompClient_Init(DecompClient* const me);
void DecompClient_Cleanup(DecompClient* const me);
DecompClient * DecompClient_Create(void);
void DecompClient_Destroy(DecompClient* const me);


#endif //ANDSTATE_DECOMPCLIENT_H
