import os
import subprocess 
import re

def release_git_branch_update(repo_path : str = None,branch : str = None):
    if repo_path:
        commit_id = None
        os.chdir(path=repo_path)
        try:
            cmd = r'git config --global --add safe.directory ' + repo_path
            p = subprocess.run(cmd,capture_output=True,timeout = 30)
            cmd = r'git reset --hard'
            p = subprocess.run(cmd,capture_output=True,timeout = 30)
            if branch:
                cmd = r'git checkout ' + branch
                p = subprocess.run(cmd,capture_output=True,timeout = 30)
            cmd = r'git pull'
            p = subprocess.run(cmd,capture_output=True,timeout = 30)
            cmd = r'git submodule update --init'
            p = subprocess.run(cmd,capture_output=True,timeout = 30)
            cmd = r'git reflog'
            # cmd = r'git log -1'
            p = subprocess.run(cmd,capture_output=True,timeout = 120)
        except:
            print(f'Git update failed , command {cmd} execute error,retcode is {p.returncode}')
            cmd = r'git reflog'
            # cmd = 'git log -1'
            p = subprocess.run(cmd,capture_output=True,timeout = 120)
       
        if p.returncode == 0:
            try:
                pattern = r'^(\w{7})(.*)HEAD@\{0\}:.*'
                # pattern = r'commit (\w+)(.*)(HEAD.*)'
                regex = re.compile(pattern=pattern,flags=re.M)
                commit_id = regex.search(p.stdout.decode()).group(1)
                print(f'repo :{repo_path}\ncurrent commit_id = {commit_id}')
            except:
                print(f'Can\'t find commit id ! git info is :\n{p.stdout.decode()}')  
        else:
            print(f'Git update error ! Repo_path = {repo_path},command is {cmd}, return code is {p.returncode},git error info is :\n{p.stdout.decode()}')  
            # exit(-1)
        return f'Repo:{repo_path}\t\t\tbranch:{branch}\t\tcurrent commit_id = {commit_id}\n'

if __name__=="__main__":

    path = r'E:\00_Code\MFC5J3_Platform\01_APP\MFC5J3_M18_Mcu_App'
    release_git_branch_update(path)
    pass

