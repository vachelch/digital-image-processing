#include "patterns.h"

bool Morphological_Cond_Pattern::check(vector<vector<unsigned char> >& image, int r, int c){
	if (image[r][c] == 0) return false;
	int M = image.size();
	int N = image[0].size();

	// cal bond count
	int bd_cnt = 0;
	for(int i=-1; i<= 1; i++)
		for(int j=-1; j<= 1; j++){
			if (!(i==0 && j == 0) && image[r+i][c+j] != 0){
				if ((i == -1 && j == 0) || (i == 1 && j == 0) || (i == 0 && j == 1) || (i == 0 && j == -1))
					bd_cnt += 2;
				else
					bd_cnt ++;
			}
		}

	if (patterns.find(bd_cnt) == patterns.end()) return false;

	for(int k = 0; k< patterns[bd_cnt].size(); k++){
		int match = 0;
		for(int i=0; i< 3; i++){
			for(int j=0; j< 3; j++){
				if (patterns[bd_cnt][k][i][j] != (image[r+i-1][c+j-1] > 0)) {
					break;
				}
				match ++;
			}
		}

		if (match == 9) return true;
	}

	return false;
}


vector<vector<unsigned char> > Morphological_Cond_Pattern::conditional_hit(vector<vector<unsigned char> >& image){
	int M = image.size();
	int N = image[0].size();

	vector<vector<unsigned char> > M_image(M, vector<unsigned char>(N, 0));
	for(int i=1; i< M-1; i++){
		for(int j=1; j< N-1; j++){
			bool hit = check(image, i, j);
			if (hit) M_image[i][j] = 1;
		}
	}

	return M_image;
}


vector<vector<unsigned char> > Morphological_Uncond_Pattern::unconditional_hit(vector<vector<unsigned char> >& image){
	int M = image.size();
	int N = image[0].size();

	vector<vector<unsigned char> > P_image(M, vector<unsigned char>(N, 0));
	for(int i=1; i< M-1; i++){
		for(int j=1; j< N-1; j++){
			bool hit = check(image, i, j);
			if (hit) P_image[i][j] = 1;
		}
	}

	return P_image;
}

bool Morphological_Uncond_Pattern::check(vector<vector<unsigned char> >& image, int r, int c){
	if (image[r][c] == 0) return false;
	int M = image.size();
	int N = image[0].size();

	for(int k = 0; k< patterns.size(); k++){
		int match = 0;
		int abc = 0;
		bool abc_1 = false;

		for(int i=0; i< 3; i++){
			for(int j=0; j< 3; j++){
				if (patterns[k][i][j] == -1 || patterns[k][i][j] == (image[r+i-1][c+j-1] > 0)) {
					match ++;
				}
				if (patterns[k][i][j] == -2){
					abc ++;
				}
				if (patterns[k][i][j] == -2 && image[r+i-1][c+j-1] > 0){
					abc_1 = true;
				}
			}
		}

		if (match == 9 && abc == 0) return true;
		if ((match + abc == 9) && abc_1) return true;
	}

	return false;
}



