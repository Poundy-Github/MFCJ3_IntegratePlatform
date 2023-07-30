/**EB_Automotive_C_Source_File */
[!CODE!]
[!AUTOSPACING!]
#if (!defined CANTRCV_1_T03_SYMBOLICNAMES_PBCFG_H)
#define CANTRCV_1_T03_SYMBOLICNAMES_PBCFG_H


/*==================[includes]===============================================*/

/*==================[macros]=================================================*/

/*------------------[symbolic name values]----------------------------------*/

/* generated macros for CanTrcvChannelIds */
[!SELECT "as:modconf('CanTrcv')[(CommonPublishedInformation/VendorId = 1) and (CommonPublishedInformation/VendorApiInfix = 'T03')]"!]
[!LOOP "CanTrcvConfigSet/*[1]/CanTrcvChannel/*"!][!//

#if (defined CanTrcvConf_1_T03_CanTrcvChannel_[!"name(.)"!])      /* To prevent double declaration */
#error CanTrcvConf_1_T03_CanTrcvChannel_[!"name(.)"!] already defined!
#endif /* #if (defined CanTrcvConf_1_T03_CanTrcvChannel_[!"name(.)"!]) */

/** \brief SymbolicName value for  [!"name(.)"!] */
#define CanTrcvConf_1_T03_CanTrcvChannel_[!"name(.)"!]   [!"CanTrcvChannelId"!]U

#if (!defined CANTRCV_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)

#if (defined [!"name(.)"!])      /* To prevent double declaration */
#error [!"name(.)"!] already defined!
#endif /* #if (defined [!"name(.)"!]) */

/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define [!"name(.)"!]   [!"CanTrcvChannelId"!]U

#if (defined CanTrcv_1_T03_[!"@name"!])      /* To prevent double declaration */
#error CanTrcv_1_T03_[!"@name"!] already defined!
#endif /* #if (defined CanTrcv_1_T03_[!"@name"!]) */

/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define CanTrcv_1_T03_[!"@name"!] [!"CanTrcvChannelId"!]U

#endif /* !defined CANTRCV_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!][!//
[!ENDSELECT!]
/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* if !defined( CANTRCV_1_T03_SYMBOLICNAMES_PBCFG_H ) */
/*==================[end of file]============================================*/
[!ENDCODE!]
