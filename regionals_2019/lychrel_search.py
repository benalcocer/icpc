# @author Benjamin Alcocer

import sys

def display(count, length):
    if count <= 500:
        print(count, end = " ")
        print(length)
    else:
        print(">500")

for line in sys.stdin:
    line = line.replace('\n','')  # remove end-of-line present in strings read from input
    array = line.split()
    if len(array) != 2:
        break

    palin = []
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
                # Put previous result in Forward list, and build backward list
                # Else convert into correct base
                if len(palin) != 0:
                    forward.clear()
                    backward.clear()
                    for element in palin:
                        forward.insert(0, element)
                        backward.append(element)
                    palin.clear()
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
                result = 0
                carry = 0
                while i >= 0:
                    result = forward[i] + backward[i] + carry - base
                    if result >= 0:
                        palin.insert(0, result)
                        carry = 1
                    else:
                        palin.insert(0, result + base)
                        carry = 0
                    i -= 1
                if carry != 0:
                    palin.insert(0, 1)
                
                # Reverse Potential Palindrome
                arr = []
                for x in palin:
                    arr.append(x)
                
                # Check if Palindrome
                isPalin = True
                k = len(palin) - 1
                digits = k
                for j in range(len(arr)):
                    if arr[j] != palin[k]:
                        isPalin = False
                        break
                    k -= 1

                # Exit if palindrome or count > 500
                count += 1
                if isPalin or count > 500:
                    break
            display(count, len(palin))
sys.exit()
