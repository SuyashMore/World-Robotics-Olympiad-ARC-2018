import cv2
import numpy as np

cap = cv2.VideoCapture(1)

while (True):
    ret, frame = cap.read()
    # frame = cv2.GaussianBlur(frame, (25, 25), 2)
    frame_hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    cv2.imshow('frame', frame)
    if cv2.waitKey(1) == 27:
        break

bboxRed = cv2.selectROI(frame)
redObj = frame_hsv[int(bboxRed[1]):int(bboxRed[1] + bboxRed[3]), int(bboxRed[0]):int(bboxRed[0] + bboxRed[2])]

# # # bboxBlue = cv2.selectROI(frame)
# # # blueObj = frame_hsv[int(bboxBlue[1]):int(bboxBlue[1]+bboxBlue[3]), int(bboxBlue[0]):int(bboxBlue[0]+bboxBlue[2])]


hR, sR, vR = np.median(redObj[:, :, 0]), np.median(redObj[:, :, 1]), np.median(redObj[:, :, 2])

lower_rangeRed = np.array([hR - 3, sR - 40, vR - 130])
higher_rangeRed = np.array([hR + 3, sR + 40, vR + 130])


print(hR, sR, vR)
print([lower_rangeRed[0], lower_rangeRed[1], lower_rangeRed[2]])
print([higher_rangeRed[0], higher_rangeRed[1], higher_rangeRed[2]])

Centeres=[[],[]]

# lower_rangeRed = [112,125,180]
# higher_rangeRed = [124,175,135]


# lower_rangeRed = np.array(lower_rangeRed)
# higher_rangeRed = np.array(higher_rangeRed)


# hB, sB, vB = np.median(blueObj[:,:,0]), np.median(blueObj[:,:,1]), np.median(blueObj[:,:,2])
# lower_rangeBlue = np.array([hB-5, sB-50, vB-70])
# higher_rangeBlue = np.array([hB+5, sB+50, vB+70])

def get_everything(frame, edge):
    image, contours, hierarchy = cv2.findContours(edge, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    approx = []
    maxI = 0
    maxArea1 = 0
    smallest_x = 640
    maxArea2 = 0
    Centeres=[[],[]]
    MaxConours = []
    c1 = []
    c2 = []
    for i in range(len(contours)):
        area = cv2.contourArea(contours[i])
        epsilon = 0.01 * cv2.arcLength(contours[i], True)
        approx = cv2.approxPolyDP(contours[i], epsilon, True)
        if area > maxArea1 and area>500:
            maxArea2 = maxArea1
            maxArea1 = area
            c1 = contours[i]
        # less than maxArea1
        elif area > maxArea2 and area>500:
            maxArea2 = area
            c2 = contours[i]
        # print(approx)
        # if area > maxArea :
        #     maxArea = area
        #     maxI = i
        # print(maxArea, len(approx))
        x_low = 640
        for j in approx:
            # print(j[0][0])
            if j[0][0] < x_low:
                x_low = j[0][0]

        if x_low < smallest_x:
            smallest_x = x_low

        # img = cv2.drawContours(mask2, contours, maxI, (0, 255, 0), 5)
        #cv2.line(frame, (smallest_x, 0), (smallest_x, 480), (0, 0, 255), thickness=3)
    MaxConours.append(c1)
    MaxConours.append(c2)
    for i in range(len(MaxConours)):
        cnt=MaxConours[i]
        #print(cnt)

        try:
            M = cv2.moments(cnt)
            cX = int(M["m10"] / M["m00"])
            cY = int(M["m01"] / M["m00"])

            cv2.circle(frame, (cX, cY), 7, (238, 130, 238), -1)
            Centeres[i]=[cX,cY]
        except ZeroDivisionError:
            print("00000000000000000000000000000000000000000000000000000000000000000000000000")
        except TypeError:
            print("Typeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee")
    return frame,Centeres



dic = {'8': 0, '4': 0, '6': 0}
while (True):

    ok, frame = cap.read()
    original=frame
    #frame = frame[200:480, 0:640]
    frame = frame[0:150,0:500]

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    hsv = cv2.GaussianBlur(hsv, (15, 15), 1)
    hsv = cv2.dilate(hsv, np.ones((3, 3), np.uint8), 1)
    hsv = cv2.erode(hsv, np.ones((3, 3), np.uint8), 3)
    maskRed = cv2.inRange(hsv, lower_rangeRed, higher_rangeRed)

    # hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    # hsv = cv2.GaussianBlur(hsv, (15, 15), 1)
    # hsv = cv2.dilate(hsv, np.ones((3, 3), np.uint8), 1)
    # hsv = cv2.erode(hsv, np.ones((5, 5), np.uint8), 1)
    # maskGreen = cv2.inRange(hsv, np.array([39.0, 118.0, 46.0]), np.array([49.0, 218.0, 246.0]))

    # thresh = cv2.cvtColor(mask, cv2.COLOR_BGR2GRAY)
    # edge = cv2.Canny(mask, 100, 200)
    # im2, contours, hierarchy = cv2.findContours(edge, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    # n=0
    # for i in contours:
    #     area = cv2.contourArea(i)
    #     img = cv2.drawContours(edge, contours, i)
    #     print(area)

    # cv2.imshow("thresh", thresh)

    # edge = cv2.Canny(maskRed, 100, 200)
    # # gaus = edge
    # gaus = cv2.GaussianBlur(maskRed, (5, 5), 1)
    # mask1 = cv2.dilate(gaus, np.ones((15, 15), np.uint8, 3))
    # mask2 = cv2.erode(mask1, np.ones((5, 5), np.uint8, 1))
    # edgeRed = mask2
    edgeRed = maskRed
    # edge = cv2.Canny(maskGreen, 100, 200)
    # gaus = edge
    # gaus = cv2.GaussianBlur(maskGreen, (5, 5), 1)
    # mask1 = cv2.dilate(gaus, np.ones((15, 15), np.uint8, 3))
    # mask2 = cv2.erode(mask1, np.ones((5, 5), np.uint8, 1))
    # edgeGreen = mask2

    frame1,Centeres=get_everything(frame,edgeRed)
    # frame2, Centeres2 = get_everything(frame1, edgeGreen)
    # frame2 = get_everything(frame, edge)

    cv2.imshow("Red", maskRed)
    # cv2.imshow("Green", maskGreen)
    # cv2.imshow("img", img)
    cv2.imshow("frame", frame1)
    # cv2.imshow("mask1",gaus)
    if cv2.waitKey(1) == 27:
        break
    # cv2.imshow("mask",mask)
print([lower_rangeRed[0], lower_rangeRed[1], lower_rangeRed[2]])
print([higher_rangeRed[0], higher_rangeRed[1], higher_rangeRed[2]])
#print(Centeres, end="")
AllCenteres=[]
for i in Centeres:
    AllCenteres.append(i)
# for j in Centeres2:
#     AllCenteres.append(j)
print("\t", AllCenteres)