#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    // TODO Fill this in'
    float pixel=im.data[x+y*im.w+c*im.w*im.h];
    return pixel;

}

void set_pixel(image im, int x, int y, int c, float v)
{

    im.data[x+y*im.w+c*im.w*im.h]=v;
    // TODO Fill this in
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);

    for(int i=0;i<im.w*im.h*im.c;i++){
        copy.data[i]=im.data[i];
    }

    // TODO Fill this in
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);

    for(int i=0;i<im.w;i++){
        for(int j=0;j<im.h;j++){
            float r=get_pixel(im,i,j,0);
            float g=get_pixel(im,i,j,1);
            float b=get_pixel(im,i,j,2);
            float gray_pixel=0.299*r+0.587*g+0.114*b;
            set_pixel(gray,i,j,0,gray_pixel);
        }
        
    }


    // TODO Fill this in
    return gray;
}

void shift_image(image im, int c, float v)
{
    for(int i=0;i<im.w;i++){
        for(int j=0;j<im.h;j++){
            float pixel=get_pixel(im,i,j,c);
            set_pixel(im,i,j,c,pixel+v);
        }
    }
    // TODO Fill this in
}

void clamp_image(image im)
{
    // TODO Fill this in

    for(int i=0;i<im.w;i++){
        for(int j=0;j<im.h;j++){
            for(int k=0;k<im.c;k++){
                float pixel=get_pixel(im,i,j,k);
                if(pixel>1){
                    set_pixel(im,i,j,k,1);
                }
                if(pixel<0){
                    set_pixel(im,i,j,k,0);
                }
            }
        }
    }


}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
    float r, g, b, min, max, c, h, s, v;
    for (int y = 0; y < im.h; y++) {
        for (int x = 0; x < im.w; x++) {
            r = im.data[x + y*im.w];
            g = im.data[x + y*im.w + im.w*im.h];
            b = im.data[x + y*im.w + 2*im.w*im.h];
            min = three_way_min(r, g, b);
            max = three_way_max(r, g, b);
            c = max - min;
            v = max;
            if (v != 0) {
                s = c / v;
            } else {
                s = 0;
            }

            if (c != 0) {
                if (v == r) {
                    h = (g - b) / c;
                } else if (v == g) {
                    h = ((b - r) / c) + 2;
                } else {
                    h = ((r - g) / c) + 4;
                }
            } else {
                h = 0;
            }

            h /= 6;
            if (h < 0) {
                h++;
            }
            im.data[x + y*im.w] = h;
            im.data[x + y*im.w + im.w*im.h] = s;
            im.data[x + y*im.w + 2*im.w*im.h] = v;
        }
    }
}


void hsv_to_rgb(image im)
{
    // TODO Fill this in
    float h, s, v, c, max, min, r, g, b, h_temp;
    for (int y = 0; y < im.h; y++) {
        for (int x = 0; x < im.w; x++) {
            h = im.data[x + y*im.w];
            s = im.data[x + y*im.w + im.w*im.h];
            v = im.data[x + y*im.w + 2*im.w*im.h];
            c = s * v;
            max = v;

            if (v != c) {
            min = v - c;
            } else {
                min = 0.0;
            }
            h_temp = h * 6;
            if (c == 0) {
                r = v;
                g = v;
                b = v;
            } else if (h_temp > 5 && h_temp < 6) {
                r = max;
                g = min;
                b = ((((h_temp /  6) - 1) * 6 * c) - g) * -1;
            } else if (h_temp == 5) {
                r = max;
                g = min;
                b = max;
            } else if (h_temp < 5 && h_temp > 4) {
                g = min;
                r = (h_temp - 4) * c + g;
                b = max;
            } else if (h_temp == 4) {
                r = min;
                g = min;
                b = max;
            } else if (h_temp < 4 && h_temp > 3) {
                r = min;
                g = (((h_temp - 4) * c) - r) * -1;
                b = max;
            } else if (h_temp == 3) {
                r = min;
                g = max;
                b = max;
            } else if (h_temp < 3 && h_temp > 2) {
                r = min;
                g = max;
                b = ((h_temp - 2) * c) + r;
            } else if (h_temp == 2) {
                r = min;
                g = max;
                b = min;
            } else if (h_temp < 2 && h_temp > 1) {
                g = max;
                b = min;
                r = (((h_temp - 2) * c) - b) * -1;
            } else if (h_temp == 1) {
                r = max;
                g = max;
                b = min;
            } else if (h_temp < 1 && h_temp > 0) {
                r = max;
                b = min;
                g = (h_temp * c) + b;
            } else {
                r = max;
                g = min;
                b = min;
            }
            im.data[x + y*im.w] = r;
            im.data[x + y*im.w + im.w*im.h] = g;
            im.data[x + y*im.w + 2*im.w*im.h] = b;
        }
    }
}