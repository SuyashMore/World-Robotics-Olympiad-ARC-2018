import math
import constants

L1=constants.L1
L2=constants.L2
L3=constants.L3
L4=constants.L4
L5=constants.L5

def process(x,y,z):
	w1=x # x co-ordinate of end effector 
	w2=y # y co-ordinate of end effector
	w3=z # z co-ordinate of end effector
	w4=0
	w5=0
	w6=-1

	d1=L1
	a2=L2
	a3=L3
	a4=L4
	d5=L5      #length of link 5

	q1=math.atan2(w2,w1)

	c1=math.cos(q1)
	s1=math.sin(q1)

	q234=math.atan2((-1)*(c1*w4+s1*w5),(-1)*w6)
	
	c234=math.cos(q234)
	s234=math.sin(q234)
	
	b1=c1*w1+s1*w2-a4*(c234)+d5*(s234)


	b2=d1-a4*(s234)-d5*(c234)-w3
	b=b1**2+b2**2 
	
	z=(b-(a2**2)-(a3**2))/(2*a2*a3)
	


	if z>-1 and z<1:

		q3=(math.acos(z))                    
		#c3=math.cos(q3)
		c3 = z	
		
		
		s3=math.sin(q3)
		

		q2=math.atan2(((a2+a3*(c3))*b2 - a3*(s3)*b1),((a2+a3*c3)*b1+a3*s3*b2)) 

		q4=q234-q2-q3

		# q5=math.pi*(math.log(math.sqrt(w4*w4+w5*w5+w6*w6))

		q1=q1*(180/math.pi)
		q2=q2*(180/math.pi)
		q3=q3*(180/math.pi)
		q4=q4*(180/math.pi)
		#q5=q5*(180/math.pi)
		q5=31

		return q1,q2,q3,q4,q5,True

	else:
		print("this point is not in range")
		return 0,0,0,0,0,False
