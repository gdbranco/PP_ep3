#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main()
{
	int j; //1048576 = 2^20
	cin >> j;
	ofstream file;
	file.open ("input.txt");
	file << j << "\n";
	float *a = new float[j];
	for (int i=0; i< j; i++) {
		a[i] = 1 + (float) (rand()) /( (float) (RAND_MAX/(100-1)));
		file << a[i] << " ";
	}
	file.close();
	return 0;
}

