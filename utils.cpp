#include "utils.h"

void cnt_edge(unsigned char new_image[][Image_Size]){
	cout << "\nedge percentage\n";	
	int cnt = 0;
	for(int i=0; i< Image_Size; i++)
		for(int j=0; j< Image_Size; j++)
			cnt += (new_image[i][j] == 255);

	cout << cnt *100.0 / (Image_Size*Image_Size)<< endl;
}

// Image_IO
vector<vector<unsigned char> > Image_IO::read_image(string name, int M, int N){
	vector<vector<unsigned char> > Imagedata(M, vector<unsigned char> (N));

	fstream fs;
	fs.open(name, ios::in);
	if (!fs)
	{
		cout<<"Cannot open file!"<<endl;
		exit(0);
	}

	for(int i=0; i< Imagedata.size(); i++)
		for(int j=0; j< Imagedata[0].size(); j++)
			fs >> Imagedata[i][j];

	fs.close();

	return Imagedata;
}

void Image_IO::write_image(vector<vector<unsigned char> >& Imagedata, string name){
	fstream fs;
	fs.open(name, ios::out);
	if (!fs)
	{
		cout<<"Cannot open file!"<<endl;
		return ;
	}

	for(int i=0; i< Imagedata.size(); i++)
		for(int j=0; j< Imagedata[0].size(); j++)
			fs << Imagedata[i][j];

	fs.close();
}

void Image_IO::write_histogram(int histogram[], string name){
	fstream fs;
	fs.open(name, ios::out);
	if (!fs)
	{
		cout<<"Cannot open file!"<<endl;
		return;
	}
	for(int i=0; i< Color_Size; i++){
		fs << histogram[i] << " ";
	}
	fs << endl;

	fs.close();
}

vector<vector<vector<unsigned char> > > Image_IO::read_image_rgb(string name, int M, int N){
	vector<vector<vector<unsigned char> > >Imagedata(3, vector<vector<unsigned char> >(M, vector<unsigned char>(N)));
	fstream fs;
	fs.open(name, ios::in);
	if (!fs)
	{
		cout<<"Cannot open file!"<<endl;
		exit(00);
	}

	for(int i=0; i< 3; i++){
		for(int j=0; j< Imagedata[0].size(); j++)
			for(int k=0; k< Imagedata[0][0].size(); k++)
				fs >> Imagedata[i][j][k];
	}
	
	fs.close();

	return Imagedata;
}

void Image_IO::write_image_rgb(vector<vector<vector<unsigned char> > >& Imagedata, string name){
	fstream fs;
	fs.open(name, ios::out);
	if (!fs)
	{
		cout<<"Cannot open file!"<<endl;
		return ;
	}

	for(int i=0; i< 3; i++)
		for(int j=0; j< Imagedata[0].size(); j++)
			for(int k=0; k< Imagedata[0][0].size(); k++)
				fs << Imagedata[i][j][k];

	fs.close();
}




// Utils
void Utils::image_expansion(unsigned char origin_image[][Image_Size], float expanded_image[][MAX_SIZE], int filter_size){
	int padding = (filter_size -1)/2;

	for(int i= padding; i< Image_Size + padding; i++){
		for(int j= padding; j< Image_Size + padding; j++){
			expanded_image[i][j] = origin_image[i-padding][j-padding];
		}
	}

	int repeat = 2;
	while (repeat--){
		int start = 0;
		int end = Image_Size + 2 * padding - 1;
		for(int k=padding; k>= 1; k--){
			for(int j = start; j< end; j++)
				expanded_image[start][j] = expanded_image[start+ (k*2-1)][j];
			for(int i = start; i< end; i++)
				expanded_image[i][end] = expanded_image[i][end - (k*2-1)];

			for(int j = end; j> start ; j--)
				expanded_image[end][j] = expanded_image[end- (k*2-1)][j];

			for(int i = end; i> start ; i--)
				expanded_image[i][start] = expanded_image[i][start+ (k*2-1)];

			start ++;
			end --;
		}
	}

}

int Utils::local_mean(float expanded_image[][MAX_SIZE], int r, int c, int filter_size){
	int mean = 0;
	int diff = (filter_size -1) / 2;

	for(int i = r - diff; i<= r + diff; i++){
		for(int j= c - diff; j<= c + diff; j++){
			mean += expanded_image[i][j];
		}
	}

	return mean / pow(diff*2 + 1, 2);
}

