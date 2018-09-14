import numpy as np
import cv2 as cv
ID=1
L=[]
dic={4:0, 6:0, 8:0}
dic2={'I':0, 'L':0, 'J':0, 'O':0, 'Z':0, 'S':0}
dic3={'I':0, 'L':0, 'J':0, 'O':0, 'Z':0, 'S':0}
class BlockRecognition:

    def __init__(self,ID,l1,l2,l3,l4, Lxx):
        self.ID=ID
        self.li1=l1
        self.li2 = l2
        self.li3 = l3
        self.li4 = l4
        self.Lxxe6=Lxx[5]
        self.Lxxe1 = Lxx[0]
        self.Lxxe2 = Lxx[1]
        self.Lxxe3 = Lxx[2]
        self.Lxxe4 = Lxx[3]
        self.Lxxe5 = Lxx[4]

    def run(self):
        q=0
        dic2 = {'I': 0, 'L': 0, 'J': 0, 'O': 0, 'Z': 0, 'S': 0}
        # Defining some global values
        RED = (0, 0, 255)
        YELLOW = (20, 210, 208)     # 37.244 26.828 118.232250  #37,27,118 # 27,17,70 # 47,37,168
        BLUE = (255, 0, 0)
        GREEN = (76, 177, 34)
        ORANGE = (39, 127, 255)
        VIOLET = (63, 2, 7)

        # Defining the lower and upper limits for the 3 colors upon calibration
        LOWER_RED = np.array([1.0, 175.0, -4.0]) #  [0.0, 170.0, 61.0]
        UPPER_RED = np.array([7.0, 255.0, 256.0])   #  [5.0, 230.0, 311.0]
        LOWER_YELLOW = np.array([20.0, 178.0, 59.0])     #[21.0, 126.0, 0.0]
        UPPER_YELLOW = np.array([26.0, 258.0, 279.0])   #[29.0, 226.0, 234.0]
        LOWER_BLUE = np.array([91.0, 73.0, 48.0])          #[95.0, 80.0, 9.0]
        UPPER_BLUE = np.array([99.0, 153.0, 328.0])       #[103.0, 140.0, 229.0]
        LOWER_ORANGE = np.array([6.0, 166.0, 84.0])   #  [5.0, 148.0, 66.0]
        UPPER_ORANGE = np.array([12.0, 246.0, 344.0]) # #[11.0, 228.0, 326.0]
        LOWER_GREEN = np.array([46.0, 121.0, 4.0])#[40.0, 160.0, 49.0])
        UPPER_GREEN = np.array([48.0, 281.0, 216.0])#[47.0, 260.0, 199.0])
        LOWER_PURPLE = np.array([140, 100, 100])
        UPPER_PURPLE = np.array([160, 255, 255])
        LOWER_VIOLET = np.array([111.0, 66.0, -53.5])#[108.0, 6.0, 17.0]) #
        UPPER_VIOLET = np.array([117.0, 186.0, 206.5])#[116.0, 166.0, 237.0])   #

        def drawResult(color, img):

            height, width, _ = img.shape
            text = ""
            # print("dic33333333333",dic3['S'])
            if color==YELLOW and dic3['O']>self.Lxxe1:
                dic2['O']=dic2['O']+1
                text="O"
            elif color==ORANGE and dic3['L']>self.Lxxe2:
                dic2['L']=dic2['L']+1
                text="L"
            elif color==VIOLET and dic3['J']>self.Lxxe3:
                dic2['J']=dic2['J']+1
                text="J"
                # print("dic3: ",dic3)
            elif color==BLUE and dic3['I']>self.Lxxe4:
                dic2['I']=dic2['I']+1
                text="I"
            elif color==RED and dic3['Z']>self.Lxxe6:
                dic2['Z']=dic2['Z']+1
                text="Z"
            if color==GREEN and dic3['S']>self.Lxxe5:
                dic2['S']=dic2['S']+1
                text="S"
            # if dic2['I']==50 or dic2['J']==50 or dic2['L']==50 or dic2['O']==50 or dic2['S']==50 or dic2['Z']==50:
            #     print(time.time()-start)
            #     sys.exit()

            # print(dic2,dic)

            cv.putText(img, text, (width - 120, height - 24), cv.FONT_HERSHEY_DUPLEX, 2, color, 2, cv.LINE_AA)
            return img,dic2

        # Function to find any contour and count its corners


        # Capturing the video feed

        vid = cv.VideoCapture(ID)

        while True:
            _, frame = vid.read()
            # Blurring the frame to be ready for color filtering and edge detection
            original = frame
            cv.imshow("Plain",original)
            # height    width
            part1 = original[self.li1:self.li2, self.li3:self.li4]
            # part1 = original[120:310, 100:380]
            #cv.imshow("Part1",part1)
            original=part1
            frame=part1
            # part2 = original[310:480, 100:400]
            # cv.imshow("Part2", part2)
            # part3 = original[0:120, 100:380]
            # cv.imshow("Part3", part3)
            #frame = cv.undistort(frame, cameraMatrix=config.cameraMatrix, distCoeffs=config.distortionCoeffs, dst=None, newCameraMatrix=None)
            
            # frame = cv.dilate(frame, np.ones((15, 15), np.uint8))
            # frame = cv.erode(frame, np.ones((15, 15), np.uint8))

            # Converting the colors from RGB to HSV
            hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
            frame = cv.GaussianBlur(hsv, (25, 25), 2)
            #Yellow
            hsvY = cv.cvtColor(original, cv.COLOR_BGR2HSV)
            hsvY = cv.GaussianBlur(hsvY, (15, 15), 2)
            mask_yellow = cv.inRange(hsvY, LOWER_YELLOW, UPPER_YELLOW)
            #cv.imshow("Yellow", mask_yellow)

            #Blue
            # hsvB = cv.cvtColor(original, cv.COLOR_BGR2HSV)
            # hsvB = cv.GaussianBlur(hsvB, (15, 15), 2)
            # hsvB = cv.dilate(hsvB, np.ones((15, 15), np.uint8), 5)
            # hsvB = cv.erode(hsvB, np.ones((5, 5), np.uint8), 3)
            # mask_blue = cv.inRange(hsvB, LOWER_BLUE, UPPER_BLUE)
            # #cv.imshow("Blue", mask_blue)

            # #Red
            # hsvR = cv.cvtColor(original, cv.COLOR_BGR2HSV)
            # hsvR = cv.GaussianBlur(hsvR, (15, 15), 1)
            # hsvR = cv.dilate(hsvR, np.ones((5, 5), np.uint8), 5)
            # hsvR = cv.erode(hsvR, np.ones((8, 8), np.uint8), 2)
            # mask_red = cv.inRange(hsvR, LOWER_RED, UPPER_RED)
            # #cv.imshow("Red", mask_red)

            # #Orange
            # hsvO = cv.cvtColor(original, cv.COLOR_BGR2HSV)
            # hsvO = cv.GaussianBlur(hsvO, (15, 15), 1)
            # hsvO = cv.dilate(hsvO, np.ones((3, 3), np.uint8), 1)
            # hsvO = cv.erode(hsvO, np.ones((3, 3), np.uint8), 3)
            # mask_orange = cv.inRange(hsvO, LOWER_ORANGE, UPPER_ORANGE)
            # #cv.imshow("Orange", mask_orange)

            # #Green
            # hsvG = cv.cvtColor(original, cv.COLOR_BGR2HSV)
            # hsvG = cv.GaussianBlur(hsvG, (15, 15), 1)
            # hsvG = cv.dilate(hsvG, np.ones((15, 15), np.uint8), 5)
            # hsvG = cv.erode(hsvG, np.ones((16, 16), np.uint8), 1)
            # mask_green = cv.inRange(hsvG, LOWER_GREEN, UPPER_GREEN)
            # #cv.imshow("Green", mask_green)

            # #Violet
            # hsvV = cv.cvtColor(original, cv.COLOR_BGR2HSV)
            # hsvV = cv.GaussianBlur(hsvV, (15, 15), 1)
            # hsvV = cv.dilate(hsvV, np.ones((15, 15), np.uint8), 5)
            # hsvV = cv.erode(hsvV, np.ones((16, 16), np.uint8), 1)
            # mask_violet = cv.inRange(hsvV, LOWER_VIOLET, UPPER_VIOLET)
            # #cv.imshow("Green", mask_green)

            # # imstack = np.hstack(imstack,mask_yellow )
            # # imstack = np.hstack(imstack, mask_blue  )
            # # imstack = np.hstack(imstack, mask_violet)
            # # imstack = np.hstack(imstack, mask_green )
            # # imstack = np.hstack(imstack, mask_orange)
            # # imstack = np.hstack(imstack, mask_red   )
            # #
            # # cv.imshow("stack",imstack)

            # dic3['O'] = np.sum(mask_yellow == 255)
            # dic3['I'] = np.sum(mask_blue == 255)
            # dic3['J'] = np.sum(mask_violet == 255)
            # dic3['Z'] = np.sum(mask_red == 255)
            # dic3['S'] = np.sum(mask_green == 255)
            # dic3['L'] = np.sum(mask_orange == 255)

            # # Drawing the result on the original image
            # original,dicx = drawResult(RED   ,original.copy())
            # original,dicx = drawResult(YELLOW,original.copy())
            # original,dicx = drawResult(BLUE  ,original.copy())
            # original,dicx = drawResult(GREEN ,original.copy())
            # original,dicx = drawResult(ORANGE,original.copy())
            # original,dicx = drawResult(VIOLET,original.copy())
            # print("dddddddddddddddddddddddddddd",dicx)
            # cv.imshow('Original', original)

            cv.imshow("part1",part1)
            cv.imshow("yellow",mask_yellow)

            if cv.waitKey(1) & 0xff == ord('q'):
                break
            # for key,value in dicx.items():
                # print(value)
                if value>150:
                    q=1
                    break
            if q==1:
                break
        # D={'I':CenteresBlue[0], 'S':CenteresGreen[0], 'L':CenteresOrange[0], 'Z':CenteresRed[0], 'J':CenteresViolet[0], 'O':CenteresYellow[0]}
        # sortDic = sorted(D.items())
        # Stri=''
        # for key,values in sortDic:
        #     Stri=Stri+str(key)
        # print(Stri)
        # return dicx

        vid.release()
        cv.destroyAllWindows()
