# @author Benjamin Alcocer

import sys

def display(count, length):
    print('{} {}'.format(count, length) if count <= 500 else '>500')

def isPalindrome(arr1):
    # Check original with reverse
    i = 0
    j = len(arr1) - 1
    while i < j:
        if arr1[i] != arr1[j]:
            return False
        j -= 1
        i += 1
    return True

for line in sys.stdin:
    array = line.replace('\n','').split()  # remove end-of-line present in strings read from input

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
            backward = []
            base = int(array[0])
            while count <= 500:
                count += 1
                if len(backward) == 0:
                    backward.append(orig % base)
                    while orig // base != 0:
                        orig = orig // base
                        value = orig % base
                        backward.append(value)

                # Do bases other than 10 arithmetic
                size = len(backward) - 1
                i = size
                partialResult = 0
                carry = False
                result = [0] * len(backward)
                while i >= 0:
                    partialResult = backward[i] + backward[size - i] + carry
                    carry = partialResult // base
                    result[i] = partialResult % base
                    i -= 1
                if carry:
                    result.insert(0, 1)

                # Check if Palindrome
                if isPalindrome(result):
                    break
                backward = result
            display(count, len(result))
