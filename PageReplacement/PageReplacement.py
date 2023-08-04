import sys

def inputTXT( fileName ):
    pageRef = []
    fin = open( fileName + '.txt', 'r' )

    frameNum = fin.readline()
    frameNum = int( frameNum.strip() )

    inputStr = fin.read(1)
    while inputStr != '' and inputStr != '\n':
        # read data from .txt and convert all inputs to list from array
        pageRef.append( inputStr )
        inputStr = fin.read(1)
    #print('pageRef : ',pageRef )                           #test print
    fin.close()

    for n in range(len(pageRef)):
        #convert all element in inputNum to int from str
        pageRef[n] = int( pageRef[n] )

    return frameNum, pageRef

def outputTXT( fileName, pageType, pageRef, frameState, fault, frameNum ):
    fout = open( 'ouput' + fileName[5:6] + '_.txt', 'a' )
    #fout.seek( 0, 2 )   #seek for the tale of file

    #-------------------------------------------------------------FIFO---------------------------------------------------------------------------
    if pageType == 'FIFO':
        fout.write( '--------------FIFO-----------------------\n' )
        for i in range( len( pageRef ) ):
            outstr = str( pageRef[i] ).ljust( 10 )
            fout.write( outstr )
            outstr = str( frameState[i] ).ljust( 20 )
            fout.write( outstr )
            if fault[i] == 'F' or fault[i] == 'R':
                fout.write( 'F' )
            fout.write( '\n' )
        pageF = fault.count('R') + fault.count('F')
        fout.write( 'Page Fault = ' + str( pageF ) + '  Page Replaces = ' + str( fault.count('R') ) + '  Page Frames = ' + str( frameNum ) + '\n' )
    #-------------------------------------------------------------FIFO---------------------------------------------------------------------------

    #-------------------------------------------------------------LRU----------------------------------------------------------------------------
    elif pageType == 'LRU':
        fout.write( '--------------LRU-----------------------\n' )
        for i in range( len( pageRef ) ):
            outstr = str( pageRef[i] ).ljust( 10 )
            fout.write( outstr )
            outstr = str( frameState[i] ).ljust( 20 )
            fout.write( outstr )
            if fault[i] == 'F' or fault[i] == 'R':
                fout.write( 'F' )
            fout.write( '\n' )
        pageF = fault.count('R') + fault.count('F')
        fout.write( 'Page Fault = ' + str( pageF ) + '  Page Replaces = ' + str( fault.count('R') ) + '  Page Frames = ' + str( frameNum ) + '\n' )
    #-------------------------------------------------------------LRU----------------------------------------------------------------------------

    #-------------------------------------------------------------MFU----------------------------------------------------------------------------
    elif pageType == 'MFU':
        fout.write( '--------------MFU-----------------------\n' )
        for i in range( len( pageRef ) ):
            outstr = str( pageRef[i] ).ljust( 10 )
            fout.write( outstr )
            outstr = str( frameState[i] ).ljust( 20 )
            fout.write( outstr )
            if fault[i] == 'F' or fault[i] == 'R':
                fout.write( 'F' )
            fout.write( '\n' )
        pageF = fault.count('R') + fault.count('F')
        fout.write( 'Page Fault = ' + str( pageF ) + '  Page Replaces = ' + str( fault.count('R') ) + '  Page Frames = ' + str( frameNum ) + '\n' )
    #-------------------------------------------------------------MFU----------------------------------------------------------------------------

    #-------------------------------------------------------------LFU----------------------------------------------------------------------------
    elif pageType == 'LFU':
        fout.write( '--------------LFU-----------------------\n' )
        for i in range( len( pageRef ) ):
            outstr = str( pageRef[i] ).ljust( 10 )
            fout.write( outstr )
            outstr = str( frameState[i] ).ljust( 20 )
            fout.write( outstr )
            if fault[i] == 'F' or fault[i] == 'R':
                fout.write( 'F' )
            fout.write( '\n' )
        pageF = fault.count('R') + fault.count('F')
        fout.write( 'Page Fault = ' + str( pageF ) + '  Page Replaces = ' + str( fault.count('R') ) + '  Page Frames = ' + str( frameNum ) + '\n' )
    #-------------------------------------------------------------LFU----------------------------------------------------------------------------

    #-------------------------------------------------------------ARB----------------------------------------------------------------------------
    elif pageType == 'ARB':
        fout.write( '--------------ARB-----------------------\n' )
        for i in range( len( pageRef ) ):
            outstr = str( pageRef[i] ).ljust( 10 )
            fout.write( outstr )
            outstr = str( frameState[i] ).ljust( 20 )
            fout.write( outstr )
            if fault[i] == 'F' or fault[i] == 'R':
                fout.write( 'F' )
            fout.write( '\n' )
        pageF = fault.count('R') + fault.count('F')
        fout.write( 'Page Fault = ' + str( pageF ) + '  Page Replaces = ' + str( fault.count('R') ) + '  Page Frames = ' + str( frameNum ) + '\n' )
    #-------------------------------------------------------------ARB----------------------------------------------------------------------------

    #-------------------------------------------------------------SC----------------------------------------------------------------------------
    elif pageType == 'SC':
        fout.write( '--------------SC-----------------------\n' )
        for i in range( len( pageRef ) ):
            outstr = str( pageRef[i] ).ljust( 10 )
            fout.write( outstr )
            outstr = str( frameState[i] ).ljust( 20 )
            fout.write( outstr )
            if fault[i] == 'F' or fault[i] == 'R':
                fout.write( 'F' )
            fout.write( '\n' )
        pageF = fault.count('R') + fault.count('F')
        fout.write( 'Page Fault = ' + str( pageF ) + '  Page Replaces = ' + str( fault.count('R') ) + '  Page Frames = ' + str( frameNum ) + '\n' )
    #-------------------------------------------------------------SC----------------------------------------------------------------------------


    fout.close()