Morphological_Cond_Pattern::Morphological_Cond_Pattern(){
	vector<vector<unsigned char> > tmp(3, vector<unsigned char>(3, 0));
	// bond 4
	// 4.1
	vector<vector<unsigned char> > cur = tmp;
	cur[0][1] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	patterns[4].push_back(cur);
	// 4.2
	cur = tmp;
	cur[0][1] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	patterns[4].push_back(cur);
	// 4.3
	cur = tmp;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][1] = 1;
	patterns[4].push_back(cur);
	// 4.4
	cur = tmp;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][1] = 1;
	patterns[4].push_back(cur);
	
	// 4.5
	cur = tmp;
	cur[0][2] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][2] = 1;
	patterns[4].push_back(cur);
	// 4.6
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][1] = 1;
	patterns[4].push_back(cur);
	// 4.7
	cur = tmp;
	cur[0][0] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][0] = 1;
	patterns[4].push_back(cur);
	// 4.8
	cur = tmp;
	cur[1][1] = 1;
	cur[2][0] = 1;
	cur[2][1] = 1;
	cur[2][2] = 1;
	patterns[4].push_back(cur);

	// bond 6
	// 6.3
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	patterns[6].push_back(cur);
	// 6.4
	cur = tmp;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][2] = 1;
	patterns[6].push_back(cur);
	// 6.5
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	patterns[6].push_back(cur);
	// 6.6
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][0] = 1;
	patterns[6].push_back(cur);
	// 6.7
	cur = tmp;
	cur[0][0] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][0] = 1;
	cur[2][1] = 1;
	patterns[6].push_back(cur);
	// 6.8
	cur = tmp;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][0] = 1;
	cur[2][1] = 1;
	cur[2][2] = 1;
	patterns[6].push_back(cur);
	// 6.9
	cur = tmp;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][0] = 1;
	cur[2][1] = 1;
	cur[2][2] = 1;
	patterns[6].push_back(cur);
	// 6.10
	cur = tmp;
	cur[0][2] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][1] = 1;
	cur[2][2] = 1;
	patterns[6].push_back(cur);
	
	// bond 7
	// 7.1
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][2] = 1;
	patterns[7].push_back(cur);
	// 7.2
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][0] = 1;
	patterns[7].push_back(cur);
	// 7.3
	cur = tmp;
	cur[0][0] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][0] = 1;
	cur[2][1] = 1;
	cur[2][2] = 1;
	patterns[7].push_back(cur);
	// 7.4
	cur = tmp;
	cur[0][2] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][0] = 1;
	cur[2][1] = 1;
	cur[2][2] = 1;
	patterns[7].push_back(cur);

	// bond 8
	// 8.1
	cur = tmp;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][1] = 1;
	cur[2][2] = 1;
	patterns[8].push_back(cur);
	// 8.2
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	patterns[8].push_back(cur);
	// 8.3
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][0] = 1;
	cur[2][1] = 1;
	patterns[8].push_back(cur);
	// 8.4
	cur = tmp;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][0] = 1;
	cur[2][1] = 1;
	cur[2][2] = 1;
	patterns[8].push_back(cur);

	// bond 9
	// 9.1
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][1] = 1;
	cur[2][2] = 1;
	patterns[9].push_back(cur);
	// 9.2
	cur = tmp;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][0] = 1;
	cur[2][1] = 1;
	cur[2][2] = 1;
	patterns[9].push_back(cur);
	// 9.3
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][0] = 1;
	patterns[9].push_back(cur);
	// 9.4
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][2] = 1;
	patterns[9].push_back(cur);
	// 9.5
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][0] = 1;
	cur[2][1] = 1;
	patterns[9].push_back(cur);
	// 9.6
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][0] = 1;
	cur[2][1] = 1;
	cur[2][2] = 1;
	patterns[9].push_back(cur);
	// 9.7
	cur = tmp;
	cur[0][0] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][0] = 1;
	cur[2][1] = 1;
	cur[2][2] = 1;
	patterns[9].push_back(cur);
	// 9.8
	cur = tmp;
	cur[0][2] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][0] = 1;
	cur[2][1] = 1;
	cur[2][2] = 1;
	patterns[9].push_back(cur);

	// bond 10
	// 10.1
	tmp = vector<vector<unsigned char>> (3, vector<unsigned char>(3, 1));
	cur = tmp;
	cur[1][0] = 0;
	patterns[10].push_back(cur);
	// 10.2
	cur = tmp;
	cur[2][1] = 0;
	patterns[10].push_back(cur);
	// 10.3
	cur = tmp;
	cur[1][2] = 0;
	patterns[10].push_back(cur);
	// 10.4
	cur = tmp;
	cur[0][1] = 0;
	patterns[10].push_back(cur);
}


