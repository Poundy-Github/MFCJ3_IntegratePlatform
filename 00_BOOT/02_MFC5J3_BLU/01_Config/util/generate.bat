@echo ===============================================================================

SET BLU_MOT_FILE=..\output\bin\TRICORE_TC38XQ_01_Config.mot
SET BLU_HEX_FILE=..\output\bin\TRICORE_TC38XQ_01_Config.hex -intel

srec_cat.exe ^
 %BLU_MOT_FILE% -crop 0x800A4100 0x800C0000 ^
 %BLU_MOT_FILE% -crop 0x70000000 0x70001000 -offset +0x100A5000 ^
 -o %BLU_MOT_FILE% -address-length=4 -disable=data-count -Execution_Start_Address=0x0000

srec_cat.exe ^
 %BLU_HEX_FILE% -crop 0x800A4100 0x800C0000 ^
 %BLU_HEX_FILE% -crop 0x70000000 0x70001000 -offset +0x100A5000 ^
 -o %BLU_HEX_FILE%

@echo ===============================================================================
