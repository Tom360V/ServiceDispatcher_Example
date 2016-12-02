/*
 * main.c
 *
 *  Created on: Nov 30, 2016
 *      Author: nxa03718
 */

#include <stdio.h>
#include <stdint.h>
#include "ServiceDispatcherQueue.h"
#include "ServiceDispatcherRouter.h"

#include "msgRGBClient.h"
#include "msgRGBServer.h"

int8_t mySendToDevice(SDHandle_t sdqHandle, uint8_t *topic, uint8_t topicLength, uint8_t *data, uint8_t dataLength)
{
    printf("Report:: t:%s", topic);
    SDQ_AddToRecvQueue(topic, topicLength, data, dataLength, NULL);
    return 0;
}

void Delivered(SDHandle_t handle, int8_t succeed)
{
    printf("Report:: h:%d, t:%d", handle, succeed);
}

//int main (int argc, char *argv[])
int main (void)
{
    // Init Service Dispatcher
    SDR_Init();
    SDQ_Init(&mySendToDevice);

    //Let services subscribe
    msgRGBServer_Init(&SDR_SubscribeService);
    msgRGBClient_Init(&SDR_SubscribeService);

    msgRGBClient_GetColor();
    while(1)
    {
        SDQ_Thread();
    }
    return 0;
}