int Utils::local_median(float expanded_image[][MAX_SIZE], int r, int c, int filter_size){
	int mean = 0;
	int diff = (filter_size -1) / 2;
	vector<int> vec;

	for(int i = r - diff; i<= r + diff; i++)
		for(int j= c - diff; j<= c + diff; j++)
			vec.push_back(expanded_image[i][j]);

	sort(vec.begin(), vec.end());
	int median = vec[vec.size() / 2];
			
	return median;
}

int Utils::max_in_3 (int a, int b, int c){
	int l = max(a, b);
	return max(l, c);
}

int Utils::min_in_3 (int a, int b, int c){
	int s = min(a, b);
	return min(s, c);
}

void Utils::get_local_histogram(float expanded_image[][MAX_SIZE], int r, int c, int window_size, int local_histogram[]){
	for(int i=0; i< Color_Size; i++) local_histogram[i] = 0;

	int diff = (window_size -1)/2;

	for(int i = r-diff; i<= r + diff; i++){
		for(int j= c-diff; j<= c + diff; j++){
			int color = expanded_image[i][j];
			local_histogram[color] ++;
		}
	}
}

void Utils::get_histogram(unsigned char Imagedata[][Image_Size], int histogram[]){
	for (int i=0; i< Image_Size; i++)
		histogram[i] = 0;

	for(int i=0; i< Image_Size; i++){
		for(int j=0; j< Image_Size; j++){
			int color = Imagedata[i][j];
			histogram[color] ++;
		}
	}
}
void Utils::filter_3(float expanded_image[][MAX_SIZE], float output_image[][Image_Size], vector<vector<float> > filter){
	memset(output_image, 0, sizeof(float)*Image_Size*Image_Size);

	int filter_size = filter.size();
	int pad = (filter_size - 1) / 2;
	for(int i=pad; i< Image_Size + pad; i++)
		for(int j=pad; j< Image_Size+pad; j++)
			for(int k=-1*pad; k<=pad; k++)
				for(int l=-1*pad; l<=pad; l++)
					output_image[i-pad][j-pad] += expanded_image[i+k][j+l] * filter[k+pad][l+pad];
}


int Enhancement::local_pseudomedian(float expanded_image[][MAX_SIZE], int r, int c, int filter_size){
	Utils * util = new Utils();

	int mean = 0;
	int diff = (filter_size -1) / 2;

	int min_max_x = INT_MAX;
	int max_min_x = 0;
	int min_max_y = INT_MAX;
	int max_min_y = 0;

	// find PMED_y
	for(int i = r - diff; i<= r + diff-2; i++){
		int larger = util->max_in_3(expanded_image[i][c], expanded_image[i+1][c], expanded_image[i+2][c]);
		int smaller = util->min_in_3(expanded_image[i][c], expanded_image[i+1][c], expanded_image[i+2][c]);

		min_max_y = min(min_max_y, larger);
		max_min_y = max(max_min_y, smaller);
	}

	// find PMED_x
	for(int j = c - diff; j<= c + diff-2; j++){
		int larger = util->max_in_3(expanded_image[r][j], expanded_image[r][j+1], expanded_image[r][j+2]);
		int smaller = util->min_in_3(expanded_image[r][j], expanded_image[r][j+1], expanded_image[r][j+2]);

		min_max_x = min(min_max_x, larger);
		max_min_x = max(max_min_x, smaller);
	}

	return round(0.5*max(max_min_x, max_min_y) + 0.5*min(min_max_x, min_max_y));
	// return min(min_max_x, min_max_y);
	// return max(max_min_x, max_min_y);

	// float PMED_x = 0.5* (min_max_x + max_min_x);
	// float PMED_y = 0.5* (min_max_y + max_min_y);
	// return round(0.5* (PMED_x + PMED_y));
}

