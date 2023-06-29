import matplotlib.pyplot as plt
import numpy as np
import time 
import c_deserial

nav_struct = """typedef struct __attribute__ ((__packed__)){
    float pitch;
    float roll;     
    float ele;      
    double lat;
    double lon;
    float velocity; 
    float course;   
    float track_ang;
} nav_t;
"""

head_struct = """typedef struct __attribute__ ((__packed__)){
    uint16_t marker;
    uint16_t version;
    uint16_t size;
    uint16_t cnt;
    uint16_t id;
    uint16_t type;
} head_t;
"""

img_struct = """typedef struct __attribute__ ((__packed__)){
    float dx;
    float dy;
    float course;
    float roll;
    float x0;
    uint8_t word_size;
    uint8_t polarization;
    int16_t y;
    uint16_t nx;
    uint16_t ny;           
    float k;                
} img_t;
"""


class ArrayReader():
    def __init__(self, data):
        self.index = 0
        self.data = data

    def read(self, length):

        if self.index >= len(self.data):
            return np.nan

        if (length == 1):
            data = self.data[self.index]
        else:
            data = self.data[self.index:self.index + length]
        self.index += length
        return data


data = np.fromfile('./data.bin', dtype='uint8')

ar = ArrayReader(data)

pack_head = c_deserial.Deserial(head_struct)
pack_nav = c_deserial.Deserial(nav_struct)
pack_img = c_deserial.Deserial(img_struct)

a = np.array([])
while 1:
    header = ar.read(84)
    if not hasattr(header, '__len__'):
        break
    header_reader = ArrayReader(header)

    head = pack_head.to_dict(header_reader.read(pack_head.size()))
    nav = pack_nav.to_dict(header_reader.read(pack_nav.size()))
    img = pack_img.to_dict(header_reader.read(pack_img.size()))

    # print(head)
    # print(nav)
    # print(img)

    chunk = ar.read(head["size"])
    if img["word_size"] == 2:
        chunk = chunk.view(np.uint16)
    chunk = chunk * img["k"]

    a = np.append(a, chunk)

print("word_size:", img["word_size"])
line_len = int(img["dx"] * img["nx"])
n_rows = int(len(a) / line_len)
a = a.reshape((n_rows, line_len))

plt.matshow(a, cmap='gray')

plt.show()
