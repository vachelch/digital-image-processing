#include "packages.h"
# include "utils.h"

int main(int argc, char *argv[]){
	string origin_name_1 = "../raw/sample1.raw";

	Image_IO *io = new Image_IO();
	vector<vector<unsigned char> > Imagedata = io->read_image(origin_name_1, 256, 256);

	Morphology *morph = new Morphology();
	// vector<vector<vector<unsigned char> > >  boundary = morph->connected_component_labeling(Imagedata);
	// io->write_image_rgb(boundary, "test_8.raw");

	vector<vector<unsigned char> > image_thined = morph->thinning(Imagedata);
	vector<vector<unsigned char> > image_skeletoned = morph->skeletonizing(Imagedata);
	io->write_image(image_thined, "test_12.raw");
	io->write_image(image_skeletoned, "test_13.raw");

	return 0;
}	