void Enhancement::bucket_filling(int histogram[], int new_histogram[], vector<deque<pair<int, int> > >& mapping){
	// get new histogram
	int total = 0;
	for (int i=0; i< Color_Size; i++)
		total += histogram[i];

	int average = total / Color_Size;
	for(int i=0; i< Color_Size; i++)
		new_histogram[i] = average;

	// get mapping
	deque< pair<int, int> > color_cnt;
	for(int i=0; i< Color_Size; i++){
		// complement 
		// positive
		if (color_cnt.empty()){
			int diff = histogram[i] - average;
			if (diff != 0) color_cnt.push_back(make_pair(i, diff));
		}
		else if (color_cnt[0].second > 0){
			int cnt_cur = 0;
			while(!color_cnt.empty() && cnt_cur < average){
				int color_candi = color_cnt[0].first;
				int cnt_candi = color_cnt[0].second;

				if (cnt_candi <= (average - cnt_cur)){
					cnt_cur += cnt_candi;
					mapping[color_candi].push_back(make_pair(i, cnt_candi));
					color_cnt.pop_front();
				}
				else{
					// update mappig , color_cnt, cnt_cur
					mapping[color_candi].push_back(make_pair(i, average - cnt_cur));
					color_cnt[0].second -= (average - cnt_cur);
					cnt_cur = average;
				}
			}

			cnt_cur += histogram[i];
			int diff = cnt_cur - average;
			if (diff != 0) color_cnt.push_back(make_pair(i, diff));
		}
		// negtive
		else {
			int cnt_cur = histogram[i];
			while(!color_cnt.empty() && cnt_cur > 0){
				int color_candi = color_cnt[0].first;
				int cnt_candi = color_cnt[0].second;

				if (cnt_candi + cnt_cur >= 0){
					cnt_cur += cnt_candi;
					mapping[i].push_back(make_pair(color_candi, abs(cnt_candi)));
					color_cnt.pop_front();
				}
				else{
					// update queue, mappig, color_cnt
					mapping[i].push_back(make_pair(abs(color_candi), cnt_cur));
					color_cnt[0].second += cnt_cur;
					cnt_cur = 0;
				}
			}

			int diff = cnt_cur - average;
			if (diff != 0) color_cnt.push_back(make_pair(i, diff));
		}
	}
}

void Enhancement::equilization(unsigned char Imagedata[][Image_Size], unsigned char new_imagedata[][Image_Size], vector<deque<pair<int, int> > > mapping){
	for(int i=0; i< Image_Size; i++){
		for(int j=0; j< Image_Size; j++){
			int color = Imagedata[i][j];
			if (mapping[color].empty()){
				new_imagedata[i][j] = Imagedata[i][j];
			}
			else{
				int color_candi = mapping[color][0].first;
				int cnt_candi = mapping[color][0].second;

				new_imagedata[i][j] = color_candi;

				mapping[color][0].second --;
				cnt_candi --;
				if (cnt_candi == 0) mapping[color].pop_front();
			}
		}
	}
}




// Image_Processing
void Enhancement::flipping(unsigned char origin_image[][Image_Size]){
	for(int i=0; i<Image_Size; i++){
		int l = 0, r = Image_Size-1;
		while(l < r){
			unsigned char tmp = origin_image[i][l];
			origin_image[i][l] = origin_image[i][r];
			origin_image[i][r] = tmp;

			l ++, r--;
		}
	}
}

void Enhancement::power_law_transform(unsigned char origin_image[][Image_Size], double p){
	for(int i=0; i< Image_Size; i++){
		for(int j=0; j< Image_Size; j++){
			origin_image[i][j] = round(pow(origin_image[i][j] * 1.0 / 255, p) * 255);
		}
	}
}

void Enhancement::decrease_brightness(unsigned char origin_image[][Image_Size], unsigned char new_image[][Image_Size], int d){
	for(int i=0; i< Image_Size; i++){
		for(int j=0; j< Image_Size; j++){
			new_image[i][j] = origin_image[i][j] / d;
		}
	}
}

/*********************************
below is denoising.  
*************************************/
void Enhancement::low_pass_filtering(unsigned char origin_image[][Image_Size], unsigned char new_image[][Image_Size], int filter_size){
	Utils *utils = new Utils();
	float expanded_image[MAX_SIZE][MAX_SIZE];
	utils->image_expansion(origin_image, expanded_image, filter_size);

	// convolution
	int padding = (filter_size-1) / 2;
	for(int i=0; i< Image_Size; i++){
		for(int j=0; j< Image_Size; j++){
			new_image[i][j] = utils->local_mean(expanded_image, padding+i, padding+j, filter_size);
		}
	}
}

