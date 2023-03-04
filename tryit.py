from uwimg import *

im = load_image("data/dogsmall.jpg")
a = nn_resize(im, im.w*4, im.h*4)
save_image(a, "dog4x-nn")

im = load_image("data/dogsmall.jpg")
b = bilinear_resize(im, im.w*4, im.h*4)
save_image(b, "dog4x-bl")

from uwimg import *
im = load_image("data/dog.jpg")
c = nn_resize(im, im.w//7, im.h//7)
save_image(c, "dog7th-bl")

from uwimg import *
im = load_image("data/dog.jpg")
f = make_box_filter(7)
blur = convolve_image(im, f, 1)
save_image(blur, "dog-box7")

from uwimg import *
im = load_image("data/dog.jpg")
f = make_emboss_filter()
blur = convolve_image(im, f, 1)
clamp_image(blur)
save_image(blur, "dog-box_emboss")

from uwimg import *
im = load_image("data/dog.jpg")
f = make_highpass_filter()
blur = convolve_image(im, f, 0)
clamp_image(blur)
save_image(blur, "dog-box_highpass_0")

from uwimg import *
im = load_image("data/dog.jpg")
f = make_highpass_filter()
blur = convolve_image(im, f, 1)
clamp_image(blur)
save_image(blur, "dog-box_highpass_1")



from uwimg import *
im = load_image("data/dog.jpg")
f = make_sharpen_filter()
blur = convolve_image(im, f, 1)
clamp_image(blur)
save_image(blur, "dog-box_sharpen")

from uwimg import *
im = load_image("data/dog.jpg")
f = make_gaussian_filter(2)
blur = convolve_image(im, f, 1)
save_image(blur, "dog-gauss2")


from uwimg import *
im = load_image("data/dog.jpg")
f = make_gaussian_filter(2)
lfreq = convolve_image(im, f, 1)
hfreq = im - lfreq
reconstruct = lfreq + hfreq
save_image(lfreq, "low-frequency")
save_image(hfreq, "high-frequency")
save_image(reconstruct, "reconstruct")

from uwimg import *
im = load_image("data/ron.png")
f = make_gaussian_filter(2)
lfreq_ron = convolve_image(im, f, 1)
hfrw_ron= im - lfreq_ron
save_image(hfrw_ron, "high-frequency_ron")
save_image(lfreq_ron, "low-frequency_ron")

im = load_image("data/dumbledore.png")
lfreq_dumbledore = convolve_image(im, f, 1)
high_freq_dumbledore = im - lfreq_dumbledore
save_image(lfreq_dumbledore, "low-frequency_dumbledore")
save_image(high_freq_dumbledore, "high-frequency_dumbledore")

reconstruct1 = lfreq_ron + high_freq_dumbledore
reconstruct2= lfreq_dumbledore + hfrw_ron
save_image(reconstruct1, "reconstruct_ron_dumbledore")
save_image(reconstruct2, "reconstruct_dumbledore_ron")


from uwimg import *
im = load_image("data/dog.jpg")
res = sobel_image(im)
mag = res[0]
feature_normalize(mag)
save_image(mag, "magnitude")

from uwimg import *
im = load_image("data/dog.jpg")
res = colorize_sobel(im)
feature_normalize(res)
save_image(res, "colorize_sobel")



