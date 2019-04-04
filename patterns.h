#include "packages.h"

class Morphological_Cond_Pattern{
public:
	map<int, vector<vector<vector<unsigned char> > > > patterns;

	Morphological_Cond_Pattern();
	vector<vector<unsigned char> > conditional_hit(vector<vector<unsigned char> >& image);
	bool check(vector<vector<unsigned char> >& image, int r, int c);
};

class Thin_Pattern: public Morphological_Cond_Pattern{
public:
	Thin_Pattern();
};


class Skeleton_Pattern:  public Morphological_Cond_Pattern{
public:
	Skeleton_Pattern();
};


class Morphological_Uncond_Pattern{
public:
	vector<vector<vector<int> > > patterns;
	Morphological_Uncond_Pattern();
	vector<vector<unsigned char> > unconditional_hit(vector<vector<unsigned char> >& image);
	bool check(vector<vector<unsigned char> >& image, int r, int c);
};