void Enhancement::median_filtering(unsigned char origin_image[][Image_Size], unsigned char new_image[][Image_Size], int filter_size){
	Utils *utils = new Utils();
	float expanded_image[MAX_SIZE][MAX_SIZE];
	utils->image_expansion(origin_image, expanded_image, filter_size);

	// convolution
	int padding = (filter_size-1) / 2;
	for(int i=0; i< Image_Size; i++){
		for(int j=0; j< Image_Size; j++){
			new_image[i][j] = utils->local_median(expanded_image, padding+i, padding+j, filter_size);
		}
	}
}

void Enhancement::pseudomedian_filtering(unsigned char origin_image[][Image_Size], unsigned char new_image[][Image_Size], int filter_size){
	Utils *utils = new Utils();
	float expanded_image[MAX_SIZE][MAX_SIZE];
	utils->image_expansion(origin_image, expanded_image, filter_size);

	// convolution
	int padding = (filter_size-1) / 2;
	for(int i=0; i< Image_Size; i++){
		for(int j=0; j< Image_Size; j++){
			new_image[i][j] = local_pseudomedian(expanded_image, padding+i, padding+j, filter_size);
		}
	}
}

/*******************
below is equalization.  
*******************/
void Enhancement::histogram_equalization_transfer_function(unsigned char Imagedata[][Image_Size], unsigned char new_imagedata[][Image_Size], int new_histogram[]){
	int histogram[Color_Size] = {0};

	Utils *util = new Utils();
	util->get_histogram(Imagedata, histogram);
	for (int i=0; i< Color_Size; i++) new_histogram[i] = 0;

	int total = 0;
	for(int i=0; i< Color_Size; i++)
		total += histogram[i];

	// get new histogram
	int mapping[Color_Size];
	int sum = 0;
	for(int i=0; i< Color_Size; i++){
		sum += histogram[i];
		int color = round(sum * 1.0 / total * 255);
		int cnt = histogram[i];
		
		mapping[i] = color;
		new_histogram[color] += cnt;
	}

	// mapping to new image
	for(int i=0; i< Image_Size; i++){
		for(int j=0; j< Image_Size; j++){
			int color = Imagedata[i][j];
			new_imagedata[i][j] = mapping[color];
		}
	}
}

void Enhancement::histogram_equalization_bucket_filling(unsigned char Imagedata[][Image_Size], unsigned char new_imagedata[][Image_Size], int new_histogram[]){
	Utils *util = new Utils();

	int histogram[Color_Size] = {0};
	util->get_histogram(Imagedata, histogram);
	for (int i=0; i< Color_Size; i++) new_histogram[i] = 0;
	vector<deque<pair<int, int> > > mapping(Color_Size);

	bucket_filling(histogram, new_histogram, mapping);
	equilization(Imagedata, new_imagedata, mapping);
}

void Enhancement::local_histogram_equalization(unsigned char Imagedata[][Image_Size], unsigned char new_imagedata[][Image_Size], int new_histogram[], int window_size){
	int local_histogram[] = {0};
	Utils *util = new Utils();
	float expanded_image[MAX_SIZE][MAX_SIZE];
	util->image_expansion(Imagedata, expanded_image, window_size);

	int padding = (window_size-1)/ 2;
	for(int i=padding; i< Image_Size + padding; i++){
		for(int j=padding; j < Image_Size + padding; j++){
			util->get_local_histogram(expanded_image, i, j, window_size, local_histogram);
			
			// perform equlization on (i, j)
			int summation = 0;
			int color = expanded_image[i][j];
			for (int k=0; k <= color; k++)
				summation += local_histogram[k];

			new_imagedata[i-padding][j-padding] = summation * 255 / (window_size* window_size) ;
		}
	}

	// new histogram
	for (int i=0; i< Color_Size; i++) new_histogram[i] = 0;
	util->get_histogram(new_imagedata, new_histogram);
}



double Enhancement::metric_PSNR(unsigned char y_true[][Image_Size], unsigned char y_pred[][Image_Size]){
	double mse = 0;
	for(int i=0; i< Image_Size; i++){
		for(int j=0; j< Image_Size; j++){
			mse += (y_true[i][j] - y_pred[i][j]) * (y_true[i][j] - y_pred[i][j]);
		}
	}
	// mse = mse / (Size * Size);
	double psnr = 10 * log10(255*255 * 1.0 * Image_Size* Image_Size / mse );

	return psnr;
}


