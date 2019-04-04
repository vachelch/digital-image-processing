# Digital Image Processing
## Description
C++ realization of varieties of image processing functions, including: image enhancement, edge detection, morphology processing etc. More contents will be obtained and code style is under revising.

## What this repo incldue, currently?
You can find all APIs in the header `Utils.h`

#### Image IO:
```ascii
* Read Image (gray level)
* Write Image (gray level)
* Write Image RGB 
* Write Image RGB 
```

#### Enhancement:
```ascii
* Transform
* Denoise
    * Low pass filtering (for uniform nosie)
    * Median Filtering (for impulse nosie)

* Equilization
    * Bucket Filling
    * Transfer Function
    * Local Equilization

* PSNR
    * Obtain the PSNR score of the given image
```

#### Edge: 
```ascii
* Edge Detection
    * First Order Edge Detection
    * Second Order Edge Detection
    * Canny Edge Detection

* Edge Crispening
    * Unsharp Masking
```

#### Morphology:
```ascii
* Dilation
* Erosion
* Boundary Extraction
* Connected Component Labeling
* Thinning
* Skeletonizing
```

## How to use?
```bash
git clone git@github.com:vachelch/digital-image-processing.git
cd digital-image-processing
make main
```

## What's more?
You may find that '.raw' image is unable to be openned, that is because '.raw' is not the usual 'jpg' or 'png' image format, it's all raw pixel value in it. If you meet the problem, and meanwhile you don't have photoshop installed in you PC, I recommender [Raw Pixel Viewer](http://rawpixels.net/) for you.




