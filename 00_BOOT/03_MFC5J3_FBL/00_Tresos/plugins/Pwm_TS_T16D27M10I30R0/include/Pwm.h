#if !defined( PWM_H )
#define PWM_H

#include <Pwm_17_GtmCcu6.h> 

#define PWM_AR_RELEASE_MAJOR_VERSION PWM_17_GTMCCU6_AR_RELEASE_MAJOR_VERSION
#define PWM_AR_RELEASE_MINOR_VERSION PWM_17_GTMCCU6_AR_RELEASE_MINOR_VERSION

/* Global Macro Definitions */
#define PWM_NOTIFICATION_SUPPORTED  PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
#define PWM_RISING_EDGE		PWM_17_GTMCCU6_RISING_EDGE
#define PWM_FALLING_EDGE	PWM_17_GTMCCU6_FALLING_EDGE
#define PWM_BOTH_EDGES		PWM_17_GTMCCU6_BOTH_EDGES
#endif /* PWM_NOTIFICATION_SUPPORTED */
#define PWM_HIGH		PWM_17_GTMCCU6_HIGH
#define PWM_LOW			PWM_17_GTMCCU6_LOW

/* Global Type Definitions */
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
typedef Pwm_17_GtmCcu6_EdgeNotificationType  Pwm_EdgeNotificationType;
#endif /* PWM_NOTIFICATION_SUPPORTED */
typedef Pwm_17_GtmCcu6_OutputStateType       Pwm_OutputStateType; 
typedef Pwm_17_GtmCcu6_PeriodType            Pwm_PeriodType;       
typedef Pwm_17_GtmCcu6_ChannelType           Pwm_ChannelType;  
typedef Pwm_17_GtmCcu6_ChannelClassType      Pwm_ChannelClassType; 
typedef Pwm_17_GtmCcu6_ConfigType            Pwm_ConfigType;


/* Global Function Declarations */
#define Pwm_Init                     Pwm_17_GtmCcu6_Init
#define Pwm_DeInit                   Pwm_17_GtmCcu6_DeInit
#define Pwm_SetDutyCycle             Pwm_17_GtmCcu6_SetDutyCycle
#define Pwm_SetPeriodAndDuty         Pwm_17_GtmCcu6_SetPeriodAndDuty
#define Pwm_SetOutputToIdle          Pwm_17_GtmCcu6_SetOutputToIdle
#define Pwm_GetOutputState           Pwm_17_GtmCcu6_GetOutputState
#define Pwm_DisableNotification      Pwm_17_GtmCcu6_DisableNotification
#define Pwm_EnableNotification       Pwm_17_GtmCcu6_EnableNotification
#define Pwm_GetVersionInfo           Pwm_17_GtmCcu6_GetVersionInfo

#endif  