void Edge::first_order_detection(unsigned char origin_image[][Image_Size], unsigned char new_image[][Image_Size], float threshold){
	// 3 points gradient
	memset(new_image, 0, sizeof(unsigned char)*Image_Size*Image_Size);
	float image_magnitude[Image_Size][Image_Size];
	float image_orientation[Image_Size][Image_Size];
	first_order_magnitude(origin_image, image_magnitude, image_orientation);

	
	for(int i=0; i< Image_Size; i++){
		for(int j=0; j< Image_Size; j++){
			new_image[i][j] = (image_magnitude[i][j] > threshold? 255: 0);
		}
	}
}

void Edge::first_order_magnitude(unsigned char origin_image[][Image_Size], float image_magnitude[][Image_Size], float image_orientation[][Image_Size]){
	Utils *utils = new Utils();
	int filter_size = 3;
	int padding = 1;
	float expanded_image[MAX_SIZE][MAX_SIZE];
	utils->image_expansion(origin_image, expanded_image, filter_size);
	
	// 3 points gradient
	for(int j= padding; j< Image_Size + padding; j++){
		for(int k= padding; k< Image_Size + padding; k++){
			int G_c = expanded_image[j][k] - expanded_image[j+1][k];
			int G_r = expanded_image[j][k] - expanded_image[j][k-1];

			float G = sqrt(G_c*G_c + G_r*G_r);

			image_magnitude[j-padding][k-padding] = G;
			image_orientation[j-padding][k-padding] = atan(G_c*1.0 / G_r);
		}	
	}
}

void Edge::second_order_laplacian(unsigned char origin_image[][Image_Size], float laplacian_image[][Image_Size]){
	Utils *util = new Utils();
	int filter_size = 3;
	int padding = 1;
	float expanded_image[MAX_SIZE][MAX_SIZE];
	util->image_expansion(origin_image, expanded_image, filter_size);

	// 4 neighbor 
	vector<vector<float> >H(3, vector<float>(3, 0));
	H[0][1] = -1 * 0.25;
	H[1][0] = -1 * 0.25;
	H[1][1] = 4 * 0.25;
	H[1][2] = -1 * 0.25;
	H[2][1] = -1 * 0.25;

	util->filter_3(expanded_image, laplacian_image, H);
}

void Edge::second_order_detection(unsigned char origin_image[][Image_Size], unsigned char new_image[][Image_Size], float threshold){
	// 4 neighbor 
	memset(new_image, 0, sizeof(unsigned char)*Image_Size*Image_Size);
	float laplacian_image[Image_Size][Image_Size] = {0};
	second_order_laplacian(origin_image, laplacian_image);

	for(int i=1; i< Image_Size-1; i++){
		for(int j=1; j< Image_Size-1; j++){
			if (abs(laplacian_image[i][j]) <= threshold){
				bool zero_cross_x = (laplacian_image[i][j-1] * laplacian_image[i][j+1] < 0);
				bool zero_cross_y = (laplacian_image[i-1][j] * laplacian_image[i+1][j] < 0);
				// bool zero_cross_xy = (laplacian_image[i-1][j-1] * laplacian_image[i+1][j+1] < 0) 
										// || (laplacian_image[i-1][j+1] * laplacian_image[i+1][j-1] < 0);

				if (zero_cross_x || zero_cross_y) new_image[i][j] = 255;
			}
		}
	}
}

void Edge::dfs(unsigned char new_image[][Image_Size], int r, int c){
	if (r < 0 || r >= Image_Size || c < 0 || c>= Image_Size || new_image[r][c] != 2) return ;
	
	new_image[r][c] = 255;
	for(int i=-1; i<=1; i++){
		for(int j=-1; j<= 1; j++){
			if (!(i == 0&& j==0)) dfs(new_image, r+i, c+j);
		}
	}
}
	
