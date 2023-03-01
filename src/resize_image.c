#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
    // TODO Fill in
    

    return get_pixel(im, round(x), round(y), c);
    
}

image nn_resize(image im, int w, int h)
{
    // TODO Fill in (also fix that first line)
    image im_new=make_image(w,h,im.c);

    float a=(float)im.w/w;
    float b=(float)im.h/h;

   
    
    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++){
            for(int k=0;k<im.c;k++){

                im_new.data[i+w*j+w*h*k] = nn_interpolate(im, (i*a+ 0.5*(a-1)), (j*b+0.5*(b-1)),k);
            }
        }
    }


    return im_new;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO

    int x1=floor(x);
    int x2=ceil(x);
    int y1=floor(y);
    int y2=ceil(y);

    float q11=get_pixel(im,x1,y1,c);
    float q12=get_pixel(im,x1,y2,c);
    float q21=get_pixel(im,x2,y1,c);
    float q22=get_pixel(im,x2,y2,c);

    float r1=q11*(x2-x)+q21*(x-x1);
    float r2=q12*(x2-x)+q22*(x-x1);

    float r=r1*(y2-y)+r2*(y-y1);

    return r;

}

image bilinear_resize(image im, int w, int h)
{
    // TODO
    image im_new=make_image(w,h,im.c);

    float a=(float)im.w/w;
    float b=(float)im.h/h;

   
    
    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++){
            for(int k=0;k<im.c;k++){

                im_new.data[i+w*j+w*h*k] = bilinear_interpolate(im, (i*a+ 0.5*(a-1)), (j*b+0.5*(b-1)),k);
            }
        }
    }


    return im_new;
}