def findEarlies( frame, timestamp ):
    #找目前frame裡的所有page中，最早進的page
    earliest = 0
    for i in range( len( frame ) ):
        if timestamp[frame[i]] <= timestamp[frame[earliest]]: 
            earliest = i
    #print( 'earliest:', earliest )                     #test print
    return earliest

def findMFreq( frame, timestamp, freq ):
    num = 0
    for i in range( len( frame ) ):
        if freq[frame[i]] > freq[frame[num]]:
            num = i
        elif freq[frame[i]] == freq[frame[num]]: #如果頻率一樣，則以LRU方式，pop掉比較早進來的page
            if timestamp[frame[i]] < timestamp[frame[num]]:
                num = i
    #print( 'MF:', num )
    return num

def findLFreq( frame, timestamp, freq ):
    num = 0 #min
    for i in range( len( frame ) ):
        if freq[frame[i]] < freq[frame[num]]:
            num = i
        elif freq[frame[i]] == freq[frame[num]]: #如果頻率一樣，則以LRU方式，pop掉比較早進來的page
            if timestamp[frame[i]] < timestamp[frame[num]]:
                num = i
    #print( 'LF:', num )
    return num

def findMinShift( frame, shiftReg ):
    num = 0 #min
    str_i = ''
    str_min = ''
    for i in range( len( frame ) ):
        str_i = ''.join( str( s ) for s in shiftReg[frame[i]] )    #list to string
        str_min = ''.join( str( s ) for s in shiftReg[frame[num]] )
        if str_i < str_min:
            num = i
    return num

def findNoChance( frame, chance, timestamp ):
    num = 0
        #initial num
    for i in range( len( frame ) ):
        if chance[frame[i]] == 0:
            num = i
    found = [False for i in range( 0 , 10 )] #如果找到的page還沒給過機會則給一次機會，然後將found設為TRUE，chance設為0，如果frame裡面的page的chance都是1，就把chance全設為0，並直接把最早進的page replace掉
    
    checkChance = True #只要有任何一個chance是0就設為False
    for i in range( len( frame ) ):
        if chance[frame[i]] == 0:
            checkChance = False

    if checkChance == True: #chance全部都是1
        for i in range( len( frame ) ): #找最早進的
            if timestamp[frame[i]] <= timestamp[frame[num]] and found[frame[i]] == False: 
                num = i
        for i in range( len( frame ) ): #把所有chance變成0
            chance[frame[i]] = 0
    

    else: #有chance為0
        while 1 == 1:
            for i in range( len( frame ) ):
                if timestamp[frame[i]] <= timestamp[frame[num]] and chance[frame[i]] == 0 and found[frame[i]] == False: 
                    num = i
            if chance[frame[num]] == 1: #給第二次機會
                found[frame[i]] = True #這輪不再找這個page了
                chance[frame[num]] = 0
            else: #沒機會了
                break

    #print( 'NC:', num )
    return num, chance