void Edge::candy_detection(unsigned char origin_image[][Image_Size], unsigned char new_image[][Image_Size], float Tl, float Th, int filter_size, string& filter){
	memset(new_image, 0, sizeof(unsigned char)*Image_Size*Image_Size);
	// step 1, noise reduction
	Enhancement *enhance = new Enhancement();
	unsigned char filted_image[Image_Size][Image_Size] = {0};
	if (filter == "lowPass")
		enhance->low_pass_filtering(origin_image, filted_image, filter_size);
	else if (filter == "median"){
		enhance->median_filtering(origin_image, filted_image, filter_size);
		enhance->low_pass_filtering(filted_image, filted_image, filter_size);
	}
		

	else{
		for (int i=0; i< Image_Size; i++)
			for (int j=0; j< Image_Size; j++)
				filted_image[i][j] = origin_image[i][j];
	}

	// step 2, gradient magnitude and orientation
	float image_magnitude[Image_Size][Image_Size];
	float image_orientation[Image_Size][Image_Size];
	first_order_magnitude(filted_image, image_magnitude, image_orientation);

	// step 3, non-maximal suppression
	for(int i=0; i<Image_Size; i++){
		for(int j=0; j< Image_Size; j++){
			// tend to vertical to x
			if (abs(image_orientation[i][j]) > atan(1)){
				if (i == 0 || i == Image_Size - 1)
					image_magnitude[i][j] = 0;
				else{
					if (!(image_magnitude[i][j] > image_magnitude[i-1][j] && image_magnitude[i][j] > image_magnitude[i+1][j]))
						image_magnitude[i][j] = 0;
				}
			}
			// tend to vertical to y
			else{
				if (j == 0 || j == Image_Size - 1)
					image_magnitude[i][j] = 0;
				else{
					if (!(image_magnitude[i][j] > image_magnitude[i][j-1] && image_magnitude[i][j] > image_magnitude[i][j+1]))
						image_magnitude[i][j] = 0;
				}
			}
		}
	}

	// step 4, threshoding, background 0, candidate 2, edge 255
	memset(new_image, 2, sizeof(unsigned char)*Image_Size*Image_Size);
	for(int i=0; i<Image_Size; i++){
		for(int j=0; j< Image_Size; j++){
			if (image_magnitude[i][j] < Tl) new_image[i][j] = 0;
			else if (image_magnitude[i][j] > Th) new_image[i][j] = 255;
		}
	}

	// step 5, connect 
	for(int i=0; i< Image_Size; i++)
		for(int j=0; j< Image_Size; j++)
			if (new_image[i][j] == 1)  {
				for(int k=-1; k<= 1; k++)
					for(int l=-1; l<=1; l++)
						if (!(k== 0 && l == 0)) dfs(new_image, i+k, j+l);
			}
	for(int i=0; i< Image_Size; i++)
		for(int j=0; j< Image_Size; j++)
			if(new_image[i][j] == 2) new_image[i][j] = 0;
}


void Edge::unsharp_masking(unsigned char origin_image[][Image_Size], unsigned char new_image[][Image_Size], float c){
	float high_coeff = c / (2*c - 1);
	float low_coeff = (1-c) / (2*c - 1);

	Utils *util = new Utils();
	int filter_size = 5;
	
	Enhancement *enhance = new Enhancement();
	unsigned char low_passed_image[Image_Size][Image_Size];
	enhance->low_pass_filtering(origin_image, low_passed_image, filter_size);

	for(int i=0; i< Image_Size; i++)
		for(int j=0; j< Image_Size; j++){
			float res = high_coeff*origin_image[i][j] - low_coeff*low_passed_image[i][j];
			if (res > 0)
				new_image[i][j] = res;
			else
				new_image[i][j] = 0;
		}
}


vector<vector<unsigned char> > Morphology::binary(vector<vector<unsigned char> >& origin_image){
	int M = origin_image.size();
	int N = origin_image[0].size();
	vector<vector<unsigned char> > G = origin_image;

	for(int i=0; i< M; i++)
		for(int j=0; j< N; j++)
			G[i][j] = origin_image[i][j] > 0? 1: 0;

	return G;
}


vector<vector<unsigned char> > Morphology::complement(vector<vector<unsigned char> >& G){
	vector<vector<unsigned char> > G_c = G;
	int M = G.size();
	int N = G[0].size();

	for(int i=0; i< M; i++)
		for(int j=0; j< N; j++)
			G_c[i][j] = G[i][j] == 0? 1 : 0;

	return G_c;
}

vector<vector<unsigned char> > Morphology::dilation(vector<vector<unsigned char> >& G, vector<vector<int> >& H){
	int M = H.size();
	int N = H[0].size();
	int o_r = (M - 1) / 2;
	int o_c = (N - 1) / 2;

	vector<vector<unsigned char> > G_new(G.size(), vector<unsigned char>(G[0].size(), 0));

	for(int i=0; i < M; i++)
		for(int j=0; j< N; j++){
			if (H[i][j])
				dilate(G, G_new, o_r - i, o_c - j);
		}

	return G_new;
}

