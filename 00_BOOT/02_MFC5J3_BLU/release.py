

import sys
sys.path.append("..\..")

from release_api import *

if __name__=="__main__":

    log = 'release.log'

    cmd_list = [r'launch.bat make clean',r'launch.bat make -j10'] 
    # cmd_list = [r'launch.bat make -j10']

    cwd = os.getcwd()

    os.chdir(cwd + r'\01_Config\util') 

    # release_mode_preprocess(release_makefile['BOOT'],'DEBUG')

    release_run_makefile(cmd_list,logFile=log)

    pass