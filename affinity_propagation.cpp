#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 25;
double S[N][N] = {0};
double R[N][N] = {0};
double A[N][N] = {0};
string dataFileName = "ToyProblemData.txt";
void readS(double S[N][N], string dfn) {
	//read data 
	ifstream myfile("ToyProblemData.txt");
	double dataPoint[N][2] = {0};
	for(int i=0; i<N; i++) {
		myfile >> dataPoint[i][0] >> dataPoint[i][1];
	}
	myfile.close();
	
	int size = N*(N-1)/2;
	vector<double> tmpS(size);
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
	int iter = 230;
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
				R[i][k] = S[i][k] - max;
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
					A[i][k] = sum;
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
					A[i][k] = min(0.0, R[k][k]+sum);
				}
			}
		}
	}
	
	//find the exemplar
	double E[N][N] = {0};
	vector<int> center(10);
	int num = 0;
	for(int i=0; i<N; i++) {
		E[i][i] = R[i][i] + A[i][i];
		if(E[i][i]>0) {
			center.push_back(i);
			num++;
		}
	}
	cout << num << endl;
	for(int i=0; i<num; i++) {
		cout << center[i] << endl;
	}
	
}


