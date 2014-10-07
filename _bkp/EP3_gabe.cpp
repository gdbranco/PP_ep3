#include <iostream>
#include <cstdlib>
#include <ctime>
#include "mpi/mpi.h"

using namespace std;
using namespace MPI;

float Sum (int begin, int end, float *a) {
	int i, j=2, k=1;
	while ((end+k)/j >= 1)
	{
		i=begin;
		while((end >= i) && (end >= i+k))
		{
			a[i] = a[i] + a[i+k];
			i+=j;
		}
		k=j;
		j*=2;
	}
	return a[begin];
}

int main (int argc, char *argv[]) {
	int i=0, a_begin, a_end, a_size, sum=0;
	int world_size, world_rank;
	float *a, a_result=0, a_result_total=0;
	MPI::Status mpi_status;
	
	// Receive Input
	//cin >> a_size;
	a_size = 10000;
	srand(time(0)); 
	a = (float*)malloc(a_size*sizeof(float));
	/*while(i<a_size)
	{
		cin >> number;
		a[i] = number;
		i++;
	}*/
	for (i=1; i<=a_size; i++) {
		a[i] = i;
		sum += i;
	}
	
	Init(argc, argv);					// Initialize the MPI environment
	world_size = COMM_WORLD.Get_size();	// Get the size of the process
	world_rank = COMM_WORLD.Get_rank();	// Get the rank of the process
	
	a_begin = a_size*world_rank/world_size + 1;			// Subvector begin
	a_end = a_size*(world_rank + 1)/world_size;		// Subvector end
	a_result_total = Sum(a_begin, a_end, a);		// Local result

	// Reduction Operation
	if (world_rank != 0) {
		COMM_WORLD.Send(&a_result_total, 1, FLOAT, 0, 1);
	}
	else {
		for (i=1; i < world_size; i++) {
			COMM_WORLD.Recv(&a_result, 1, FLOAT, i, 1, mpi_status);
			a_result_total += a_result;
			cout << a_result<<endl;
		}
	}
	if (world_rank == 0) {
		cout << "Result = " << a_result_total << endl;
		cout << "Expected = " << sum << endl;
	}
	
	// Finalize the MPI environment
	MPI_Finalize();
	return 0;
}
