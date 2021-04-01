import matplotlib.pyplot as plt
from skimage import io
from skimage.color import rgb2hsv
from skimage.color import hsv2rgb
from skimage.viewer import ImageViewer

rgb_img = io.imread('IMG_4703.jpg')
hsv_img = rgb2hsv(rgb_img)
hue_img = hsv_img[:, :, 0]

for i in range(0, rgb_img.shape[0]):
    for j in range(0, rgb_img.shape[1]):
        if(hsv_img[i,j,0] > 0.05 and hsv_img[i,j,0] < 0.95):    #If the hue is not red
            hsv_img[i,j,1] = 0                                  #Set the saturation to 0

rgb_result_img = hsv2rgb(hsv_img)

print("Image grayscaled.")  

hsv_result_img = rgb2hsv(rgb_result_img)
hue_hsv_res_img = []
for i in range(0, hsv_result_img.shape[0]):
    for j in range(0, hsv_result_img.shape[1]):
        hue_hsv_res_img.append(hsv_result_img[i,j,0])
    
print("HSV Results gathered")    
    
hue_hsv_original_img = []
for i in range(0, rgb_img.shape[0]):
    for j in range(0, rgb_img.shape[1]):
        hue_hsv_original_img.append(hsv_img[i,j,0])
        
print("HSV_2 Results gathered")  
        
plt.hist(hue_hsv_res_img, 255)
plt.xlabel('Hue')
plt.ylabel('Amount')
plt.title(r'Hue grayscaled image')
plt.show()

print("First plot created")

plt.hist(hsv_img[:, :, 0].flatten(), 255, color='red')
plt.xlabel('Hue')
plt.ylabel('Amount')
plt.title(r'Hue original image')
plt.show()

print("Second plot created")

viewer = ImageViewer(rgb_result_img)
viewer.show()
