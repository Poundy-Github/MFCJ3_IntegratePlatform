


# RELEASE_VERSION = 'V1.0'
# #########################################################################################
#         # IMPORTANT: These are the BASE path for all operations !!! 
# INTEGRATE_BASE_PATH = r'E:\MFC5J3_Platform_Local'

# APP_BIN_PATH = INTEGRATE_BASE_PATH + r'\01_APP\MFC5J3_C673_Mcu_App\05_Output\bin'
# APP_BASE_PATH = INTEGRATE_BASE_PATH + r'\01_APP\MFC5J3_C673_Mcu_App'
# #########################################################################################
import os
import sys

##
project_list = {'C673':'MFC5J3_C673_Mcu_App','M18':'MFC5J3_M18_Mcu_App'}

APP_MAKE_BASE_PATH = None
APP_BIN_PATH = None
INTEGRATE_BASE_PATH = os.getcwd()
    
print(f'INTEGRATE_BASE_PATH = {INTEGRATE_BASE_PATH}')

if len(sys.argv) == 1:
    # print all available project information
    # for p in project_list:
    #     print(f'{p}')
    pass
else:
    pn = project_list.get(sys.argv[1].strip('').upper())
    if pn != None:
        APP_MAKE_BASE_PATH = INTEGRATE_BASE_PATH + r'\01_APP\\' + pn
        print(f'Project is {pn}, app path is {APP_MAKE_BASE_PATH}')
    
if APP_MAKE_BASE_PATH == None:
    print(f'There are no project specified ! Use default project C673')
    pn = project_list.get('C673')
    APP_MAKE_BASE_PATH = INTEGRATE_BASE_PATH + r'\01_APP\\' + pn
    if not os.path.exists(APP_MAKE_BASE_PATH):
        print(f'Application {pn} not exist !')
        exit(-1)


for r,ds,fs in os.walk(INTEGRATE_BASE_PATH + r'\01_APP\\' + pn):
    
    if 'output' in r.lower():
        if 'bin' in ds:
            APP_BIN_PATH = r + r'\bin'
            print(f'APP_BIN_PATH = {APP_BIN_PATH}')

if APP_BIN_PATH == None:
    print(f'APP_BIN_PATH not found !')
    exit(-1)

if os.path.exists(r'.\ReleaseConfiguration.txt') is False:
        print(f' Release input infomation file not exist,please check if compiling is complete !')
else:
    with open(file=r'.\ReleaseConfiguration.txt',mode='r',encoding='gb2312') as info:
        cmd = info.read()
exec(cmd)


projects_info = {
    'IBM':{
        'basedir': INTEGRATE_BASE_PATH + r'\00_BOOT\01_MFC5J3_IBM',
    },
    'BLU':{
        'basedir': INTEGRATE_BASE_PATH + r'\00_BOOT\02_MFC5J3_BLU',
    },
    'FBL':{
        'basedir': INTEGRATE_BASE_PATH + r'\00_BOOT\03_MFC5J3_FBL',
    },
    'FLASHER':{
        'basedir': INTEGRATE_BASE_PATH + r'\02_UTILS\01_TOOLS',
    },
    'APP':{
        'basedir': APP_MAKE_BASE_PATH,
    }
}


projects_info['IBM']['branch'] = Branch_Config['IBM']
projects_info['BLU']['branch'] = Branch_Config['BLU']
projects_info['FBL']['branch'] = Branch_Config['FBL']
projects_info['FLASHER']['branch'] = Branch_Config['FLASHER']
projects_info['APP']['branch'] = Branch_Config['APP']


# release mode :
# 0 -- DEBUG 
# 1 -- RELEASE
RELEASE_MODE = 'RELEASE'

# Release folder path 
RELEASE_BASE_PATH = INTEGRATE_BASE_PATH + r'\03_RELEASE'

