#include <iostream>
#include <cstdlib>
using namespace std;
float soma(unsigned int inicio, unsigned int tam_vetor,float *vetor);
int main()
{
	unsigned int i=0, tam_vetor;
	float result;
	float elemento, *vetor=NULL;
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
		//i=0;
		//while(i<tam_vetor)
		//{
			//cout << *(vetor+i) << ' ';
			//i++;
		//}
		//cout << endl;
		result = soma(0,tam_vetor,vetor);
		//i=0;
		//while(i<tam_vetor)
		//{
			//cout << *(vetor+i) << ' ';
			//i++;
		//}
		//cout << endl;
		cout << result <<endl;
	}
	return 0;
}
float soma(unsigned int inicio, unsigned int tam_vetor,float *vetor)
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
