@echo off

SET OUTPUT_PATH="../output/bin"
SET ELF_FILE=%OUTPUT_PATH%/"TRICORE_TC38XQ_Boot.elf"
SET DUMP_FILE=%OUTPUT_PATH%/"TRICORE_TC38XQ_Boot.dump"

C:\TASKING\TriCorev6.3r1\ctc\bin\hldumptc.exe --disassembly-intermix -o %DUMP_FILE% %ELF_FILE%