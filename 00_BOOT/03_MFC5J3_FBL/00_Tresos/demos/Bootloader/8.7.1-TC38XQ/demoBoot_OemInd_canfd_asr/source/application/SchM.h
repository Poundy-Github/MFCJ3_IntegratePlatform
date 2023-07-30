#if (!defined SCHM_H)
#define SCHM_H

#include <Std_Types.h>

#define SCHM_VENDOR_ID 0x01U
#define SCHM_MODULE_ID 130U
#define SCHM_AR_MAJOR_VERSION 1U
#define SCHM_AR_MINOR_VERSION 1U
#define SCHM_AR_PATCH_VERSION 0U
#define SCHM_SW_MAJOR_VERSION 3U
#define SCHM_SW_MINOR_VERSION 0U
#define SCHM_SW_PATCH_VERSION 0U

#define SCHM_INIT_ID     0x00U
#define SCHM_DEINIT_ID      0x01U
#define SCHM_GETVERSIONINFO_ID      0x02U
#define SCHM_ENTER_CAN_ID     0x03
#define SCHM_ENTER_DLT_ID     0x03
#define SCHM_ENTER_DEVAUTH_ID     0x03
#define SCHM_ENTER_DOIP_ID     0x03
#define SCHM_ENTER_FR_ID     0x03
#define SCHM_ENTER_LINIF_ID     0x03
#define SCHM_ENTER_LIN_ID     0x03
#define SCHM_ENTER_LINTRCV_ID     0x03
#define SCHM_ENTER_SPI_ID     0x03
#define SCHM_ENTER_STBM_ID     0x03
#define SCHM_ENTER_EEP_ID     0x03
#define SCHM_ENTER_FLS_ID     0x03
#define SCHM_ENTER_PORT_ID     0x03
#define SCHM_ENTER_DIO_ID     0x03
#define SCHM_ENTER_PWM_ID     0x03
#define SCHM_ENTER_ICU_ID     0x03
#define SCHM_ENTER_ADC_ID     0x03
#define SCHM_ENTER_GPT_ID     0x03
#define SCHM_ENTER_MCU_ID     0x03
#define SCHM_ENTER_WDG_ID     0x03
#define SCHM_ENTER_RAMTST_ID     0x03
#define SCHM_ENTER_WDGIF_ID     0x03
#define SCHM_ENTER_EA_ID     0x03
#define SCHM_ENTER_CANIF_ID     0x03
#define SCHM_ENTER_CANTSYN_ID     0x03
#define SCHM_ENTER_ETH_ID     0x03
#define SCHM_ENTER_ETHIF_ID     0x03
#define SCHM_ENTER_ETHSM_ID     0x03
#define SCHM_ENTER_ETHTSYN_ID     0x03
#define SCHM_ENTER_XCP_ID     0x03
#define SCHM_ENTER_FRIF_ID     0x03
#define SCHM_ENTER_FRTSYN_ID     0x03
#define SCHM_ENTER_CRC_ID     0x03
#define SCHM_ENTER_CSM_ID     0x03
#define SCHM_ENTER_OS_ID     0x03
#define SCHM_ENTER_BSWM_ID     0x03
#define SCHM_ENTER_COMM_ID     0x03
#define SCHM_ENTER_ECUM_ID     0x03
#define SCHM_ENTER_DET_ID     0x03
#define SCHM_ENTER_FIM_ID     0x03
#define SCHM_ENTER_CNM_ID     0x03
#define SCHM_ENTER_CANNM_ID     0x03
#define SCHM_ENTER_J1939NM_ID     0x03
#define SCHM_ENTER_CANSM_ID     0x03
#define SCHM_ENTER_FRNM_ID     0x03
#define SCHM_ENTER_FRSM_ID     0x03
#define SCHM_ENTER_COM_ID     0x03
#define SCHM_ENTER_PDUR_ID     0x03
#define SCHM_ENTER_CANTRCV_ID     0x03
#define SCHM_ENTER_FRTRCV_ID     0x03
#define SCHM_ENTER_CANTP_ID     0x03
#define SCHM_ENTER_FRTP_ID     0x03
#define SCHM_ENTER_DCM_ID     0x03
#define SCHM_ENTER_DEM_ID     0x03
#define SCHM_ENTER_FEE_ID     0x03
#define SCHM_ENTER_NVM_ID     0x03
#define SCHM_ENTER_MEMIF_ID     0x03
#define SCHM_ENTER_WDGM_ID     0x03
#define SCHM_ENTER_IPDUM_ID     0x03
#define SCHM_ENTER_NM_ID     0x03
#define SCHM_ENTER_CDD_CIC310_MLI_ID     0x03
#define SCHM_ENTER_EEPIF_ID     0x03
#define SCHM_ENTER_FLSIF_ID     0x03
#define SCHM_ENTER_RTE_ID     0x03
#define SCHM_ENTER_TCPIP_ID     0x03
#define SCHM_ENTER_WDG_DIOEXT_ID     0x03
#define SCHM_ENTER_LINSM_ID     0x03
#define SCHM_ENTER_SOAD_ID     0x03
#define SCHM_ENTER_SOMEIPTP_ID     0x03
#define SCHM_ENTER_UDPNM_ID     0x03
#define SCHM_ENTER_UDSC_ID     0x03
#define SCHM_EXIT_CAN_ID     0x04
#define SCHM_EXIT_DLT_ID     0x04
#define SCHM_EXIT_DEVAUTH_ID     0x04
#define SCHM_EXIT_DOIP_ID     0x04
#define SCHM_EXIT_FR_ID     0x04
#define SCHM_EXIT_LINIF_ID     0x04
#define SCHM_EXIT_LIN_ID     0x04
#define SCHM_EXIT_LINTRCV_ID     0x04
#define SCHM_EXIT_SPI_ID     0x04
#define SCHM_EXIT_STBM_ID     0x04
#define SCHM_EXIT_EEP_ID     0x04
#define SCHM_EXIT_FLS_ID     0x04
#define SCHM_EXIT_PORT_ID     0x04
#define SCHM_EXIT_DIO_ID     0x04
#define SCHM_EXIT_PWM_ID     0x04
#define SCHM_EXIT_ICU_ID     0x04
#define SCHM_EXIT_ADC_ID     0x04
#define SCHM_EXIT_GPT_ID     0x04
#define SCHM_EXIT_MCU_ID     0x04
#define SCHM_EXIT_WDG_ID     0x04
#define SCHM_EXIT_RAMTST_ID     0x04
#define SCHM_EXIT_WDGIF_ID     0x04
#define SCHM_EXIT_EA_ID     0x04
#define SCHM_EXIT_CANIF_ID     0x04
#define SCHM_EXIT_CANTSYN_ID     0x04
#define SCHM_EXIT_ETH_ID     0x04
#define SCHM_EXIT_ETHIF_ID     0x04
#define SCHM_EXIT_ETHSM_ID     0x04
#define SCHM_EXIT_ETHTSYN_ID     0x04
#define SCHM_EXIT_XCP_ID     0x04
#define SCHM_EXIT_FRIF_ID     0x04
#define SCHM_EXIT_FRTSYN_ID     0x04
#define SCHM_EXIT_CRC_ID     0x04
#define SCHM_EXIT_CSM_ID     0x04
#define SCHM_EXIT_OS_ID     0x04
#define SCHM_EXIT_BSWM_ID     0x04
#define SCHM_EXIT_COMM_ID     0x04
#define SCHM_EXIT_ECUM_ID     0x04
#define SCHM_EXIT_DET_ID     0x04
#define SCHM_EXIT_FIM_ID     0x04
#define SCHM_EXIT_CNM_ID     0x04
#define SCHM_EXIT_CANNM_ID     0x04
#define SCHM_EXIT_J1939NM_ID     0x04
#define SCHM_EXIT_CANSM_ID     0x04
#define SCHM_EXIT_FRNM_ID     0x04
#define SCHM_EXIT_FRSM_ID     0x04
#define SCHM_EXIT_COM_ID     0x04
#define SCHM_EXIT_PDUR_ID     0x04
#define SCHM_EXIT_CANTRCV_ID     0x04
#define SCHM_EXIT_FRTRCV_ID     0x04
#define SCHM_EXIT_CANTP_ID     0x04
#define SCHM_EXIT_FRTP_ID     0x04
#define SCHM_EXIT_DCM_ID     0x04
#define SCHM_EXIT_DEM_ID     0x04
#define SCHM_EXIT_FEE_ID     0x04
#define SCHM_EXIT_NVM_ID     0x04
#define SCHM_EXIT_MEMIF_ID     0x04
#define SCHM_EXIT_WDGM_ID     0x04
#define SCHM_EXIT_IPDUM_ID     0x04
#define SCHM_EXIT_NM_ID     0x04
#define SCHM_EXIT_CDD_CIC310_MLI_ID     0x04
#define SCHM_EXIT_EEPIF_ID     0x04
#define SCHM_EXIT_FLSIF_ID     0x04
#define SCHM_EXIT_RTE_ID     0x04
#define SCHM_EXIT_TCPIP_ID     0x04
#define SCHM_EXIT_WDG_DIOEXT_ID     0x04
#define SCHM_EXIT_LINSM_ID     0x04
#define SCHM_EXIT_SOAD_ID     0x04
#define SCHM_EXIT_SOMEIPTP_ID     0x04
#define SCHM_EXIT_UDPNM_ID     0x04
#define SCHM_EXIT_UDSC_ID     0x04
#define SCHM_ACTMAINFUNCTION_CAN_ID     0x05
#define SCHM_ACTMAINFUNCTION_DLT_ID     0x05
#define SCHM_ACTMAINFUNCTION_DEVAUTH_ID     0x05
#define SCHM_ACTMAINFUNCTION_DOIP_ID     0x05
#define SCHM_ACTMAINFUNCTION_FR_ID     0x05
#define SCHM_ACTMAINFUNCTION_LINIF_ID     0x05
#define SCHM_ACTMAINFUNCTION_LIN_ID     0x05
#define SCHM_ACTMAINFUNCTION_LINTRCV_ID     0x05
#define SCHM_ACTMAINFUNCTION_SPI_ID     0x05
#define SCHM_ACTMAINFUNCTION_STBM_ID     0x05
#define SCHM_ACTMAINFUNCTION_EEP_ID     0x05
#define SCHM_ACTMAINFUNCTION_FLS_ID     0x05
#define SCHM_ACTMAINFUNCTION_PORT_ID     0x05
#define SCHM_ACTMAINFUNCTION_DIO_ID     0x05
#define SCHM_ACTMAINFUNCTION_PWM_ID     0x05
#define SCHM_ACTMAINFUNCTION_ICU_ID     0x05
#define SCHM_ACTMAINFUNCTION_ADC_ID     0x05
#define SCHM_ACTMAINFUNCTION_GPT_ID     0x05
#define SCHM_ACTMAINFUNCTION_MCU_ID     0x05
#define SCHM_ACTMAINFUNCTION_WDG_ID     0x05
#define SCHM_ACTMAINFUNCTION_RAMTST_ID     0x05
#define SCHM_ACTMAINFUNCTION_WDGIF_ID     0x05
#define SCHM_ACTMAINFUNCTION_EA_ID     0x05
#define SCHM_ACTMAINFUNCTION_CANIF_ID     0x05
#define SCHM_ACTMAINFUNCTION_CANTSYN_ID     0x05
#define SCHM_ACTMAINFUNCTION_XCP_ID     0x05
#define SCHM_ACTMAINFUNCTION_FRIF_ID     0x05
#define SCHM_ACTMAINFUNCTION_FRTSYN_ID     0x05
#define SCHM_ACTMAINFUNCTION_CRC_ID     0x05
#define SCHM_ACTMAINFUNCTION_CSM_ID     0x05
#define SCHM_ACTMAINFUNCTION_OS_ID     0x05
#define SCHM_ACTMAINFUNCTION_BSWM_ID     0x05
#define SCHM_ACTMAINFUNCTION_COMM_ID     0x05
#define SCHM_ACTMAINFUNCTION_ECUM_ID     0x05
#define SCHM_ACTMAINFUNCTION_DET_ID     0x05
#define SCHM_ACTMAINFUNCTION_FIM_ID     0x05
#define SCHM_ACTMAINFUNCTION_CNM_ID     0x05
#define SCHM_ACTMAINFUNCTION_CANNM_ID     0x05
#define SCHM_ACTMAINFUNCTION_CANSM_ID     0x05
#define SCHM_ACTMAINFUNCTION_ETH_ID     0x05
#define SCHM_ACTMAINFUNCTION_ETHIF_ID     0x05
#define SCHM_ACTMAINFUNCTION_ETHSM_ID     0x05
#define SCHM_ACTMAINFUNCTION_ETHTSYN_ID     0x05
#define SCHM_ACTMAINFUNCTION_FRNM_ID     0x05
#define SCHM_ACTMAINFUNCTION_FRSM_ID     0x05
#define SCHM_ACTMAINFUNCTION_COM_ID     0x05
#define SCHM_ACTMAINFUNCTION_PDUR_ID     0x05
#define SCHM_ACTMAINFUNCTION_CANTRCV_ID     0x05
#define SCHM_ACTMAINFUNCTION_FRTRCV_ID     0x05
#define SCHM_ACTMAINFUNCTION_CANTP_ID     0x05
#define SCHM_ACTMAINFUNCTION_FRTP_ID     0x05
#define SCHM_ACTMAINFUNCTION_DCM_ID     0x05
#define SCHM_ACTMAINFUNCTION_DEM_ID     0x05
#define SCHM_ACTMAINFUNCTION_FEE_ID     0x05
#define SCHM_ACTMAINFUNCTION_NVM_ID     0x05
#define SCHM_ACTMAINFUNCTION_MEMIF_ID     0x05
#define SCHM_ACTMAINFUNCTION_WDGM_ID     0x05
#define SCHM_ACTMAINFUNCTION_IPDUM_ID     0x05
#define SCHM_ACTMAINFUNCTION_NM_ID     0x05
#define SCHM_ACTMAINFUNCTION_CDD_CIC310_MLI_ID     0x05
#define SCHM_ACTMAINFUNCTION_EEPIF_ID     0x05
#define SCHM_ACTMAINFUNCTION_FLSIF_ID     0x05
#define SCHM_ACTMAINFUNCTION_RTE_ID     0x05
#define SCHM_ACTMAINFUNCTION_TCPIP_ID     0x05
#define SCHM_ACTMAINFUNCTION_WDG_DIOEXT_ID     0x05
#define SCHM_ACTMAINFUNCTION_LINSM_ID     0x05
#define SCHM_ACTMAINFUNCTION_SOAD_ID     0x05
#define SCHM_ACTMAINFUNCTION_UDPNM_ID     0x05
#define SCHM_CANCELMAINFUNCTION_CAN_ID     0x06
#define SCHM_CANCELMAINFUNCTION_DLT_ID     0x06
#define SCHM_CANCELMAINFUNCTION_DEVAUTH_ID     0x06
#define SCHM_CANCELMAINFUNCTION_DOIP_ID     0x06
#define SCHM_CANCELMAINFUNCTION_FR_ID     0x06
#define SCHM_CANCELMAINFUNCTION_LINIF_ID     0x06
#define SCHM_CANCELMAINFUNCTION_LIN_ID     0x06
#define SCHM_CANCELMAINFUNCTION_LINTRCV_ID     0x06
#define SCHM_CANCELMAINFUNCTION_SPI_ID     0x06
#define SCHM_CANCELMAINFUNCTION_STBM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_EEP_ID     0x06
#define SCHM_CANCELMAINFUNCTION_FLS_ID     0x06
#define SCHM_CANCELMAINFUNCTION_PORT_ID     0x06
#define SCHM_CANCELMAINFUNCTION_DIO_ID     0x06
#define SCHM_CANCELMAINFUNCTION_PWM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_ICU_ID     0x06
#define SCHM_CANCELMAINFUNCTION_ADC_ID     0x06
#define SCHM_CANCELMAINFUNCTION_GPT_ID     0x06
#define SCHM_CANCELMAINFUNCTION_MCU_ID     0x06
#define SCHM_CANCELMAINFUNCTION_WDG_ID     0x06
#define SCHM_CANCELMAINFUNCTION_RAMTST_ID     0x06
#define SCHM_CANCELMAINFUNCTION_WDGIF_ID     0x06
#define SCHM_CANCELMAINFUNCTION_EA_ID     0x06
#define SCHM_CANCELMAINFUNCTION_CANIF_ID     0x06
#define SCHM_CANCELMAINFUNCTION_CANTSYN_ID     0x06
#define SCHM_CANCELMAINFUNCTION_XCP_ID     0x06
#define SCHM_CANCELMAINFUNCTION_FRIF_ID     0x06
#define SCHM_CANCELMAINFUNCTION_FRTSYN_ID     0x06
#define SCHM_CANCELMAINFUNCTION_CRC_ID     0x06
#define SCHM_CANCELMAINFUNCTION_CSM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_OS_ID     0x06
#define SCHM_CANCELMAINFUNCTION_BSWM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_COMM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_ECUM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_DET_ID     0x06
#define SCHM_CANCELMAINFUNCTION_FIM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_CNM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_CANNM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_CANSM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_ETH_ID     0x06
#define SCHM_CANCELMAINFUNCTION_ETHIF_ID     0x06
#define SCHM_CANCELMAINFUNCTION_ETHSM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_ETHTSYN_ID     0x06
#define SCHM_CANCELMAINFUNCTION_FRNM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_FRSM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_COM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_PDUR_ID     0x06
#define SCHM_CANCELMAINFUNCTION_CANTRCV_ID     0x06
#define SCHM_CANCELMAINFUNCTION_FRTRCV_ID     0x06
#define SCHM_CANCELMAINFUNCTION_CANTP_ID     0x06
#define SCHM_CANCELMAINFUNCTION_FRTP_ID     0x06
#define SCHM_CANCELMAINFUNCTION_DCM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_DEM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_FEE_ID     0x06
#define SCHM_CANCELMAINFUNCTION_NVM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_MEMIF_ID     0x06
#define SCHM_CANCELMAINFUNCTION_WDGM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_IPDUM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_NM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_CDD_CIC310_MLI_ID     0x06
#define SCHM_CANCELMAINFUNCTION_EEPIF_ID     0x06
#define SCHM_CANCELMAINFUNCTION_FLSIF_ID     0x06
#define SCHM_CANCELMAINFUNCTION_RTE_ID     0x06
#define SCHM_CANCELMAINFUNCTION_TCPIP_ID     0x06
#define SCHM_CANCELMAINFUNCTION_WDG_DIOEXT_ID     0x06
#define SCHM_CANCELMAINFUNCTION_LINSM_ID     0x06
#define SCHM_CANCELMAINFUNCTION_SOAD_ID     0x06
#define SCHM_CANCELMAINFUNCTION_UDPNM_ID     0x06
#define     SCHM_INIT_STUB_INIT { 0, NULL_PTR }
#define     SCHM_DEINIT_STUB_INIT { 0, NULL_PTR }
#define     SCHM_GETVERSIONINFO_STUB_INIT { 0, NULL_PTR, NULL_PTR }
#define SCHM_ENTER_CAN_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_DLT_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_DEVAUTH_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_DOIP_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_FR_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_LINIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_LIN_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_LINTRCV_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_SPI_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_STBM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_EEP_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_FLS_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_PORT_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_DIO_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_PWM_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_ICU_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_ADC_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_GPT_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_MCU_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_WDG_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_RAMTST_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_WDGIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_EA_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_CANIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_CANTSYN_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_XCP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_FRIF_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_FRTSYN_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_CRC_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_CSM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_OS_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_BSWM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_COMM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_ECUM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_DET_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_FIM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_CNM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_CANNM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_J1939NM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_CANSM_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_ETH_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_ETHIF_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_ETHSM_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_ETHTSYN_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_FRNM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_FRSM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_COM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_PDUR_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_CANTRCV_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_FRTRCV_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_CANTP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_FRTP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_DCM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_DEM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_FEE_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ENTER_NVM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_MEMIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_WDGM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_IPDUM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_NM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_CDD_CIC310_MLI_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_EEPIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_FLSIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_RTE_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_TCPIP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_WDG_DIOEXT_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_LINSM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_SOAD_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_SOMEIPTP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_SD_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_UDPNM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ENTER_UDSC_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_CAN_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_DLT_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_DEVAUTH_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_DOIP_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_FR_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_LINIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_LIN_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_LINTRCV_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_SPI_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_STBM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_EEP_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_FLS_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_PORT_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_DIO_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_PWM_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_ICU_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_ADC_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_GPT_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_MCU_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_WDG_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_RAMTST_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_WDGIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_EA_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_CANIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_CANTSYN_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_XCP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_FRIF_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_FRTSYN_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_CRC_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_CSM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_OS_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_BSWM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_COMM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_ECUM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_DET_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_FIM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_CNM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_CANNM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_J1939NM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_CANSM_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_ETH_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_ETHIF_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_ETHSM_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_ETHTSYN_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_FRNM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_FRSM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_COM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_PDUR_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_CANTRCV_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_FRTRCV_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_CANTP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_FRTP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_DCM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_DEM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_FEE_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_EXIT_NVM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_MEMIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_WDGM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_IPDUM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_NM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_CDD_CIC310_MLI_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_EEPIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_FLSIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_RTE_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_TCPIP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_WDG_DIOEXT_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_LINSM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_SOAD_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_SOMEIPTP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_SD_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_UDPNM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_EXIT_UDSC_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_CAN_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_DLT_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_DEVAUTH_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_DOIP_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_FR_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_LINIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_LIN_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_LINTRCV_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_SPI_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_STBM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_EEP_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_FLS_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_PORT_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_DIO_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_PWM_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_ICU_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_ADC_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_GPT_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_MCU_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_WDG_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_RAMTST_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_WDGIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_EA_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_CANIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_CANTSYN_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_XCP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_FRIF_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_FRTSYN_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_CRC_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_CSM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_OS_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_BSWM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_COMM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_ECUM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_DET_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_FIM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_CNM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_CANNM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_CANSM_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_ETH_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_ETHIF_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_ETHSM_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_ETHTSYN_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_FRNM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_FRSM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_COM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_PDUR_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_CANTRCV_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_FRTRCV_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_CANTP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_FRTP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_DCM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_DEM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_FEE_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_ACTMAINFUNCTION_NVM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_MEMIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_WDGM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_IPDUM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_NM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_CDD_CIC310_MLI_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_EEPIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_FLSIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_RTE_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_TCPIP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_WDG_DIOEXT_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_LINSM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_SOAD_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_ACTMAINFUNCTION_UDPNM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_CAN_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_DLT_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_DEVAUTH_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_DOIP_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_FR_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_LINIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_LIN_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_LINTRCV_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_SPI_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_STBM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_EEP_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_FLS_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_PORT_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_DIO_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_PWM_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_ICU_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_ADC_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_GPT_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_MCU_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_WDG_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_RAMTST_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_WDGIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_EA_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_CANIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_CANTSYN_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_XCP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_FRIF_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_FRTSYN_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_CRC_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_CSM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_OS_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_BSWM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_COMM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_ECUM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_DET_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_FIM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_CNM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_CANNM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_CANSM_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_ETH_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_ETHIF_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_ETHSM_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_ETHTSYN_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_FRNM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_FRSM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_COM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_PDUR_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_CANTRCV_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_FRTRCV_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_CANTP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_FRTP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_DCM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_DEM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_FEE_STUB_INIT { 0, NULL_PTR, 0, 0 }
#define SCHM_CANCELMAINFUNCTION_NVM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_MEMIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_WDGM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_IPDUM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_NM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_CDD_CIC310_MLI_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_EEPIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_FLSIF_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_RTE_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_TCPIP_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_WDG_DIOEXT_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_LINSM_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_SOAD_STUB_INIT { 0, NULL_PTR, 0 }
#define SCHM_CANCELMAINFUNCTION_UDPNM_STUB_INIT { 0, NULL_PTR, 0 }

