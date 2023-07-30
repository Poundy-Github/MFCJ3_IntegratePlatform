
import hexrec.records as hr
from bytesparse.inplace import Memory
import os
import zipfile
import subprocess 
import re
import shutil
from Integrate.signature import *
from Integrate.database import *
from Integrate.git_branch import *

def FBL_gen(memory_origin:Memory = None,layout:dict = None):
   
    try:
        block_info = layout.get('FlashDriver')
        memory_fls_driver = memory_origin.cut(start=block_info['start'],endex=block_info['end'],bound=True)
        memory_fls_driver.fill(start=block_info['start'],endex=memory_fls_driver.content_start,pattern=0xFF)

        #Flash driver structure pattern
        memory_fls_driver.write(address=block_info['start'],data= bytes.fromhex(COMMON_FLAG_4B))
        # add signature 
        data_to_signature = memory_fls_driver.to_bytes()
        # # add signature part  
        signature = release_signature_gen(data= data_to_signature[0x20:],flag=COMMON_FLAG_4B,start=0,size=0)
        memory_fls_driver.write(address=0x70000000 ,data=signature)

        # flash driver generate
        hr.save_memory(path= block_info['outFile'],memory= memory_fls_driver)

        # FBL info got 
        block_info = layout.get('block_pfls0')

        # 80060000 - 8006a000
        memory_fbl = memory_origin.cut(start=block_info['start'],endex=block_info['end'],bound=True)
        memory_fbl.fill(start=block_info['start'],endex=memory_fbl.content_start,pattern=0xFF)
        memory_fbl.fill(start=memory_fbl.content_endex,endex=block_info['end'],pattern=0xFF)

        gap_list = list(memory_fbl.gaps(start=memory_fbl.content_start,endex=memory_fbl.content_endex))
        for s,e in gap_list:
            if s != None and e != None:
                memory_fbl.fill(s ,e ,pattern=0xFF)
            else:
                print(f'Invalid gap start is {s},gap end is {e}')

        # add valid flag
        memory_fbl.write(address=block_info['start'],data= bytes.fromhex(COMMON_FLAG_32B))

        data_to_signature = memory_fbl.to_bytes()
        # # add signature part  
        signature = release_signature_gen(data= data_to_signature[0x4040:],flag=COMMON_FLAG_4B,\
                                    start=0x80064040,size=len(data_to_signature[0x4040:]))
        
        memory_fbl.write(address=0x80064020 ,data=signature)

            
        # add signature whole
        data_to_signature = memory_fbl.to_bytes()
        signature = release_signature_gen(data= data_to_signature[0x4020:],flag=COMMON_FLAG_4B,start=0,size=0)
        memory_fbl.write(address= 0x80064000 , data = signature)
        
    
        # export FBL.s19
        hr.save_memory(path= block_info['outFile'],memory= memory_fbl)

        #Generate FBL_FOR_BLU.s19 
        # cut 0x80064000 -  0x800A0000 as fbl for blu data
        data = memory_fbl.cut(start=memory_fbl.content_start + 0x4000,endex=memory_fbl.content_endex).to_bytes()
        # stuff data to memory_fbl_blu 0x800c4000 - 0x800fffff + 1
        memory_fbl_blu = Memory.from_bytes(data=data,offset=memory_fbl.content_start + 0x4000 + 0x60000)
        # add signature part  
        signature = release_signature_gen(data= data[0x40:],flag=COMMON_FLAG_4B,\
                                    start=0x80064040,size=len(data[0x40:]))
        memory_fbl_blu.write(address= 0x800C4020 , data = signature)

        # add signature whole  
        data = memory_fbl_blu.to_bytes()
        signature = release_signature_gen(data= data[0x20:],flag=COMMON_FLAG_4B,\
                                    start=0,size=0)
        memory_fbl_blu.write(address= 0x800C4000 , data = signature)

        out_dir = os.path.split(block_info['outFile'])[0]
        hr.save_memory(path= os.path.join( RELEASE_BASE_PATH + r'\01_OTA' + r'\FBL_BLU.s19'),memory= memory_fbl_blu)  

        # fbl_for_blu_gen(memory_fbl)
        print(f'FBL_gen Generate SUCCESS !')
        
    except:
        print(f'FBL_gen Generate ERROR!')