def FIFO( frameNum, pageRef, frameState ):
    frame = [] #pageframe
    fault = [] #record page fault, 0 == F
    timestamp = [sys.maxsize for i in range(0, 10)] #只有page一開始進入frame時要更新，如果再次reference到不用更新
    for i in range( len( pageRef ) ):
        if pageRef[i] not in frame: #page fault or replace
            if len( frame ) == frameNum : #page replacement, need pop the earliest and insert current page
                frame.pop( findEarlies( frame, timestamp ) )
                frame.insert( 0, pageRef[i] )
                fault.append( 'R' )
            else:  #just page fault
                frame.insert( 0, pageRef[i] )
                fault.append( 'F' )
            timestamp[pageRef[i]] = i #update timestamp
        else: #no page fault
            fault.append( '' )

        #print( 'page:', pageRef[i], 'frame:', frame, 'fault:', fault[i], 'time:', timestamp )  #test print
        frameState.append( frame.copy() )
    
    #print( 'frameState:', frameState )                         #test print
    return frameState, fault

def LRU( frameNum, pageRef, frameState ):
    frame = [] #pageframe
    fault = [] #record page fault, '0 == F'
    timestamp = [sys.maxsize for i in range(0, 10)] #每次page reference到都要更新

    for i in range( len( pageRef ) ):
        if pageRef[i] not in frame: #page fault or replace
            if len( frame ) == frameNum : #page replacement, need pop the earliest and insert current page
                frame.pop( findEarlies( frame, timestamp ) )
                frame.insert( 0, pageRef[i] )
                fault.append( 'R' )
            else:  #just page fault
                frame.insert( 0, pageRef[i] )
                fault.append( 'F' )
            timestamp[pageRef[i]] = i #updata timestamp
        else: #no page fault
            fault.append( '' )
            timestamp[pageRef[i]] = i #updata timestamp


        #print( 'page:', pageRef[i], 'frame:', frame, 'fault:', fault[i], 'time :', timestamp )  #test print
        frameState.append( frame.copy() )
    
    #print( 'frameState:', frameState )                         #test print
    return frameState, fault

def MFU( frameNum, pageRef, frameState ):
    frame = [] #pageframe
    fault = [] #record page fault, '0 == F'
    timestamp = [sys.maxsize for i in range(0, 10)] #每次page reference到都要更新
    freq = [0 for i in range(0, 10)] #record page frequency
    num = 0
    
    for i in range( len( pageRef ) ):
        if pageRef[i] not in frame: #page fault or replace
            if len( frame ) == frameNum : #page replacement, need pop the highest freq page and insert current page, and reset the freq of poped page
                num = findMFreq( frame, timestamp, freq )
                freq[frame[num]] = 0
                frame.pop( num )
                frame.insert( 0, pageRef[i] )
                fault.append( 'R' )
            else:  #just page fault
                frame.insert( 0, pageRef[i] )
                fault.append( 'F' )
            timestamp[pageRef[i]] = i #updata timestamp
            freq[pageRef[i]] += 1     #updata freq
        else: #no page fault
            fault.append( '' )
            timestamp[pageRef[i]] = i #updata timestamp
            freq[pageRef[i]] += 1     #updata freq

        #print( 'page:', pageRef[i], 'frame:', frame, 'fault:', fault[i], 'freq:', freq, 'time:', timestamp )  #test print
        frameState.append( frame.copy() )

    return frameState, fault

def LFU( frameNum, pageRef, frameState ):
    frame = [] #pageframe
    fault = [] #record page fault, '0 == F'
    timestamp = [sys.maxsize for i in range(0, 10)] #每次page reference到都要更新
    freq = [0 for i in range(0, 10)] #record page frequency
    num = 0 #min
    
    for i in range( len( pageRef ) ):
        if pageRef[i] not in frame: #page fault or replace
            if len( frame ) == frameNum : #page replacement, need pop the highest freq page and insert current page, and reset the freq of poped page
                num = findLFreq( frame, timestamp, freq )
                freq[frame[num]] = 0
                frame.pop( num )
                frame.insert( 0, pageRef[i] )
                fault.append( 'R' )
            else:  #just page fault
                frame.insert( 0, pageRef[i] )
                fault.append( 'F' )
            timestamp[pageRef[i]] = i #updata timestamp
            freq[pageRef[i]] += 1     #updata freq
        else: #no page fault
            fault.append( '' )
            timestamp[pageRef[i]] = i #updata timestamp
            freq[pageRef[i]] += 1     #updata freq

        #print( 'page:', pageRef[i], 'frame:', frame, 'fault:', fault[i], 'freq:', freq, 'time:', timestamp )  #test print
        frameState.append( frame.copy() )

    return frameState, fault

