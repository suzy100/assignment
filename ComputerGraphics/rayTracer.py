#!/usr/bin/env python3
# -*- coding: utf-8 -*
# sample_python aims to allow seamless integration with lua.
# see examples below

import os
import sys
import pdb  # use pdb.set_trace() for debugging
import code # or use code.interact(local=dict(globals(), **locals()))  for debugging.
import xml.etree.ElementTree as ET
import numpy as np
from PIL import Image

class Color:
    def __init__(self, R, G, B):
        self.color=np.array([R,G,B]).astype(np.float)

    # Gamma corrects this color.
    # @param gamma the gamma value to use (2.2 is generally used).
    def gammaCorrect(self, gamma):
        inverseGamma = 1.0 / gamma;
        self.color=np.power(self.color, inverseGamma)

    def toUINT8(self):
        return (np.clip(self.color, 0,1)*255).astype(np.uint8)

class Ray:
    def __init__(self, origin, direction):
        self.origin = origin
        self.direction = direction

class Sphere:
    def __init__(self, center, radius, my_ref):
        self.center = center
        self.radius = radius
        self.my_ref = my_ref

    def intersect(self, r, tmin):
        n = r.origin - self.center
        b = np.dot(n, r.direction)
        c = np.dot(n, n) - np.square(self.radius)
        a = np.dot(r.direction, r.direction)

        D = b*b-a*c

        if D<0:
            return False, tmin

        t1 = -1*b + np.sqrt(D)
        t2 = -1*b - np.sqrt(D)

        if t1<0 and t2<0:
            return False, tmin
        if t1>=0 and t2>=0:
            t = min(t1, t2)
        else:
            t = max(t1, t2)

        if tmin>=t/a:
            tmin = t/a
            return True, tmin

        return False, tmin

    def get_normv(self, point):
        return (point-self.center)/np.linalg.norm(point-self.center)

    def shading(self, r, n, l_vector, l, sh):
        h = (-1*r.direction+l_vector)/np.linalg.norm(-1*r.direction+l_vector)
        if sh.typen == 'Phong':
            L = sh.diffuseColor.color*l.intensity*max(0, np.dot(n, l_vector))+sh.specularColor.color*l.intensity*np.power(max(0, np.dot(n, h)), sh.exponent)
        elif sh.typen == 'Lambertian':
            L = sh.diffuseColor.color*l.intensity*max(0, np.dot(n, l_vector))

        return L

class Box:
    def __init__(self, minPt, maxPt, my_ref):
        self.minPt = minPt
        self.maxPt = maxPt
        self.my_ref = my_ref

    def intersect(self, r, tmin):
        i_dir = 1/r.direction

        x_min = (self.minPt[0]-r.origin[0])*i_dir[0]
        x_max = (self.maxPt[0]-r.origin[0])*i_dir[0]

        if i_dir[0]<0:
            x_min, x_max = x_max, x_min

        y_min = (self.minPt[1]-r.origin[1])*i_dir[1]
        y_max = (self.maxPt[1]-r.origin[1])*i_dir[1]

        if i_dir[1]<0:
            y_min, y_max = y_max, y_min

        if x_min>y_max or y_min>x_max:
            return False, tmin

        if y_min>x_min:
            x_min = y_min

        if y_max<x_max:
            x_max = y_max

        z_min = (self.minPt[2]-r.origin[2])*i_dir[2]
        z_max = (self.maxPt[2]-r.origin[2])*i_dir[2]
        
        if i_dir[2]<0:
            z_min, z_max = z_max, z_min

        if x_min>z_max or z_min>x_max:
            return False, tmin

        if z_min>x_min:
            x_min = z_min

        if z_max<x_max:
            x_max = z_max
        
        h = x_min
        if x_min < 0:
            if x_max < 0: return False, tmin
            else: h = x_max
        
        if tmin>=h:
            tmin = h
            return True, tmin

        return False, tmin

    def get_normv(self, point):
        center = np.array((self.minPt+self.maxPt)/2)
        p = point - center
        yee = 1.000001

        dx = abs(self.minPt[0]-self.maxPt[0])/2
        dy = abs(self.minPt[1]-self.maxPt[1])/2
        dz = abs(self.minPt[2]-self.maxPt[2])/2

        x = (p[0]/dx)*yee
        y = (p[1]/dy)*yee
        z = (p[2]/dz)*yee

        n = np.array([int(x), int(y), int(z)]).astype(np.float)
        n_size = np.linalg.norm(n)
        n = n/n_size

        return n

    def shading(self, r, n, l_vector, l, sh):
        h = (-1*r.direction+l_vector)/np.linalg.norm(-1*r.direction+l_vector)
        if sh.typen == 'Phong':
            L = sh.diffuseColor.color*l.intensity*max(0, np.dot(n, l_vector))+sh.specularColor.color*l.intensity*np.power(max(0, np.dot(n, h)), sh.exponent)
        elif sh.typen == 'Lambertian':
            L = sh.diffuseColor.color*l.intensity*max(0, np.dot(n, l_vector))

        return L

class Light:
    def __init__ (self, position, intensity):
        self.position = position
        self.intensity = intensity

class Shader:
    def __init__ (self, name, typen, diffuseColor, specularColor = None, exponent = None):
        self.name = name
        self.typen = typen
        self.diffuseColor = diffuseColor
        self.specularColor = specularColor
        self.exponent = exponent

