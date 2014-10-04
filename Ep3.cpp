#include <iostream>
#include <cstdlib>
#include <mpi/mpi.h>
using namespace std;
float soma_tree(unsigned int inicio, unsigned int tam_vetor,float *vetor);
int main()
{
	unsigned int i=0, tam_vetor;
	float elemento, *vetor=NULL;
	int size,rank;
	float total_result=0,local_result;
	unsigned int local_tamvetor,local_inicio,local_fim;
	MPI::Status mpi_status;
	cin >> tam_vetor;
	vetor = (float*)malloc(tam_vetor*sizeof(float));
	if(vetor)
	{
		while(i<tam_vetor)
		{
			cin >> elemento;
			*(vetor+i) = elemento;
			i++;
		}
	}
	MPI::Init();
	//MPI_Init(NULL,NULL);
	rank = MPI::COMM_WORLD.Get_rank();
	size = MPI::COMM_WORLD.Get_size();
	//MPI_Comm_size(MPI::COMM_WORLD, &size);
	//MPI_Comm_rank(MPI::COMM_WORLD, &rank);
	local_tamvetor = tam_vetor/size;
	local_inicio = rank*local_tamvetor;
	local_fim   = local_inicio+local_tamvetor;
	local_result = soma_tree(local_inicio,local_fim,vetor);
	if(rank!=0)
	{
		//MPI_Send(&local_result, 1, MPI_FLOAT,0,0,MPI_COMM_WORLD);
		MPI::COMM_WORLD.Send(&local_result,1,MPI::FLOAT,0,0);
	}
	else
	{
		total_result = local_result;
		for(unsigned int source = 1;source < (unsigned)size; source++)
		{
			//MPI_Recv(&local_result,1,MPI_FLOAT,source,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI::COMM_WORLD.Recv(&local_result,1,MPI::FLOAT,source,0,mpi_status);
			total_result += local_result;
		}
	}
	if(rank == 0)
	{
		cout << total_result << endl;
	}
	//MPI_Finalize();
	MPI::Finalize();
	return 0;
}
float soma_tree(unsigned int inicio, unsigned int tam_vetor,float *vetor)
{
	unsigned int i,c=0,l=2,j=0,k=1;
	while(j<(float)tam_vetor/2)
	{
		i=inicio;
		c=0; 
		//cout << endl;
		while(i<tam_vetor && i+k<tam_vetor)
		{
			//if(i+k<tam_vetor)
			//{
				//cout << "Vetor[" << i << "] :" << vetor[i] << " vetor[" << i+k << "] :" << vetor[i+k];
				//cout << "vetor[" << i << "] : " << vetor[i] << endl;
				vetor[i] = vetor[i] + vetor[i+k];
				//cout << " = Vetor[" << i << "]c :" << vetor[i] << endl;
				//cout << endl;
			//}
			i+=l;
			c++;
		}
		//unsigned int t=0;
		//while(t<tam_vetor)
		//{
			//cout << vetor[t]<< ' ';
			//t++;
		//}
		j++;
		k*=2;
		l*=2;
	}
	return vetor[inicio];
}
