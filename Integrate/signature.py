import os
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.primitives import cmac
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes 
import cryptography.exceptions


key_path = 'key.txt'

SIG_STATE_IDLE = 0
SIG_STATE_HASH_START= 1
SIG_STATE_HASH_UPDATE = 2
SIG_STATE_HASH_FINISH = 3
SIG_STATE_AUTH_START = 4
SIG_STATE_AUTH_FINISH = 5

EncMacKey = bytes([0x20, 0x85, 0xCD, 0xBB, 0x81, 0xBC, 0xE0, 0x79, 0xD8, 0x42, 0x06,0x8E, 0x93, 0x6B, 0x76, 0xAE])
EcuKey    = bytes([0x07, 0x5D, 0xAF, 0xE3, 0xFC, 0xF8, 0xAB, 0x22, 0x2B, 0x50, 0x4A, 0x4A, 0xBB, 0x4B, 0x83, 0x7D])

class Signature:
    def __init__(self) -> None:

        # if os.path.exists(key_path):
        #     # print(f'Storaged key will be used ! ')
        #     with open(file=key_path,mode='rb') as k:
        #         self._key = k.read()
        # else:
        #     self._key = os.urandom(16)
        #     with open(file=key_path,mode='wb') as k:
        #         k.write(self._key)

        cipher = Cipher(algorithms.AES(EcuKey), modes.ECB())
        decryptor = cipher.decryptor()

        self._key = decryptor.update(EncMacKey) + decryptor.finalize()

        self._cmac = None
        self._algo = algorithms.AES(self._key)
        self._state = SIG_STATE_IDLE
        self._res = None
        self._hash = None
    
    def get(self):
        return self._key,self._hash,self._res
    
    def hash_start(self,data = None):
        self._digest = hashes.Hash(hashes.MD5())
        self._state = SIG_STATE_HASH_START
        if data:
            self._digest.update(data)
            self._state = SIG_STATE_HASH_UPDATE

    def hash_update(self,data = None):
        if data:
            self._digest.update(data)
        else:
            print(f'warning : hash data is none.')
        self._state = SIG_STATE_HASH_UPDATE

    def hash_finish(self,data = None):
        if data:
            self._digest.update(data)
        self._hash = self._digest.finalize()
        self._state = SIG_STATE_HASH_FINISH

    def hash(self,data):
        if data:
            self.hash_start()
            self.hash_update(data)
            self.hash_finish()
        else:
            self._state = SIG_STATE_IDLE
        

    def authentic(self,data= None)->bytes:
        # if self._state == SIG_STATE_IDLE:
        #     self.hash(data)

        if self._state != SIG_STATE_HASH_FINISH:
            self.hash(data)
        
        # self._cmac = cmac.CMAC(self._algo)
        # self._cmac.update(self._hash)
        self._encryptor = Cipher(algorithms.AES(self._key), modes.ECB()).encryptor()

        # self._res = self._cmac.finalize()

        self._res = self._encryptor.update(self._hash) + self._encryptor.finalize()
        self._state = SIG_STATE_AUTH_FINISH
        return self._res
    
    def verify(self,data):

        if data and self._state == SIG_STATE_AUTH_FINISH:
            try:
                self._cmac.verify(data)
                return True
            except cryptography.exceptions.InvalidSignature:
                return False
        else:
            return False


    def print(self):
        print(f'key = {self._key.hex()}')
        if self._state >= SIG_STATE_HASH_FINISH:
            print(f'hash = {self._hash.hex()} ')
            if self._state >= SIG_STATE_AUTH_FINISH:
                print(f'cmac = {self._res.hex()}')

import hexrec.records as hr
from bytesparse.inplace import Memory
import os

# from release import app_layout

# def signature_get_data(layout : dict = None):

#     cipher = Signature()

#     for item in layout.items():
#         k = item[0]
#         v = item[1]
#         mem = hr.load_memory(path=v['outFile'])
#         to_hash_data = mem.to_bytes()
#         if 'block_pfls0' == k:
#             cipher.hash_start(data=to_hash_data[32:])
            
#         else:
#             cipher.hash_update(data=to_hash_data)

#     cipher.hash_finish()
#     cipher.authentic()
#     cipher.print()

#     return cipher.get()

def signature_get_data(data : bytes = None):

    cipher = Signature()
    cipher.hash(data)
    cipher.authentic()
    cipher.print()

    return cipher.get()
    
if __name__=="__main__":
    pass
    # d = bytes()
    # for item in app_layout.items():
    #     k = item[0]
    #     v = item[1]
    #     mem = hr.load_memory(path=v['outFile'])
    #     to_hash_data = mem.to_bytes()
    #     if 'block_pfls0' == k:
    #         d += to_hash_data[32:]
    #         # cipher.hash_start(data=to_hash_data[32:])
            
    #     else:
    #         d+=to_hash_data
    #         # cipher.hash_update(data=to_hash_data)

    # signature_get_data(d)

    # # salt = PBKDF2HMAC()
    
    # data = bytes([0xF2,0xFE,0xF3,0xF4,0xF5,0xF6,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF1,0xF2,0xF3,0xF4])
    # print(data.hex())
    # # data = bytes.fromhex('3bc2b5028568e50ae0adcfa0daea8f49')

    # signature_get_data(app_layout['APP_A'])

    signature_get_data(d)


