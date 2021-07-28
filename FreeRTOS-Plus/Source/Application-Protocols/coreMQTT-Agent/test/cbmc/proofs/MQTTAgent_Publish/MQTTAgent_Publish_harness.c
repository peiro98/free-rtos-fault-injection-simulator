/*
 * coreMQTT Agent v1.0.1
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* MQTT agent include. */
#include "core_mqtt_agent.h"

#include "mqtt_agent_cbmc_state.h"

void harness()
{
    MQTTAgentContext_t * pMqttAgentContext;
    MQTTPublishInfo_t * pPublishInfo;
    MQTTAgentCommandInfo_t * pCommandInfo;
    MQTTStatus_t mqttStatus;

    pMqttAgentContext = allocateMqttAgentContext( NULL );
    __CPROVER_assume( isValidMqttAgentContext( pMqttAgentContext ) );

    /* MQTTAgentCommandInfo and MQTTPublishInfo_t are only added to Queue
     * in MQTTAgent_Publish and non deterministic values for the
     * members of MQTTAgentCommandInfo_t and MQTTPublishInfo_t type will be
     * sufficient for this proof.*/
    pPublishInfo = malloc( sizeof( MQTTPublishInfo_t ) );
    pCommandInfo = malloc( sizeof( MQTTAgentCommandInfo_t ) );

    mqttStatus = MQTTAgent_Publish( pMqttAgentContext,
                                    pPublishInfo,
                                    pCommandInfo );

    __CPROVER_assert( isAgentSendCommandFunctionStatus( mqttStatus ), "The return value is a MQTTStatus_t." );
}