def FBL_DEBUG_gen(memory_origin:Memory = None,layout:dict = None):
    # try:
        # FBL info got 
        block_info = layout.get('block_pfls0')
        # 80060000 - 8006a000
        memory_fbl = memory_origin.cut(start=block_info['start'],endex=block_info['end'],bound=True)
        memory_fbl.fill(start=block_info['start'],endex=memory_fbl.content_start,pattern=0xFF)
        memory_fbl.fill(start=memory_fbl.content_endex,endex=block_info['end'],pattern=0xFF)

        gap_list = list(memory_fbl.gaps(start=memory_fbl.content_start,endex=memory_fbl.content_endex))
        for s,e in gap_list:
            if s != None and e != None:
                memory_fbl.fill(s ,e ,pattern=0xFF)
            else:
                print(f'Invalid gap start is {s},gap end is {e}')

        # add valid flag
        memory_fbl.write(address=block_info['start'],data= bytes.fromhex(COMMON_FLAG_32B))

        data_to_signature = memory_fbl.to_bytes()
        # # add signature part  
        signature = release_signature_gen(data= data_to_signature[0x4040:],flag=COMMON_FLAG_4B,\
                                    start=0x80064040,size=len(data_to_signature[0x4040:]))
        
        memory_fbl.write(address=0x80064020 ,data=signature)

        # add signature whole
        data_to_signature = memory_fbl.to_bytes()
        signature = release_signature_gen(data= data_to_signature[0x4020:],flag=COMMON_FLAG_4B,start=0,size=0)
        memory_fbl.write(address= 0x80064000 , data = signature)
    
        # export FBL.s19
        hr.save_memory(path= block_info['outFile'],memory= memory_fbl)

        print(f'FBL_DEBUG_gen Generate success!')
        
    # except:
    #     print(f'FBL_DEBUG_gen Generate ERROR!')