# Executables to be generated path 
INTEGRATE_APP_BIN_PATH = INTEGRATE_BASE_PATH + r'\03_RELEASE\03_ORIGIN_EXECUTABLES\APP'
INTEGRATE_IBM_BIN_PATH = INTEGRATE_BASE_PATH + r'\03_RELEASE\03_ORIGIN_EXECUTABLES\IBM\RELEASE'
INTEGRATE_BLU_BIN_PATH = INTEGRATE_BASE_PATH + r'\03_RELEASE\03_ORIGIN_EXECUTABLES\BLU\RELEASE'
INTEGRATE_FBL_BIN_PATH = INTEGRATE_BASE_PATH + r'\03_RELEASE\03_ORIGIN_EXECUTABLES\FBL\RELEASE'

# Generate input files 
release_input_path = {
        'IBM_DEBUG':INTEGRATE_BASE_PATH + r'\03_RELEASE\03_ORIGIN_EXECUTABLES\IBM\DEBUG',
        'FBL_DEBUG':INTEGRATE_BASE_PATH + r'\03_RELEASE\03_ORIGIN_EXECUTABLES\FBL\DEBUG',
        'IBM':INTEGRATE_IBM_BIN_PATH,
        'BLU':INTEGRATE_BLU_BIN_PATH,
        'FBL':INTEGRATE_FBL_BIN_PATH,
        'APP':INTEGRATE_APP_BIN_PATH,
}

RELEASE_PROJECT_BASE_PATH = INTEGRATE_BASE_PATH

RELEASE_PROJECT_BASE_UTIL_IBM =  RELEASE_PROJECT_BASE_PATH + r'\00_BOOT\01_MFC5J3_IBM\01_Config\util\releaseMake.bat'
RELEASE_PROJECT_BASE_UTIL_BLU =  RELEASE_PROJECT_BASE_PATH + r'\00_BOOT\02_MFC5J3_BLU\01_Config\util\releaseMake.bat'
RELEASE_PROJECT_BASE_UTIL_FBL =  RELEASE_PROJECT_BASE_PATH + r'\00_BOOT\03_MFC5J3_FBL\01_Config\util\releaseMake.bat'
RELEASE_PROJECT_BASE_UTIL_APP =  APP_MAKE_BASE_PATH + r'\01_AsrConfig\util\RemakeAll.bat'

release_makefile = {
    'BOOT':[RELEASE_PROJECT_BASE_UTIL_IBM,RELEASE_PROJECT_BASE_UTIL_BLU,RELEASE_PROJECT_BASE_UTIL_FBL],
    'APP':[RELEASE_PROJECT_BASE_UTIL_APP],
}


###################################################################################
# Logic blocks layout configurations

#boot infos -- release 
flash_ibm_layout= {
    'block_pfls0' : {
        'start':0x80040000,
        'end':0x8005ffff + 1,
        'len':0x1ff80,
        'name':'IBM.s19',
        'outFile': RELEASE_BASE_PATH + r'\00_PRGMR\IBM.s19'
    }
}

flash_fbl_layout= {
    'FlashDriver' : {
        'start':0x70000000,
        'end':0x70001000,
        'len':0x1000,
        'name':'FlashDriver.s19',
        'outFile': RELEASE_BASE_PATH + r'\01_OTA\FlashDriver.s19'
    },
    'block_pfls0' : {
        'start':0x80060000,
        'end':0x8009ffff + 1,
        'len':0x40000,
        'name':'FBL.s19',
        'outFile':  RELEASE_BASE_PATH + r'\00_PRGMR\FBL.s19'
    }
}

flash_blu_layout= {
    'block_pfls0' : {
        'start':0x800a4000,
        'end':0x800bffff + 1,
        'len':0x200000-0x4000,
        'name':'BLU.s19',
        'outFile':  RELEASE_BASE_PATH + r'\01_OTA\BLU.s19'
    }
}

#boot infos -- debug 
flash_ibm_layout_debug= {
    'block_pfls0' : {
        'start':0x80040000,
        'end':0x8005ffff + 1,
        'len':0x1ff80,
        'name':'IBM.s19',
        'outFile': RELEASE_BASE_PATH + r'\00_PRGMR\IBM_DEBUG.s19'
    }
}

flash_fbl_layout_debug= {
    'block_pfls0' : {
        'start':0x80060000,
        'end':0x8009ffff + 1,
        'len':0x40000,
        'name':'FBL.s19',
        'outFile':  RELEASE_BASE_PATH + r'\00_PRGMR\FBL_DEBUG.s19'
    }
}

