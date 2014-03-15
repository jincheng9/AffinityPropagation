#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

//N is the number of two-dimension data points
//S is the similarity matrix
//R is the responsibility matrix
//A is the availabiltiy matrix
//iter is the maximum number of iterations
//lambda is the damping factor
const int N = 25;
double S[N][N] = {0};
double R[N][N] = {0};
double A[N][N] = {0};
int iter = 230;
double lambda = 0.9;

const char* dataFileName = "ToyProblemData.txt";
void readS(double S[N][N], const char* dfn) {
	//read data 
	ifstream myfile(dfn);
	
	double dataPoint[N][2] = {0};
	for(int i=0; i<N; i++) {
		myfile >> dataPoint[i][0] >> dataPoint[i][1];
	}
	myfile.close();
	
	int size = N*(N-1)/2;
	vector<double> tmpS;
	//compute similarity between data point i and j (i is not equal to j)
	for(int i=0; i<N-1; i++) {
		for(int j=i+1; j<N; j++) {
			S[i][j] = -((dataPoint[i][0]-dataPoint[j][0])*(dataPoint[i][0]-dataPoint[j][0])+(dataPoint[i][1]-dataPoint[j][1])*(dataPoint[i][1]-dataPoint[j][1]));
			S[j][i] = S[i][j];
			tmpS.push_back(S[i][j]); 
		}
	}
	//compute preferences for all data points: median 
	sort(tmpS.begin(), tmpS.end());
	double median = 0;
	
	if(size%2==0) 
		median = (tmpS[size/2]+tmpS[size/2-1])/2;
	else 
		median = tmpS[size/2];
	for(int i=0; i<N; i++) S[i][i] = median;
}

int main()
{
	readS(S, dataFileName);
	
	for(int m=0; m<iter; m++) {
	//update responsibility
		for(int i=0; i<N; i++) {
			for(int k=0; k<N; k++) {
				double max = -1e100;
				for(int kk=0; kk<k; kk++) {
					if(S[i][kk]+A[i][kk]>max) 
						max = S[i][kk]+A[i][kk];
				}
				for(int kk=k+1; kk<N; kk++) {
					if(S[i][kk]+A[i][kk]>max) 
						max = S[i][kk]+A[i][kk];
				}
				R[i][k] = (1-lambda)*(S[i][k] - max) + lambda*R[i][k];
			}
		}
	//update availability
		for(int i=0; i<N; i++) {
			for(int k=0; k<N; k++) {
				if(i==k) {
					double sum = 0.0;
					for(int ii=0; ii<i; ii++) {
						sum += max(0.0, R[ii][k]);
					}
					for(int ii=i+1; ii<N; ii++) {
						sum += max(0.0, R[ii][k]);
					}
					A[i][k] = (1-lambda)*sum + lambda*A[i][k];
				} else {
					double sum = 0.0;
					int maxik = max(i, k);
					int minik = min(i, k);
					for(int ii=0; ii<minik; ii++) {
						sum += max(0.0, R[ii][k]);
					}
					for(int ii=minik+1; ii<maxik; ii++) {
						sum += max(0.0, R[ii][k]);
					}
					for(int ii=maxik+1; ii<N; ii++) {
						sum += max(0.0, R[ii][k]);
					}
					A[i][k] = (1-lambda)*min(0.0, R[k][k]+sum) + lambda*A[i][k];
				}
			}
		}
	}
	
	//find the exemplar
	double E[N][N] = {0};
	vector<int> center;
	for(int i=0; i<N; i++) {
		E[i][i] = R[i][i] + A[i][i];
		if(E[i][i]>0) {
			center.push_back(i);
		}
	}
	//data point assignment, idx[i] is the exemplar for data point i
	int idx[N] = {0};
	for(int i=0; i<N; i++) {
		int idxForI = 0;
		double maxSim = -1e100;
		for(int j=0; j<center.size(); j++) {
			int c = center[j];
			if (S[i][c]>maxSim) {
				maxSim = S[i][c];
				idxForI = c;
			}
		}
		idx[i] = idxForI;
	}
	//output the assignment
	for(int i=0; i<N; i++) {
		//since the index of data points starts from zero, I add 1 to let it start from 1
		cout << idx[i]+1 << endl; 
	}
}


