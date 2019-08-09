import h5py 

def keySearch(dictionary,layer):
    layer+=1
    try:
        keys = dictionary.keys()
        for key in keys:
            printStr = ""
            for i in range(0,layer):
                printStr += "--"
            printStr += key
            print(printStr)
            keySearch(dictionary[key],layer)
    except:
        a = 1

def main():
    testDict = {'a':1,'b':2,'c':3,'d':4}
    testDict['a'] = {'aa':1,'ab':2,'ac':3}
    testDict['a']['ab'] = {'aba':1,'abb':2,'abc':123}
    testDict['b'] = {'bb':2}
    testDict['c'] = {'ca':1,'cd':4}
    print('testDict contents:')
    #keySearch(testDict,0)
    #filepath = "/home/lerandc/gitRepos/prismatic/test/AuDeca_7_2.h5"
    filepath = "/media/lerandc/DATA/files/Ta_tilt_series/tilt_45/Ta_tilt_series_45_group1.h5"
    #filepath = "/media/lerandc/DATA/files/prismatic_test/fullTest/fullTest.h5"
    AuDeca = h5py.File(filepath,'r')

    print('AuDeca_test3.h5 filestructure:')
    keySearch(AuDeca,0)
    
    #print(AuDeca['4DSTEM_simulation'].attrs['version_minor'])
    #print('Sample_LFP_datacube.h5 filestructure:')
    #sample = h5py.File("Sample_LFP_datacube.h5",'r')
    #keySearch(sample,0)
    

if __name__ == '__main__':
    main()
