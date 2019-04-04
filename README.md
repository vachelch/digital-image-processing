# Digital Image Processing
## Description
A C++ realization of varieties of image processing functions, including: image enhancement, edge detection, morphology processing etc. More contents will be obtained and code style is under revising.

## What this repo incldue, currently?
### Image IO:
```ascii
* Read Image (gray level)
* Write Image (gray level)
* Write Image RGB 
* Write Image RGB 
```

### Enhancement:
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

### Edge: 
```ascii
* Edge Detection
  * First Order Edge Detection
  * Second Order Edge Detection
  * Canny Edge Detection
* Edge Crispening
  * Unsharp Masking
```

### Morphology:
```ascii
  * Dilation
  * Erosion
  * Boundary Extraction
  * Connected Component Labeling
  * thinning
  * skeletonizing
```


## How to use?
You can find all APIs in the header `Utils.h`
```C++
class Image_IO{
public:
  vector<vector<unsigned char> > read_image(string name, int M, int N);
  void write_image(vector<vector<unsigned char> >& Imagedata, string name);
  vector<vector<vector<unsigned char> > > read_image_rgb(string name, int M, int N);
  void write_image_rgb(vector<vector<vector<unsigned char> > >& Imagedata, string name);
  void write_histogram(int histogram[], string name);
};

class Utils{
public:
  void image_expansion(unsigned char origin_image[][Image_Size], float expanded_image[][MAX_SIZE],
     int filter_size);
  void get_local_histogram(float expanded_image[][MAX_SIZE], int r, int c, int window_size, 
     int local_histogram[]);
  void get_histogram(unsigned char Imagedata[][Image_Size], int histogram[]);
};

class Enhancement{
public:
  // Transform
  void power_law_transform(unsigned char origin_image[][Image_Size], double p);

  // Equalization
  void histogram_equalization_transfer_function(unsigned char Imagedata[][Image_Size], 
     unsigned char new_imagedata[][Image_Size], int new_histogram[]);
  void histogram_equalization_bucket_filling(unsigned char Imagedata[][Image_Size],
     unsigned char new_imagedata[][Image_Size], int new_histogram[]);
  void local_histogram_equalization(unsigned char Imagedata[][Image_Size],
     unsigned char new_imagedata[][Image_Size], int new_histogram[], int window_size);
  
  // Denoise
  void low_pass_filtering(unsigned char origin_image[][Image_Size], 
     unsigned char new_image[][Image_Size], int filter_size);
  void median_filtering(unsigned char origin_image[][Image_Size], 
     unsigned char new_image[][Image_Size], int filter_size);
  
  // PSNR 
  double metric_PSNR(unsigned char y_true[][Image_Size], unsigned char y_pred[][Image_Size]);
};


class Edge{
public:
  // Edge Detection
  void first_order_detection(unsigned char origin_image[][Image_Size],
     unsigned char new_image[][Image_Size], float threshold);
  void second_order_laplacian(unsigned char origin_image[][Image_Size],
     float laplacian_image[][Image_Size]);
  void second_order_detection(unsigned char origin_image[][Image_Size],
     unsigned char new_image[][Image_Size], float threshold);
  void candy_detection(unsigned char origin_image[][Image_Size],
     unsigned char new_image[][Image_Size], float Tl, float Th, int filter_size, string & filter);
  
  // Edge Crispening
  void unsharp_masking(unsigned char origin_image[][Image_Size], 
     unsigned char new_image[][Image_Size], float c);
};  

class Morphology{
public:
  vector<vector<unsigned char> > dilation(vector<vector<unsigned char> >& G, vector<vector<int> >& H);
  vector<vector<unsigned char> > erosion(vector<vector<unsigned char> >& G, vector<vector<int> >& H);
  vector<vector<unsigned char> > boundary_extract(vector<vector<unsigned char> >& origin_image);
  vector<vector<vector<unsigned char> > > connected_component_labeling(
     vector<vector<unsigned char> >& origin_image);
  vector<vector<unsigned char> > thinning(vector<vector<unsigned char> >& Imagedata);
  vector<vector<unsigned char> > skeletonizing(vector<vector<unsigned char> >& Imagedata);
};

```