def main():

    tree = ET.parse(sys.argv[1])
    root = tree.getroot()

    # set default values
    viewDir=np.array([0,0,-1]).astype(np.float)
    viewUp=np.array([0,1,0]).astype(np.float)
    viewProjNormal=-1*viewDir  # you can safely assume this. (no examples will use shifted perspective camera)
    viewWidth=1.0
    viewHeight=1.0
    projDistance=1.0
    intensity=np.array([1,1,1]).astype(np.float)  # how bright the light is.
    
    objects = []
    objects_num = 0

    shades = []
    shades_num = 0
    lights = []
    lights_num = 0

    imgSize=np.array(root.findtext('image').split()).astype(np.int)

    for c in root.findall('camera'):
        viewPoint=np.array(c.findtext('viewPoint').split()).astype(np.float)
        viewDir=np.array(c.findtext('viewDir').split()).astype(np.float)
        projNormal=np.array(c.findtext('projNormal').split()).astype(np.float)
        viewUp=np.array(c.findtext('viewUp').split()).astype(np.float)
        if(c.findtext('projDistance') != None):
            projDistance=np.array(c.findtext('projDistance').split()).astype(np.float)
        viewWidth=np.array(c.findtext('viewWidth').split()).astype(np.float)
        viewHeight=np.array(c.findtext('viewHeight').split()).astype(np.float)

    for c in root.findall('shader'):
        color_n = c.get('name')
        shade_type = c.get('type')
        color_v = np.array(c.findtext('diffuseColor').split()).astype(np.float)
        diffuseColor = Color(color_v[0],color_v[1],color_v[2])

        if shade_type == 'Phong':
            shade_v = np.array(c.findtext('specularColor').split()).astype(np.float)
            specularColor = Color(shade_v[0], shade_v[1], shade_v[2])
            exponent = float(c.findtext('exponent'))
            shades.append(Shader(color_n, shade_type, diffuseColor, specularColor, exponent))

        elif shade_type == 'Lambertian':
            shades.append(Shader(color_n, shade_type, diffuseColor))

        shades_num += 1

    for c in root.findall('surface'):
        s_type = c.get('type')

        if s_type=='Sphere':
            for q in c.findall('shader'):
                my_ref = q.get('ref')
            center = np.array(c.findtext('center').split()).astype(np.float)
            radius = float(c.findtext('radius'))
            objects.append(Sphere(center, radius, my_ref))

        elif s_type=='Box':
            for q in c.findall('shader'):
                my_ref = q.get('ref')
            minPt = np.array(c.findtext('minPt').split()).astype(np.float)
            maxPt = np.array(c.findtext('maxPt').split()).astype(np.float)
            objects.append(Box(minPt, maxPt, my_ref))

        objects_num += 1

    for c in root.findall('light'):
        light_pos = np.array(c.findtext('position').split()).astype(np.float)
        light_int = np.array(c.findtext('intensity').split()).astype(np.float)
        lights.append(Light(light_pos, light_int))

        lights_num += 1

    #code.interact(local=dict(globals(), **locals()))  

   
    # Create an empty image
    channels=3
    img = np.zeros((imgSize[1], imgSize[0], channels), dtype=np.uint8)
    img[:,:]=0


    # replace the code block below!
    u = np.cross(projNormal, viewUp)
    v = np.cross(u, projNormal)
    w = projNormal

    real_u = -1*u/np.linalg.norm(u)
    real_v = v/np.linalg.norm(v)
    real_w = w/np.linalg.norm(w)

    pixelWidth = viewWidth/imgSize[0]
    pixelHeight = viewHeight/imgSize[1]

    start = viewPoint-projDistance*real_w-0.5*viewWidth*real_u+0.5*viewHeight*real_v
    start = start+0.5*pixelWidth*real_u+0.5*pixelHeight*real_v

    for i in np.arange(imgSize[1]):
        for j in np.arange(imgSize[0]):

            tmin = sys.maxsize
            
            sp = start+j*pixelWidth*real_u-i*pixelHeight*real_v
            rayDi = sp - viewPoint

            rayDir = rayDi/np.sqrt(np.dot(rayDi, rayDi))

            r = Ray(viewPoint, rayDir)
            color_i = -1

            for e in range(objects_num):
                flag, tmin = objects[e].intersect(r, tmin)
                if flag:
                    intersect_point = r.origin + tmin*r.direction
                    n = objects[e].get_normv(intersect_point)
                    for c in range(shades_num):
                        if shades[c].name==objects[e].my_ref:
                            # shades[c].diffuseColor.gammaCorrect(2.2)
                            # img[i][j] = shades[c].diffuseColor.toUINT8()
                            color_i = c
                            break

                    L = [0,0,0]
                   
                    for l in range(lights_num):
                        t = tmin
                        isit = 0
                        lay_s = np.linalg.norm(intersect_point-lights[l].position)
                        lay = (intersect_point-lights[l].position)/lay_s
                        line = Ray(lights[l].position, lay)
                        for x in range(objects_num):
                            f, t = objects[x].intersect(line, tmin)
                            if f:
                                if (lay_s-t)>(0.0001):
                                    isit = 1

                        if isit == 1:
                            continue
                        
                        l_vector = (lights[l].position-intersect_point)/np.linalg.norm(lights[l].position-intersect_point)
                        LC = objects[e].shading(r, n, l_vector, lights[l], shades[color_i])
                        L += LC
                    
                    LC = Color(L[0], L[1], L[2])
                    LC.gammaCorrect(2.2)
                    img[i][j] = LC.toUINT8()

    rawimg = Image.fromarray(img, 'RGB')
    #rawimg.save('out.png')
    rawimg.save(sys.argv[1]+'.png')
    
if __name__=="__main__":
    main()
