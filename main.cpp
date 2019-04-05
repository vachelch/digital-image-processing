#include "packages.h"
# include "utils.h"

int main(int argc, char *argv[]){
    string origin_name = "raw/sample1.raw";

    Image_IO *io = new Image_IO();
    vector<vector<unsigned char> > Imagedata = io->read_image(origin_name, 256, 256);

    Morphology *morph = new Morphology();
    vector<vector<vector<unsigned char> > >  connected_image = morph->connected_component_labeling(Imagedata);
    io->write_image_rgb(connected_image, "test.raw");

    cout << "Succeed! test.raw has been saved in current directory." << endl;
    return 0;
}	


