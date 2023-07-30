from xml.dom.minidom import * 
from lxml import etree

def readFromXML(path:str = None):
    if path:
        db = parse(path)
        rootNode : Document = db.documentElement   
        print(f'rootNode = {rootNode.nodeName}')

        nodes = rootNode.getElementsByTagName('INSTANCE')
        for n in nodes:

            print(n.attributes)
        # attr = rootNode.getElementById
        # for n in nodes:

        #     print(n.getUserData('REQUEST'))

        # for node in rootNode.childNodes:
        #     if node.nodeName == 'INSTANCE':
        #         print(f'node =INSTANCE')
        #         for a in node.childNodes:
        #             if a.nodeName == 'REQUEST':
        #                 print(f'node = {a.nodeName}')
        #                 for b in a.childNodes:
        #                     print(f'node = {b.nodeName}')
        #                     pass
        #             if a.nodeName == 'RESPONSE':
        #                 print(f'node = {a.nodeName}')
        #                 for b in a.childNodes:
        #                     print(f'node = {b.nodeName}')
        #                     pass
        #                 pass




        # doc = ''
        # with open(file = path,mode='rb') as f:
        #     doc = f.read()
        # xml = etree.XML(doc)

        # xml.

        # print(xml.xpath(r"//"))



if __name__=="__main__":

    readFromXML(r'E:\FBL_DEV\02_Tools\FBL_UDS_CANoe12\uds\UDS_C673.xml')

    pass