def APP_gen(memory_origin:Memory = None,app_layout:dict = None,validFilledOutput:bool = True):
 
    # try:
        # get app bank layout 
        layout = {}
        for item in app_layout.items():
            s = item[1]['block_pfls0']['start']
            e = item[1]['block_pfls0']['end']
            if memory_origin.content_start >= s and memory_origin.content_start <= e:
                layout = item[1]
                break

        # filled all gap region 
        gap_list = list(memory_origin.gaps(start=layout['block_pfls0']['start'],endex=memory_origin.content_start))
        for s,e in gap_list:
            if s != None and e != None:
                memory_origin.fill(s ,e ,pattern=0xFF)
            else:
                print(f'Invalid gap start is {s},gap end is {e}')

        # Genrate all block 
        data_to_signature : bytes = None
        all_in_one_list = []
        for item in layout.items():
            k = item[0].strip('')
            v = item[1]
            s = v['start']
            e = v['end']
            name = v['name']
            out_file = v["outFile"]
            all_in_one_list.append(out_file)

            if k == 'block_pfls0':
                # Genrate block 0
                print('block_pfls0 0x%08x 0x%08x %s' % (layout['block_pfls0']['start'],layout['block_pfls0']['end'],layout['block_pfls0']['name']))
                # First segment 0x80104000
                memory = memory_origin.cut(start=layout['block_pfls0']['start'] + ADDR_OFFSET_SIGNATURE_WHOLE,endex=layout['block_pfls0']['end'],bound= True)

                hr.save_memory(path= layout['block_pfls0']['outFile'],memory= memory)

                
            else:
                memory = memory_origin.cut(s,e,bound= True)
                print('%s 0x%08x 0x%08x %s' % (k,s,e,name))

            # get data to be hashed
            if data_to_signature == None:
                data_to_signature = memory.to_bytes()
            else:
                data_to_signature += memory.to_bytes()
            
            hr.save_memory(path= out_file,memory= memory)

        
        memory_pfls0 = hr.load_memory(layout['block_pfls0']['outFile'])
        # add signature part  start 0x80106000, size 0x20000
        signature_part = release_signature_gen(data= data_to_signature[0x2000:0x2000 + 0x20000],flag=COMMON_FLAG_4B,\
                                    start=layout['block_pfls0']['start'] + ADDR_OFFSET_SW_START,size=len(data_to_signature[0x2000:0x2000 + 0x20000]))
        
        memory_pfls0.write(address=layout['block_pfls0']['start'] + ADDR_OFFSET_SIGNATURE_PART ,data=signature_part)

            
        # add signature whole  0x80104000 - 0x80200000
        pfls_update = memory_pfls0.to_bytes()
        data_to_signature = pfls_update  + data_to_signature[len(pfls_update):] 
        # start 0x80104020 --- end
        signature_whole = release_signature_gen(data= data_to_signature[0x20:],flag=COMMON_FLAG_4B,start=0,size=0)
        memory_pfls0.write(address= layout['block_pfls0']['start'] + ADDR_OFFSET_SIGNATURE_WHOLE , data = signature_whole)

        hr.save_memory(path= layout['block_pfls0']['outFile'],memory= memory_pfls0)

        # trans
        filled_file_path = None
        if validFilledOutput == True:
                if layout['block_pfls0']['name'].find('B_Application') >= 0:
                    filled_file_path = RELEASE_BASE_PATH + r'\00_PRGMR\APP_B.s19' 
                if layout['block_pfls0']['name'].find('A_Application') >= 0:
                    filled_file_path = RELEASE_BASE_PATH + r'\00_PRGMR\APP_A.s19'

         # save all filled s19 with application valid flag 
        if filled_file_path != None:
            all_in_one_path = filled_file_path.replace('00_PRGMR','01_OTA').replace('APP','APP_OTA')
            exe_merge_file(all_in_one_list,all_in_one_path)

            # add valid data to image 
            memory_programer = hr.load_memory(all_in_one_path)
            memory_programer.fill(start=layout['block_pfls0']['start'],endex=memory_programer.content_start,pattern=0xFF)
            valid_data = bytes.fromhex(COMMON_FLAG_32B)
            memory_programer.write(address=layout['block_pfls0']['start'],data=valid_data)
            hr.save_memory(filled_file_path,memory= memory_programer)  
            print(f'Generate {filled_file_path} success !')

        print(f'APP Generate SUCCESS !')

    # except:
    #     print(f'APP Generate ERROR!')

def BLU_gen(memory:Memory = None,layout:dict = None):
    try:
        if memory and layout:
            layout_blu = layout['block_pfls0']

            fls_drv_mem = memory.cut(start=memory.content_start,endex=memory.content_start + 0x1000,bound=True)
            blu_memory = memory.cut(start=layout_blu['start'],endex=layout_blu['end'],bound=True)
            
            gap_list = list(fls_drv_mem.gaps(start=fls_drv_mem.content_start,endex=fls_drv_mem.content_endex))
            for s,e in gap_list:
                if s != None and e != None:
                    fls_drv_mem.fill(s ,e ,pattern=0x00)


            blu_memory.write(address=0x800a5000,data=fls_drv_mem.to_bytes())

            blu_memory.fill(start=layout_blu['start'],endex=blu_memory.content_start,pattern=0xff)
            blu_memory.fill(start=blu_memory.content_endex,endex=layout_blu['end'],pattern=0xff)

            gap_list = list(blu_memory.gaps(start=blu_memory.content_start,endex=blu_memory.content_endex))
            for s,e in gap_list:
                if s != None and e != None:
                    blu_memory.fill(s ,e ,pattern=0xff)

            # add signature part  
            data_to_signature = blu_memory.to_bytes()
            signature = release_signature_gen(data= data_to_signature[0x100:0x100 + 0x10000],flag=COMMON_FLAG_4B,\
                                        start=0x800a4100,size=0x10000)
            
            blu_memory.write(address=0x800a4020 ,data=signature)

                
            # add signature whole 
            data_to_signature = blu_memory.to_bytes()
            signature = release_signature_gen(data= data_to_signature[0x20:],flag=COMMON_FLAG_4B,start=0,size=0)
            blu_memory.write(address= 0x800a4000 , data = signature)

            hr.save_memory(path= layout['block_pfls0']['outFile'],memory= blu_memory)
            print(f'BLU_gen SUCCESS !')
        else:
            print(f'Input error !')
        pass
    except:
        print(f'BLU data Generate ERROR!')
  
