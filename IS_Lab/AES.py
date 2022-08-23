
inMessage = input("Enter the message: ")
exMessage = inMessage + (16-(len(inMessage)%16)) * "~"

#hardcoded tables

s_box = [
    "63", "7C", "77", "7B", "F2", "6B", "6F", "C5", "30", "01", "67", "2B", "FE", "D7", "AB", "76"
    ,"CA", "82", "C9", "7D", "FA", "59", "47", "F0", "AD", "D4", "A2", "AF", "9C", "A4", "72", "C0"
    ,"B7", "FD", "93", "26", "36", "3F", "F7", "CC", "34", "A5", "E5", "F1", "71", "D8", "31", "15"
    ,"04", "C7", "23", "C3", "18", "96", "05", "9A", "07", "12", "80", "E2", "EB", "27", "B2", "75"
    ,"09", "83", "2C", "1A", "1B", "6E", "5A", "A0", "52", "3B", "D6", "B3", "29", "E3", "2F", "84"
    ,"53", "D1", "00", "ED", "20", "FC", "B1", "5B", "6A", "CB", "BE", "39", "4A", "4C", "58", "CF"
    ,"D0", "EF", "AA", "FB", "43", "4D", "33", "85", "45", "F9", "02", "7F", "50", "3C", "9F", "A8"
    ,"51", "A3", "40", "8F", "92", "9D", "38", "F5", "BC", "B6", "DA", "21", "10", "FF", "F3", "D2"
    ,"CD", "0C", "13", "EC", "5F", "97", "44", "17", "C4", "A7", "7E", "3D", "64", "5D", "19", "73"
    ,"60", "81", "4F", "DC", "22", "2A", "90", "88", "46", "EE", "B8", "14", "DE", "5E", "0B", "DB"
    ,"E0", "32", "3A", "0A", "49", "06", "24", "5C", "C2", "D3", "AC", "62", "91", "95", "E4", "79"
    ,"E7", "C8", "37", "6D", "8D", "D5", "4E", "A9", "6C", "56", "F4", "EA", "65", "7A", "AE", "08"
    ,"BA", "78", "25", "2E", "1C", "A6", "B4", "C6", "E8", "DD", "74", "1F", "4B", "BD", "8B", "8A"
    ,"70", "3E", "B5", "66", "48", "03", "F6", "0E", "61", "35", "57", "B9", "86", "C1", "1D", "9E"
    ,"E1", "F8", "98", "11", "69", "D9", "8E", "94", "9B", "1E", "87", "E9", "CE", "55", "28", "DF"
    ,"8C", "A1", "89", "0D", "BF", "E6", "42", "68", "41", "99", "2D", "0F", "B0", "54", "BB", "16"
]

inv_s_box = [

]

mixCol = [
    "02", "03", "01", "01",
    "01", "02", "03", "01",
    "01", "01", "02", "03",
    "03", "01", "01", "02"
    ]

Rconstant =["01", "02", "04", "08", "10", "20", "40", "80", "1b", "36"]

def rotWord(temp):
    storee = temp[0]
    i=1
    while (i<4):
        temp[i-1] = temp[i]
        if i==3:
            temp[i] = storee
        i+=1

def subWord(temp):
    i=0
    while (i<4):
        temp[i]=sbox[temp[i]]
        i+=1

exKey = ""
def keyExpansion(inKey):
    i=0
    while (i<16):
        exKey[i] = inKey[i]
        i+=1
    while (i<176):
        temp = ""
        j=0
        while (j<4):
            temp[j]=exKey[i-4+j]
            j+=1

        if((i%16)==0):
            rotWord(temp)
            subWord(temp)
            temp[0] ^= Rconstant[(i/16)-1]

        k=0
        while (k<4):
            exKey[i+k]=temp[k]^exKey[i-16+k]
            k+=1
        i+=4

def addRoundKey(state,round):
    i=0
    while (i<16):
         state[i] ^= exKey[round*16+i]
         i+=1


def encryption(exMessage):
    addRoundKey(exMessage,0)
    i=0
    while(i<10):
        subBytes(exMessage)
        shift_rows(exMessage)
        if(i!=9):
            mixColumn(exMessage)
        addRoundKey(exMessage,i)
        i+=1
