# Jupyter Digitizer Data Converter
## By Jack Livingston (u5559529)
## ANU Undergraduate PHYS3042
### Importing Modules Section:
#pylab inline

from struct import *
from scipy.optimize import curve_fit
from statistics import *
from numpy import *
from pylab import *


def header(x,num):
	'''Operation :
	Takes the headers out of a data set x, contains metadata
Input:
x=data set
Output:
set of headers for the data
	'''
	q = len(x)
	k = int(q / num)
	iterh = [0.0] * k
	C = [0.0] * k
	for i in range(k):
		iterh[i] = iter_unpack('l', x[0 + (i * num):20 + (i * num)])
		C[i] = [inner for outer in iterh[i] for inner in outer]
	return C

def wavedata(x,num):
	"""
	Operation:
	Takes the data out of a data set x
	Input:
	x=data set
	Output:
	set of data for each waveform
	"""
	q = len(x)
	k = int(q / num)
	iterd = [0.0] * k
	C = [0.0] * k
	for j in range(k):
		iterd[j] = iter_unpack('h', x[24 + (j * num):num + (j * num)])
		C[j] = [inner for outer in iterd[j] for inner in outer]
	return C
def integ(H):
	"""
Operation:
Takes away background from an event's data, sums the remaining data and then adds it to a new set
Input:
x=data set
Output:
Each event summed within data set
	"""
	q=len(H)
	C=[0.0]*q
	D=[0.0]*q
	for i in range(q):
		avg=mean(H[i][0:argmin(H[i])-2])  # two channel before the min point.
		C[i]=H[i][argmin(H[i])-2:]-array(avg)
		D[i]=sum(C[i])
	return D

def gaussian(x,amp, mu, sig):
	n=len(x)
	C=[0.0]*n
	for i in range(n):
		C[i]=amp*exp(-power(x[i] - mu, 2.) / (2 * power(sig, 2.)))
	return C

def testdata(x,n):
	C=[0.0]*n
	for i in range(n):
		C[i]=i*15+x
	return C

def peakplot(x,l,h):
	ydata = x[int(l / 15):int(h / 15)]
	xdata = arange(len(ydata))
	plot(xdata, ydata, '.', label='data')

	def func(t, m, x, w):
		return m * exp(-(t - x) ** 2 / (2 * w ** 2))

	opt, conver = curve_fit(func, xdata, ydata)
	plot(xdata, func(xdata, *opt), 'r-', label='fit')
	residuals = ydata - func(xdata, *opt)
	ss_res = sum(residuals ** 2)
	ss_tot = sum((ydata - mean(ydata)) ** 2)
	r_squared = 1 - (ss_res / ss_tot)
	# print('r squared =', r_squared)
	# print('height=', opt[0])
	# print('mean=', opt[1] * 15 + l)
	# print('width=', abs(opt[2] * 15))
	xlabel('x')
	ylabel('y')
	legend()
	show()

#file=open('NaI_Cs137.dat','rb')
file=open('HPGe_Cs137.dat','rb')
X=file.read()
num_sam=unpack('l',X[0:4])[0]
head=header(X,num_sam)
# print(head)
wave=wavedata(X,num_sam)
int_cal=integ(wave)
# print(int_cal)
#h=hist(int_cal, bins=1000)
plot(wave[1])
show()




