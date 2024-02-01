# Compression script made by Virgile (Lipatant) Berrier

def displayData(char, count = int):
    print(char,end="")
    if count == 1:
        print("!",end="")
    else:
        if count < 10:
            print("000",end="")
        elif count < 100:
            print("00",end="")
        elif count < 1000:
            print("0",end="")
        print(count,end="")

def getCharacter(c):
    if (c == 'M'):
        return 'D'
    if ('a' <= c and c <= 'z'):
        return 'C'
    if (('A' <= c and c <= 'Z') or ('0' <= c and c <= '9') or c == '@'):
        return 'B'
    return 'A'

def displayFile(filepath = str):
    file = open(filepath, 'r')

    charCurrent = None
    charCurrentCount = 0

    while True:
        # Read Line
        line = file.readline()
        # Break
        if not line:
            break
        # Combine
        i = 0
        length = len(line) - 1
        while i < length:
            char = getCharacter(line[i])
            if charCurrent == char:
                charCurrentCount += 1
            else:
                if charCurrent != None:
                    displayData(charCurrent, charCurrentCount)
                charCurrent = char
                charCurrentCount = 1
            i += 1

    if charCurrent != None and charCurrent != 'A':
        displayData(charCurrent, charCurrentCount)
        charCurrent = char
        charCurrentCount = 1

    print("")

    file.close()

for i in range(1, 6569 + 1):
    displayFile('BA' + str(i) + '.txt')
