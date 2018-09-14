import numpy as np
import cv2 as cv

Letters=[]

dic={4:0, 6:0, 8:0}
dic2={'I':0, 'L':0, 'J':0, 'O':0, 'Z':0, 'S':0}
dic3={'I':0, 'L':0, 'J':0, 'O':0, 'Z':0, 'S':0}
class BlockRecognition2:

    def __init__(self,ID,l1,l2,l3,l4, Lxx):
        self.camera_id = ID
        self.fps = optimal_fps

        self.li1 = l1
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
        LOWER_RED = np.array([1.0, 180.0, 25.0])
        UPPER_RED = np.array([4.0, 260.0, 225.0])
        LOWER_YELLOW = np.array([21.0, 126.0, 0.0])#[20.0, 167.0, 122.0]
        UPPER_YELLOW = np.array([29.0, 226.0, 234.0])#[24.0, 267.0, 262.0]
        LOWER_BLUE = np.array([95.0, 80.0, 9.0])
        UPPER_BLUE = np.array([103.0, 140.0, 229.0])
        LOWER_ORANGE = np.array([8.0, 143.0, 59.0])
        UPPER_ORANGE = np.array([10.0, 223.0, 309.0])
        LOWER_GREEN = np.array([45.0, 95.0, 110.0])#[40.0, 160.0, 49.0])
        UPPER_GREEN = np.array([51.0, 215.0, 350.0])#[47.0, 260.0, 199.0])
        LOWER_PURPLE = np.array([140, 100, 100])
        UPPER_PURPLE = np.array([160, 255, 255])
        LOWER_VIOLET = np.array([111.0, 50.0, -52.0])#[108.0, 0.0, 40.0])
        UPPER_VIOLET = np.array([117.0, 170.0, 188.0])#[118.0, 172.0, 180.0])

        def get_everything(frame, edge):
            image, contours, hierarchy = cv.findContours(edge, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
            approx = []
            maxI = 0
            maxArea1 = 0
            smallest_x = 640
            maxArea2 = 0
            Centers = [[], []]
            MaxContours = []
            c1 = []
            c2 = []
            Num = len(contours)
            for i in range(len(contours)):
                area = cv.contourArea(contours[i])
                # epsilon = 0.01 * cv.arcLength(contours[i], True)
                # approx = cv.approxPolyDP(contours[i], epsilon, True)
                if area > maxArea1 and area > 2000:
                    maxArea2 = maxArea1
                    maxArea1 = area
                    c1 = contours[i]
                # less than maxArea1
                elif area > maxArea2 and area > 2000:
                    maxArea2 = area
                    c2 = contours[i]

                #img = cv.drawContours(mask2, contours, maxI, (0, 255, 0), 5)
                # cv.line(frame, (smallest_x, 0), (smallest_x, 480), (0, 0, 255), thickness=3)
            MaxContours.append(c1)
            MaxContours.append(c2)


            for i in range(len(MaxContours)):
                cnt = MaxContours[i]
                # print(cnt)

                try:
                    M = cv.moments(cnt)
                    cX = int(M["m10"] / M["m00"])
                    cY = int(M["m01"] / M["m00"])

                    cv.circle(frame, (cX, cY), 7, (238, 130, 238), -1)
                    Centers[i] = [cX, cY]
                except ZeroDivisionError:
                    # print("00000000000000000000000000000000000000000000000000000000000000000000000000")
                    pass
                except TypeError:
                    # print("Typeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee")
                    pass
            if not c2:
                Num -=1
                if Centers[0][1] > Centers[1][1]:
                    Centers.pop(1)

                elif Centers[0][1]< Centers[1][1]:
                    Centers.pop(0)

            return frame, Centers,Num

        def drawResult(color, img):

            height, width, _ = img.shape
            text = ""
            print("dic33333333333",dic3['S'])
            if color==YELLOW and dic3['O']>self.Lxxe1:
                dic2['O']=dic2['O']+1
                text="O"
            elif color==ORANGE and dic3['L']>self.Lxxe2:
                dic2['L']=dic2['L']+1
                text="L"
            elif color==VIOLET and dic3['J']>self.Lxxe3:
                dic2['J']=dic2['J']+1
                text="J"
                print("dic3: ",dic3)
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

        vid = cv.VideoCapture(2)

        while True:
            _, frame = vid.read()
            repeat = None
            Stri = ''
            Strirepeat = ''

#            #print(frame.shape)

            # Blurring the frame to be ready for color filtering and edge detection
            original = frame
            original_main=original
            #cv.imshow("Plane",original)
            # height    width

            original= original[150:350, 0:640]
            # cv.imshow("Part2", part2)
            # part3 = original[0:120, 100:380]
            # cv.imshow("Part3", part3)
            #frame = cv.undistort(frame, cameraMatrix=config.cameraMatrix, distCoeffs=config.distortionCoeffs, dst=None, newCameraMatrix=None)
            frame = cv.GaussianBlur(frame, (25, 25), 2)
            # frame = cv.dilate(frame, np.ones((15, 15), np.uint8),2)
            # frame = cv.erode(frame, np.ones((15, 15), np.uint8),3)

            # Converting the colors from RGB to HSV
            # hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)

            #Yellow
            hsvY = cv.cvtColor(original, cv.COLOR_BGR2HSV)
            hsvY = cv.GaussianBlur(hsvY, (15, 15), 2)
            mask_yellow = cv.inRange(hsvY, LOWER_YELLOW, UPPER_YELLOW)

            #Blue
            hsvB = cv.cvtColor(original, cv.COLOR_BGR2HSV)
            hsvB = cv.GaussianBlur(hsvB, (15, 15), 2)
            hsvB = cv.dilate(hsvB, np.ones((15, 15), np.uint8), 5)
            hsvB = cv.erode(hsvB, np.ones((5, 5), np.uint8), 3)
            mask_blue = cv.inRange(hsvB, LOWER_BLUE, UPPER_BLUE)

            #Red
            hsvR = cv.cvtColor(original, cv.COLOR_BGR2HSV)
            hsvR = cv.GaussianBlur(hsvR, (15, 15), 1)
            hsvR = cv.dilate(hsvR, np.ones((5, 5), np.uint8), 5)
            hsvR = cv.erode(hsvR, np.ones((8, 8), np.uint8), 2)
            mask_red = cv.inRange(hsvR, LOWER_RED, UPPER_RED)

            #Orange
            hsvO = cv.cvtColor(original, cv.COLOR_BGR2HSV)
            hsvO = cv.GaussianBlur(hsvO, (15, 15), 1)
            hsvO = cv.dilate(hsvO, np.ones((15, 15), np.uint8), 5)
            hsvO = cv.erode(hsvO, np.ones((16, 16), np.uint8), 3)
            mask_orange = cv.inRange(hsvO, LOWER_ORANGE, UPPER_ORANGE)

            #Green
            hsvG = cv.cvtColor(original, cv.COLOR_BGR2HSV)
            hsvG = cv.GaussianBlur(hsvG, (15, 15), 1)
            hsvG = cv.dilate(hsvG, np.ones((15, 15), np.uint8), 5)
            hsvG = cv.erode(hsvG, np.ones((16, 16), np.uint8), 1)
            mask_green = cv.inRange(hsvG, LOWER_GREEN, UPPER_GREEN)


            # mask_purple = cv.inRange(hsv, LOWER_PURPLE, UPPER_PURPLE)
            hsvV = cv.cvtColor(original, cv.COLOR_BGR2HSV)
            hsvV = cv.GaussianBlur(hsvG, (15, 15), 1)
            hsvV = cv.dilate(hsvG, np.ones((15, 15), np.uint8), 5)
            hsvV = cv.erode(hsvG, np.ones((16, 16), np.uint8), 1)
            mask_violet = cv.inRange(hsvV, LOWER_VIOLET, UPPER_VIOLET)

            # Erode
            mask_red = cv.dilate(mask_red, np.ones((5, 5), np.uint8), 6)
            mask_red = cv.erode(mask_red, np.ones((5, 5), np.uint8), 1)
            cv.imshow("Red", mask_red)
            #mask_yellow = cv.erode(mask_yellow, np.ones((2, 2), np.uint8, 0))
            #mask_yellow = cv.dilate(mask_yellow, np.ones((5, 5), np.uint8))
            cv.imshow("Yellow",mask_yellow)
            mask_orange = cv.erode(mask_orange, np.ones((2, 2), np.uint8, 2))
            mask_orange = cv.dilate(mask_orange, np.ones((5, 5), np.uint8))
            cv.imshow("Orange", mask_orange)
            mask_blue = cv.dilate(mask_blue, np.ones((5, 5), np.uint8),6)
            mask_blue = cv.erode(mask_blue, np.ones((5, 5), np.uint8),1)
            cv.imshow("Blue", mask_blue)
            mask_violet = cv.erode(mask_violet, np.ones((5, 5), np.uint8, 2))
            cv.imshow("Violet", mask_violet)
            cv.imshow("Green",mask_green)
            #print("blue!!!!!!!!!!!!", np.sum(mask_blue == 255), "yellow!!!!!!!!!!!!!", np.sum(mask_yellow == 255), "violet!!!!!!!!!!!",np.sum(mask_violet==255))

            frameRed, CentersRed,rednum = get_everything(original_main, mask_red)
            frameGreen, CentersGreen,greennum = get_everything(frameRed, mask_green)
            frameBlue, CentersBlue,bluenum = get_everything(frameGreen, mask_blue)
            frameOrange, CentersOrange,orangenum = get_everything(frameBlue, mask_orange)
            frameViolet, CentersViolet,violetnum = get_everything(frameOrange, mask_violet)
            frameYellow, CentersYellow,yellownum = get_everything(frameViolet, mask_yellow)

            cv.imshow("Final Frame", frameYellow)

            dic3['O']=np.sum(mask_yellow == 255)
            dic3['I'] = np.sum(mask_blue == 255)
            dic3['J'] = np.sum(mask_violet == 255)
            dic3['Z'] = np.sum(mask_red == 255)
            dic3['S'] = np.sum(mask_green == 255)
            dic3['L'] = np.sum(mask_orange == 255)
            # # Filtering colors
            # red_filter = cv.bitwise_and(frame, frame, mask=mask_red)

            # Drawing the result on the original image
            original,dicx = drawResult(RED, original.copy())
            original,dicx = drawResult(YELLOW, original.copy())
            original,dicx = drawResult(BLUE, original.copy())
            original,dicx = drawResult(GREEN, original.copy())
            original,dicx = drawResult(ORANGE, original.copy())
            original,dicx = drawResult(VIOLET, original.copy())
            # print("dddddddddddddddddddddddddddd",dicx)
            cv.imshow('Original', original)
            print("Centers:  B:",CentersBlue,"  G:",CentersGreen,"  O:",CentersOrange,"  R:",CentersRed,"  V:",CentersViolet,"  Y:",CentersYellow)
            # list1 =
            # list2 =
            # D= {'I': [],'S':[]}
            # D=['I'].append(list1)
            # D=['S'].append(list2)
            # if len(CentersBlue.shape)>1:
            if rednum + greennum + bluenum + orangenum + violetnum + yellownum == 3:
                repeat = False
                q=1
                D = {'I': CentersBlue[0][1], 'S': CentersGreen[0][1], 'L': CentersOrange[0][1], 'Z': CentersRed[0][1],
                     'J': CentersViolet[0][1], 'O': CentersYellow[0][1]}
                sortDic = sorted(D.items(),reverse=True)
                Stri = ''
                for key, values in sortDic:
                    Stri = Stri + str(key)
            elif rednum + greennum + bluenum + orangenum + violetnum + yellownum == 2:
                repeat = True
                q = 1
                D = {'I': CentersBlue[0][1], 'S': CentersGreen[0][1], 'L': CentersOrange[0][1], 'Z': CentersRed[0][1],
                     'J': CentersViolet[0][1], 'O': CentersYellow[0][1]}
                sortDic = sorted(D.items(), reverse=True)
                Strirepeat = ''
                for key, values in sortDic:
                    Strirepeat = Strirepeat + str(key)

            if cv.waitKey(1) & 0xff == ord('q'):
                break
            if q==1:
                break
        if repeat:
            return Strirepeat
        elif not repeat:
            return Stri

        vid.release()
        cv.destroyAllWindows()
