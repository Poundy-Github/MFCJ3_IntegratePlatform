
from Integrate.release_api import *

def release_main():

    release_git_update()

    if release_step_make():
    # if 1:
        release_step_generate()
    else:
        print(f'Release make failed !')

def debug_main():

    # if debug_step_make():
    if 1:
        debug_step_generate()
    else:
        print(f'Debug main failed !')

if __name__=="__main__":

    pass    #jenkins Test
    pass
    release_main()
    # debug_main()


    



    
