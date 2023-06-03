#!/usr/bin/python
# -*- coding: utf-8 -*-

import xml.etree.ElementTree as ET

import os
import matplotlib as mpl
mpl.use("Agg");
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.lines as ml

from matplotlib.colors import Normalize


class Gpx(object):
    # Plotting
    def createColormap(self, x, y, ax=None):
    
        lenx = len(x) - 2;
        colors = plt.cm.jet(np.linspace(0,1, 101));
        colormap = np.zeros( (lenx, 4), dtype=float);
        norm = Normalize( np.min(y), np.max(y) )
        
        
        for i in range(lenx):
            colormap[i] = colors[int((norm(y[i]) * 100) + 0.5)];
            line = ml.Line2D(x[i:i+2], y[i:i+2], color=colormap[i] );
            ax.add_line(line);
        
        ax.autoscale();
        return colormap;

    def colorPlot(self, x, y, colormap, ax=None):
        
        lenx = len(x) - 2;
        for i in range(lenx):
            line = ml.Line2D(x[i:i+2], y[i:i+2], color=colormap[i] );
            ax.add_line(line);
        ax.autoscale();
    
    def latlon2dist(self, lat1, lon1, lat2, lon2):
                
        R = 6371008;
        
        lat1 *= np.pi / 180;
        lat2 *= np.pi / 180;
        lon1 *= np.pi / 180;
        lon2 *= np.pi / 180;

        #вычисление косинусов и синусов широт и разницы долгот
        cl1 = np.cos(lat1);
        cl2 = np.cos(lat2);
        sl1 = np.sin(lat1);
        sl2 = np.sin(lat2);
        
        delta = lon2 - lon1;
        cdelta = np.cos(delta);
        sdelta = np.sin(delta);
        
        y = np.sqrt(np.power(cl2 * sdelta, 2) + np.power(cl1 * sl2 - sl1 * cl2 * cdelta, 2));
        x = sl1 * sl2 + cl1 * cl2 * cdelta;
        ad = np.arctan2(y, x);
        dist = ad * R; #расстояние между двумя координатами в метрах
        
        return dist
    
    def Plot(self, show=True, image=None, color=False):
              
        time = [ float(self.time_data[i] - self.start ) for i in range(self.len)];
        
        plt.ioff();
        
        fig = plt.figure( figsize=(16,9));

        
        ax_speed = fig.add_subplot(2, 2, 1);
        ax_ele = fig.add_subplot(2, 2, 3);
        ax_track = fig.add_subplot(1, 2, 2);
        
        #ax_speed.set_xlabel('Время с начала запуска, с');
        #ax_speed.set_ylabel('Скорость, км/ч');
        
        #ax_ele.set_xlabel('Время с начала запуска, с');
        #ax_ele.set_ylabel('Высота, м');
        
        ax_speed.set_xlabel('Time, s');
        ax_speed.set_ylabel('Speed, km/h');
        
        ax_ele.set_xlabel('Time, s');
        ax_ele.set_ylabel('Elevation, m');
        
        #ax_track.scatter(self.lat, self.lon, s=3);
        
        latm = [ float( self.latlon2dist(self.lat[0], 0, self.lat[i], 0) ) for i in range(self.len)];
        lonm = [ float( self.latlon2dist(0, self.lon[0], 0, self.lon[i]) ) for i in range(self.len)];
        
        ax_track.annotate('Start', xy=(latm[0], lonm[0]) );
        #ax_track.set_xlabel('GPS трек, м');
        ax_track.set_xlabel('GPS track, m');
        
        if(color == True):
            
            colormap = self.createColormap(time, self.speed_data, ax=ax_speed);
            
            self.colorPlot(time, self.ele_data, colormap, ax=ax_ele);
            self.colorPlot(latm, lonm, colormap, ax=ax_track);
            #self.colorPlot(time, self.ele_data, ax=ax_ele);
            
            
        else:
            ax_ele.plot(time, self.ele_data);
            ax_speed.plot(time, self.speed_data);
            ax_track.plot(latm, lonm, '-o');
        
        def on_move(event):
            # get the x and y pixel coords
            # import numpy as np
            
            if event.inaxes:
                
                x, y = event.xdata, event.ydata
                indx = min(np.searchsorted(self.lat, x), len(self.lat) - 1);
                print('Index: ', indx);
                #print('data coords %f %f' % (event.xdata, event.ydata))
        
        
        
        #fig.tight_layout();
        
        if(show == True):
            #binding_id = plt.connect('motion_notify_event', on_move)
            plt.show();
        
        if(image != None):
            fig.savefig(image);
            
    
    
    # Parsing
    def ConvertTime(self, time_str):
        
        position = time_str.find('T') + 1;
        time_str = time_str[position:-1].split(':');
        
        h = float(time_str[0])
        m = float(time_str[1])
        s = float(time_str[2])
        
        return (h*3600 + m*60 + s)
    
    def SeekOffset(self, offset):
        
        for i in range(self.len):
            d = self.time_data[i] - self.start
            
            if(d < 0):
                d = ( (24 * 3600) + self.time_data[i] ) - self.start
            
            if(d == offset):
                self.time = self.time_data[i]
                self.speed = self.speed_data[i]
                self.ele = self.ele_data[i]
                self.dir = self.dir_data[i]
                self.lat1 = self.lat[i]
                self.lon1 = self.lon[i]
                return i
            if(d > offset):
                i -= 1;
                self.time = self.time_data[i]
                self.speed = self.speed_data[i]
                self.ele = self.ele_data[i]
                self.dir = self.dir_data[i]
                self.lat1 = self.lat[i]
                self.lon1 = self.lon[i]
                return i
            
    def ParseGpx(self, file):
        tree = ET.parse(file)
        root = tree.getroot()
        
        time = root.findall("trk/trkseg/trkpt/time")
        speed = root.findall("trk/trkseg/trkpt/speed")
        ele = root.findall("trk/trkseg/trkpt/ele")
        sats = root.findall("trk/trkseg/trkpt/sats")
        trkpt = root.findall("trk/trkseg/trkpt")
        
        dr = root.findall("trk/trkseg/trkpt/direction")
        
        self.len = len(time)
        
        # Need to fix NavSAR.py
        # Right way:
        #for i in range(self.len):
        
        #for i in range(0, self.len, 4):
        for i in range(0, self.len):
            if(sats[i].text != '0'):
                self.time_data.append(self.ConvertTime(time[i].text));
                self.speed_data.append(float(speed[i].text));
                self.ele_data.append(float(ele[i].text));
                self.lat.append(float(trkpt[i].attrib['lat']));
                self.lon.append(float(trkpt[i].attrib['lon']));
                self.dir_data.append(float(dr[i].text));
        self.len = len(self.time_data);
        
        #print(self.len);
        '''
        self.time_data = [self.ConvertTime(time[i].text) for i in range(self.len)]
        self.speed_data = [ float(speed[i].text) for i in range(self.len)]
        self.ele_data = [ float(ele[i].text) for i in range(self.len)]
        
        self.lat = [ float(trkpt[i].attrib['lat']) for i in range(self.len)]
        self.lon = [ float(trkpt[i].attrib['lon']) for i in range(self.len)]
        '''
        if(self.len):
            self.start = self.time_data[0]
        
        del tree, root, time, speed, ele, sats
        
    # Math
    @classmethod
    def Interpolate(self, arr, im_size):
        if(hasattr(arr, "__len__")):
            larr = len(arr)
        else:
            return [arr] * im_size
        xp = np.linspace(1, larr, larr)
        x = np.linspace(1, larr, im_size)
        return np.interp(x, xp, arr) 

    def GetSpeedElevation(self, Tshift, Ts, im_size=0):

        stop = self.SeekOffset(Tshift+Ts);
        start = self.SeekOffset(Tshift);
        
        
        if(start == None or stop == None):
            return np.nan, np.nan
            
        if(start == stop):
            V = self.speed_data[start] / 3.6
            H = self.ele_data[start]
        else:
            V = np.array(self.speed_data[start:stop]);
            V /= 3.6;
        
            H = np.array(self.ele_data[start:stop]);
        
        if(im_size):
            V = self.Interpolate(V, im_size);
            H = self.Interpolate(H, im_size);
            return V.tolist(), H.tolist();
        else:
            V = np.mean(V);
            H = np.mean(H);
            return [V], [H];
    
    def GetTravelAngle(self, Tshift, Ts):
        '''
        stop = self.SeekOffset(Tshift+Ts);
        start = self.SeekOffset(Tshift);
        
        lat = self.lat[start:stop];
        lon = self.lon[start:stop];
        
        #print "Lats:", lat
        
        ay = lat[1] - lat[0]
        ax = lon[1] - lon[0]

        alphav = np.arccos( (ax ) / np.sqrt(ax**2 + ay**2) )
        
        #print ax, ay
        
        #print "Alpha:", np.rad2deg(alphav)
        
        return alphav + np.pi/2
        '''
        self.SeekOffset(Tshift+Ts/2);
        return self.dir

            
            
    def __init__(self, file):
        
        self.len = 0
        self.time_data = []
        self.start = 0
        self.speed_data = []
        self.time = 0
        self.speed = 0
        self.ele_data = []
        self.ele = 0
        self.dir = 0;
        self.dir_data = []
        
        self.lat = []
        self.lon = []
        
        self.lat1 = 0;
        self.lon1 = 0;
        
        self.ParseGpx(file)




