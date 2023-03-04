#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853

void l1_normalize(image im)
{
    // TODO
    float sum=0;
    for(int i=0;i<im.w*im.h*im.c;i++){
        sum+=im.data[i];
    }

    for(int i=0;i<im.w*im.h*im.c;i++){
        im.data[i]=im.data[i]/sum;
    }

}

image make_box_filter(int w)
{
    // TODO
    image box=make_image(w,w,1);
    for(int i=0;i<w*w;i++){
        box.data[i]=1;
    }
    l1_normalize(box);
    return box;
}
   

image convolve_image(image im, image filter, int preserve)
{
    // TODO
    assert(filter.c==im.c || filter.c==1);

    image conv=make_image(im.w,im.h,im.c);

    image conv_npres=make_image(im.w,im.h,1);

    for(int i=0;i<im.w;i++){
        for(int j=0;j<im.h;j++ ){
            for(int k=0;k<im.c;k++){

                float sum=0;
                for(int l=0;l<filter.w;l++){
                    for(int m=0;m<filter.h;m++){
                        int x=i+l-filter.w/2;
                        int y=j+m-filter.h/2;
                        if(x>=0 && x<im.w && y>=0 && y<im.h){
                            if(filter.c==1){
                                sum+=get_pixel(im,x,y,k)*get_pixel(filter,l,m,0);
                            }
                            else{
                                sum+=get_pixel(im,x,y,k)*get_pixel(filter,l,m,k);
                            }
                        }
                    }
                }
                if(preserve==1){
                    set_pixel(conv,i,j,k,sum);
                }
                else{
                    set_pixel(conv_npres,i,j,0,sum);
                }

            }
        }
    }

    if(preserve==1){
        return conv;
    }
    else{
        return conv_npres;
    }
    

    
}

image make_highpass_filter()
{
    // TODO
    image high=make_image(3,3,1);
    high.data[0]=0;
    high.data[1]=-1;
    high.data[2]=0;
    high.data[3]=-1;
    high.data[4]=4;
    high.data[5]=-1;
    high.data[6]=0;
    high.data[7]=-1;
    high.data[8]=0;
    return high;
}

image make_sharpen_filter()
{
    // TODO
    image sharp=make_image(3,3,1);
    sharp.data[0]=0;
    sharp.data[1]=-1;
    sharp.data[2]=0;
    sharp.data[3]=-1;
    sharp.data[4]=5;
    sharp.data[5]=-1;
    sharp.data[6]=0;
    sharp.data[7]=-1;
    sharp.data[8]=0;
    return sharp;
    
}

image make_emboss_filter()
{
    // TODO
    image emboss=make_image(3,3,1);
    emboss.data[0]=-2;
    emboss.data[1]=-1;
    emboss.data[2]=0;
    emboss.data[3]=-1;
    emboss.data[4]=1;
    emboss.data[5]=1;
    emboss.data[6]=0;
    emboss.data[7]=1;
    emboss.data[8]=2;
    return emboss;

    
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: TODO

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: TODO

image make_gaussian_filter(float sigma)
{
    // TODO
    int size=ceil(sigma*6);
    if(size%2==0){
        size++;
    }
    image gauss=make_image(size,size,1);
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            float x=i-size/2;
            float y=j-size/2;
            float val=exp(-(x*x+y*y)/(2*sigma*sigma))/(TWOPI*sigma*sigma);
            set_pixel(gauss,i,j,0,val);
        }
    }

    l1_normalize(gauss);
    return gauss;
}

image add_image(image a, image b)
{
    // TODO
    assert(a.w==b.w && a.h==b.h && a.c==b.c);
    image added=make_image(a.w,a.h,a.c);
    for(int i=0;i<a.w*a.h*a.c;i++){
        added.data[i]=a.data[i]+b.data[i];
    }
    return added;

}

image sub_image(image a, image b)
{   
    assert(a.w==b.w && a.h==b.h && a.c==b.c);
    image sub=make_image(a.w,a.h,a.c);
    for(int i=0;i<a.w*a.h*a.c;i++){
        sub.data[i]=a.data[i]-b.data[i];
    }
    return sub;


    // TODO
}

image make_gx_filter()
{
    // TODO
    image gx=make_image(3,3,1);
    gx.data[0]=-1;
    gx.data[1]=0;
    gx.data[2]=1;
    gx.data[3]=-2;
    gx.data[4]=0;
    gx.data[5]=2;
    gx.data[6]=-1;
    gx.data[7]=0;
    gx.data[8]=1;
    return gx;

    
}

image make_gy_filter()
{
    // TODO
    image gy=make_image(3,3,1);
    gy.data[0]=-1;
    gy.data[1]=-2;
    gy.data[2]=-1;
    gy.data[3]=0;
    gy.data[4]=0;
    gy.data[5]=0;
    gy.data[6]=1;
    gy.data[7]=2;
    gy.data[8]=1;
    return gy;
   
}

void feature_normalize(image im)
{
    // TODO
    float min=im.data[0];
    float max=im.data[0];

    for(int i=0;i<im.w*im.h*im.c;i++){
        if(im.data[i]<min){
            min=im.data[i];
        }
        if(im.data[i]>max){
            max=im.data[i];
        }
    }
    if(max==min){
        
        for(int i=0;i<im.w*im.h*im.c;i++){
            im.data[i]=0;
        }
        return;

    }

    for(int i=0;i<im.w*im.h*im.c;i++){
        im.data[i]=(im.data[i]-min)/(max-min);
    }
    return;
}

image *sobel_image(image im)
{
    // TODO
    image gx=make_gx_filter();
    image gy=make_gy_filter();

    image conv_x=convolve_image(im,gx,0);
    image conv_y=convolve_image(im,gy,0);

    image *sobel=(image *)calloc(2,sizeof(image));
    sobel[0]=make_image(im.w,im.h,1);
    sobel[1]=make_image(im.w,im.h,1);

    for(int i=0;i<im.w*im.h;i++){
        sobel[0].data[i]=sqrt(conv_x.data[i]*conv_x.data[i]+conv_y.data[i]*conv_y.data[i]);
        sobel[1].data[i]=atan2(conv_y.data[i],conv_x.data[i]);
    }
    free_image(conv_x);
    free_image(conv_y);
    free_image(gx);
    free_image(gy);
    return sobel;
}

//colorise sobel using hue and saturation and value

image colorize_sobel(image im)
{
    // TODO
    image *sobel=sobel_image(im);
    feature_normalize(sobel[0]);
    feature_normalize(sobel[1]);

    image color=make_image(im.w,im.h,3);
    int hue=50;
    int sat=1;
    int val=2;
    
   
}
