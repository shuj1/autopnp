/*
 * Copyright (c) 2011-2014, fortiss GmbH.
 * Licensed under the Apache License, Version 2.0.
 *
 * Use, modification and distribution are subject to the terms specified
 * in the accompanying license file LICENSE.txt located at the root directory
 * of this software distribution. A copy is available at
 * http://chromosome.fortiss.org/.
 *
 * This file is part of CHROMOSOME.
 *
 * $Id: loginClientProcessResponseFunction.c 7837 2014-03-14 12:33:13Z wiesmueller $
 */

/**
 * \file
 *         Source file for function loginClientProcessResponse in component loginClient.
 *
 * \author
 *         This file has been generated by the CHROMOSOME Modeling Tool (XMT)
 *         (fortiss GmbH).
 */

/******************************************************************************/
/***   Includes                                                             ***/
/******************************************************************************/
#include "xme/core/login/include-gen/loginClientProcessResponseFunction.h"

#include "xme/core/login/include-gen/loginClientProcessResponseFunctionWrapper.h"
#include "xme/core/login/include-gen/loginClientComponent.h"
#include "xme/core/login/include-gen/loginClientComponentWrapper.h"
#include "xme/core/login/include-gen/loginClientManifest.h"

#include "xme/core/logUtils.h"

#include "xme/hal/include/mem.h"

// PROTECTED REGION ID(XME_CORE_LOGIN_LOGINCLIENTPROCESSRESPONSEFUNCTION_C_INCLUDES) ENABLED START
#include "xme/core/login/include/loginClient.h"	
// PROTECTED REGION END

/******************************************************************************/
/***   Definitions                                                          ***/
/******************************************************************************/

// PROTECTED REGION ID(XME_CORE_LOGIN_LOGINCLIENTPROCESSRESPONSEFUNCTION_C_DEFINITIONS) ENABLED START

// PROTECTED REGION END

/******************************************************************************/
/***   Variables                                                            ***/
/******************************************************************************/
/**
 * \brief  Variable holding the value of the optional output port 'outLoginAcknowledgment'.
 *
 * \details If necessary initialize this in the init function.
 *          The value of this variable will be written to the port at the end of
 *          the step function.
 */
static xme_core_topic_login_loginAcknowledgment_t
portOutLoginAcknowledgmentData;

// PROTECTED REGION ID(XME_CORE_LOGIN_LOGINCLIENTPROCESSRESPONSEFUNCTION_C_VARIABLES) ENABLED START

// PROTECTED REGION END

/******************************************************************************/
/***   Prototypes                                                           ***/
/******************************************************************************/

// PROTECTED REGION ID(XME_CORE_LOGIN_LOGINCLIENTPROCESSRESPONSEFUNCTION_C_PROTOTYPES) ENABLED START

// PROTECTED REGION END

/******************************************************************************/
/***   Implementation                                                       ***/
/******************************************************************************/
xme_status_t
xme_core_login_loginClientProcessResponseFunction_init
(
    xme_core_login_loginClientComponent_config_t* const componentConfig
)
{
    // PROTECTED REGION ID(XME_CORE_LOGIN_LOGINCLIENTPROCESSRESPONSEFUNCTION_INITIALIZE_C) ENABLED START

    // Nothing to do

    XME_UNUSED_PARAMETER(componentConfig);

    return XME_STATUS_SUCCESS;

    // PROTECTED REGION END
}

void
xme_core_login_loginClientProcessResponseFunction_step
(
    xme_core_login_loginClientComponent_config_t* const componentConfig
)
{
    xme_status_t status[1];
    
    xme_core_topic_login_loginResponse_t portInResponseData; // Required port.
    xme_core_topic_login_loginAcknowledgment_t* portOutLoginAcknowledgmentDataPtr = &portOutLoginAcknowledgmentData;
    
    (void)xme_hal_mem_set(&portInResponseData, 0u, sizeof(xme_core_topic_login_loginResponse_t));
    
    status[0] = xme_core_login_loginClientComponentWrapper_readPortInResponse(&portInResponseData);
    
    {
        // PROTECTED REGION ID(XME_CORE_LOGIN_LOGINCLIENTPROCESSRESPONSEFUNCTION_STEP_C) ENABLED START

        XME_UNUSED_PARAMETER(componentConfig);

        portOutLoginAcknowledgmentDataPtr = NULL;
        if (XME_STATUS_SUCCESS==status[0])
        {
            //process only if successful login
            if (XME_CORE_TOPIC_LOGIN_LOGINRESPONSE_LOGINSTATUS_LOGIN_SUCCESS==portInResponseData.loginStatus)
            {
                //and the Current Node is invalid
                //we delay the check of guid because it is with loginclient
                //and we dont want to read that value again in init to avoid any races.
                if (XME_CORE_NODE_INVALID_NODE_ID == xme_core_node_getCurrentNodeId())
                {
                    xme_status_t loginResponseStatus;

                    loginResponseStatus = xme_core_login_loginClient_processLoginResponse(&portInResponseData);

                    if (XME_STATUS_SUCCESS != loginResponseStatus)
                    {
                        XME_LOG
                        (
                            XME_LOG_NOTE,
                            "[LoginClient] Cannot process login response. Return status: %d \n",
                            loginResponseStatus
                        );
                    }
                    else
                    {
                        XME_LOG
                        (
                            XME_LOG_NOTE,
                            "[LoginClient] LOGIN SUCCESS Login Manager allocated NodeId as %d \n",
                            portInResponseData.nodeId
                        );
                        portOutLoginAcknowledgmentDataPtr = &portOutLoginAcknowledgmentData;
                        portOutLoginAcknowledgmentData.nodeId = portInResponseData.nodeId;
                    }

                }
            }
        }
        // PROTECTED REGION END
    }
    
    status[0] = xme_core_login_loginClientComponentWrapper_writePortOutLoginAcknowledgment(portOutLoginAcknowledgmentDataPtr);
    
    {
        // PROTECTED REGION ID(XME_CORE_LOGIN_LOGINCLIENTPROCESSRESPONSEFUNCTION_STEP_2_C) ENABLED START

        if (XME_STATUS_SUCCESS != status[0])
            XME_LOG(XME_LOG_DEBUG, "[loginClientProcessResponseFunction] Failed to write the Acknowledgement to port with status %d\n", status[0]);
        // PROTECTED REGION END
    }
}

void
xme_core_login_loginClientProcessResponseFunction_fini
(
    xme_core_login_loginClientComponent_config_t* const componentConfig
)
{
    // PROTECTED REGION ID(XME_CORE_LOGIN_LOGINCLIENTPROCESSRESPONSEFUNCTION_TERMINATE_C) ENABLED START

    // Nothing to do

    XME_UNUSED_PARAMETER(componentConfig);

    // PROTECTED REGION END
}

// PROTECTED REGION ID(XME_CORE_LOGIN_LOGINCLIENTPROCESSRESPONSEFUNCTION_IMPLEMENTATION_C) ENABLED START

// PROTECTED REGION END