import numpy as np
import math
import constants

L1=constants.L1
L2=constants.L2
L3=constants.L3
L4=constants.L4
L5=constants.L5


def process(a1,a2,a3,a4,a5):

    q1=a1*(np.pi/180)
    q2=a2*(np.pi/180)
    q3=a3*(np.pi/180)
    q4=a4*(np.pi/180)
    q5=a5*(np.pi/180)

    PT=[[0,-90*(np.pi/180),L1,q1],[L2,0,0,(-1)*(90*(np.pi/180)-q2)],[L3,0,0,(90*(np.pi/180)+q3)],[L4,(-1)*90*(np.pi/180),0,q4],[0,0,L5,q5]]

    i=0
    H0_1=[[np.cos(PT[i][3]),-np.sin(PT[i][3])*np.cos(PT[i][1]),np.sin(PT[i][3])*np.sin(PT[i][1]),PT[i][0]*np.cos(PT[i][3])],
    	[np.sin(PT[i][3]),np.cos(PT[i][3])*np.cos(PT[i][1]),-np.cos(PT[i][3])*np.sin(PT[i][1]),PT[i][0]*np.sin(PT[i][3])],
    	[0,np.sin(PT[i][1]),np.cos(PT[i][1]),PT[i][2]],
    	[0,0,0,1]]
    i=1

    H1_2=[[np.cos(PT[i][3]),-np.sin(PT[i][3])*np.cos(PT[i][1]),np.sin(PT[i][3])*np.sin(PT[i][1]),PT[i][0]*np.cos(PT[i][3])],
    	[np.sin(PT[i][3]),np.cos(PT[i][3])*np.cos(PT[i][1]),-np.cos(PT[i][3])*np.sin(PT[i][1]),PT[i][0]*np.sin(PT[i][3])],
    	[0,np.sin(PT[i][1]),np.cos(PT[i][1]),PT[i][2]],
    	[0,0,0,1]]

    i=2

    H2_3=[[np.cos(PT[i][3]),-np.sin(PT[i][3])*np.cos(PT[i][1]),np.sin(PT[i][3])*np.sin(PT[i][1]),PT[i][0]*np.cos(PT[i][3])],
    	[np.sin(PT[i][3]),np.cos(PT[i][3])*np.cos(PT[i][1]),-np.cos(PT[i][3])*np.sin(PT[i][1]),PT[i][0]*np.sin(PT[i][3])],
    	[0,np.sin(PT[i][1]),np.cos(PT[i][1]),PT[i][2]],
    	[0,0,0,1]]

    i=3

    H3_4=[[np.cos(PT[i][3]),-np.sin(PT[i][3])*np.cos(PT[i][1]),np.sin(PT[i][3])*np.sin(PT[i][1]),PT[i][0]*np.cos(PT[i][3])],
    	[np.sin(PT[i][3]),np.cos(PT[i][3])*np.cos(PT[i][1]),-np.cos(PT[i][3])*np.sin(PT[i][1]),PT[i][0]*np.sin(PT[i][3])],
    	[0,np.sin(PT[i][1]),np.cos(PT[i][1]),PT[i][2]],
    	[0,0,0,1]]
    i=4
    H4_5=[[np.cos(PT[i][3]),-np.sin(PT[i][3])*np.cos(PT[i][1]),np.sin(PT[i][3])*np.sin(PT[i][1]),PT[i][0]*np.cos(PT[i][3])],
    	[np.sin(PT[i][3]),np.cos(PT[i][3])*np.cos(PT[i][1]),-np.cos(PT[i][3])*np.sin(PT[i][1]),PT[i][0]*np.sin(PT[i][3])],
    	[0,np.sin(PT[i][1]),np.cos(PT[i][1]),PT[i][2]],
    	[0,0,0,1]]

    H1_2=np.dot(H0_1,H1_2)
    H2_3=np.dot(H1_2,H2_3)
    H3_4=np.dot(H2_3,H3_4)
    H0_5=np.dot(H3_4,H4_5)


    
    # print("H0_1=")
    # print(np.matrix(H0_1))
    # print("H1_2=")
    # print(np.matrix(H1_2))
    # print("H2_3=")
    # print(np.matrix(H2_3))
    # print("H3_4=")
    # print(np.matrix(H3_4))
    # print("H4_5=")
    # print(np.matrix(H4_5))
    # print("H0_5=")
    # print(np.matrix(H0_5))

    if constants.ENABLE_KINEMATIC_DEBUG_MESSAGES_RES:
        print("position of end effector is :")
        print("x co-ordinate=",H0_5[0][3])
        print("y co-ordinate=",H0_5[1][3])
        print("z co-ordinate=",H0_5[2][3])

        x=H0_5[0][3]
        y=H0_5[1][3]
        z=H0_5[2][3]
        print("Radius Vector=",(np.sqrt(x**2+y**2+z**2)))