'''
directory = 'gpx/'

gpx_list = os.listdir(directory);

for i in range(len(gpx_list)):
    
    file = gpx_list[i];
    gpx = Gpx(directory + file);
    
    if(gpx.len):
        img = "img/" + file[:-4];
        gpx.Plot(image=img, show=False, color=True);
    del gpx;

    
'''

nav_struct = """struct nav_pack_t{
    uint32_t _marker;
    uint8_t version;
    double _lat;
    double _lon;
    double _ele;
    double _velocity_course;
    double velocity_east;
    double velocity_north;
    double velocity_vertical;
    double pitch;
    double roll;
    double yaw;
    double _course;
    uint64_t _time;
    uint8_t valid;
}nav_info;
"""


CRC16TABLE = [
      0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7
    , 0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF
    , 0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6
    , 0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE
    , 0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485
    , 0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D
    , 0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4
    , 0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC
    , 0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823
    , 0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B
    , 0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12
    , 0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A
    , 0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41
    , 0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49
    , 0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70
    , 0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78
    , 0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F
    , 0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067
    , 0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E
    , 0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256
    , 0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D
    , 0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405
    , 0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C
    , 0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634
    , 0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB
    , 0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3
    , 0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A
    , 0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92
    , 0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9
    , 0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1
    , 0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8
    , 0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
]

