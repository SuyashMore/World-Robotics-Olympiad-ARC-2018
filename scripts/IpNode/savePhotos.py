import cv2
import numpy as np

cam = cv2.VideoCapture(1)

i = 0;

if __name__=="__main__":
	_,frame = cam.read()
	key = cv2.waitKey(1) & 0xff
	if key == ord('q'):
		break
	elif key ==ord('e'):
		fname = 'image'+i+'png'
		cv2.imwrite(fname,grey_img)


cam.release()
cv2.destroyAllWindows()


     