import json
import utm
import numpy as np
import os

# mArrUTMX = []
# mArrUTMY = []
#
# for pts in data['surveys']:
#     utmX , utmY , a , b = utm.from_latlon(float(pts['latitude']), float(pts['longitude']))
#     mArrUTMX.append(utmX)
#     mArrUTMY.append(utmY)
#
# print(mArrUTMX)


class GNSSPoint:
    def __init__(self, data):

        self.date = []
        self.time = []
        self.hdop = []
        self.vdop = []
        self.lat = []
        self.lng = []
        self.alt = []
        self.GS = []
        self.hacc = []
        self.vacc = []

        self.meanLat = 90
        self.meanLng = 90
        self.meanAlt = -1

        self.utmX = -1
        self.utmY = -1

        for pts in data['surveys']:
            self.date.append(pts['date'])
            self.time.append(pts['time'])
            self.hdop.append(float(pts['hdop']))
            self.vdop.append(float(pts['vdop']))
            self.lat.append(float(pts['latitude']))
            self.lng.append(float(pts['longitude']))
            self.alt.append(float(pts['altitude']))
            self.GS.append(float(pts['GeoidSeparation']))
            self.hacc.append(float(pts['hacc']))
            self.vacc.append(float(pts['vacc']))

        self.mData = zip(self.date, self.time, self.hdop, self.vdop, self.lat, self.lng, self.alt, self.GS, self.hacc, self.vacc)

    def __repr__(self):
        mstr = str(self.meanLat) + " " + str(self.meanLng) + " " + str(self.meanAlt)
        return mstr

    def Best_Mean(self):
        pres = 0.2
        meanPts = [[], [], []]

        for pts in self.mData:
            if pts[8] <= pres:
                meanPts[0].append(pts[4])
                meanPts[1].append(pts[5])
                meanPts[2].append(pts[6])

        if len(meanPts[0]) != 0:
            self.meanLat = format(np.average(meanPts[0]), '.9f')
            self.meanLng = format(np.average(meanPts[1]), '.9f')
            self.meanAlt = format(np.average(meanPts[2]), '.2f')

    def projUTM(self):
        if self.meanLat != 90 and self.meanLng != 90:
            self.utmX, self.utmY, a, b = utm.from_latlon(float(self.meanLat), float(self.meanLng))


def handleFile(file):
    f = open(file, 'r')
    string = f.read()
    f.close()

    data = json.loads(string)
    surveyedPoints.append(GNSSPoint(data))

#-------------------------------------------------------------------------------------
# MAIN PROGRAM
#-------------------------------------------------------------------------------------

dir = os.listdir()

surveyedPoints = []

i = 0

for files in dir:
    if files.endswith('.json'):
        handleFile(files)

for pts in surveyedPoints:
    pts.Best_Mean()
    pts.projUTM()

ff = open("test.txt", 'w')

for pts in surveyedPoints:
    s = str(pts.utmX) + " " + str(pts.utmY) + " " + str(pts.meanAlt) + "\n"
    ff.write(s)

ff.close()