def crc16_ccitt(data):
    
    crc = 0xFFFF

    for d in data:
        crc = ((crc << 8) ^ CRC16TABLE[ ((crc >> 8) ^ d) &0xff ] ) & 0xffff        
    return crc


if __name__ == '__main__':

    # Пример использования класса Gpx
    #file = "m3-25-02-2020_09-38-19"
    import sys
    import c_deserial

    fn = sys.argv[1]
    
    gpx = Gpx(fn)


    nav = c_deserial.Deserial(nav_struct, '>')

    time = 1684670380000

    print(nav.pack_format)

    out_fn = fn[:-3] + 'nav'

    f = open(out_fn, 'wb')

    for i in range(0, len(gpx.lat)):
        marker = 0x55AA55AA
        version = 0x02
        lat = gpx.lat[i]
        lon = gpx.lon[i]
        ele = gpx.ele_data[i]
        spd = gpx.speed_data[i] / 3.6
        ve = 0
        vn = 0
        vv = 0
        p = 0
        r = 0
        yaw = gpx.dir_data[i]
        course = gpx.dir_data[i]
        time += 100
        valid = 1


        pack = nav.serial(( marker, version, lat, lon, ele, spd, ve, vn, vv, p, r, yaw, course, time, valid))

        crc = crc16_ccitt(pack)
        crc = crc.to_bytes(length = 2, byteorder = 'big')

        pack += crc

        f.write(pack)

    f.close()
    #a = gpx.latlon2dist(0, 0, 0, 5);
    #b = gpx.latlon2dist(0, 0, 5, 0);

    #v, h = gpx.GetSpeedElevation(1, 1, 100);

    #plt.plot(v);
    #plt.show();
    #element = gpx.SeekOffset(3.1) # Сдвиг в секундах относительно старта

    #print("Element: ", element)
    #print("Speed:   ", gpx.speed)
    #print("Time:    ", gpx.time)
    #print("Ele:     ", gpx.ele)

    #gpx.Plot(image=file);
    #gpx.Plot();
    #gpx.Plot(color=True);