typedef uint8 SchM_ReturnType;

typedef void(*SchM_Init_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Init_CalloutType Callout;
} SchM_Init_StubType;

typedef void(*SchM_Deinit_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Deinit_CalloutType Callout;
} SchM_Deinit_StubType;

typedef void(*SchM_GetVersionInfo_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_GetVersionInfo_CalloutType Callout;
  P2VAR(Std_VersionInfoType, AUTOMATIC, SCHM_APPL_DATA) versioninfo;
} SchM_GetVersionInfo_StubType;

typedef void(*SchM_Enter_Can_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Can_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Can_StubType;

typedef void(*SchM_Enter_Dlt_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Dlt_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Dlt_StubType;

typedef void(*SchM_Enter_DevAuth_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_DevAuth_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_DevAuth_StubType;

typedef void(*SchM_Enter_DoIP_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_DoIP_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_DoIP_StubType;

typedef void(*SchM_Enter_Fr_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Fr_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Fr_StubType;

typedef void(*SchM_Enter_LinIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_LinIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_LinIf_StubType;

typedef void(*SchM_Enter_Lin_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Lin_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Lin_StubType;

typedef void(*SchM_Enter_LinTrcv_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_LinIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_LinTrcv_StubType;

typedef void(*SchM_Enter_Spi_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Spi_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Spi_StubType;

typedef void(*SchM_Enter_StbM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_StbM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_StbM_StubType;

typedef void(*SchM_Enter_Eep_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Eep_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Eep_StubType;

typedef void(*SchM_Enter_Fls_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Fls_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Fls_StubType;

typedef void(*SchM_Enter_Port_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Port_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Port_StubType;

typedef void(*SchM_Enter_Dio_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Dio_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Dio_StubType;

typedef void(*SchM_Enter_Pwm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Pwm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Pwm_StubType;

typedef void(*SchM_Enter_Icu_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Icu_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Icu_StubType;

typedef void(*SchM_Enter_Adc_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Adc_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Adc_StubType;

typedef void(*SchM_Enter_Gpt_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Gpt_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Gpt_StubType;

typedef void(*SchM_Enter_Mcu_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Mcu_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Mcu_StubType;

typedef void(*SchM_Enter_Wdg_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Wdg_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Wdg_StubType;

typedef void(*SchM_Enter_RamTst_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_RamTst_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_RamTst_StubType;

typedef void(*SchM_Enter_WdgIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_WdgIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_WdgIf_StubType;

typedef void(*SchM_Enter_Ea_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Ea_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Ea_StubType;

typedef void(*SchM_Enter_CanIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_CanIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_CanIf_StubType;

typedef void(*SchM_Enter_CanTSyn_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_CanTSyn_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_CanTSyn_StubType;

typedef void(*SchM_Enter_Xcp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Xcp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Xcp_StubType;

typedef void(*SchM_Enter_FrIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_FrIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_FrIf_StubType;

typedef void(*SchM_Enter_FrTSyn_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_FrTSyn_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_FrTSyn_StubType;

typedef void(*SchM_Enter_Crc_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Crc_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Crc_StubType;

typedef void(*SchM_Enter_Csm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Csm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Csm_StubType;

typedef void(*SchM_Enter_Os_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Os_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Os_StubType;

typedef void(*SchM_Enter_BswM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_BswM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_BswM_StubType;

typedef void(*SchM_Enter_ComM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_ComM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_ComM_StubType;

typedef void(*SchM_Enter_EcuM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_EcuM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_EcuM_StubType;

typedef void(*SchM_Enter_Det_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Det_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Det_StubType;

typedef void(*SchM_Enter_Fim_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Fim_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Fim_StubType;

typedef void(*SchM_Enter_CNm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_CNm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_CNm_StubType;

typedef void(*SchM_Enter_CanNm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_CanNm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_CanNm_StubType;

typedef void(*SchM_Enter_J1939Nm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_J1939Nm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_J1939Nm_StubType;

typedef void(*SchM_Enter_CanSM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_CanSM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_CanSM_StubType;

typedef void(*SchM_Enter_Eth_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Eth_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Eth_StubType;

typedef void(*SchM_Enter_EthIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_EthIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_EthIf_StubType;

typedef void(*SchM_Enter_EthSM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_EthSM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_EthSM_StubType;

typedef void(*SchM_Enter_EthTSyn_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_EthTSyn_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_EthTSyn_StubType;

typedef void(*SchM_Enter_FrNm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_FrNm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_FrNm_StubType;

typedef void(*SchM_Enter_FrSM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_FrSM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_FrSM_StubType;

typedef void(*SchM_Enter_Com_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Com_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Com_StubType;

typedef void(*SchM_Enter_PduR_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_PduR_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_PduR_StubType;

typedef void(*SchM_Enter_CanTrcv_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_CanTrcv_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_CanTrcv_StubType;

typedef void(*SchM_Enter_FrTrcv_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_FrTrcv_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_FrTrcv_StubType;

typedef void(*SchM_Enter_CanTp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_CanTp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_CanTp_StubType;

typedef void(*SchM_Enter_FrTp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_FrTp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_FrTp_StubType;

typedef void(*SchM_Enter_Dcm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Dcm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Dcm_StubType;

typedef void(*SchM_Enter_Dem_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Dem_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Dem_StubType;

typedef void(*SchM_Enter_Fee_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Fee_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Fee_StubType;

typedef void(*SchM_Enter_NvM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_NvM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_NvM_StubType;

typedef void(*SchM_Enter_MemIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_MemIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_MemIf_StubType;

typedef void(*SchM_Enter_WdgM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_WdgM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_WdgM_StubType;

typedef void(*SchM_Enter_IpduM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_IpduM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_IpduM_StubType;

typedef void(*SchM_Enter_Nm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Nm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Nm_StubType;

typedef void(*SchM_Enter_CDD_CIC310_MLI_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_CDD_CIC310_MLI_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_CDD_CIC310_MLI_StubType;

typedef void(*SchM_Enter_EepIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_EepIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_EepIf_StubType;

typedef void(*SchM_Enter_FlsIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_FlsIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_FlsIf_StubType;

typedef void(*SchM_Enter_Rte_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Rte_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Rte_StubType;

typedef void(*SchM_Enter_TcpIp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_TcpIp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_TcpIp_StubType;

typedef void(*SchM_Enter_Wdg_DioExt_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Wdg_DioExt_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Wdg_DioExt_StubType;

typedef void(*SchM_Enter_LinSM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_LinSM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_LinSM_StubType;

typedef void(*SchM_Enter_SoAd_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_SoAd_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_SoAd_StubType;

typedef void(*SchM_Enter_SomeIpTp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_SomeIpTp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_SomeIpTp_StubType;

typedef void(*SchM_Enter_Sd_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_Sd_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_Sd_StubType;

typedef void(*SchM_Enter_UdpNm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_UdpNm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_UdpNm_StubType;

typedef void(*SchM_Enter_UdsC_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Enter_UdsC_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Enter_UdsC_StubType;

typedef void(*SchM_Exit_Can_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Can_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Can_StubType;

typedef void(*SchM_Exit_Dlt_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Dlt_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Dlt_StubType;

typedef void(*SchM_Exit_DevAuth_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_DevAuth_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_DevAuth_StubType;

typedef void(*SchM_Exit_DoIP_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_DoIP_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_DoIP_StubType;

typedef void(*SchM_Exit_Fr_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Fr_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Fr_StubType;

typedef void(*SchM_Exit_LinIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_LinIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_LinIf_StubType;

typedef void(*SchM_Exit_Lin_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Lin_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Lin_StubType;

typedef void(*SchM_Exit_LinTrcv_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Lin_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_LinTrcv_StubType;

typedef void(*SchM_Exit_Spi_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Spi_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Spi_StubType;

typedef void(*SchM_Exit_StbM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_StbM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_StbM_StubType;

typedef void(*SchM_Exit_Eep_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Eep_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Eep_StubType;

typedef void(*SchM_Exit_Fls_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Fls_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Fls_StubType;

typedef void(*SchM_Exit_Port_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Port_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Port_StubType;

typedef void(*SchM_Exit_Dio_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Dio_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Dio_StubType;

typedef void(*SchM_Exit_Pwm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Pwm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Pwm_StubType;

typedef void(*SchM_Exit_Icu_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Icu_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Icu_StubType;

typedef void(*SchM_Exit_Adc_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Adc_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Adc_StubType;

typedef void(*SchM_Exit_Gpt_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Gpt_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Gpt_StubType;

typedef void(*SchM_Exit_Mcu_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Mcu_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Mcu_StubType;

typedef void(*SchM_Exit_Wdg_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Wdg_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Wdg_StubType;

typedef void(*SchM_Exit_RamTst_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_RamTst_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_RamTst_StubType;

typedef void(*SchM_Exit_WdgIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_WdgIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_WdgIf_StubType;

typedef void(*SchM_Exit_Ea_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Ea_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Ea_StubType;

typedef void(*SchM_Exit_CanIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_CanIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_CanIf_StubType;

typedef void(*SchM_Exit_CanTSyn_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_CanTSyn_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_CanTSyn_StubType;

typedef void(*SchM_Exit_Xcp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Xcp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Xcp_StubType;

typedef void(*SchM_Exit_FrIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_FrIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_FrIf_StubType;

typedef void(*SchM_Exit_FrTSyn_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_FrTSyn_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_FrTSyn_StubType;

typedef void(*SchM_Exit_Crc_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Crc_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Crc_StubType;

typedef void(*SchM_Exit_Csm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Csm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Csm_StubType;

typedef void(*SchM_Exit_Os_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Os_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Os_StubType;

typedef void(*SchM_Exit_BswM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_BswM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_BswM_StubType;

typedef void(*SchM_Exit_ComM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_ComM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_ComM_StubType;

typedef void(*SchM_Exit_EcuM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_EcuM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_EcuM_StubType;

typedef void(*SchM_Exit_Det_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Det_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Det_StubType;

typedef void(*SchM_Exit_Fim_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Fim_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Fim_StubType;

typedef void(*SchM_Exit_CNm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_CNm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_CNm_StubType;

typedef void(*SchM_Exit_CanNm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_CanNm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_CanNm_StubType;

typedef void(*SchM_Exit_J1939Nm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_J1939Nm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_J1939Nm_StubType;

typedef void(*SchM_Exit_CanSM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_CanSM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_CanSM_StubType;

typedef void(*SchM_Exit_Eth_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Eth_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Eth_StubType;

typedef void(*SchM_Exit_EthIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_EthIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_EthIf_StubType;

typedef void(*SchM_Exit_EthSM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_EthSM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_EthSM_StubType;

typedef void(*SchM_Exit_EthTSyn_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_EthTSyn_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_EthTSyn_StubType;

typedef void(*SchM_Exit_FrNm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_FrNm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_FrNm_StubType;

typedef void(*SchM_Exit_FrSM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_FrSM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_FrSM_StubType;

typedef void(*SchM_Exit_Com_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Com_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Com_StubType;

typedef void(*SchM_Exit_PduR_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_PduR_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_PduR_StubType;

typedef void(*SchM_Exit_CanTrcv_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_CanTrcv_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_CanTrcv_StubType;

typedef void(*SchM_Exit_FrTrcv_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_FrTrcv_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_FrTrcv_StubType;

typedef void(*SchM_Exit_CanTp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_CanTp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_CanTp_StubType;

typedef void(*SchM_Exit_FrTp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_FrTp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_FrTp_StubType;

typedef void(*SchM_Exit_Dcm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Dcm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Dcm_StubType;

typedef void(*SchM_Exit_Dem_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Dem_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Dem_StubType;

typedef void(*SchM_Exit_Fee_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Fee_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Fee_StubType;

typedef void(*SchM_Exit_NvM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_NvM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_NvM_StubType;

typedef void(*SchM_Exit_MemIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_MemIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_MemIf_StubType;

typedef void(*SchM_Exit_WdgM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_WdgM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_WdgM_StubType;

typedef void(*SchM_Exit_IpduM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_IpduM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_IpduM_StubType;

typedef void(*SchM_Exit_Nm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Nm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Nm_StubType;

typedef void(*SchM_Exit_CDD_CIC310_MLI_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_CDD_CIC310_MLI_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_CDD_CIC310_MLI_StubType;

typedef void(*SchM_Exit_EepIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_EepIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_EepIf_StubType;

typedef void(*SchM_Exit_FlsIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_FlsIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_FlsIf_StubType;

typedef void(*SchM_Exit_Rte_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Rte_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Rte_StubType;

typedef void(*SchM_Exit_TcpIp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_TcpIp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_TcpIp_StubType;

typedef void(*SchM_Exit_Wdg_DioExt_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Wdg_DioExt_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Wdg_DioExt_StubType;

typedef void(*SchM_Exit_LinSM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_LinSM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_LinSM_StubType;

typedef void(*SchM_Exit_SoAd_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_SoAd_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_SoAd_StubType;

typedef void(*SchM_Exit_SomeIpTp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_SomeIpTp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_SomeIpTp_StubType;

typedef void(*SchM_Exit_Sd_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_Sd_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_Sd_StubType;

typedef void(*SchM_Exit_UdpNm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_UdpNm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_UdpNm_StubType;

typedef void(*SchM_Exit_UdsC_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_Exit_UdsC_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ExclusiveArea;
} SchM_Exit_UdsC_StubType;

typedef void(*SchM_ActMainFunction_Can_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Can_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Can_StubType;

typedef void(*SchM_ActMainFunction_Dlt_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Dlt_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Dlt_StubType;

typedef void(*SchM_ActMainFunction_DevAuth_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_DevAuth_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_DevAuth_StubType;

typedef void(*SchM_ActMainFunction_DoIP_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_DoIP_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_DoIP_StubType;

typedef void(*SchM_ActMainFunction_Fr_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Fr_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Fr_StubType;

typedef void(*SchM_ActMainFunction_LinIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_LinIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_LinIf_StubType;

typedef void(*SchM_ActMainFunction_Lin_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Lin_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Lin_StubType;

typedef void(*SchM_ActMainFunction_LinTrcv_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_LinTrcv_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_LinTrcv_StubType;

typedef void(*SchM_ActMainFunction_Spi_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Spi_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Spi_StubType;

typedef void(*SchM_ActMainFunction_StbM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_StbM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_StbM_StubType;

typedef void(*SchM_ActMainFunction_Eep_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Eep_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Eep_StubType;

typedef void(*SchM_ActMainFunction_Fls_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Fls_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Fls_StubType;

typedef void(*SchM_ActMainFunction_Port_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Port_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Port_StubType;

typedef void(*SchM_ActMainFunction_Dio_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Dio_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Dio_StubType;

typedef void(*SchM_ActMainFunction_Pwm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Pwm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Pwm_StubType;

typedef void(*SchM_ActMainFunction_Icu_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Icu_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Icu_StubType;

typedef void(*SchM_ActMainFunction_Adc_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Adc_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Adc_StubType;

typedef void(*SchM_ActMainFunction_Gpt_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Gpt_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Gpt_StubType;

typedef void(*SchM_ActMainFunction_Mcu_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Mcu_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Mcu_StubType;

typedef void(*SchM_ActMainFunction_Wdg_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Wdg_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Wdg_StubType;

typedef void(*SchM_ActMainFunction_RamTst_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_RamTst_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_RamTst_StubType;

typedef void(*SchM_ActMainFunction_WdgIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_WdgIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_WdgIf_StubType;

typedef void(*SchM_ActMainFunction_Ea_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Ea_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Ea_StubType;

typedef void(*SchM_ActMainFunction_CanIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_CanIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_CanIf_StubType;

typedef void(*SchM_ActMainFunction_CanTSyn_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_CanTSyn_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_CanTSyn_StubType;

typedef void(*SchM_ActMainFunction_Xcp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Xcp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Xcp_StubType;

typedef void(*SchM_ActMainFunction_FrIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_FrIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_FrIf_StubType;

typedef void(*SchM_ActMainFunction_FrTSyn_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_FrTSyn_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_FrTSyn_StubType;

typedef void(*SchM_ActMainFunction_Crc_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Crc_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Crc_StubType;

typedef void(*SchM_ActMainFunction_Csm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Csm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Csm_StubType;

typedef void(*SchM_ActMainFunction_Os_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Os_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Os_StubType;

typedef void(*SchM_ActMainFunction_BswM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_BswM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_BswM_StubType;

typedef void(*SchM_ActMainFunction_ComM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_ComM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_ComM_StubType;

typedef void(*SchM_ActMainFunction_EcuM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_EcuM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_EcuM_StubType;

typedef void(*SchM_ActMainFunction_Det_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Det_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Det_StubType;

typedef void(*SchM_ActMainFunction_Fim_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Fim_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Fim_StubType;

typedef void(*SchM_ActMainFunction_CNm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_CNm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_CNm_StubType;

typedef void(*SchM_ActMainFunction_CanNm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_CanNm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_CanNm_StubType;

typedef void(*SchM_ActMainFunction_CanSM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_CanSM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_CanSM_StubType;

typedef void(*SchM_ActMainFunction_Eth_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Eth_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Eth_StubType;

typedef void(*SchM_ActMainFunction_EthIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_EthIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_EthIf_StubType;

typedef void(*SchM_ActMainFunction_EthSM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_EthSM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_EthSM_StubType;

typedef void(*SchM_ActMainFunction_EthTSyn_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_EthTSyn_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_EthTSyn_StubType;

typedef void(*SchM_ActMainFunction_FrNm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_FrNm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_FrNm_StubType;

typedef void(*SchM_ActMainFunction_FrSM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_FrSM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_FrSM_StubType;

typedef void(*SchM_ActMainFunction_Com_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Com_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Com_StubType;

typedef void(*SchM_ActMainFunction_PduR_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_PduR_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_PduR_StubType;

typedef void(*SchM_ActMainFunction_CanTrcv_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_CanTrcv_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_CanTrcv_StubType;

typedef void(*SchM_ActMainFunction_FrTrcv_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_FrTrcv_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_FrTrcv_StubType;

typedef void(*SchM_ActMainFunction_CanTp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_CanTp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_CanTp_StubType;

typedef void(*SchM_ActMainFunction_FrTp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_FrTp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_FrTp_StubType;

typedef void(*SchM_ActMainFunction_Dcm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Dcm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Dcm_StubType;

typedef void(*SchM_ActMainFunction_Dem_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Dem_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Dem_StubType;

typedef void(*SchM_ActMainFunction_Fee_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Fee_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Fee_StubType;

typedef void(*SchM_ActMainFunction_NvM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_NvM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_NvM_StubType;

typedef void(*SchM_ActMainFunction_MemIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_MemIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_MemIf_StubType;

typedef void(*SchM_ActMainFunction_WdgM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_WdgM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_WdgM_StubType;

typedef void(*SchM_ActMainFunction_IpduM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_IpduM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_IpduM_StubType;

typedef void(*SchM_ActMainFunction_Nm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Nm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Nm_StubType;

typedef void(*SchM_ActMainFunction_CDD_CIC310_MLI_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_CDD_CIC310_MLI_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_CDD_CIC310_MLI_StubType;

typedef void(*SchM_ActMainFunction_EepIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_EepIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_EepIf_StubType;

typedef void(*SchM_ActMainFunction_FlsIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_FlsIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_FlsIf_StubType;

typedef void(*SchM_ActMainFunction_Rte_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Rte_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Rte_StubType;

typedef void(*SchM_ActMainFunction_TcpIp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_TcpIp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_TcpIp_StubType;

typedef void(*SchM_ActMainFunction_Wdg_DioExt_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_Wdg_DioExt_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_Wdg_DioExt_StubType;

typedef void(*SchM_ActMainFunction_LinSM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_LinSM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_LinSM_StubType;

typedef void(*SchM_ActMainFunction_SoAd_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_SoAd_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_SoAd_StubType;

typedef void(*SchM_ActMainFunction_UdpNm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_ActMainFunction_UdpNm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_ActMainFunction_UdpNm_StubType;

typedef void(*SchM_CancelMainFunction_Can_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Can_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Can_StubType;

typedef void(*SchM_CancelMainFunction_Dlt_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Dlt_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Dlt_StubType;

typedef void(*SchM_CancelMainFunction_DevAuth_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_DevAuth_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_DevAuth_StubType;

typedef void(*SchM_CancelMainFunction_DoIP_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_DoIP_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_DoIP_StubType;

typedef void(*SchM_CancelMainFunction_Fr_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Fr_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Fr_StubType;

typedef void(*SchM_CancelMainFunction_LinIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_LinIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_LinIf_StubType;

typedef void(*SchM_CancelMainFunction_Lin_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Lin_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Lin_StubType;

typedef void(*SchM_CancelMainFunction_LinTrcv_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_LinTrcv_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_LinTrcv_StubType;

typedef void(*SchM_CancelMainFunction_Spi_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Spi_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Spi_StubType;

typedef void(*SchM_CancelMainFunction_StbM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_StbM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_StbM_StubType;

typedef void(*SchM_CancelMainFunction_Eep_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Eep_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Eep_StubType;

typedef void(*SchM_CancelMainFunction_Fls_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Fls_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Fls_StubType;

typedef void(*SchM_CancelMainFunction_Port_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Port_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Port_StubType;

typedef void(*SchM_CancelMainFunction_Dio_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Dio_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Dio_StubType;

typedef void(*SchM_CancelMainFunction_Pwm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Pwm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Pwm_StubType;

typedef void(*SchM_CancelMainFunction_Icu_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Icu_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Icu_StubType;

typedef void(*SchM_CancelMainFunction_Adc_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Adc_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Adc_StubType;

typedef void(*SchM_CancelMainFunction_Gpt_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Gpt_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Gpt_StubType;

typedef void(*SchM_CancelMainFunction_Mcu_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Mcu_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Mcu_StubType;

typedef void(*SchM_CancelMainFunction_Wdg_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Wdg_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Wdg_StubType;

typedef void(*SchM_CancelMainFunction_RamTst_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_RamTst_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_RamTst_StubType;

typedef void(*SchM_CancelMainFunction_WdgIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_WdgIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_WdgIf_StubType;

typedef void(*SchM_CancelMainFunction_Ea_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Ea_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Ea_StubType;

typedef void(*SchM_CancelMainFunction_CanIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_CanIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_CanIf_StubType;

typedef void(*SchM_CancelMainFunction_CanTSyn_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_CanTSyn_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_CanTSyn_StubType;

typedef void(*SchM_CancelMainFunction_Xcp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Xcp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Xcp_StubType;

typedef void(*SchM_CancelMainFunction_FrIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_FrIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_FrIf_StubType;

typedef void(*SchM_CancelMainFunction_FrTSyn_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_FrTSyn_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_FrTSyn_StubType;

typedef void(*SchM_CancelMainFunction_Crc_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Crc_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Crc_StubType;

typedef void(*SchM_CancelMainFunction_Csm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Csm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Csm_StubType;

typedef void(*SchM_CancelMainFunction_Os_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Os_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Os_StubType;

typedef void(*SchM_CancelMainFunction_BswM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_BswM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_BswM_StubType;

typedef void(*SchM_CancelMainFunction_ComM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_ComM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_ComM_StubType;

typedef void(*SchM_CancelMainFunction_EcuM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_EcuM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_EcuM_StubType;

typedef void(*SchM_CancelMainFunction_Det_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Det_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Det_StubType;

typedef void(*SchM_CancelMainFunction_Fim_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Fim_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Fim_StubType;

typedef void(*SchM_CancelMainFunction_CNm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_CNm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_CNm_StubType;

typedef void(*SchM_CancelMainFunction_CanNm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_CanNm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_CanNm_StubType;

typedef void(*SchM_CancelMainFunction_CanSM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_CanSM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_CanSM_StubType;

typedef void(*SchM_CancelMainFunction_Eth_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Eth_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Eth_StubType;

typedef void(*SchM_CancelMainFunction_EthIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_EthIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_EthIf_StubType;

typedef void(*SchM_CancelMainFunction_EthSM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_EthSM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_EthSM_StubType;

typedef void(*SchM_CancelMainFunction_EthTSyn_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_EthTSyn_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_EthTSyn_StubType;

typedef void(*SchM_CancelMainFunction_FrNm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_FrNm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_FrNm_StubType;

typedef void(*SchM_CancelMainFunction_FrSM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_FrSM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_FrSM_StubType;

typedef void(*SchM_CancelMainFunction_Com_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Com_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Com_StubType;

typedef void(*SchM_CancelMainFunction_PduR_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_PduR_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_PduR_StubType;

typedef void(*SchM_CancelMainFunction_CanTrcv_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_CanTrcv_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_CanTrcv_StubType;

typedef void(*SchM_CancelMainFunction_FrTrcv_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_FrTrcv_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_FrTrcv_StubType;

typedef void(*SchM_CancelMainFunction_CanTp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_CanTp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_CanTp_StubType;

typedef void(*SchM_CancelMainFunction_FrTp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_FrTp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_FrTp_StubType;

typedef void(*SchM_CancelMainFunction_Dcm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Dcm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Dcm_StubType;

typedef void(*SchM_CancelMainFunction_Dem_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Dem_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Dem_StubType;

typedef void(*SchM_CancelMainFunction_Fee_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Fee_CalloutType Callout;
  VAR(uint8, AUTOMATIC) Instance;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Fee_StubType;

typedef void(*SchM_CancelMainFunction_NvM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_NvM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_NvM_StubType;

typedef void(*SchM_CancelMainFunction_MemIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_MemIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_MemIf_StubType;

typedef void(*SchM_CancelMainFunction_WdgM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_WdgM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_WdgM_StubType;

typedef void(*SchM_CancelMainFunction_IpduM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_IpduM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_IpduM_StubType;

typedef void(*SchM_CancelMainFunction_Nm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Nm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Nm_StubType;

typedef void(*SchM_CancelMainFunction_CDD_CIC310_MLI_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_CDD_CIC310_MLI_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_CDD_CIC310_MLI_StubType;

typedef void(*SchM_CancelMainFunction_EepIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_EepIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_EepIf_StubType;

typedef void(*SchM_CancelMainFunction_FlsIf_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_FlsIf_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_FlsIf_StubType;

typedef void(*SchM_CancelMainFunction_Rte_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Rte_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Rte_StubType;

typedef void(*SchM_CancelMainFunction_TcpIp_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_TcpIp_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_TcpIp_StubType;

typedef void(*SchM_CancelMainFunction_Wdg_DioExt_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_Wdg_DioExt_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_Wdg_DioExt_StubType;

typedef void(*SchM_CancelMainFunction_LinSM_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_LinSM_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_LinSM_StubType;

typedef void(*SchM_CancelMainFunction_SoAd_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_SoAd_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_SoAd_StubType;

typedef void(*SchM_CancelMainFunction_UdpNm_CalloutType)
(
  void
);
typedef struct
{
  uint32 Count;
  SchM_CancelMainFunction_UdpNm_CalloutType Callout;
  VAR(uint8, AUTOMATIC) ActivationPoint;
} SchM_CancelMainFunction_UdpNm_StubType;


#define EBSTUBS_START_SEC_VAR_UNSPECIFIED
#include <EBStubs_MemMap.h>

extern VAR(SchM_Init_StubType, SCHM_VAR)
    SchM_Init_Stub;
extern VAR(SchM_Deinit_StubType, SCHM_VAR)
    SchM_Deinit_Stub;
extern VAR(SchM_GetVersionInfo_StubType, SCHM_VAR)
    SchM_GetVersionInfo_Stub;
extern VAR(SchM_Enter_Can_StubType, SCHM_VAR)
    SchM_Enter_Can_Stub;
extern VAR(SchM_Enter_Dlt_StubType, SCHM_VAR)
    SchM_Enter_Dlt_Stub;
extern VAR(SchM_Enter_DevAuth_StubType, SCHM_VAR)
    SchM_Enter_DevAuth_Stub;
extern VAR(SchM_Enter_DoIP_StubType, SCHM_VAR)
    SchM_Enter_DoIP_Stub;
extern VAR(SchM_Enter_Fr_StubType, SCHM_VAR)
    SchM_Enter_Fr_Stub;
extern VAR(SchM_Enter_LinIf_StubType, SCHM_VAR)
    SchM_Enter_LinIf_Stub;
extern VAR(SchM_Enter_Lin_StubType, SCHM_VAR)
    SchM_Enter_Lin_Stub;
extern VAR(SchM_Enter_LinTrcv_StubType, SCHM_VAR)
    SchM_Enter_LinTrcv_Stub;
extern VAR(SchM_Enter_Spi_StubType, SCHM_VAR)
    SchM_Enter_Spi_Stub;
extern VAR(SchM_Enter_StbM_StubType, SCHM_VAR)
    SchM_Enter_StbM_Stub;
extern VAR(SchM_Enter_Eep_StubType, SCHM_VAR)
    SchM_Enter_Eep_Stub;
extern VAR(SchM_Enter_Fls_StubType, SCHM_VAR)
    SchM_Enter_Fls_Stub;
extern VAR(SchM_Enter_Port_StubType, SCHM_VAR)
    SchM_Enter_Port_Stub;
extern VAR(SchM_Enter_Dio_StubType, SCHM_VAR)
    SchM_Enter_Dio_Stub;
extern VAR(SchM_Enter_Pwm_StubType, SCHM_VAR)
    SchM_Enter_Pwm_Stub;
extern VAR(SchM_Enter_Icu_StubType, SCHM_VAR)
    SchM_Enter_Icu_Stub;
extern VAR(SchM_Enter_Adc_StubType, SCHM_VAR)
    SchM_Enter_Adc_Stub;
extern VAR(SchM_Enter_Gpt_StubType, SCHM_VAR)
    SchM_Enter_Gpt_Stub;
extern VAR(SchM_Enter_Mcu_StubType, SCHM_VAR)
    SchM_Enter_Mcu_Stub;
extern VAR(SchM_Enter_Wdg_StubType, SCHM_VAR)
    SchM_Enter_Wdg_Stub;
extern VAR(SchM_Enter_RamTst_StubType, SCHM_VAR)
    SchM_Enter_RamTst_Stub;
extern VAR(SchM_Enter_WdgIf_StubType, SCHM_VAR)
    SchM_Enter_WdgIf_Stub;
extern VAR(SchM_Enter_Ea_StubType, SCHM_VAR)
    SchM_Enter_Ea_Stub;
extern VAR(SchM_Enter_CanIf_StubType, SCHM_VAR)
    SchM_Enter_CanIf_Stub;
extern VAR(SchM_Enter_CanTSyn_StubType, SCHM_VAR)
    SchM_Enter_CanTSyn_Stub;
extern VAR(SchM_Enter_Xcp_StubType, SCHM_VAR)
    SchM_Enter_Xcp_Stub;
extern VAR(SchM_Enter_FrIf_StubType, SCHM_VAR)
    SchM_Enter_FrIf_Stub;
extern VAR(SchM_Enter_FrTSyn_StubType, SCHM_VAR)
    SchM_Enter_FrTSyn_Stub;
extern VAR(SchM_Enter_Crc_StubType, SCHM_VAR)
    SchM_Enter_Crc_Stub;
extern VAR(SchM_Enter_Csm_StubType, SCHM_VAR)
    SchM_Enter_Csm_Stub;
extern VAR(SchM_Enter_Os_StubType, SCHM_VAR)
    SchM_Enter_Os_Stub;
extern VAR(SchM_Enter_BswM_StubType, SCHM_VAR)
    SchM_Enter_BswM_Stub;
extern VAR(SchM_Enter_ComM_StubType, SCHM_VAR)
    SchM_Enter_ComM_Stub;
extern VAR(SchM_Enter_EcuM_StubType, SCHM_VAR)
    SchM_Enter_EcuM_Stub;
extern VAR(SchM_Enter_Det_StubType, SCHM_VAR)
    SchM_Enter_Det_Stub;
extern VAR(SchM_Enter_Fim_StubType, SCHM_VAR)
    SchM_Enter_Fim_Stub;
extern VAR(SchM_Enter_CNm_StubType, SCHM_VAR)
    SchM_Enter_CNm_Stub;
extern VAR(SchM_Enter_CanNm_StubType, SCHM_VAR)
    SchM_Enter_CanNm_Stub;
extern VAR(SchM_Enter_J1939Nm_StubType, SCHM_VAR)
    SchM_Enter_J1939Nm_Stub;
extern VAR(SchM_Enter_CanSM_StubType, SCHM_VAR)
    SchM_Enter_CanSM_Stub;
extern VAR(SchM_Enter_Eth_StubType, SCHM_VAR)
    SchM_Enter_Eth_Stub;
extern VAR(SchM_Enter_EthIf_StubType, SCHM_VAR)
    SchM_Enter_EthIf_Stub;
extern VAR(SchM_Enter_EthSM_StubType, SCHM_VAR)
    SchM_Enter_EthSM_Stub;
extern VAR(SchM_Enter_EthTSyn_StubType, SCHM_VAR)
    SchM_Enter_EthTSyn_Stub;
extern VAR(SchM_Enter_FrNm_StubType, SCHM_VAR)
    SchM_Enter_FrNm_Stub;
extern VAR(SchM_Enter_FrSM_StubType, SCHM_VAR)
    SchM_Enter_FrSM_Stub;
extern VAR(SchM_Enter_Com_StubType, SCHM_VAR)
    SchM_Enter_Com_Stub;
extern VAR(SchM_Enter_PduR_StubType, SCHM_VAR)
    SchM_Enter_PduR_Stub;
extern VAR(SchM_Enter_CanTrcv_StubType, SCHM_VAR)
    SchM_Enter_CanTrcv_Stub;
extern VAR(SchM_Enter_FrTrcv_StubType, SCHM_VAR)
    SchM_Enter_FrTrcv_Stub;
extern VAR(SchM_Enter_CanTp_StubType, SCHM_VAR)
    SchM_Enter_CanTp_Stub;
extern VAR(SchM_Enter_FrTp_StubType, SCHM_VAR)
    SchM_Enter_FrTp_Stub;
extern VAR(SchM_Enter_Dcm_StubType, SCHM_VAR)
    SchM_Enter_Dcm_Stub;
extern VAR(SchM_Enter_Dem_StubType, SCHM_VAR)
    SchM_Enter_Dem_Stub;
extern VAR(SchM_Enter_Fee_StubType, SCHM_VAR)
    SchM_Enter_Fee_Stub;
extern VAR(SchM_Enter_NvM_StubType, SCHM_VAR)
    SchM_Enter_NvM_Stub;
extern VAR(SchM_Enter_MemIf_StubType, SCHM_VAR)
    SchM_Enter_MemIf_Stub;
extern VAR(SchM_Enter_WdgM_StubType, SCHM_VAR)
    SchM_Enter_WdgM_Stub;
extern VAR(SchM_Enter_IpduM_StubType, SCHM_VAR)
    SchM_Enter_IpduM_Stub;
extern VAR(SchM_Enter_Nm_StubType, SCHM_VAR)
    SchM_Enter_Nm_Stub;
extern VAR(SchM_Enter_CDD_CIC310_MLI_StubType, SCHM_VAR)
    SchM_Enter_CDD_CIC310_MLI_Stub;
extern VAR(SchM_Enter_EepIf_StubType, SCHM_VAR)
    SchM_Enter_EepIf_Stub;
extern VAR(SchM_Enter_FlsIf_StubType, SCHM_VAR)
    SchM_Enter_FlsIf_Stub;
extern VAR(SchM_Enter_Rte_StubType, SCHM_VAR)
    SchM_Enter_Rte_Stub;
extern VAR(SchM_Enter_TcpIp_StubType, SCHM_VAR)
    SchM_Enter_TcpIp_Stub;
extern VAR(SchM_Enter_Wdg_DioExt_StubType, SCHM_VAR)
    SchM_Enter_Wdg_DioExt_Stub;
extern VAR(SchM_Enter_LinSM_StubType, SCHM_VAR)
    SchM_Enter_LinSM_Stub;
extern VAR(SchM_Enter_SoAd_StubType, SCHM_VAR)
    SchM_Enter_SoAd_Stub;
extern VAR(SchM_Enter_SomeIpTp_StubType, SCHM_VAR)
    SchM_Enter_SomeIpTp_Stub;
extern VAR(SchM_Enter_UdsC_StubType, SCHM_VAR)
    SchM_Enter_UdsC_Stub;
extern VAR(SchM_Enter_Sd_StubType, SCHM_VAR)
    SchM_Enter_Sd_Stub;
extern VAR(SchM_Exit_Sd_StubType, SCHM_VAR)
    SchM_Exit_Sd_Stub;
extern VAR(SchM_Exit_Can_StubType, SCHM_VAR)
    SchM_Exit_Can_Stub;
extern VAR(SchM_Exit_Dlt_StubType, SCHM_VAR)
    SchM_Exit_Dlt_Stub;
extern VAR(SchM_Exit_DevAuth_StubType, SCHM_VAR)
    SchM_Exit_DevAuth_Stub;
extern VAR(SchM_Exit_DoIP_StubType, SCHM_VAR)
    SchM_Exit_DoIP_Stub;
extern VAR(SchM_Exit_Fr_StubType, SCHM_VAR)
    SchM_Exit_Fr_Stub;
extern VAR(SchM_Exit_LinIf_StubType, SCHM_VAR)
    SchM_Exit_LinIf_Stub;
extern VAR(SchM_Exit_Lin_StubType, SCHM_VAR)
    SchM_Exit_Lin_Stub;
extern VAR(SchM_Exit_LinTrcv_StubType, SCHM_VAR)
    SchM_Exit_LinTrcv_Stub;
extern VAR(SchM_Exit_Spi_StubType, SCHM_VAR)
    SchM_Exit_Spi_Stub;
extern VAR(SchM_Exit_StbM_StubType, SCHM_VAR)
    SchM_Exit_StbM_Stub;
extern VAR(SchM_Exit_Eep_StubType, SCHM_VAR)
    SchM_Exit_Eep_Stub;
extern VAR(SchM_Exit_Fls_StubType, SCHM_VAR)
    SchM_Exit_Fls_Stub;
extern VAR(SchM_Exit_Port_StubType, SCHM_VAR)
    SchM_Exit_Port_Stub;
extern VAR(SchM_Exit_Dio_StubType, SCHM_VAR)
    SchM_Exit_Dio_Stub;
extern VAR(SchM_Exit_Pwm_StubType, SCHM_VAR)
    SchM_Exit_Pwm_Stub;
extern VAR(SchM_Exit_Icu_StubType, SCHM_VAR)
    SchM_Exit_Icu_Stub;
extern VAR(SchM_Exit_Adc_StubType, SCHM_VAR)
    SchM_Exit_Adc_Stub;
extern VAR(SchM_Exit_Gpt_StubType, SCHM_VAR)
    SchM_Exit_Gpt_Stub;
extern VAR(SchM_Exit_Mcu_StubType, SCHM_VAR)
    SchM_Exit_Mcu_Stub;
extern VAR(SchM_Exit_Wdg_StubType, SCHM_VAR)
    SchM_Exit_Wdg_Stub;
extern VAR(SchM_Exit_RamTst_StubType, SCHM_VAR)
    SchM_Exit_RamTst_Stub;
extern VAR(SchM_Exit_WdgIf_StubType, SCHM_VAR)
    SchM_Exit_WdgIf_Stub;
extern VAR(SchM_Exit_Ea_StubType, SCHM_VAR)
    SchM_Exit_Ea_Stub;
extern VAR(SchM_Exit_CanIf_StubType, SCHM_VAR)
    SchM_Exit_CanIf_Stub;
extern VAR(SchM_Exit_CanTSyn_StubType, SCHM_VAR)
    SchM_Exit_CanTSyn_Stub;
extern VAR(SchM_Exit_Xcp_StubType, SCHM_VAR)
    SchM_Exit_Xcp_Stub;
extern VAR(SchM_Exit_FrIf_StubType, SCHM_VAR)
    SchM_Exit_FrIf_Stub;
extern VAR(SchM_Exit_FrTSyn_StubType, SCHM_VAR)
    SchM_Exit_FrTSyn_Stub;
extern VAR(SchM_Exit_Crc_StubType, SCHM_VAR)
    SchM_Exit_Crc_Stub;
extern VAR(SchM_Exit_Csm_StubType, SCHM_VAR)
    SchM_Exit_Csm_Stub;
extern VAR(SchM_Exit_Os_StubType, SCHM_VAR)
    SchM_Exit_Os_Stub;
extern VAR(SchM_Exit_BswM_StubType, SCHM_VAR)
    SchM_Exit_BswM_Stub;
extern VAR(SchM_Exit_ComM_StubType, SCHM_VAR)
    SchM_Exit_ComM_Stub;
extern VAR(SchM_Exit_EcuM_StubType, SCHM_VAR)
    SchM_Exit_EcuM_Stub;
extern VAR(SchM_Exit_Det_StubType, SCHM_VAR)
    SchM_Exit_Det_Stub;
extern VAR(SchM_Exit_Fim_StubType, SCHM_VAR)
    SchM_Exit_Fim_Stub;
extern VAR(SchM_Exit_CNm_StubType, SCHM_VAR)
    SchM_Exit_CNm_Stub;
extern VAR(SchM_Exit_CanNm_StubType, SCHM_VAR)
    SchM_Exit_CanNm_Stub;
extern VAR(SchM_Exit_J1939Nm_StubType, SCHM_VAR)
    SchM_Exit_J1939Nm_Stub;
extern VAR(SchM_Exit_CanSM_StubType, SCHM_VAR)
    SchM_Exit_CanSM_Stub;
extern VAR(SchM_Exit_Eth_StubType, SCHM_VAR)
    SchM_Exit_Eth_Stub;
extern VAR(SchM_Exit_EthIf_StubType, SCHM_VAR)
    SchM_Exit_EthIf_Stub;
extern VAR(SchM_Exit_EthSM_StubType, SCHM_VAR)
    SchM_Exit_EthSM_Stub;
extern VAR(SchM_Exit_EthTSyn_StubType, SCHM_VAR)
    SchM_Exit_EthTSyn_Stub;
extern VAR(SchM_Exit_FrNm_StubType, SCHM_VAR)
    SchM_Exit_FrNm_Stub;
extern VAR(SchM_Exit_FrSM_StubType, SCHM_VAR)
    SchM_Exit_FrSM_Stub;
extern VAR(SchM_Exit_Com_StubType, SCHM_VAR)
    SchM_Exit_Com_Stub;
extern VAR(SchM_Exit_PduR_StubType, SCHM_VAR)
    SchM_Exit_PduR_Stub;
extern VAR(SchM_Exit_CanTrcv_StubType, SCHM_VAR)
    SchM_Exit_CanTrcv_Stub;
extern VAR(SchM_Exit_FrTrcv_StubType, SCHM_VAR)
    SchM_Exit_FrTrcv_Stub;
extern VAR(SchM_Exit_CanTp_StubType, SCHM_VAR)
    SchM_Exit_CanTp_Stub;
extern VAR(SchM_Exit_FrTp_StubType, SCHM_VAR)
    SchM_Exit_FrTp_Stub;
extern VAR(SchM_Exit_Dcm_StubType, SCHM_VAR)
    SchM_Exit_Dcm_Stub;
extern VAR(SchM_Exit_Dem_StubType, SCHM_VAR)
    SchM_Exit_Dem_Stub;
extern VAR(SchM_Exit_Fee_StubType, SCHM_VAR)
    SchM_Exit_Fee_Stub;
extern VAR(SchM_Exit_NvM_StubType, SCHM_VAR)
    SchM_Exit_NvM_Stub;
extern VAR(SchM_Exit_MemIf_StubType, SCHM_VAR)
    SchM_Exit_MemIf_Stub;
extern VAR(SchM_Exit_WdgM_StubType, SCHM_VAR)
    SchM_Exit_WdgM_Stub;
extern VAR(SchM_Exit_IpduM_StubType, SCHM_VAR)
    SchM_Exit_IpduM_Stub;
extern VAR(SchM_Exit_Nm_StubType, SCHM_VAR)
    SchM_Exit_Nm_Stub;
extern VAR(SchM_Exit_CDD_CIC310_MLI_StubType, SCHM_VAR)
    SchM_Exit_CDD_CIC310_MLI_Stub;
extern VAR(SchM_Exit_EepIf_StubType, SCHM_VAR)
    SchM_Exit_EepIf_Stub;
extern VAR(SchM_Exit_FlsIf_StubType, SCHM_VAR)
    SchM_Exit_FlsIf_Stub;
extern VAR(SchM_Exit_Rte_StubType, SCHM_VAR)
    SchM_Exit_Rte_Stub;
extern VAR(SchM_Exit_TcpIp_StubType, SCHM_VAR)
    SchM_Exit_TcpIp_Stub;
extern VAR(SchM_Exit_Wdg_DioExt_StubType, SCHM_VAR)
    SchM_Exit_Wdg_DioExt_Stub;
extern VAR(SchM_Exit_LinSM_StubType, SCHM_VAR)
    SchM_Exit_LinSM_Stub;
extern VAR(SchM_Exit_SoAd_StubType, SCHM_VAR)
    SchM_Exit_SoAd_Stub;
extern VAR(SchM_Exit_SomeIpTp_StubType, SCHM_VAR)
    SchM_Exit_SomeIpTp_Stub;
extern VAR(SchM_Exit_UdsC_StubType, SCHM_VAR)
    SchM_Exit_UdsC_Stub;
extern VAR(SchM_ActMainFunction_Can_StubType, SCHM_VAR)
    SchM_ActMainFunction_Can_Stub;
extern VAR(SchM_ActMainFunction_Dlt_StubType, SCHM_VAR)
    SchM_ActMainFunction_Dlt_Stub;
extern VAR(SchM_ActMainFunction_DevAuth_StubType, SCHM_VAR)
    SchM_ActMainFunction_DevAuth_Stub;
extern VAR(SchM_ActMainFunction_DoIP_StubType, SCHM_VAR)
    SchM_ActMainFunction_DoIP_Stub;
extern VAR(SchM_ActMainFunction_Fr_StubType, SCHM_VAR)
    SchM_ActMainFunction_Fr_Stub;
extern VAR(SchM_ActMainFunction_LinIf_StubType, SCHM_VAR)
    SchM_ActMainFunction_LinIf_Stub;
extern VAR(SchM_ActMainFunction_Lin_StubType, SCHM_VAR)
    SchM_ActMainFunction_Lin_Stub;
extern VAR(SchM_ActMainFunction_LinTrcv_StubType, SCHM_VAR)
    SchM_ActMainFunction_LinTrcv_Stub;
extern VAR(SchM_ActMainFunction_Spi_StubType, SCHM_VAR)
    SchM_ActMainFunction_Spi_Stub;
extern VAR(SchM_ActMainFunction_StbM_StubType, SCHM_VAR)
    SchM_ActMainFunction_StbM_Stub;
extern VAR(SchM_ActMainFunction_Eep_StubType, SCHM_VAR)
    SchM_ActMainFunction_Eep_Stub;
extern VAR(SchM_ActMainFunction_Fls_StubType, SCHM_VAR)
    SchM_ActMainFunction_Fls_Stub;
extern VAR(SchM_ActMainFunction_Port_StubType, SCHM_VAR)
    SchM_ActMainFunction_Port_Stub;
extern VAR(SchM_ActMainFunction_Dio_StubType, SCHM_VAR)
    SchM_ActMainFunction_Dio_Stub;
extern VAR(SchM_ActMainFunction_Pwm_StubType, SCHM_VAR)
    SchM_ActMainFunction_Pwm_Stub;
extern VAR(SchM_ActMainFunction_Icu_StubType, SCHM_VAR)
    SchM_ActMainFunction_Icu_Stub;
extern VAR(SchM_ActMainFunction_Adc_StubType, SCHM_VAR)
    SchM_ActMainFunction_Adc_Stub;
extern VAR(SchM_ActMainFunction_Gpt_StubType, SCHM_VAR)
    SchM_ActMainFunction_Gpt_Stub;
extern VAR(SchM_ActMainFunction_Mcu_StubType, SCHM_VAR)
    SchM_ActMainFunction_Mcu_Stub;
extern VAR(SchM_ActMainFunction_Wdg_StubType, SCHM_VAR)
    SchM_ActMainFunction_Wdg_Stub;
extern VAR(SchM_ActMainFunction_RamTst_StubType, SCHM_VAR)
    SchM_ActMainFunction_RamTst_Stub;
extern VAR(SchM_ActMainFunction_WdgIf_StubType, SCHM_VAR)
    SchM_ActMainFunction_WdgIf_Stub;
extern VAR(SchM_ActMainFunction_Ea_StubType, SCHM_VAR)
    SchM_ActMainFunction_Ea_Stub;
extern VAR(SchM_ActMainFunction_CanIf_StubType, SCHM_VAR)
    SchM_ActMainFunction_CanIf_Stub;
extern VAR(SchM_ActMainFunction_CanTSyn_StubType, SCHM_VAR)
    SchM_ActMainFunction_CanTSyn_Stub;
extern VAR(SchM_ActMainFunction_Xcp_StubType, SCHM_VAR)
    SchM_ActMainFunction_Xcp_Stub;
extern VAR(SchM_ActMainFunction_FrIf_StubType, SCHM_VAR)
    SchM_ActMainFunction_FrIf_Stub;
extern VAR(SchM_ActMainFunction_FrTSyn_StubType, SCHM_VAR)
    SchM_ActMainFunction_FrTSyn_Stub;
extern VAR(SchM_ActMainFunction_Crc_StubType, SCHM_VAR)
    SchM_ActMainFunction_Crc_Stub;
extern VAR(SchM_ActMainFunction_Csm_StubType, SCHM_VAR)
    SchM_ActMainFunction_Csm_Stub;
extern VAR(SchM_ActMainFunction_Os_StubType, SCHM_VAR)
    SchM_ActMainFunction_Os_Stub;
extern VAR(SchM_ActMainFunction_BswM_StubType, SCHM_VAR)
    SchM_ActMainFunction_BswM_Stub;
extern VAR(SchM_ActMainFunction_ComM_StubType, SCHM_VAR)
    SchM_ActMainFunction_ComM_Stub;
extern VAR(SchM_ActMainFunction_EcuM_StubType, SCHM_VAR)
    SchM_ActMainFunction_EcuM_Stub;
extern VAR(SchM_ActMainFunction_Det_StubType, SCHM_VAR)
    SchM_ActMainFunction_Det_Stub;
extern VAR(SchM_ActMainFunction_Fim_StubType, SCHM_VAR)
    SchM_ActMainFunction_Fim_Stub;
extern VAR(SchM_ActMainFunction_CNm_StubType, SCHM_VAR)
    SchM_ActMainFunction_CNm_Stub;
extern VAR(SchM_ActMainFunction_CanNm_StubType, SCHM_VAR)
    SchM_ActMainFunction_CanNm_Stub;
extern VAR(SchM_ActMainFunction_CanSM_StubType, SCHM_VAR)
    SchM_ActMainFunction_CanSM_Stub;
extern VAR(SchM_ActMainFunction_Eth_StubType, SCHM_VAR)
    SchM_ActMainFunction_Eth_Stub;
extern VAR(SchM_ActMainFunction_EthIf_StubType, SCHM_VAR)
    SchM_ActMainFunction_EthIf_Stub;
extern VAR(SchM_ActMainFunction_EthSM_StubType, SCHM_VAR)
    SchM_ActMainFunction_EthSM_Stub;
extern VAR(SchM_ActMainFunction_EthTSyn_StubType, SCHM_VAR)
    SchM_ActMainFunction_EthTSyn_Stub;
extern VAR(SchM_ActMainFunction_FrNm_StubType, SCHM_VAR)
    SchM_ActMainFunction_FrNm_Stub;
extern VAR(SchM_ActMainFunction_FrSM_StubType, SCHM_VAR)
    SchM_ActMainFunction_FrSM_Stub;
extern VAR(SchM_ActMainFunction_Com_StubType, SCHM_VAR)
    SchM_ActMainFunction_Com_Stub;
extern VAR(SchM_ActMainFunction_PduR_StubType, SCHM_VAR)
    SchM_ActMainFunction_PduR_Stub;
extern VAR(SchM_ActMainFunction_CanTrcv_StubType, SCHM_VAR)
    SchM_ActMainFunction_CanTrcv_Stub;
extern VAR(SchM_ActMainFunction_FrTrcv_StubType, SCHM_VAR)
    SchM_ActMainFunction_FrTrcv_Stub;
extern VAR(SchM_ActMainFunction_CanTp_StubType, SCHM_VAR)
    SchM_ActMainFunction_CanTp_Stub;
extern VAR(SchM_ActMainFunction_FrTp_StubType, SCHM_VAR)
    SchM_ActMainFunction_FrTp_Stub;
extern VAR(SchM_ActMainFunction_Dcm_StubType, SCHM_VAR)
    SchM_ActMainFunction_Dcm_Stub;
extern VAR(SchM_ActMainFunction_Dem_StubType, SCHM_VAR)
    SchM_ActMainFunction_Dem_Stub;
extern VAR(SchM_ActMainFunction_Fee_StubType, SCHM_VAR)
    SchM_ActMainFunction_Fee_Stub;
extern VAR(SchM_ActMainFunction_NvM_StubType, SCHM_VAR)
    SchM_ActMainFunction_NvM_Stub;
extern VAR(SchM_ActMainFunction_MemIf_StubType, SCHM_VAR)
    SchM_ActMainFunction_MemIf_Stub;
extern VAR(SchM_ActMainFunction_WdgM_StubType, SCHM_VAR)
    SchM_ActMainFunction_WdgM_Stub;
extern VAR(SchM_ActMainFunction_IpduM_StubType, SCHM_VAR)
    SchM_ActMainFunction_IpduM_Stub;
extern VAR(SchM_ActMainFunction_Nm_StubType, SCHM_VAR)
    SchM_ActMainFunction_Nm_Stub;
extern VAR(SchM_ActMainFunction_CDD_CIC310_MLI_StubType, SCHM_VAR)
    SchM_ActMainFunction_CDD_CIC310_MLI_Stub;
extern VAR(SchM_ActMainFunction_EepIf_StubType, SCHM_VAR)
    SchM_ActMainFunction_EepIf_Stub;
extern VAR(SchM_ActMainFunction_FlsIf_StubType, SCHM_VAR)
    SchM_ActMainFunction_FlsIf_Stub;
extern VAR(SchM_ActMainFunction_Rte_StubType, SCHM_VAR)
    SchM_ActMainFunction_Rte_Stub;
extern VAR(SchM_ActMainFunction_TcpIp_StubType, SCHM_VAR)
    SchM_ActMainFunction_TcpIp_Stub;
extern VAR(SchM_ActMainFunction_Wdg_DioExt_StubType, SCHM_VAR)
    SchM_ActMainFunction_Wdg_DioExt_Stub;
extern VAR(SchM_ActMainFunction_LinSM_StubType, SCHM_VAR)
    SchM_ActMainFunction_LinSM_Stub;
extern VAR(SchM_ActMainFunction_SoAd_StubType, SCHM_VAR)
    SchM_ActMainFunction_SoAd_Stub;
extern VAR(SchM_CancelMainFunction_Can_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Can_Stub;
extern VAR(SchM_CancelMainFunction_Dlt_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Dlt_Stub;
extern VAR(SchM_CancelMainFunction_DevAuth_StubType, SCHM_VAR)
    SchM_CancelMainFunction_DevAuth_Stub;
extern VAR(SchM_CancelMainFunction_DoIP_StubType, SCHM_VAR)
    SchM_CancelMainFunction_DoIP_Stub;
extern VAR(SchM_CancelMainFunction_Fr_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Fr_Stub;
extern VAR(SchM_CancelMainFunction_LinIf_StubType, SCHM_VAR)
    SchM_CancelMainFunction_LinIf_Stub;
extern VAR(SchM_CancelMainFunction_Lin_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Lin_Stub;
extern VAR(SchM_CancelMainFunction_LinTrcv_StubType, SCHM_VAR)
    SchM_CancelMainFunction_LinTrcv_Stub;
extern VAR(SchM_CancelMainFunction_Spi_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Spi_Stub;
extern VAR(SchM_CancelMainFunction_StbM_StubType, SCHM_VAR)
    SchM_CancelMainFunction_StbM_Stub;
extern VAR(SchM_CancelMainFunction_Eep_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Eep_Stub;
extern VAR(SchM_CancelMainFunction_Fls_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Fls_Stub;
extern VAR(SchM_CancelMainFunction_Port_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Port_Stub;
extern VAR(SchM_CancelMainFunction_Dio_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Dio_Stub;
extern VAR(SchM_CancelMainFunction_Pwm_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Pwm_Stub;
extern VAR(SchM_CancelMainFunction_Icu_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Icu_Stub;
extern VAR(SchM_CancelMainFunction_Adc_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Adc_Stub;
extern VAR(SchM_CancelMainFunction_Gpt_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Gpt_Stub;
extern VAR(SchM_CancelMainFunction_Mcu_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Mcu_Stub;
extern VAR(SchM_CancelMainFunction_Wdg_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Wdg_Stub;
extern VAR(SchM_CancelMainFunction_RamTst_StubType, SCHM_VAR)
    SchM_CancelMainFunction_RamTst_Stub;
extern VAR(SchM_CancelMainFunction_WdgIf_StubType, SCHM_VAR)
    SchM_CancelMainFunction_WdgIf_Stub;
extern VAR(SchM_CancelMainFunction_Ea_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Ea_Stub;
extern VAR(SchM_CancelMainFunction_CanIf_StubType, SCHM_VAR)
    SchM_CancelMainFunction_CanIf_Stub;
extern VAR(SchM_CancelMainFunction_CanTSyn_StubType, SCHM_VAR)
    SchM_CancelMainFunction_CanTSyn_Stub;
extern VAR(SchM_CancelMainFunction_Xcp_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Xcp_Stub;
extern VAR(SchM_CancelMainFunction_FrIf_StubType, SCHM_VAR)
    SchM_CancelMainFunction_FrIf_Stub;
extern VAR(SchM_CancelMainFunction_FrTSyn_StubType, SCHM_VAR)
    SchM_CancelMainFunction_FrTSyn_Stub;
extern VAR(SchM_CancelMainFunction_Crc_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Crc_Stub;
extern VAR(SchM_CancelMainFunction_Csm_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Csm_Stub;
extern VAR(SchM_CancelMainFunction_Os_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Os_Stub;
extern VAR(SchM_CancelMainFunction_BswM_StubType, SCHM_VAR)
    SchM_CancelMainFunction_BswM_Stub;
extern VAR(SchM_CancelMainFunction_ComM_StubType, SCHM_VAR)
    SchM_CancelMainFunction_ComM_Stub;
extern VAR(SchM_CancelMainFunction_EcuM_StubType, SCHM_VAR)
    SchM_CancelMainFunction_EcuM_Stub;
extern VAR(SchM_CancelMainFunction_Det_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Det_Stub;
extern VAR(SchM_CancelMainFunction_Fim_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Fim_Stub;
extern VAR(SchM_CancelMainFunction_CNm_StubType, SCHM_VAR)
    SchM_CancelMainFunction_CNm_Stub;
extern VAR(SchM_CancelMainFunction_CanNm_StubType, SCHM_VAR)
    SchM_CancelMainFunction_CanNm_Stub;
extern VAR(SchM_CancelMainFunction_CanSM_StubType, SCHM_VAR)
    SchM_CancelMainFunction_CanSM_Stub;
extern VAR(SchM_CancelMainFunction_Eth_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Eth_Stub;
extern VAR(SchM_CancelMainFunction_EthIf_StubType, SCHM_VAR)
    SchM_CancelMainFunction_EthIf_Stub;
extern VAR(SchM_CancelMainFunction_EthSM_StubType, SCHM_VAR)
    SchM_CancelMainFunction_EthSM_Stub;
extern VAR(SchM_CancelMainFunction_EthTSyn_StubType, SCHM_VAR)
    SchM_CancelMainFunction_EthTSyn_Stub;
extern VAR(SchM_CancelMainFunction_FrNm_StubType, SCHM_VAR)
    SchM_CancelMainFunction_FrNm_Stub;
extern VAR(SchM_CancelMainFunction_FrSM_StubType, SCHM_VAR)
    SchM_CancelMainFunction_FrSM_Stub;
extern VAR(SchM_CancelMainFunction_Com_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Com_Stub;
extern VAR(SchM_CancelMainFunction_PduR_StubType, SCHM_VAR)
    SchM_CancelMainFunction_PduR_Stub;
extern VAR(SchM_CancelMainFunction_CanTrcv_StubType, SCHM_VAR)
    SchM_CancelMainFunction_CanTrcv_Stub;
extern VAR(SchM_CancelMainFunction_FrTrcv_StubType, SCHM_VAR)
    SchM_CancelMainFunction_FrTrcv_Stub;
extern VAR(SchM_CancelMainFunction_CanTp_StubType, SCHM_VAR)
    SchM_CancelMainFunction_CanTp_Stub;
extern VAR(SchM_CancelMainFunction_FrTp_StubType, SCHM_VAR)
    SchM_CancelMainFunction_FrTp_Stub;
extern VAR(SchM_CancelMainFunction_Dcm_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Dcm_Stub;
extern VAR(SchM_CancelMainFunction_Dem_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Dem_Stub;
extern VAR(SchM_CancelMainFunction_Fee_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Fee_Stub;
extern VAR(SchM_CancelMainFunction_NvM_StubType, SCHM_VAR)
    SchM_CancelMainFunction_NvM_Stub;
extern VAR(SchM_CancelMainFunction_MemIf_StubType, SCHM_VAR)
    SchM_CancelMainFunction_MemIf_Stub;
extern VAR(SchM_CancelMainFunction_WdgM_StubType, SCHM_VAR)
    SchM_CancelMainFunction_WdgM_Stub;
extern VAR(SchM_CancelMainFunction_IpduM_StubType, SCHM_VAR)
    SchM_CancelMainFunction_IpduM_Stub;
extern VAR(SchM_CancelMainFunction_Nm_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Nm_Stub;
extern VAR(SchM_CancelMainFunction_CDD_CIC310_MLI_StubType, SCHM_VAR)
    SchM_CancelMainFunction_CDD_CIC310_MLI_Stub;
extern VAR(SchM_CancelMainFunction_EepIf_StubType, SCHM_VAR)
    SchM_CancelMainFunction_EepIf_Stub;
extern VAR(SchM_CancelMainFunction_FlsIf_StubType, SCHM_VAR)
    SchM_CancelMainFunction_FlsIf_Stub;
extern VAR(SchM_CancelMainFunction_Rte_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Rte_Stub;
extern VAR(SchM_CancelMainFunction_TcpIp_StubType, SCHM_VAR)
    SchM_CancelMainFunction_TcpIp_Stub;
extern VAR(SchM_CancelMainFunction_Wdg_DioExt_StubType, SCHM_VAR)
    SchM_CancelMainFunction_Wdg_DioExt_Stub;
extern VAR(SchM_CancelMainFunction_LinSM_StubType, SCHM_VAR)
    SchM_CancelMainFunction_LinSM_Stub;
extern VAR(SchM_CancelMainFunction_SoAd_StubType, SCHM_VAR)
    SchM_CancelMainFunction_SoAd_Stub;
extern VAR(SchM_CancelMainFunction_UdpNm_StubType, SCHM_VAR)
    SchM_CancelMainFunction_UdpNm_Stub;

#define EBSTUBS_STOP_SEC_VAR_UNSPECIFIED
#include <EBStubs_MemMap.h>

#define EBSTUBS_START_SEC_CODE
#include <EBStubs_MemMap.h>

extern FUNC(void, SCHM_CODE) SchM_Init
(
  void
);

extern FUNC(void, SCHM_CODE) SchM_Deinit
(
  void
);

extern FUNC(void, SCHM_CODE) SchM_GetVersionInfo
(
  P2VAR(Std_VersionInfoType, AUTOMATIC, SCHM_APPL_DATA) versioninfo
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Can
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Dlt
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_DevAuth
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_DoIP
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Fr
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_LinIf
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Lin
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_LinTrcv
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Spi
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_StbM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Eep
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Fls
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Port
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Dio
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Pwm
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Icu
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Adc
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Gpt
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Mcu
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Wdg
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_RamTst
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_WdgIf
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Ea
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_CanIf
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_CanTSyn
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Xcp
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_FrIf
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_FrTSyn
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Crc
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Csm
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Os
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_BswM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_ComM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_EcuM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Det
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Fim
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_CNm
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_CanNm
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_J1939Nm
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_CanSM
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Eth
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_EthIf
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_EthSM
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_EthTSyn
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_FrNm
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_FrSM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Com
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_PduR
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_CanTrcv
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_FrTrcv
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_CanTp
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_FrTp
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Dcm
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Dem
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Fee
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_NvM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_MemIf
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_WdgM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_IpduM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Nm
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_CDD_CIC310_MLI
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_EepIf
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_FlsIf
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Rte
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_TcpIp
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Wdg_DioExt
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_LinSM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_SoAd
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_SomeIpTp
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_Sd
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_UdpNm
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Enter_UdsC
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Can
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Dlt
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_DevAuth
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_DoIP
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Fr
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_LinIf
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Lin
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_LinTrcv
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Spi
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_StbM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Eep
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Fls
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Port
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Dio
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Pwm
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Icu
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Adc
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Gpt
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Mcu
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Wdg
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_RamTst
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_WdgIf
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Ea
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_CanIf
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_CanTSyn
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Xcp
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_FrIf
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_FrTSyn
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Crc
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Csm
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Os
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_BswM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_ComM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_EcuM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Det
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Fim
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_CNm
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_CanNm
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_J1939Nm
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_CanSM
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Eth
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_EthIf
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_EthSM
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_EthTSyn
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_FrNm
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_FrSM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Com
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_PduR
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_CanTrcv
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_FrTrcv
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_CanTp
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_FrTp
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Dcm
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Dem
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Fee
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_NvM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_MemIf
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_WdgM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_IpduM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Nm
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_CDD_CIC310_MLI
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_EepIf
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_FlsIf
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Rte
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_TcpIp
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Wdg_DioExt
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_LinSM
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_SoAd
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_SomeIpTp
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_Sd
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_UdpNm
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_EB_Exit_UdsC
(
  VAR(uint8, AUTOMATIC) ExclusiveArea
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Can
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Dlt
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_DevAuth
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_DoIP
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Fr
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_LinIf
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Lin
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_LinTrcv
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Spi
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_StbM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Eep
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Fls
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Port
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Dio
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Pwm
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Icu
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Adc
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Gpt
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Mcu
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Wdg
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_RamTst
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_WdgIf
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Ea
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_CanIf
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_CanTSyn
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Xcp
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_FrIf
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_FrTSyn
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Crc
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Csm
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Os
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_BswM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_ComM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_EcuM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Det
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Fim
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_CNm
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_CanNm
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_CanSM
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Eth
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_EthIf
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_EthSM
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_EthTSyn
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_FrNm
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_FrSM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Com
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_PduR
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_CanTrcv
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_FrTrcv
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_CanTp
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_FrTp
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Dcm
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Dem
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Fee
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_NvM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_MemIf
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_WdgM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_IpduM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Nm
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_CDD_CIC310_MLI
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_EepIf
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_FlsIf
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Rte
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_TcpIp
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_Wdg_DioExt
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_LinSM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_SoAd
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_ActMainFunction_UdpNm
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Can
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Dlt
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_DevAuth
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_DoIP
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Fr
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_LinIf
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Lin
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_LinTrcv
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Spi
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_StbM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Eep
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Fls
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Port
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Dio
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Pwm
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Icu
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Adc
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Gpt
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Mcu
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Wdg
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_RamTst
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_WdgIf
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Ea
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_CanIf
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_CanTSyn
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Xcp
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_FrIf
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_FrTSyn
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Crc
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Csm
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Os
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_BswM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_ComM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_EcuM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Det
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Fim
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_CNm
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_CanNm
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_CanSM
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Eth
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_EthIf
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_EthSM
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_EthTSyn
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_FrNm
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_FrSM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Com
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_PduR
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_CanTrcv
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_FrTrcv
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_CanTp
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_FrTp
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Dcm
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Dem
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Fee
(
  VAR(uint8, AUTOMATIC) Instance,
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_NvM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_MemIf
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_WdgM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_IpduM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Nm
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_CDD_CIC310_MLI
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_EepIf
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_FlsIf
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Rte
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_TcpIp
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_Wdg_DioExt
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_LinSM
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_SoAd
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

extern FUNC(void, SCHM_CODE) SchM_CancelMainFunction_UdpNm
(
  VAR(uint8, AUTOMATIC) ActivationPoint
);

#define EBSTUBS_STOP_SEC_CODE
#include <EBStubs_MemMap.h>

#endif /* if !defined( SCHM_H ) */
