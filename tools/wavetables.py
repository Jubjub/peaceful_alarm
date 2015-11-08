import math

resolution = 256
depth = 256

data = 'const unsigned int wavetable_size = %s;' % resolution
data += 'const unsigned char sinewave[] = {'

for i in range(0, resolution):
    value = int(math.sin((i / float(resolution - 1)) * math.pi) * (depth - 1))
    data += '0x%x, ' % value

data += '};'

print data