def IBM_gen(memory:Memory = None,layout:dict = None): 
    # try:
        if memory and layout:
            layout_ibm = layout['block_pfls0']

            memory.bound(start=layout_ibm['start'],endex=layout_ibm['end'])

            gap_list = list(memory.gaps(start=layout_ibm['start'],endex=layout_ibm['end']))
            for s,e in gap_list:
                if s != None and e != None:
                    memory.fill(s ,e ,pattern=0xFF)

            # hr.save_memory(path= layout['block_pfls0']['outFile'],memory= memory)
            
            ibm_memory = memory.cut(start=layout_ibm['start'],endex=layout_ibm['end'],bound=True)

            hr.save_memory(path= layout['block_pfls0']['outFile'],memory= ibm_memory)

            print(f'IBM_gen SUCCESS !')
        else:
            print(f'IBM_gen Input error !')
    # except:
    #     print(f'IBM data Generate ERROR!')

def IBM_DEBUG_gen(memory:Memory = None,layout:dict = None): 
    # try:
        if memory and layout:
            layout_ibm = layout['block_pfls0']

            memory.bound(start=layout_ibm['start'],endex=layout_ibm['end'])

            gap_list = list(memory.gaps(start=layout_ibm['start'],endex=layout_ibm['end']))
            for s,e in gap_list:
                if s != None and e != None:
                    memory.fill(s ,e ,pattern=0xFF)

            # hr.save_memory(path= layout['block_pfls0']['outFile'],memory= memory)
            
            ibm_memory = memory.cut(start=layout_ibm['start'],endex=layout_ibm['end'],bound=True)

            hr.save_memory(path= layout['block_pfls0']['outFile'],memory= ibm_memory)

            print(f'IBM_DEBUG_gen SUCCESS !')
        else:
            print(f'IBM_DEBUG_gen Input error !')
    # except:
    #     print(f'IBM data Generate ERROR!')

def exe_merge_file(file_list:list = None,outFile:str = None,fill = False):
    if file_list :
        hr.merge_files(file_list,outFile)

        if fill == True:
            memory =  hr.load_memory(outFile)
            gap_list = list(memory.gaps(start=memory.content_start,endex=memory.content_endex))
            for s,e in gap_list:
                if s != None and e != None:
                    memory.fill(s ,e ,pattern=0xFF)
                else:
                    print(f'Invalid gap start is {s},gap end is {e}')
            hr.save_memory(outFile,memory)

        print(f'{outFile} merged file generate ok!')

def exe_release_gen(inDir:str = None,layout:dict = None,name:str =None)->None:

    if os.path.exists(inDir) is False:
        print(f'Input directory {inDir} not exist !')
        return
    
    file_list = os.listdir(inDir)
    for f in file_list:
        if f.split('.')[-1].strip('').lower() == 'hex':
            print(f'Start parse file {inDir}\\{f} ')
            full_path = os.path.join(inDir,f)

            try:
                memory = hr.load_memory(full_path)
            except:
                print(f'file {full_path} not supported !')
                continue
            
            block_layout = None
            try:
                block_layout = layout.get(name)
                pass
            except:
                print(f'{name} has no layout data!')
                continue

            if 'APP' in name:
                name = 'APP'

            cmd = name + '_gen(memory,block_layout)'

            exec(cmd)

def release_signature_gen(data : bytes = None,flag:str = None,start : int = 0,size : int = 0)->bytes:

    sp = Signature()
    sp.hash(data)
    
    # sp.print()

    signature = bytes.fromhex(flag)# flag
    signature += bytes.fromhex('ffffffff') # dummy
    if start == 0:
        signature += bytes.fromhex('ffffffff') # dummy
    else:
        signature += int(start).to_bytes(length=4,byteorder='little')# start address
    if size ==0:
        signature += bytes.fromhex('ffffffff') # dummy
    else:
        signature += int(size).to_bytes(length=4,byteorder='little')# size

    signature += sp.authentic()

    # print(f'signature is {signature.hex()}')

    return signature

