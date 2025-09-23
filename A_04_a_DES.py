# Assignment No: 04
# Implementation of Standard Symmetric Block Ciphers 
# a) Data Encryption Standard (DES)
# b) Triple DES
# c) Advance Encryption Standard (AES)

# Data Encryption Standard (DES)
def binToDec(bin):
    binToDecDict = {
        "0" : 0,
        "1" : 1,

        "00" : 0,
        "01" : 1,
        "10" : 2,
        "11" : 3,

        "000" : 0,
        "001" : 1,
        "010" : 2,
        "011" : 3,
        "100" : 4,
        "101" : 5,
        "110" : 6,
        "111" : 7,

        "0000" : 0,
        "0001" : 1,
        "0010" : 2,
        "0011" : 3,
        "0100" : 4,
        "0101" : 5,
        "0110" : 6,
        "0111" : 7,
        "1000" : 8,
        "1001" : 9,
        "1010" : 10,
        "1011" : 11,
        "1100" : 12,
        "1101" : 13,
        "1110" : 14,
        "1111" : 15,
    }

    return binToDecDict[bin]

def decToBin(dec):
    decToBinDict = {
        0 : "0000",
        1 : "0001",
        2 : "0010",
        3 : "0011",
        4 : "0100",
        5 : "0101",
        6 : "0110",
        7 : "0111",
        8 : "1000",
        9 : "1001",
        10 : "1010",
        11 : "1011",
        12 : "1100",
        13 : "1101",
        14 : "1110",
        15 : "1111",
    }

    return decToBinDict[dec]

def binToHex(bin):
    binToHexDict = {
        "0000": '0',
        "0001": '1',
        "0010": '2',
        "0011": '3',
        "0100": '4',
        "0101": '5',
        "0110": '6',
        "0111": '7',
        "1000": '8',
        "1001": '9',
        "1010": 'A',
        "1011": 'B',
        "1100": 'C',
        "1101": 'D',
        "1110": 'E',
        "1111": 'F'}
    
    hex = ""
    
    for i in range(0, len(bin), 4):
        ch = ""
        ch = ch + str(bin[i])
        ch = ch + str(bin[i + 1])
        ch = ch + str(bin[i + 2])
        ch = ch + str(bin[i + 3])
        hex = hex + binToHexDict[ch]
 
    return hex

def hexToBin(hex):
    hexToBinDict = {
        '0': "0000",
        '1': "0001",
        '2': "0010",
        '3': "0011",
        '4': "0100",
        '5': "0101",
        '6': "0110",
        '7': "0111",
        '8': "1000",
        '9': "1001",
        'A': "1010",
        'B': "1011",
        'C': "1100",
        'D': "1101",
        'E': "1110",
        'F': "1111"}
    
    bin = list()
    for i in range(len(hex)):
        for j in hexToBinDict[hex[i]]:
            bin.append(int(j))
    return bin

def parityDrop(key):
    parityDropTable = [
        57, 49, 41, 33, 25, 17, 9, 1,
        58, 50, 42, 34, 26, 18, 10, 2,
        59, 51, 43, 35, 27, 19, 11, 3,
        60, 52, 44, 36, 63, 55, 47, 39,
        31, 23, 15, 7, 62, 54, 46, 38,
        30, 22, 14, 6, 61, 53, 45, 37,
        29, 21, 13, 5, 28, 20, 12, 4
    ]

    op = [0] * len(parityDropTable)

    for i in range(len(parityDropTable)):
        op[i] = key[parityDropTable[i] - 1]

    return op

def shiftLeft(ip):
    temp = ip[0]
    ip.pop(0)
    op = ip + [temp]
    return op

def compressionPBox(ip):
    compressionPBoxTable = [
        14, 17, 11, 24, 1, 5, 3, 28,
        15, 6, 21, 10, 23, 19, 12, 4,
        26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56,
        34, 53, 46, 42, 50, 36, 29, 32,
    ] 

    op = [0] * len(compressionPBoxTable)

    for i in range(len(compressionPBoxTable)):
        op[i] = ip[compressionPBoxTable[i] - 1]

    return op

def generateRoundKey(key):
    op = list()

    parityDropOutput = parityDrop(key)

    leftHalf = parityDropOutput[0:28]
    rightHalf = parityDropOutput[28:56]

    for i in range(16):
        if(i == 0 or i == 1 or i == 8 or i == 15):
            leftHalf = shiftLeft(leftHalf)
            rightHalf = shiftLeft(rightHalf)
        else:
            leftHalf = shiftLeft(leftHalf)
            leftHalf = shiftLeft(leftHalf)
            rightHalf = shiftLeft(rightHalf)
            rightHalf = shiftLeft(rightHalf)

        compressionPBoxOutput = compressionPBox(leftHalf+rightHalf)
        op.append(compressionPBoxOutput)

    return op
 
