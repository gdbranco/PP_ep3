#include <iostream>
#include <cstdlib>
#include <mpi/mpi.h>
#include <fstream>
#define ROOT 0
using namespace std;
float soma_tree(unsigned int tam_vetor,float *vetor);
int main()
{
	unsigned int tam_vetor;
	float *vetor=NULL,elemento;
	int size,rank;
	MPI::Status mpi_status;
	MPI::Init();
	rank = MPI::COMM_WORLD.Get_rank();
	size = MPI::COMM_WORLD.Get_size();
	if(rank==ROOT)
	{
		  cin >> tam_vetor;
	}
	MPI::COMM_WORLD.Bcast(&tam_vetor,1,MPI::INT,0);
	int elementos_por_proc = tam_vetor/size;
	vetor = new float[tam_vetor];
	if(rank==ROOT)
	{
		for(unsigned int i=0;i<tam_vetor;i++)
		{
			cin >> elemento;
			vetor[i] = elemento;
		}
	}
	MPI::COMM_WORLD.Bcast(vetor,tam_vetor,MPI::FLOAT,0);
	float *sub_vetor = new float[elementos_por_proc];
	MPI::COMM_WORLD.Scatter(vetor,elementos_por_proc,MPI::FLOAT,sub_vetor,elementos_por_proc,MPI::FLOAT,0);
	float sub_soma = soma_tree(elementos_por_proc,sub_vetor);
	float *somas = NULL;
	if(rank==ROOT)
	{
		somas = new float[size];
	}
	MPI::COMM_WORLD.Gather(&sub_soma,1,MPI::FLOAT,somas,1,MPI::FLOAT,0);
	if(rank==ROOT)
	{
		float soma = soma_tree(size,somas);
		cout << "SOMA = " << soma << endl;
		//for(int i=0;i<size;i++)
		//{
			//cout << somas[i] << endl;
		//}
		delete somas;
		delete vetor;
	}
	delete sub_vetor;
	MPI::COMM_WORLD.Barrier();
	MPI::Finalize();
	return 0;
}
float soma_tree(unsigned int tam_vetor,float *vetor)
{
	unsigned int i,l=2,k=1;
	//cout << inicio << ' ' << tam_vetor << endl;
	//cout << vetor[inicio] << ' ' << vetor[tam_vetor] << endl;
	while((tam_vetor+k)/l>=1)
	{
		i=0; 
		//cout << endl;
		//cin.get();
		while(i+k<tam_vetor)
		{
			//if(i+k<tam_vetor)
			//{
				//cout << "Vetor[" << i << "] :" << vetor[i] << " vetor[" << i+k << "] :" << vetor[i+k];
				//cout << "vetor[" << i << "] : " << vetor[i] << endl;
				vetor[i] +=  vetor[i+k];
				//cout << " = Vetor[" << i << "]c :" << vetor[i] << endl;
				//cout << endl;
		//}
			i+=l;
		}
		//unsigned int t=0;
		//while(t<tam_vetor)
		//{
			//cout << vetor[t]<< ' ';
			//t++;
		//}
		k*=2;
		l*=2;
	}
	return vetor[0];
}