def release_copy_folder(s,d):
    import shutil 
    try:
        if os.path.exists(s) and  os.path.exists(d):
            s_files = os.listdir(s)
            for f in s_files:
                # n = os.path.split(s_files)[1]
                ret = shutil.copy(src= os.path.join(s,f),dst= d)
                # print(f'target {ret} copy complete ')
        else:
            print(f'Source directory of destiny directory not exists !')
    except:
        print(f'Source directory copy failed !')

def  release_run_makefile(cmd_list : list = [],logFile:str = None,timeout = None)->bool:
    for cmd in cmd_list:
        p = subprocess.run(cmd,capture_output=True,timeout = timeout)
        if p.returncode == 0:
            print(f'{os.getcwd()} {cmd} ok !')                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
            pass
        else:
            print(f'Compile error, returncode = {p.returncode} ,Some error infomation could found in {logFile} ! ')
            info = p.stdout.decode()
            with open(os.path.join(INTEGRATE_BASE_PATH,logFile),'w+') as log:
                log.write('***************************************** log start ***************************************')
                log.write(info)
                log.write('***************************************** log end ***************************************')
                log.close()
            return False
    return True

def release_make_boot(make_list:list = [],logFile = r'logCommom.txt',outPutDir = None,mode : str = 'RELEASE'):
    '''
    Note: 
    '''
    
    origin_bak_file = INTEGRATE_BASE_PATH + r'\03_RELEASE\03_ORIGIN_EXECUTABLES'
    for f in make_list:        
        os.chdir(os.path.split(f)[0])
        bin_dir = os.path.join(os.getcwd(),r'..\output\bin')
        project_name = f.split('\\')[-4][-3:]
        target_dir = origin_bak_file + '\\' + project_name + '\\' + mode

        print(f'Project is {project_name},Start compile {f}')
        
        if not os.path.exists(target_dir):
            os.makedirs(target_dir)
        else:
            for f in os.listdir(target_dir):
                os.remove(os.path.join(target_dir,f))
        
        cmd_list = [r'launch.bat make clean',r'launch.bat make -j']

        if release_run_makefile(cmd_list,logFile,timeout=2000):
            # Rename current block executable 
            exe_list = os.listdir(bin_dir)
            for exe in exe_list:
                dest = exe.replace('TRICORE_TC38XQ_01_Config','TRICORE_TC38XQ_01_Config_' +  project_name)
                if os.path.exists(os.path.join(bin_dir,exe)):
                    os.rename(os.path.join(bin_dir,exe) ,os.path.join(bin_dir,dest)) 
                    # Move executable to generator origin directory
                    shutil.move(os.path.join(bin_dir,dest),target_dir)
                    print(f'Move {os.path.join(bin_dir,dest)} to {target_dir}!')
        else:
            print(f'Project {project_name} compile failed!')
            return False
    return True

    if outPutDir:
        # Copy executable to generator origin directort TODO
        pass
    
