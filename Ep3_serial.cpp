#include <iostream>
#include <sys/time.h>
using namespace std;
float soma_tree(unsigned int tam_vetor,float *vetor);
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
	float soma = soma_tree(tam_vetor,vetor);
	cout << soma <<endl;
	double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
	cout << delta << endl;
	delete vetor;
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