Thin_Pattern::Thin_Pattern(){
	vector<vector<unsigned char> > tmp(3, vector<unsigned char>(3, 0));
	vector<vector<unsigned char> > cur = tmp;
	/*** not the same with skeleton ***/
	// bond 5
	// 5.1
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	patterns[5].push_back(cur);
	// 5.2
	cur = tmp;
	cur[0][1] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][2] = 1;
	patterns[5].push_back(cur);
	// 5.3
	cur = tmp;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	patterns[5].push_back(cur);
	// 5.4
	cur = tmp;
	cur[0][2] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][1] = 1;
	patterns[5].push_back(cur);
	// 5.5
	cur = tmp;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	patterns[5].push_back(cur);
	// 5.6
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	patterns[5].push_back(cur);
	// 5.7
	cur = tmp;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][0] = 1;
	cur[2][1] = 1;
	patterns[5].push_back(cur);
	// 5.8
	cur = tmp;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][1] = 1;
	cur[2][2] = 1;
	patterns[5].push_back(cur);

	// bond 6
	// 6.1
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][2] = 1;
	patterns[6].push_back(cur);
	// 6.2
	cur = tmp;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][0] = 1;
	patterns[6].push_back(cur);
}

Skeleton_Pattern::Skeleton_Pattern(){
	vector<vector<unsigned char> > tmp(3, vector<unsigned char>(3, 0));
	vector<vector<unsigned char> > cur = tmp;

	/*** not the same with thining ***/
	// bond 11
	// 11.1
	tmp = vector<vector<unsigned char> > (3, vector<unsigned char>(3, 1));
	cur = tmp;
	cur[2][0] = 0;
	patterns[11].push_back(cur);
	// 11.2
	cur = tmp;
	cur[2][2] = 0;
	patterns[11].push_back(cur);
	// 11.3
	cur = tmp;
	cur[0][2] = 0;
	patterns[11].push_back(cur);
	// 11.4
	cur = tmp;
	cur[0][0] = 0;
	patterns[11].push_back(cur);
}