def release_make_app(make_list:list = [],logFile = r'logCommom.txt',outPutDir = None):

    bin_dir = APP_BIN_PATH 
    origin_bak_file = RELEASE_BASE_PATH + r'\03_ORIGIN_EXECUTABLES\APP'
    ld_file = APP_MAKE_BASE_PATH +  r'\01_AsrConfig\output\generated\TRICORE-tasking.ldscript'

    # Make output directory or empty it
    target_dir = origin_bak_file 
    if not os.path.exists(target_dir):
        os.makedirs(target_dir)
    else:
        if not os.path.exists(target_dir):
            os.makedirs(target_dir)
        else:
            for f in os.listdir(target_dir):
                os.remove(os.path.join(target_dir,f))

    # Get current block info 
    with open(ld_file,mode = 'r') as ldf:
        pattern = r'^#define TSK_COMPILE_CODE_IN_BLOCK(.*)TSK_COMPILE_CODE_IN_BLOCK_(.*)'
        ld_content = ldf.read()
        regex = re.compile(pattern=pattern,flags=re.M)
        match = regex.search(string=ld_content)

        #get current block and next block to be compiled 
        if match != None:
            if match.group(2) == 'A':
                ld_content = regex.sub(repl = r"#define TSK_COMPILE_CODE_IN_BLOCK\t\t\tTSK_COMPILE_CODE_IN_BLOCK_B\n",string= str(ld_content))
            elif match.group(2) == 'B':
                ld_content = regex.sub(repl = r"#define TSK_COMPILE_CODE_IN_BLOCK\t\t\tTSK_COMPILE_CODE_IN_BLOCK_A\n",string= str(ld_content))
            else:
                pass
    print(f'Project is Application {match.group(2) },start compile!')
    # Start compile first block 
    os.chdir(APP_MAKE_BASE_PATH + r'\01_AsrConfig\util')
    cmd_list = [r'launch.bat make clean',r'launch.bat make -j']
    if not release_run_makefile(cmd_list,logFile,3600):
        return False
    
    # Rename current block executable 
    bank = match.group(2)
    exe_list = os.listdir(bin_dir)
    for exe in exe_list:
        dest = exe.replace('TRICORE_TC38XQ_01_AsrConfig','TRICORE_TC38XQ_01_AsrConfig_' + bank)
        if os.path.exists(os.path.join(bin_dir,exe)):
            os.rename(os.path.join(bin_dir,exe) ,os.path.join(bin_dir,dest)) 
             # Move executable to generator origin directory
            shutil.move(os.path.join(bin_dir,dest),target_dir)
            print(f'Move {os.path.join(bin_dir,dest)} to {target_dir}!')
        
    # Change next block to be compiled  
    with open(ld_file,mode = 'w') as ldf:
        ldf.write(ld_content)

    bank = chr(ord('A') + ord('B') - ord(match.group(2)))
    print(f'Project is Application {bank},start compile!')
    cmd_list = [r'launch.bat make -j']
    if not release_run_makefile(cmd_list,logFile,3600):
        return False

    # Rename current block executable 
    
    exe_list = os.listdir(bin_dir)
    for exe in exe_list:
        dest = exe.replace('TRICORE_TC38XQ_01_AsrConfig','TRICORE_TC38XQ_01_AsrConfig_' + bank)
        if os.path.exists(os.path.join(bin_dir,exe)):
            os.rename(os.path.join(bin_dir,exe) ,os.path.join(bin_dir,dest)) 
            shutil.move(os.path.join(bin_dir,dest),target_dir)
            print(f'Move {os.path.join(bin_dir,dest)} to {target_dir}!')

    return True
 
 
def release_zip_all_in_one(release_name):

    copy_src = INTEGRATE_BASE_PATH + r'\02_UTILS\01_TOOLS\00_CanoeFlasher'
    copy_dst = INTEGRATE_BASE_PATH + r'\03_RELEASE\04_CANOE_FLASHER'

    shutil.copytree(copy_src,copy_dst)

    dir_list = [INTEGRATE_BASE_PATH + r'\03_RELEASE']

    os.chdir(INTEGRATE_BASE_PATH)

    zip = zipfile.ZipFile(release_name + r'.zip', 'w', zipfile.ZIP_DEFLATED)
    for dir in dir_list:
        if os.path.exists(dir):
            print(f'Ziping {dir} ...')
            for dir_path, dir_names, file_names in os.walk(dir):
                fpath = dir_path.replace(dir, '')
                for filename in file_names:
                    zip.write(os.path.join(dir_path, filename), os.path.join(fpath, filename))
            print(f'{dir} zip success!!!')
        else:
            print(f'Directory {dir} not exist !!!')
    
    zip.close()
    shutil.rmtree(copy_dst)