void Morphology::dilate(vector<vector<unsigned char> >& G, vector<vector<unsigned char> >& G_new, int a, int b){
	int M = G.size();
	int N = G[0].size();

	for(int i=0; i< M; i++)
		for(int j=0; j< N; j++){
			if ( 0<= i + a && i + a < M && 0 <= j+b && j+b < N)
				G_new[i][j] = G_new[i][j] | G[i+a][j+b];
			else
				G_new[i][j] = 0;
		}
}

vector<vector<unsigned char> > Morphology::erosion(vector<vector<unsigned char> >& G, vector<vector<int> >& H){
	int M = H.size();
	int N = H[0].size();
	int o_r = (M - 1) / 2;
	int o_c = (N - 1) / 2;

	vector<vector<unsigned char> > G_new(G.size(), vector<unsigned char>(G[0].size(), 1));

	for(int i=0; i < M; i++)
		for(int j=0; j< N; j++){
			if (H[i][j])
				erose(G, G_new, o_r - i, o_c - j);
		}

	return G_new;
}

void Morphology::erose(vector<vector<unsigned char> >& G, vector<vector<unsigned char> >& G_new, int a, int b){
	int M = G.size();
	int N = G[0].size();

	for(int i=0; i< M; i++)
		for(int j=0; j< N; j++){
			if ( 0<= i + a && i + a < M && 0 <= j+b && j+b < N)
				G_new[i][j] = G_new[i][j] & G[i+a][j+b];
			else
				G_new[i][j] = 0;
		}
}


vector<vector<unsigned char> > subtract(vector<vector<unsigned char> >& image_a, vector<vector<unsigned char> >& image_b){
	int M = image_a.size();
	int N = image_a[0].size();

	vector<vector<unsigned char> > res = image_a;
	for(int i=0; i< M; i++){
		for(int j=0; j< N; j++){
			if (image_a[i][j] != 0 && image_b[i][j] != 0)
				res[i][j] = 0;
		}
	}

	return res;
}


vector<vector<unsigned char> > Morphology::boundary_extract(vector<vector<unsigned char> >& origin_image) {
	int M = origin_image.size();
	int N = origin_image[0].size();

	vector<vector<unsigned char> > G = binary(origin_image);


	vector<vector<int> > H(3, vector<int>(3, 1));
	vector<vector<unsigned char> > G_erosed = erosion(G, H);

	G = subtract(G, G_erosed);

	vector<vector<unsigned char> > boundary = origin_image;
	for(int i=0; i< M; i++)
		for(int j=0; j< N; j++){
			if (G[i][j] == 0) boundary[i][j] = 0;
		}

	return boundary;
}




void dfs(vector<vector<unsigned char> >& inside, vector<vector<unsigned char> >& visited, int r, int c, int color){
	int M = inside.size();
	int N = inside[0].size();

	visited[r][c] = 1;
	inside[r][c] = color;

	for(int i=-1; i<= 1; i++){
		for(int j=-1; j<= 1; j++){
			if (0<= r+i && r+i < M && 0<= c+j && c+j < N && !visited[r+i][c+j] && inside[r+i][c+j] != 0){
				dfs(inside, visited, r+i, c+j, 0);
			}
		}
	}
}

int statistic_nonzero(vector<vector<unsigned char> >& origin_image){
	int total = 0;
	for(int i=0; i< origin_image.size(); i++)
		for(int j=0; j< origin_image[0].size(); j++)
			total += (origin_image[i][j] != 0);

	return total;
}

vector<vector<unsigned char> > intersect(vector<vector<unsigned char> >& image_a, vector<vector<unsigned char> >& image_b){
	int M = image_a.size();
	int N = image_a[0].size();
	vector<vector<unsigned char> > res = image_a;
	int cnt = 0;

	for(int i=0; i< M; i++)
		for(int j=0; j< N; j++){
			if (image_a[i][j] == 0 || image_b[i][j] == 0) 
				res[i][j] = 0;
			if (image_a[i][j] != 0 && image_a[i][j] != 0)
				cnt ++;
		}

	cout << "intersect cnt: " << cnt << endl;
	cout << "nonzero points: " << statistic_nonzero(res) << endl;

	return res;
}

