# @author Benjamin Alcocer

import sys

def display(count, length):
    if count <= 500:
        print(count, end = " ")
        print(length)
    else:
        print(">500")

def isPalindrome(arr1):
    # Reverse
    arr2 = []
    for element in arr1:
        arr2.insert(0, element)
    # Check original with reverse
    for i in range(len(arr1)):
        if arr1[i] != arr2[i]:
            return False
    return True

for line in sys.stdin:
    line = line.replace('\n','')  # remove end-of-line present in strings read from input
    array = line.split()
    if len(array) != 2:
        break

    result = []
    forward = []
    backward = []

    if len(array[1]) == 1:
        print("0 1")
    else:
        orig = int(array[1])
        count = 0

        # If base 10, else do other base arithmetic
        if array[0] == "10":
            reverse = int("".join(reversed(array[1])))
            while orig != reverse:
                if count > 500:
                    break
                count += 1
                orig += reverse
                reverse = int("".join(reversed(str(orig))))
            display(count, len(str(orig)))
        else:
            base = int(array[0])
            while True:
                if count > 500:
                    break
                # Put previous result in Forward list, and build backward list
                # Else convert into correct base
                if len(result) != 0:
                    forward.clear()
                    backward.clear()
                    for element in result:
                        forward.insert(0, element)
                        backward.append(element)
                    result.clear()
                else:
                    backward.append(orig % base)
                    forward.append(orig % base)
                    while orig // base != 0:
                        orig = orig // base
                        value = orig % base
                        backward.append(value)
                        forward.insert(0, value)
                
                # Do bases other than 10 arithmetic
                i = len(forward) - 1
                partialResult = 0
                carry = 0
                while i >= 0:
                    partialResult = forward[i] + backward[i] + carry - base
                    if partialResult >= 0:
                        result.insert(0, partialResult)
                        carry = 1
                    else:
                        result.insert(0, partialResult + base)
                        carry = 0
                    i -= 1
                if carry != 0:
                    result.insert(0, 1)

                # Check if Palindrome
                count += 1
                if isPalindrome(result):
                    break
            display(count, len(result))
sys.exit()