def release_step_make():

    # Compile IBM/BLU/FBL
    make_list = release_makefile['BOOT']
    if os.path.exists(RELEASE_PROJECT_BASE_PATH + r'\errorLogBoot.txt'):
        os.remove(RELEASE_PROJECT_BASE_PATH + r'\errorLogBoot.txt')
    logFile = RELEASE_PROJECT_BASE_PATH + r'\errorLogBoot.txt'

    release_mode_preprocess(make_list,mode= 'DEBUG')
    print(f'Change BOOT to DEBUG mode !')
    if not release_make_boot(make_list,logFile=logFile,mode= 'DEBUG'):
        return False
        
    release_mode_preprocess(make_list,mode= 'RELEASE')
    print(f'Change BOOT to RELEASE mode !')
    if not release_make_boot(make_list,logFile=logFile,mode= 'RELEASE'):
        return False

    # Compile APPA/APPB
    make_list = release_makefile['APP']
    if os.path.exists(RELEASE_PROJECT_BASE_PATH + r'\errorLogApp.txt'):
        os.remove(RELEASE_PROJECT_BASE_PATH + r'\errorLogApp.txt')
    logFile = RELEASE_PROJECT_BASE_PATH + r'\errorLogApp.txt'

    if not release_make_app(make_list,logFile=logFile):
        return False
    
    return True


def debug_step_make():

    # Compile IBM/BLU/FBL
    make_list = release_makefile['BOOT']
    if os.path.exists(RELEASE_PROJECT_BASE_PATH + r'\errorLogBoot.txt'):
        os.remove(RELEASE_PROJECT_BASE_PATH + r'\errorLogBoot.txt')
    logFile = RELEASE_PROJECT_BASE_PATH + r'\errorLogBoot.txt'

    release_mode_preprocess(make_list,mode= 'DEBUG')
    print(f'Change BOOT to DEBUG mode !')

    for m in make_list:
        os.chdir(os.path.split(m)[0])#
        cmd_list = [r'launch.bat make clean',r'launch.bat make -j']
        if not release_run_makefile(cmd_list,logFile,timeout=2000):
            return False

    return True

def release_step_generate():

    if RELEASE_MODE == 'DEBUG':
        exe_release_gen(inDir= INTEGRATE_FBL_BIN_PATH,layout=MFC5J3_platform_layout,name = 'FBL')
    else:
        for name,path in release_input_path.items():
            exe_release_gen(inDir= path,layout=MFC5J3_platform_layout,name = name)

    # Copy ota file to flasher folder 
    release_copy_folder(RELEASE_BASE_PATH + r'\01_OTA',INTEGRATE_BASE_PATH + r'\02_UTILS\01_TOOLS\00_CanoeFlasher\data\\')

    # IBM_FBL_MERGE
    file_boot_merged = [flash_ibm_layout['block_pfls0']['outFile'],flash_fbl_layout['block_pfls0']['outFile']]
    exe_merge_file(file_list=file_boot_merged,outFile= RELEASE_BASE_PATH + r'\00_PRGMR\IBM_FBL_MERGE.s19')
    # APP merged
    file_app_merged = [RELEASE_BASE_PATH + r'\00_PRGMR\APP_A.s19',
                        RELEASE_BASE_PATH + r'\00_PRGMR\APP_B.s19']
    exe_merge_file(file_list=file_app_merged,outFile= RELEASE_BASE_PATH + r'\00_PRGMR\APP_MERGE.s19')

    # ALL merged
    file_all_merged = [RELEASE_BASE_PATH + r'\00_PRGMR\APP_MERGE.s19',
                        RELEASE_BASE_PATH + r'\00_PRGMR\IBM_FBL_MERGE.s19',]
    exe_merge_file(file_list=file_all_merged,outFile= RELEASE_BASE_PATH + r'\00_PRGMR\ALL_MERGE.s19')


    # IBM_FBL_MERGE debug
    file_boot_merged = [flash_ibm_layout_debug['block_pfls0']['outFile'],flash_fbl_layout_debug['block_pfls0']['outFile']]
    exe_merge_file(file_list=file_boot_merged,outFile= RELEASE_BASE_PATH + r'\00_PRGMR\IBM_FBL_MERGE_DEBUG.s19')

    # ALL merged debug
    file_all_merged = [RELEASE_BASE_PATH + r'\00_PRGMR\APP_MERGE.s19',
                        RELEASE_BASE_PATH + r'\00_PRGMR\IBM_FBL_MERGE_DEBUG.s19',]
    exe_merge_file(file_list=file_all_merged,outFile= RELEASE_BASE_PATH + r'\00_PRGMR\ALL_MERGE_DEBUG.s19')

    # Zip all files need to release to one folder 
    release_zip_all_in_one(r'MCU_RELEASE_' + RELEASE_VERSION)


