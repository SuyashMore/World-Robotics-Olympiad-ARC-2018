from block_recognition import BlockRecognition
from block_recognition2 import BlockRecognition2
ID =1
#Z6 I4 O1 J3 S5 L2
Lxx1=[3000,3000,3000,3000,3000,2000]
Lxx2=[1500,1900,1000,1300,700,1200]
Lxx3=[400,700,400,600,300,1000]
Lxx4=[3000,3000,1000,3000,1300,2000]

br1 = BlockRecognition(ID,l1=230, l2=480, l3=300, l4=640, Lxx=Lxx1)
br2 = BlockRecognition(ID,l1=170, l2=250, l3=200, l4=400, Lxx=Lxx2)
br3 = BlockRecognition(ID,l1=50, l2=170, l3=250, l4=400, Lxx=Lxx3)

# br4 = BlockRecognition2(ID,l1=0, l2=480, l3=0, l4=640, Lxx=Lxx4)
# def give_all_letters():
#     global br4


def give_one_letter():
    global br1
    global br2
    global br3
    brr1=br1.run()
    brr2=br2.run()
    brr3=br3.run()
    max =0
    key =0
    for x, y in brr1.items():
        if y > max:
            key=x
            max=y
    key2 = 0
    max = 0
    for x, y in brr2.items():
        if y > max:
            key2=x
            max=y
    key3=0
    max=0
    for x,y in brr3.items():
        if y > max:
            key3=x
            max=y

    if key == 'Z':
        key = 1
    elif key == 'I':
        key = 2

    elif key == 'S':
        key = 3
    elif key == 'O':
        key = 4
    elif key == 'J':
        key = 5
    elif key == 'L':
        key = 6


    if key2 == 'Z':
        key2 = 1
    elif key2 == 'I':
        key2 = 2
    elif key2 == 'S':
        key2 = 3
    elif key2 == 'O':
        key2 = 4
    elif key2 == 'J':
        key2 = 5
    elif key2 == 'L':
        key2 = 6

    if key3 == 'Z':
        key3 = 1
    elif key3 == 'I':
        key3 = 2
    elif key3 == 'S':
        key3 = 3
    elif key3 == 'O':
        key3 = 4
    elif key3 == 'J':
        key3 = 5
    elif key3 == 'L':
        key3 = 6
    print("Supply 1:", key)
    print("Supply 2:", key2)
    print("Judge Piece:", key3)
    return key,key2,key3

if __name__=="__main__":
    while True:
            give_one_letter()

# O1 L2 J3 I4 S5 Z6
# Lxx4=[3000,3000,1000,3000,1300,2000]

# br4 = BlockRecognition2(camera_id=config.CAMERA_ID, optimal_fps=config.FPS,l1=0, l2=480, l3=0, l4=640, Lxx=Lxx4)

# brr4, Str=br4.run()

# n1=calc_digit(give_one_letter(brr1))
# n2=calc_digit(give_one_letter(brr2))
# n3=calc_digit(give_one_letter(brr3))

# n4=calc_digit(Str[0])
# n5=calc_digit(Str[0])
# n6=calc_digit(Str[0])

# N1=n1*100+n2*10+n3
# N2=n4*100+n5*10+n6

# print("1111111111111",N1)
# print("2222222222222",N2)
# #

# Select a point and perform inverse based on arm design