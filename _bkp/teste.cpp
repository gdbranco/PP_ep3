#include <iostream>
#include <mpi/mpi.h>
using namespace std;
double f(double x)
{
	return x*x;
}
double trap(
			double left_endpt,
			double right_endpt,
			int trap_count,
			double base_len)
{
	double estimate,x;
	int i;
	estimate = (f(left_endpt) + f(right_endpt))/2.0;
	for(i=1;i<=trap_count-1;i++)
	{
		x = left_endpt + i*base_len;
		estimate += f(x);
	}
	estimate = estimate*base_len;
	return estimate;
}
int main(void)
{
	int my_rank, comm_sz, n=1024, local_n;
	double a=0.0,b=3.0,h,local_a,local_b;
	double local_int, total_int;
	int source;
	
	//MPI::Init();
	MPI_Init(NULL,NULL);
	//my_rank = MPI::COMM_WORLD.Get_rank();
	//comm_sz = MPI::COMM_WORLD.Get_size();
	MPI_Comm_size(MPI::COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI::COMM_WORLD, &my_rank);

	h = (b-a)/n;
	local_n = n/comm_sz;

	local_a = a+my_rank*local_n*h;
	local_b = local_a+local_n*h;
	local_int = trap(local_a,local_b,local_n,h);
	if(my_rank!=0)
	{
		MPI_Send(&local_int, 1, MPI_FLOAT,0,0,MPI_COMM_WORLD);
		//MPI::COMM_WORLD.Send(&local_int,1,MPI_DOUBLE,0,0);
	}
	else
	{
		total_int = local_int;
		for(source = 1;source<comm_sz;source++)
		{	
			MPI_Recv(&local_int,1,MPI_FLOAT,source,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			total_int +=local_int;
		}
	}
	if(my_rank==0)
	{
		cout << "With n = " << n << " trapezoids, our estimate\n";
		cout << "of the integral from " << a <<" to " << b<< " = " << total_int << endl;
	}
	MPI_Finalize();
	return 0;
}
