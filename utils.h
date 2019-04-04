#include "packages.h"
#include "patterns.h"

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
	void image_expansion(unsigned char origin_image[][Image_Size], float expanded_image[][MAX_SIZE], int filter_size);
	int local_mean(float expanded_image[][MAX_SIZE], int r, int c, int filter_size);
	int local_median(float expanded_image[][MAX_SIZE], int r, int c, int filter_size);
	int max_in_3 (int a, int b, int c);
	int min_in_3 (int a, int b, int c);
	
	void get_local_histogram(float expanded_image[][MAX_SIZE], int r, int c, int window_size, int local_histogram[]);
	void get_histogram(unsigned char Imagedata[][Image_Size], int histogram[]);

	void filter_3(float expanded_image[][MAX_SIZE], float output_image[][Image_Size], vector<vector<float> > filter);
};

class Enhancement{
public:
	// hw0
	void flipping(unsigned char origin_image[][Image_Size]);
	void power_law_transform(unsigned char origin_image[][Image_Size], double p);

	// hw1
	void bucket_filling(int histogram[], int new_histogram[], vector<deque<pair<int, int> > >& mapping);
	void equilization(unsigned char Imagedata[][Image_Size], unsigned char new_imagedata[][Image_Size], vector<deque<pair<int, int> > > mapping);

	void decrease_brightness(unsigned char origin_image[][Image_Size], unsigned char new_image[][Image_Size], int d);
	void histogram_equalization_transfer_function(unsigned char Imagedata[][Image_Size], unsigned char new_imagedata[][Image_Size], int new_histogram[]);
	void histogram_equalization_bucket_filling(unsigned char Imagedata[][Image_Size], unsigned char new_imagedata[][Image_Size], int new_histogram[]);
	void local_histogram_equalization(unsigned char Imagedata[][Image_Size], unsigned char new_imagedata[][Image_Size], int new_histogram[], int window_size);

	// hw2
	int local_pseudomedian(float expanded_image[][MAX_SIZE], int r, int c, int filter_size);
	
	void low_pass_filtering(unsigned char origin_image[][Image_Size], unsigned char new_image[][Image_Size], int filter_size);
	void median_filtering(unsigned char origin_image[][Image_Size], unsigned char new_image[][Image_Size], int filter_size);
	void pseudomedian_filtering(unsigned char origin_image[][Image_Size], unsigned char new_image[][Image_Size], int filter_size);
	double metric_PSNR(unsigned char y_true[][Image_Size], unsigned char y_pred[][Image_Size]);
};


class Edge{
public:
	void dfs(unsigned char new_image[][Image_Size], int r, int c);

	void first_order_detection(unsigned char origin_image[][Image_Size], unsigned char new_image[][Image_Size], float threshold);
	void first_order_magnitude(unsigned char origin_image[][Image_Size], float image_magnitude[][Image_Size], float image_orientation[][Image_Size]);
	void second_order_laplacian(unsigned char origin_image[][Image_Size], float laplacian_image[][Image_Size]);
	void second_order_detection(unsigned char origin_image[][Image_Size], unsigned char new_image[][Image_Size], float threshold);
	void candy_detection(unsigned char origin_image[][Image_Size], unsigned char new_image[][Image_Size], float Tl, float Th, int filter_size, string & filter);
	void unsharp_masking(unsigned char origin_image[][Image_Size], unsigned char new_image[][Image_Size], float c);
};	

class Morphology{
public:
	vector<vector<unsigned char> > binary(vector<vector<unsigned char> >& origin_image);
	vector<vector<unsigned char> > complement(vector<vector<unsigned char> >& G);
	vector<vector<unsigned char> > dilation(vector<vector<unsigned char> >& G, vector<vector<int> >& H);
	vector<vector<unsigned char> > erosion(vector<vector<unsigned char> >& G, vector<vector<int> >& H);
	void erose(vector<vector<unsigned char> >& G, vector<vector<unsigned char> >& G_new, int a, int b);
	void dilate(vector<vector<unsigned char> >& G, vector<vector<unsigned char> >& G_new, int a, int b);
	vector<vector<unsigned char> > boundary_extract(vector<vector<unsigned char> >& origin_image);
	vector<vector<vector<unsigned char> > > connected_component_labeling(vector<vector<unsigned char> >& origin_image);
	vector<vector<unsigned char> > thinning(vector<vector<unsigned char> >& Imagedata);
	vector<vector<unsigned char> > skeletonizing(vector<vector<unsigned char> >& Imagedata);
};



