def debug_step_generate():

    release_input_path_debug = {
        'IBM':INTEGRATE_BASE_PATH + r'\00_BOOT\01_MFC5J3_IBM\01_Config\output\bin',
        'BLU':INTEGRATE_BASE_PATH + r'\00_BOOT\02_MFC5J3_BLU\01_Config\output\bin',
        'FBL':INTEGRATE_BASE_PATH + r'\00_BOOT\03_MFC5J3_FBL\01_Config\output\bin',
    }
    for name,path in release_input_path_debug.items():
        exe_release_gen(inDir= path,layout=MFC5J3_platform_layout,name = name)

    # Copy ota file to flasher folder 
    release_copy_folder(RELEASE_BASE_PATH + r'\01_OTA',INTEGRATE_BASE_PATH + r'\02_UTILS\01_TOOLS\00_CanoeFlasher\data\\')

def release_git_update()->None:

    branch_info = []
    for item in projects_info.items():
        proj_name = item[0]
        proj_info = item[1]
        info = release_git_branch_update(proj_info['basedir'],proj_info['branch'])
        branch_info.append(info)
    
    with open(RELEASE_BASE_PATH + r'\ReleaseInformation.txt','w') as f:
        for i in branch_info:
            f.writelines(i)


def release_mode_preprocess(make_list,mode = ''):

    mode = mode.strip().upper()
    if mode != 'RELEASE' and mode != 'DEBUG':
        print(f'Release mode setup error ! Origin release mode will be used !')
        return
    
    pattern = r'^BOOT_RELEASE.*=.*(false|true)'
    regex = re.compile(pattern=pattern,flags=re.M)
    
    for mak in make_list:
        basedir = os.path.dirname(mak)
        with open(basedir + r'\Makefile.mak','r') as m:
            content = m.read()
        match = regex.search(content)
        if match != None:
            if 'RELEASE' == mode:
                content = regex.sub(r'BOOT_RELEASE := true',content)
            if 'DEBUG' == mode:
                content = regex.sub(r'BOOT_RELEASE := false',content)
            with open(basedir + r'\Makefile.mak','w') as m:
                m.write(content)
                
def debug_gen_fbl(mode = 'DEBUG'):

    make_list = release_makefile['BOOT']
    release_mode_preprocess(make_list,mode= 'DEBUG')
    if not release_make_boot(make_list,mode= 'DEBUG'):
        return False
    # Gen fbl
    exe_release_gen(inDir= INTEGRATE_FBL_BIN_PATH,layout=MFC5J3_platform_layout,name = 'FBL')
    # Copy ota file to flasher folder 
    release_copy_folder(RELEASE_BASE_PATH + r'\01_OTA',INTEGRATE_BASE_PATH + r'\02_UTILS\01_TOOLS\00_CanoeFlasher\data\\')






if __name__=="__main__":
    pass
    # release_mode_preprocess(release_makefile['BOOT'],'DEBUG')

    # release_make_boot(release_makefile['BOOT'])

    # release_step_make()

    # release_step_generate()

    # # Copy ota file to flasher folder 
    # release_copy_folder(RELEASE_BASE_PATH + r'\01_OTA',INTEGRATE_BASE_PATH + r'\02_UTILS\01_TOOLS\00_CanoeFlasher\data')

    # debug_gen_fbl(mode = 'DEBUG')

    # dir = r'E:\MFC5J3_Platform_Local\03_RELEASE\03_ORIGIN_EXECUTABLES'

    # for a,b,c in os.walk(dir):
    #     print(f'a = {a},b = {b},c = {c}')

   

    