vector<vector<vector<unsigned char> > > Morphology::connected_component_labeling(vector<vector<unsigned char> >& origin_image){
	int M = origin_image.size();
	int N = origin_image[0].size();

	vector<vector<unsigned char> > inside = origin_image;

	// per inside per color
	vector<int> colors;
	vector<vector<unsigned char> > visited(M, vector<unsigned char>(N, 0));
	
	for(int i=0; i< M; i++){
		for(int j=0; j< N; j++){
			if (inside[i][j] != 0 && !visited[i][j]){
				int color = colors.size() + 1;
				colors.push_back(color);
				dfs(inside, visited, i, j, color);
			}
		}
	}

	// hole filling
	vector<vector<int> > H(3, vector<int>(3, 1));
	int init_cnt = statistic_nonzero(origin_image);
	int nonzero_cnt = 0;
	while(init_cnt != nonzero_cnt){
		inside = dilation(inside, H);
		inside = intersect(inside, origin_image);
		nonzero_cnt = statistic_nonzero(inside);
	}
	
	// generate color rgb
	srand(0);
	map<int, vector<int> > rgbs_dict;
	for(int i=0; i< colors.size(); i++){
		int color = colors[i];
		
		vector<int> cur;
		for(int j=0; j< 3; j++)
			cur.push_back(rand() % 256);

		rgbs_dict[color] = cur;
	}

	// generate image with rgb
	vector<vector<vector<unsigned char> > > res_image(3, vector<vector<unsigned char> >(M, vector<unsigned char>(N)));
	for(int i=0; i< M; i++)
		for(int j=0; j< N; j++){
			int color = inside[i][j];
			if (color){
				for(int k=0; k< 3; k++){
					res_image[k][i][j] = rgbs_dict[color][k];
				}
			}
		}

	return res_image;
}


vector<vector<unsigned char> > union_matrix(vector<vector<unsigned char> > &image_a, vector<vector<unsigned char> > &image_b){
	int M = image_a.size();
	int N = image_a[0].size();
	vector<vector<unsigned char> > res = image_a;
	
	for (int i=0; i< M; i++)
		for(int j=0; j< N; j++)
			// res[i][j] = image_a[i][j] || image_b[i][j];
			if (image_a[i][j])
				res[i][j] = image_a[i][j];
			else{
				res[i][j] = image_b[i][j];
			}

	return res;
}

vector<vector<unsigned char> > Morphology::thinning(vector<vector<unsigned char> >& Imagedata){
	int cnt_last = statistic_nonzero(Imagedata);
	int cnt_cur = 0;
	vector<vector<unsigned char> > cur = Imagedata;

	while(cnt_last != cnt_cur){
		cnt_last = cnt_cur;

		// stage 1
		Thin_Pattern *thin_cond = new Thin_Pattern();
		vector<vector<unsigned char> > M = thin_cond->conditional_hit(cur);
		// stage 2
		Morphological_Uncond_Pattern *uncond = new Morphological_Uncond_Pattern();
		vector<vector<unsigned char> > P = uncond->unconditional_hit(M);

		vector<vector<unsigned char> > M_complet = complement(M);

		vector<vector<unsigned char> > U = union_matrix(P, M_complet);

		cur = intersect(cur, U);
		cnt_cur = statistic_nonzero(cur);
	}

	return cur;
}


vector<vector<unsigned char> > Morphology::skeletonizing(vector<vector<unsigned char> >& Imagedata){
	int cnt_last = statistic_nonzero(Imagedata);
	int cnt_cur = 0;
	vector<vector<unsigned char> > cur = Imagedata;

	while(cnt_last != cnt_cur){
		cnt_last = cnt_cur;

		// stage 1
		Skeleton_Pattern *skelet_cond = new Skeleton_Pattern();
		vector<vector<unsigned char> > M = skelet_cond->conditional_hit(cur);
		// stage 2
		Morphological_Uncond_Pattern *uncond = new Morphological_Uncond_Pattern();
		vector<vector<unsigned char> > P = uncond->unconditional_hit(M);

		vector<vector<unsigned char> > M_complet = complement(M);

		vector<vector<unsigned char> > U = union_matrix(P, M_complet);

		cur = intersect(cur, U);
		cnt_cur = statistic_nonzero(cur);
	}

	return cur;
}





















