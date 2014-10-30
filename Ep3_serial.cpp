#include <iostream>
#include <sys/time.h>
using namespace std;
float soma_tree(unsigned int tam_vetor,float *vetor);
float soma_serial(unsigned int tam_vetor,float *vetor);
int main()
{
	int tam_vetor;
	float *vetor;
	struct timeval start,end;
	cin >> tam_vetor;
	vetor = new float[tam_vetor];
	for(int i=0;i<tam_vetor;i++)
	{
		cin >> vetor[i];
	}
	gettimeofday(&start,NULL);
	float soma = soma_serial(tam_vetor,vetor);
	gettimeofday(&end,NULL);
	//cout << soma <<endl;
	double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
	cout << delta << endl;
	delete vetor;
	return 0;
}
float soma_serial(unsigned int tam_vetor,float *vetor)
{
	while(tam_vetor > 1)
	{
		vetor[0] += vetor[tam_vetor];
		tam_vetor--;
	}
	return vetor[0];
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
