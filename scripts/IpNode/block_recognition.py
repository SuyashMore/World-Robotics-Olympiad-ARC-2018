import numpy as np
import cv2 as cv
ID=0
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
        LOWER_YELLOW = np.array([18.0, 176.0, 29.0])     #[21.0, 126.0, 0.0]
        UPPER_YELLOW = np.array([26.0, 256.0, 309.0])   #[29.0, 226.0, 234.0]
        LOWER_BLUE = np.array([95.0, 41.0, 110.0])          #[95.0, 80.0, 9.0]
        UPPER_BLUE = np.array([103.0, 121.0, 390.0])       #[103.0, 140.0, 229.0]
        LOWER_ORANGE = np.array([37.0, 162.0, -17.0])  #  [11.0, 110.0, 115.0]
        UPPER_ORANGE = np.array([45.0, 242.0, 263.0]) # #[19.0, 190.0, 395.0]
        LOWER_GREEN = np.array([46.0, 121.0, 4.0])  #[40.0, 160.0, 49.0])
        UPPER_GREEN = np.array([48.0, 281.0, 216.0])#[47.0, 260.0, 199.0])
        LOWER_VIOLET = np.array([109.0, 55.0, -15.0])#[108.0, 6.0, 17.0]) #
        UPPER_VIOLET = np.array([117.0, 135.0, 265.0]) #[116.0, 166.0, 237.0])   #

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

            print(dic2,dic)

            cv.putText(img, text, (width - 120, height - 24), cv.FONT_HERSHEY_DUPLEX, 2, color, 2, cv.LINE_AA)
            return img,dic2


        # Function to find any contour and count its corners


        # Capturing the video feed

        vid = cv.VideoCapture(ID)

        while True:
            _, frame = vid.read()
            # Blurring the frame to be ready for color filtering and edge detection
            original = frame
            # cv.imshow("Plain",original)
            # height    width
            part1 = original[self.li1:self.li2, self.li3:self.li4]
            # part1 = original[120:310, 100:380]
            #cv.imshow("Part1",part1)
            original=part1
            frame=part1
            cv.imshow("Part1",part1)
            # part2 = original[310:480, 100:400]
            # cv.imshow("Part2", part2)
            # part3 = original[0:120, 100:380]
            # cv.imshow("Part3", part3)
            #frame = cv.undistort(frame, cameraMatrix=config.cameraMatrix, distCoeffs=config.distortionCoeffs, dst=None, newCameraMatrix=None)
            frame = cv.GaussianBlur(frame, (25, 25), 2)


            # Converting the colors from RGB to HSV
            hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)


            #Yellow
            mask_yellow = cv.inRange(hsv, LOWER_YELLOW, UPPER_YELLOW)
            mask_yellow = cv.erode(mask_yellow, np.ones((5, 5), np.uint8), 3)
            mask_yellow = cv.dilate(mask_yellow, np.ones((3, 3), np.uint8), 1)
            #cv.imshow("Yellow", mask_yellow)

            #Blue
            mask_blue = cv.inRange(hsv, LOWER_BLUE, UPPER_BLUE)
            mask_blue = cv.erode(mask_blue, np.ones((5, 5), np.uint8), 3)
            mask_blue = cv.dilate(mask_blue, np.ones((3, 3), np.uint8), 1)
            cv.imshow("Blue", mask_blue)

            #Red
            mask_red = cv.inRange(hsv, LOWER_RED, UPPER_RED)
            mask_red = cv.erode(mask_red, np.ones((5, 5), np.uint8), 3)
            mask_red = cv.dilate(mask_red, np.ones((3, 3), np.uint8), 1)
            #cv.imshow("Red", mask_red)

            #Orange
            mask_orange = cv.inRange(hsv, LOWER_ORANGE, UPPER_ORANGE)
            mask_orange = cv.erode(mask_orange, np.ones((5, 5), np.uint8), 3)
            mask_orange = cv.dilate(mask_orange, np.ones((3, 3), np.uint8), 1)
            #cv.imshow("Orange", mask_orange)

            #Green
            mask_green = cv.inRange(hsv, LOWER_GREEN, UPPER_GREEN)
            mask_green = cv.erode(mask_green, np.ones((5, 5), np.uint8), 3)
            mask_green = cv.dilate(mask_green, np.ones((3, 3), np.uint8), 1)
            #cv.imshow("Green", mask_green)

            #Violet
            mask_violet = cv.inRange(hsv, LOWER_VIOLET, UPPER_VIOLET)
            mask_violet = cv.erode(mask_violet, np.ones((5, 5), np.uint8), 3)
            mask_violet = cv.dilate(mask_violet, np.ones((3, 3), np.uint8), 1)
            #cv.imshow("Green", mask_green)

            # imstack = np.hstack(imstack,mask_yellow )
            # imstack = np.hstack(imstack, mask_blue  )
            # imstack = np.hstack(imstack, mask_violet)
            # imstack = np.hstack(imstack, mask_green )
            # imstack = np.hstack(imstack, mask_orange)
            # imstack = np.hstack(imstack, mask_red   )
            #
            # cv.imshow("stack",imstack)

            dic3['O'] = np.sum(mask_yellow == 255)
            dic3['I'] = np.sum(mask_blue == 255)
            dic3['J'] = np.sum(mask_violet == 255)
            dic3['Z'] = np.sum(mask_red == 255)
            dic3['S'] = np.sum(mask_green == 255)
            dic3['L'] = np.sum(mask_orange == 255)

            # Drawing the result on the original image
            original,dicx = drawResult(RED,original.copy())
            original,dicx = drawResult(YELLOW,original.copy())
            original,dicx = drawResult(BLUE,original.copy())
            original,dicx = drawResult(GREEN,original.copy())
            original,dicx = drawResult(ORANGE,original.copy())
            original,dicx = drawResult(VIOLET,original.copy())
            # print("iterations:",dicx)
            # cv.imshow('Original', original)

            if cv.waitKey(1) & 0xff == ord('q'):
                break
            for key,value in dicx.items():
                # print(value)
                if value>40:
                    q=1
                    break
            if q==1:
                break
        return dicx

        vid.release()
        cv.destroyAllWindows()