def initialPermutationBox(ip):
    initialPermutationBoxTable = [
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
    ]

    op = [0] * len(initialPermutationBoxTable)

    for i in range(len(initialPermutationBoxTable)):
        op[i] = ip[initialPermutationBoxTable[i] - 1]

    return op

def expansionPBox(ip):
    expansionPBoxTable = [
        32, 1, 2, 3, 4, 5, 4, 5,
        6, 7, 8, 9, 8, 9, 10, 11,
        12, 13, 12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21, 20, 21,
        22, 23, 24, 25, 24, 25, 26, 27,
        28, 29, 28, 29, 30, 31, 32, 1
    ]

    op = [0] * len(expansionPBoxTable)

    for i in range(len(expansionPBoxTable)):
        op[i] = ip[expansionPBoxTable[i] - 1]

    return op

def XOR(ipA, ipB):
    op = [0] * len(ipA)
    for i in range(len(op)):
        op[i] = ipA[i] ^ ipB[i]

    return op

def sBox(ip, sBoxNo):
    sbox = [
        [
            [14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7],
            [0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8],
            [4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0],
            [15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13]
        ],
 
        [
            [15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10],
            [3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5],
            [0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15],
            [13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9]],
 
        [
            [10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8],
            [13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1],
            [13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7],
            [1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12]
        ],
 
        [
            [7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15],
            [13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9],
            [10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4],
            [3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14]
        ],
 
        [   
            [2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9],
            [14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6],
            [4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14],
            [11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3]
        ],
 
        [
            [12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11],
            [10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8],
            [9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6],
            [4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13]
        ],
 
        [
            [4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1],
            [13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6],
            [1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2],
            [6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12]
        ],
 
        [
            [13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7],
            [1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2],
            [7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8],
            [2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11]
        ]
    ]

    row = str(ip[0]) + str(ip[5])
    col = str(ip[1]) + str(ip[2]) + str(ip[3]) + str(ip[4])
    element = decToBin(sbox[sBoxNo][binToDec(row)][binToDec(col)])

    op = list()
    for i in element:
        op.append(int(i))

    return op

def straightPBox(ip):
    straightPBoxTable = [
        16, 7, 20, 21, 29, 12, 28, 17,
        1, 15, 23, 26, 5, 18, 31, 10,
        2, 8, 24, 14, 32, 27, 3, 9,
        19, 13, 30, 6, 22, 11, 4, 25
    ]
    
    op = [0] * len(straightPBoxTable)

    for i in range(len(straightPBoxTable)):
        op[i] = ip[straightPBoxTable[i] - 1]

    return op

def finalPermutationBox(ip):
    finalPermutationBoxTable = [
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25
    ]

    op = [0] * len(finalPermutationBoxTable)

    for i in range(len(finalPermutationBoxTable)):
        op[i] = ip[finalPermutationBoxTable[i] - 1]

    return op

def round(ip, roundKey):
    leftHalf = ip[0:32]
    rightHalf = ip[32:64]

    expandedRightHalf = expansionPBox(rightHalf)

    xoredOutput = XOR(expandedRightHalf, roundKey)
    
    j = 0
    sBoxOutput = []
    for i in range(0, 48, 6):
        sBoxOutput += sBox(xoredOutput[i:i+6], j)
        j+=1

    straightPBoxOutput = straightPBox(sBoxOutput)

    op = rightHalf + XOR(leftHalf, straightPBoxOutput)
    
    return op

def desEncryption(plaintext, key):
    roundKey = generateRoundKey(key)

    initialPermutationBoxOutput = initialPermutationBox(plaintext)
    
    roundOutput = initialPermutationBoxOutput
    for i in range(16):
        roundOutput = round(roundOutput, roundKey[i])

    finalPermutationBoxInput = roundOutput[32:64]+roundOutput[0:32]
    finalPermutationBoxOutput = finalPermutationBox(finalPermutationBoxInput)
    return finalPermutationBoxOutput

def desDecryption(ciphertext, key):
    roundKey = generateRoundKey(key)

    initialPermutationBoxOutput = initialPermutationBox(ciphertext)
    
    roundOutput = initialPermutationBoxOutput
    for i in range(15, -1, -1):
        roundOutput = round(roundOutput, roundKey[i])

    finalPermutationBoxInput = roundOutput[32:64]+roundOutput[0:32]
    finalPermutationBoxOutput = finalPermutationBox(finalPermutationBoxInput)
    return finalPermutationBoxOutput

if __name__ == "__main__":
    plaintext = "ABCD132536654321"
    plaintext = hexToBin(plaintext)

    key = "4133957999BDCCF9"
    key = hexToBin(key)

    print("Plaintext:", binToHex(plaintext), "Key:", binToHex(key))
    print()

    ciphertext = desEncryption(plaintext, key)

    print("Encryption:")
    print("Ciphertext:", binToHex(ciphertext))
    print()
    print("Decryption: ")
    print("Plaintext:", binToHex(desDecryption(ciphertext, key)), "\n")