def ARB( frameNum, pageRef, frameState ):
    frame = [] #pageframe
    fault = [] #record page fault, '0 == F'
    refBit = [0 for i in range( 0 , 10)] #每個page都給一個reg
    shiftReg = [[0 for i in range( 0, 16 )]for i in range( 0 , 10 )]
    num = 0 #min

    for i in range( len( pageRef ) ):
        if pageRef[i] not in frame: #page fault or replace
            if len( frame ) == frameNum : #page replacement, need pop the highest freq page and insert current page, and reset the freq of poped page
                num = findMinShift( frame, shiftReg )
                shiftReg[frame[num]] = [0 for i in range( 0, 16 )] #reset shiftReg
                refBit[pageRef[i]] = 1 #refBit set to 1
                frame.pop( num )
                frame.insert( 0, pageRef[i] )
                fault.append( 'R' )
            else:  #just page fault
                frame.insert( 0, pageRef[i] )
                fault.append( 'F' )
                refBit[pageRef[i]] = 1 #refBit set to 1

            #refBit right shift to shiftReg
            for j in range( len( refBit ) ):
                shiftReg[j].pop()
                shiftReg[j].insert( 0, refBit[j] )
                refBit[j] = 0
        else: #no page fault
            fault.append( '' )
            refBit[pageRef[i]] = 1 #refBit set to 1
            #refBit right shift to shiftReg
            for j in range( len( refBit ) ):
                shiftReg[j].pop()
                shiftReg[j].insert( 0, refBit[j] )
                refBit[j] = 0

        #print( 'page:', pageRef[i], 'frame:', frame, 'fault:', fault[i], 'shift:', shiftReg )  #test print
        frameState.append( frame.copy() )
    
    return frameState, fault

def SC( frameNum, pageRef, frameState ):
    frame = [] #pageframe
    fault = [] #record page fault, '0 == F'
    timestamp = [sys.maxsize for i in range(0, 10)] #只有page一開始進入frame時要更新，如果再次reference到不用更新
    chance = [0 for i in range( 0, 10 )] #被reference就變為1

    for i in range( len( pageRef ) ):
        if pageRef[i] not in frame: #page fault or replace
            if len( frame ) == frameNum : #page replacement, need pop the earliest and insert current page, after check the chance of the page
                num, chance = findNoChance( frame, chance, timestamp )
                frame.pop( num )
                frame.insert( 0, pageRef[i] )
                fault.append( 'R' )
            else:  #just page fault
                frame.insert( 0, pageRef[i] )
                fault.append( 'F' )
            chance[pageRef[i]] = 1 #update chance
            timestamp[pageRef[i]] = i #update timestamp
        else: #no page fault
            fault.append( '' )
            chance[pageRef[i]] = 1 #update chance

        #print( 'page:', pageRef[i], 'frame:', frame, 'chance:', chance, 'time:', timestamp )  #test print
        frameState.append( frame.copy() )
    
    #print( 'frameState:', frameState )                         #test print
    return frameState, fault

def main():
    frameNum = 0
    pageRef = []
    frameState = [] #紀錄frame狀態
    fault = [] #紀錄page fault

    fileName = input( 'please input the file name: ' )
    frameNum, pageRef = inputTXT( fileName )
    #print( 'Num:', frameNum, 'Ref:', pageRef)                  #test print



    frameState, fault = FIFO( frameNum, pageRef, frameState )
    outputTXT( fileName, 'FIFO', pageRef, frameState, fault, frameNum )

    frameState = []
    fault = []
    frameState, fault = LRU( frameNum, pageRef, frameState )
    outputTXT( fileName, 'LRU', pageRef, frameState, fault, frameNum )

    frameState = []
    fault = []
    frameState, fault = LFU( frameNum, pageRef, frameState )
    outputTXT( fileName, 'LFU', pageRef, frameState, fault, frameNum )

    frameState = []
    fault = []
    frameState, fault = MFU( frameNum, pageRef, frameState )
    outputTXT( fileName, 'MFU', pageRef, frameState, fault, frameNum )

    frameState = []
    fault = []
    frameState, fault = ARB( frameNum, pageRef, frameState )
    outputTXT( fileName, 'ARB', pageRef, frameState, fault, frameNum )

    frameState = []
    fault = []
    frameState, fault = SC( frameNum, pageRef, frameState )
    outputTXT( fileName, 'SC', pageRef, frameState, fault, frameNum )

main()