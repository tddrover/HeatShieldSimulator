#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

const int N=11;
const int M=N;
ofstream fp;

void init_block(float heatarray[][N],int M);
void set_boundary(float heatarray[][N], int M, int heatsource);
void  print_block(float heatarray[][N],int M);
float average_temp(float heatarray[][N],int M);
void update_cells(float heatarray[][N], int M);


int main()
{
	cout<<fixed<<setprecision(2)<<showpoint;
	fp.open("simulation_results.txt");

	float block;
	float boundary;
	float print;
	float average;
	float update;

	int i=1;


	float heatarray[M][N];
	int heatsource;

	cout<<"Enter the temperture of the heat source(Above 0): ";
	cin>>heatsource;
	
	init_block(heatarray, M);
	set_boundary(heatarray, M, heatsource);
	average=average_temp(heatarray, M);

	while(average!=heatsource){
		print_block(heatarray, M);

		cout<<"\n Average is: "<<average<<"  at "<<i<<"\n"<<endl;
		fp<<"\n Average is: "<<average<<"  at "<<i<<"\n"<<endl;

		update_cells(heatarray,M);
		average=average_temp(heatarray, M);	
		i+=1;
	}

	fp.close();
	return 0;
}
void init_block(float heatarray[][N], int M)
{
	int i,j;
	for(j=0;j<N;j++){
		for(i=0;i<N;i++){
			heatarray[j][i]={0.0};
		}
	}

	return;

}

void set_boundary(float heatarray[][N], int M, int heatsource)
{
	int i;

	for(i=0;i<N;i++){

		heatarray[0][i]=heatsource; //horizontal
		heatarray[N-1][i]=heatsource;

		heatarray[i][0]=heatsource; //vertical
		heatarray[i][N-1]=heatsource;
	}
	return;
}
void print_block(float heatarray[][N], int M)
{
	int i,j;
	for(j=0;j<N;j++)
	{
		for(i=0;i<N;i++)
		{
			cout<<heatarray[j][i]<<"  ";
			fp<<heatarray[j][i]<<"  ";

		}
		fp<<"\n";
		cout<<"\n";
	}
	return;

}
float average_temp(float heatarray[][N], int M)
{
	float count=0;
	float count2=0;
	float average=0;

	int i,j;

	for(j=0;j<N;j++)
	{
		for(i=0;i<N;i++)
		{
			count=heatarray[j][i];
			count2+=count;

		}
	}
	average=count2/(N*N);
	return average;
	

}
void update_cells(float heatarray[][N], int M)
{
	float temp[M][N];
	int i,j;

	for(j=1;j<N-1;j++)
	{
		for(i=1;i<N-1;i++)
		{
			temp[j][i]=(heatarray[j-1][i]+heatarray[j+1][i]+heatarray[j][i-1]+heatarray[j][i+1])/4;

		}
	}
	for(j=1;j<N-1;j++)
	{
		for(i=1;i<N-1;i++)
		{
			heatarray[j][i]=temp[j][i];

		}
	}
	return;

}