Morphological_Uncond_Pattern::Morphological_Uncond_Pattern(){
	vector<vector<int> > tmp(3, vector<int>(3, 0));

	// Spur
	// 1.1
	vector<vector<int> > cur = tmp;
	cur[0][2] = 1;
	cur[1][1] = 1;
	patterns.push_back(cur);
	// 1.2
	cur = tmp;
	cur[0][0] = 1;
	cur[1][1] = 1;
	patterns.push_back(cur);
	// 1.3
	cur = tmp;
	cur[1][1] = 1;
	cur[2][1] = 1;
	patterns.push_back(cur);
	// 1.4
	cur = tmp;
	cur[1][1] = 1;
	cur[1][2] = 1;
	patterns.push_back(cur);


	// L Cluster
	// 2.1
	cur = tmp;
	cur[0][2] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	patterns.push_back(cur);
	// 2.2
	cur = tmp;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][1] = 1;
	patterns.push_back(cur);
	// 2.3
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[1][1] = 1;
	patterns.push_back(cur);
	// 2.4
	cur = tmp;
	cur[0][0] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	patterns.push_back(cur);
	// 2.5
	cur = tmp;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][0] = 1;
	patterns.push_back(cur);
	// 2.6
	cur = tmp;
	cur[1][1] = 1;
	cur[2][0] = 1;
	cur[2][1] = 1;
	patterns.push_back(cur);
	// 2.7
	cur = tmp;
	cur[1][1] = 1;
	cur[2][1] = 1;
	cur[2][2] = 1;
	patterns.push_back(cur);
	// 2.8
	cur = tmp;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][2] = 1;
	patterns.push_back(cur);

	// 4-Connected offset
	// 3.1
	cur = tmp;
	cur[0][1] = 1;
	cur[0][2] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	patterns.push_back(cur);
	// 3.2
	cur = tmp;
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	patterns.push_back(cur);
	// 3.3
	cur = tmp;
	cur[0][1] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][2] = 1;
	patterns.push_back(cur);
	// 3.4
	cur = tmp;
	cur[0][2] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][1] = 1;
	patterns.push_back(cur);

	// Spur corner cluster
	// 4.1
	cur = tmp;
	cur[0][1] = -2;
	cur[1][2] = -2;
	cur[0][2] = 1;
	cur[1][1] = 1;
	cur[2][0] = 1;
	patterns.push_back(cur);
	// 4.2
	cur = tmp;
	cur[0][1] = -2;
	cur[1][0] = -2;
	cur[0][0] = 1;
	cur[1][1] = 1;
	cur[2][2] = 1;
	patterns.push_back(cur);
	// 4.3
	cur = tmp;
	cur[1][0] = -2;
	cur[2][1] = -2;
	cur[0][2] = 1;
	cur[1][1] = 1;
	cur[2][0] = 1;
	patterns.push_back(cur);
	// 4.4
	cur = tmp;
	cur[1][2] = -2;
	cur[2][1] = -2;
	cur[0][0] = 1;
	cur[1][1] = 1;
	cur[2][2] = 1;
	patterns.push_back(cur);

	// Corner cluster
	// 5.1
	cur = vector<vector<int> >(3, vector<int>(3, -1));
	cur[0][0] = 1;
	cur[0][1] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	patterns.push_back(cur);

	// Tee branch
	// 6.1
	cur = tmp;
	cur[0][0] = -1;
	cur[2][0] = -1;
	cur[0][1] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	patterns.push_back(cur);
	// 6.2
	cur = tmp;
	cur[0][2] = -1;
	cur[2][2] = -1;
	cur[0][1] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	patterns.push_back(cur);
	// 6.3
	cur = tmp;
	cur[0][2] = -1;
	cur[2][2] = -1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][1] = 1;
	patterns.push_back(cur);
	// 6.4
	cur = tmp;
	cur[0][0] = -1;
	cur[2][0] = -1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][1] = 1;
	patterns.push_back(cur);
	// 6.5
	cur = tmp;
	cur[0][0] = -1;
	cur[0][2] = -1;
	cur[0][1] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][1] = 1;
	patterns.push_back(cur);
	// 6.6
	cur = tmp;
	cur[2][0] = -1;
	cur[2][2] = -1;
	cur[0][1] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][1] = 1;
	patterns.push_back(cur);
	// 6.7
	cur = tmp;
	cur[2][0] = -1;
	cur[2][2] = -1;
	cur[0][1] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][1] = 1;
	patterns.push_back(cur);
	// 6.8
	cur = tmp;
	cur[0][0] = -1;
	cur[0][2] = -1;
	cur[0][1] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][1] = 1;
	patterns.push_back(cur);
	
	// Vee branch
	// 7.1
	cur.assign(3, vector<int>(3, 1));
	cur[2][0] = -2;
	cur[2][1] = -2;
	cur[2][2] = -2;
	cur[0][1] = -1;
	cur[1][0] = -1;
	cur[1][2] = -1;
	patterns.push_back(cur);
	// 7.2
	cur.assign(3, vector<int>(3, 1));
	cur[0][2] = -2;
	cur[1][2] = -2;
	cur[2][2] = -2;
	cur[0][1] = -1;
	cur[1][0] = -1;
	cur[2][1] = -1;
	patterns.push_back(cur);
	// 7.3
	cur.assign(3, vector<int>(3, 1));
	cur[0][0] = -2;
	cur[0][1] = -2;
	cur[0][2] = -2;
	cur[1][0] = -1;
	cur[1][2] = -1;
	cur[2][1] = -1;
	patterns.push_back(cur);
	// 7.4
	cur.assign(3, vector<int>(3, 1));
	cur[0][0] = -2;
	cur[1][0] = -2;
	cur[2][0] = -2;
	cur[0][1] = -1;
	cur[1][2] = -1;
	cur[2][1] = -1;
	patterns.push_back(cur);

	// Diagonal branch
	// 8.1
	cur = tmp;
	cur[0][0] = -1;
	cur[2][2] = -1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][0] = 1;
	patterns.push_back(cur);
	// 8.2
	cur = tmp;
	cur[0][2] = -1;
	cur[2][0] = -1;
	cur[0][1] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][2] = 1;
	patterns.push_back(cur);
	// 8.3
	cur = tmp;
	cur[0][0] = -1;
	cur[2][2] = -1;
	cur[0][2] = 1;
	cur[1][0] = 1;
	cur[1][1] = 1;
	cur[2][1] = 1;
	patterns.push_back(cur);
	// 8.4
	cur = tmp;
	cur[0][2] = -1;
	cur[2][0] = -1;
	cur[0][0] = 1;
	cur[1][1] = 1;
	cur[1][2] = 1;
	cur[2][1] = 1;
	patterns.push_back(cur);
}






















