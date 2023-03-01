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


