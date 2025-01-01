def number(A, B):
    str_A = str(A)
    str_B = str(B)


    index_A = 0
    for char in str_B:
        if index_A < len(str_A) and char == str_A[index_A]:
            index_A += 1


    return index_A == len(str_A)


A = int(input("Число A: "))
B = int(input("Число B: "))

if number(A, B):
    print("ДА")
else:
    print("НЕТ")