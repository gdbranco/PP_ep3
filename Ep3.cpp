#include <iostream>
#include <cstdlib>
#include <mpi/mpi.h>
#include <fstream>
#define ROOT 0
using namespace std;
float soma_tree(unsigned int inicio, unsigned int tam_vetor,float *vetor);
int main()
{
	//if(argc < 2)
		//return -1;
	unsigned int tam_vetor=8,i=0;
	float *vetor=NULL,elemento;
	int size,rank;
	unsigned int local_tamvetor,local_inicio,local_fim;
	//fstream input;
	//input.open(argv[1]);
	MPI::Status mpi_status;
	MPI::Init();
	rank = MPI::COMM_WORLD.Get_rank();
	size = MPI::COMM_WORLD.Get_size();
      //input >> tam_vetor;
	if(rank==ROOT)
	{
		  cin >> tam_vetor;
	}
	MPI::COMM_WORLD.Bcast(&tam_vetor,1,MPI::INT,0);
	//MPI::COMM_WORLD.Barrier();
	vetor = (float*)malloc(tam_vetor*sizeof(float));
	if(rank==ROOT)
	{ 
	    while(i<tam_vetor)
	    {
		    cin >> elemento;
		    *(vetor+i) = elemento;
		    i++;
	    }
	}
	MPI::COMM_WORLD.Bcast(vetor,tam_vetor,MPI::FLOAT,0);
	local_tamvetor = tam_vetor/size; //Ajeita os indices para cada processo
	local_inicio = rank*local_tamvetor;
	local_fim   = (rank+1)*local_tamvetor;
	if(rank==size-1)
	{
		  local_fim = tam_vetor+1; 
	}
	//Guarda a soma parcial em uma variavel local a cada e faz a do root(0)
	float total_result;
	total_result = soma_tree(local_inicio,local_fim,vetor);
	if(rank!=ROOT)
	{
		MPI::COMM_WORLD.Send(&total_result,1,MPI::FLOAT,0,0);
	}
	else
	{
		//Recebe os parciais e soma ao total_result ja calculado do 0
		float tmp;
		for(unsigned int source = 1;source < (unsigned)size; source++)
		{
			MPI::COMM_WORLD.Recv(&tmp,1,MPI::FLOAT,source,0,mpi_status);

			total_result += tmp;
		}
		cout << total_result << endl;
	}
	
	MPI::Finalize();
	//input.close();
	//free(vetor);
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
	//if(!rank)
	//{
		  ////cin >> tam_vetor;
		  ////vetor = (float*)malloc(tam_vetor*sizeof(float));
		  ////if(vetor)
		  ////{
			  ////while(i<tam_vetor)
			  ////{
				  ////cin >> elemento;
				  ///[>(vetor+i) = elemento;
				  ////i++;
			  ////}
		  ////}
		  ////MPI::COMM_WORLD.Bcast(&tam_vetor,1,MPI::INT,0);
		  ////MPI::COMM_WORLD.Bcast(vetor,tam_vetor,MPI::FLOAT,0);
		  //for(unsigned int source = 1;source < (unsigned)size;source++)
		  //{
			    //MPI::Status mpi_status;
			    //MPI::COMM_WORLD.Recv(&local_result,1,MPI::FLOAT,source,0,mpi_status);
			    //cout << endl << source << ": " << local_result;
			    //total_result += local_result;
		  //}
		  //cout << endl << total_result << endl;
	//}
	//else
	//{
		  ////MPI::COMM_WORLD.Bcast(&tam_vetor,1,MPI::INT,0);

		  ////vetor = (float*)malloc(tam_vetor*sizeof(float));
		  ////MPI::COMM_WORLD.Bcast(vetor,tam_vetor,MPI::FLOAT,0);

		  //local_tamvetor = tam_vetor/size;
		  //local_inicio = rank*local_tamvetor;
		  //local_fim   = local_inicio+local_tamvetor;
		  //local_result = soma_tree(local_inicio,local_fim,Vetor);
		  //MPI::COMM_WORLD.Send(&local_result,1,MPI::FLOAT,0,0);
	//}
