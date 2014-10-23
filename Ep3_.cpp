#include <iostream>
#include <mpi.h>
#include <sys/time.h>
#define ROOT 0
using namespace std;
float soma_tree(unsigned int tam_vetor,float *vetor);
int main()
{
	unsigned int tam_vetor;
	float *vetor=NULL,elemento;
	int size,rank;
	int offset;
	struct timeval start,end;
	MPI::Status mpi_status;
	MPI::Init();
	rank = MPI::COMM_WORLD.Get_rank();
	size = MPI::COMM_WORLD.Get_size();
	//Leitura e broadcast dos dados iniciais
	if(rank==ROOT)
	{
		  cin >> tam_vetor;
	}
	MPI::COMM_WORLD.Bcast(&tam_vetor,1,MPI::INT,0);
	unsigned int elementos_por_proc = tam_vetor/size;
	vetor = new float[tam_vetor];
	if(rank==ROOT)
	{
		for(unsigned int i=0;i<tam_vetor;i++)
		{
			cin >> elemento;
			vetor[i] = elemento;
		}
	}
	MPI::COMM_WORLD.Barrier();
	if(rank==ROOT)
	{
		gettimeofday(&start,NULL);
	}
	MPI::COMM_WORLD.Bcast(vetor,tam_vetor,MPI::FLOAT,0);
	float *sub_vetor = new float[elementos_por_proc];
	//Distribui o vetor para todos os processos
	MPI::COMM_WORLD.Scatter(vetor,elementos_por_proc,MPI::FLOAT,sub_vetor,elementos_por_proc,MPI::FLOAT,0);
	while(tam_vetor >= (unsigned int) size)
	{
		offset = size/2;
		while(offset>=1)
		{
			if(rank > offset*2){}//Garante que os processos que ficam a toa fiquem de fato a toa, ao inves de mandarem dados que nao serao recebidos
			else if(rank >= offset)//Os que forem processos validos enviam um elemento de seu sub_vetor para ser somado
			{
				for(unsigned int i=0;i<elementos_por_proc;i++)
				{
					MPI::COMM_WORLD.Send(&sub_vetor[i],1,MPI::FLOAT,rank-offset,0);
				}
			}
			else
			{
				for(unsigned int i=0;i<elementos_por_proc;i++)
				{
					MPI::COMM_WORLD.Recv(&elemento,1,MPI::FLOAT,rank+offset,0);
					sub_vetor[i]+=elemento;
				}
			}
			offset/=2;
		}
		tam_vetor = elementos_por_proc;
		elementos_por_proc /= size;
		if(rank==ROOT)
		{
			vetor = sub_vetor;
		}
		MPI::COMM_WORLD.Scatter(vetor,elementos_por_proc,MPI::FLOAT,sub_vetor,elementos_por_proc,MPI::FLOAT,0);
	}
	if(rank==ROOT)
	{
		float soma = soma_tree(size,vetor);
		gettimeofday(&end,NULL);
		//cout << "SOMA = " << soma << endl;
		double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
		cout << delta << endl;
	}
	delete[] sub_vetor;
	MPI::Finalize();
	return 0;
}
float soma_tree(unsigned int tam_vetor,float *vetor)
{
	unsigned int i,l=2,k=1;
	while((tam_vetor+k)/l>=1)
	{
		i=0; 
		while(i+k<tam_vetor)
		{
				vetor[i] +=  vetor[i+k];
			i+=l;
		}
		k*=2;
		l*=2;
	}
	return vetor[0];
}