# app info
flash_layout_bank_A = {
    'block_pfls0' : {
        'start':0x80100000,
        'end':0x801fffff + 1,
        'len':0x100000,
        'name':'A_Application_pfls0_OTA.s19',
        'outFile': RELEASE_BASE_PATH + r'\01_OTA\A_Application_pfls0_OTA.s19'
    },
    'block_pfls1' : {
        'start':0x80300000,
        'end':0x8047ffff + 1,
        'len':0x180000,
        'name':'A_Application_pfls1_OTA.s19',
        'outFile': RELEASE_BASE_PATH + r'\01_OTA\A_Application_pfls1_OTA.s19'
    },
    'block_pfls2' : {
        'start':0x80600000,
        'end':0x8077ffff + 1,
        'len':0x180000,
        'name':'A_Application_pfls2_OTA.s19',
        'outFile':  RELEASE_BASE_PATH + r'\01_OTA\A_Application_pfls2_OTA.s19'
    },
    'block_pfls3' : {
        'start':0x80900000,
        'end':0x8097ffff + 1,
        'len':0x80000,
        'name':'A_Application_pfls3_OTA.s19',
        'outFile': RELEASE_BASE_PATH + r'\01_OTA\A_Application_pfls3_OTA.s19'
    }
}

flash_layout_bank_B = {
    'block_pfls0' : {
        'start':0x80200000,
        'end':0x802fffff + 1,
        'len':0xfc000,
        'name':'B_Application_pfls0_OTA.s19',
        'outFile': RELEASE_BASE_PATH + r'\01_OTA\B_Application_pfls0_OTA.s19'
    },
    'block_pfls1' : {
        'start':0x80480000,
        'end':0x805fffff + 1,
        'len':0x180000,
        'name':'B_Application_pfls1_OTA.s19',
        'outFile': RELEASE_BASE_PATH + r'\01_OTA\B_Application_pfls1_OTA.s19'
    },
    'block_pfls2' : {
        'start':0x80780000,
        'end':0x808fffff + 1,
        'len':0x180000,
        'name':'B_Application_pfls2_OTA.s19',
        'outFile': RELEASE_BASE_PATH + r'\01_OTA\B_Application_pfls2_OTA.s19'
    },
    'block_pfls3' : {
        'start':0x80980000,
        'end':0x809fffff + 1,
        'len':0x80000,
        'name':'B_Application_pfls3_OTA.s19',
        'outFile': RELEASE_BASE_PATH + r'\01_OTA\B_Application_pfls3_OTA.s19'
    }
}

app_layout = {
    'APP_A':flash_layout_bank_A,
    'APP_B':flash_layout_bank_B,
}

MFC5J3_platform_layout= {
    'IBM_DEBUG':flash_ibm_layout_debug,
    'FBL_DEBUG':flash_fbl_layout_debug,
    'IBM':flash_ibm_layout,
    'FBL':flash_fbl_layout,
    'BLU':flash_blu_layout,
    'APP':app_layout,
}


ADDR_OFFSET_APP_VALID = 0
SIZE_APP_VALID = 0x20

ADDR_OFFSET_FP = 0x100
SIZE_FP = 0x10

ADDR_OFFSET_SIGNATURE_WHOLE = 0x4000
SIZE_SIGNATURE_WHOLE = 0x20

ADDR_OFFSET_SIGNATURE_PART = 0x4020
SIZE_SIGNATURE_PART = 0x20
SIGNATURE_PART_HASH_SIZE = 0x20000

ADDR_OFFSET_ECU_PART_NUM= 0x4040
SIZE_ECU_PART_NUM = 0x20

ADDR_OFFSET_ECU_SW_VERSION= 0x4060
SIZE_SW_VERSION = 0x20

ADDR_OFFSET_SW_START= 0x6000


# Const data 
COMMON_FLAG_4B = '5aa5a55a'
COMMON_FLAG_16B = COMMON_FLAG_4B * 4
COMMON_FLAG_32B = COMMON_FLAG_4B * 8



############################################################################################