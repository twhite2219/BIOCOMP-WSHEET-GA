// ConsoleApplication1.cpp : Defines the entry point for the console application.
//


#include <stdlib.h>
#include <stdio.h>
#include "stdafx.h"
#define N 50
#define P 50
#define mut 0.1

typedef struct {
	int gene[N];
	int fitness;
} individual;



individual population[P];
individual offspring[P];
int parentfit, offit;

void evaluate() {

	for (int i = 0; i < P; i++) {// test the code by applying a fitness function
		for (int j = 0; j < N; j++)
		{
			if (population[i].gene[j])
				population[i].fitness++;
		}
	}
}
void populate() {
	for (int i = 0; i < P; i++) {//populate population with rand numbers
		for (int j = 0; j < N; j++) {
			population[i].gene[j] = rand() % 2;
		}
	}
}


int main() {
	int totalfitness = 0;
	int highestfitness = 0;
	float averagefitness = 0;
	int parent1;
	int parent2;
	int ran;
	int ranx;
	float ranm;
	int G = 0;


	FILE *f;
	f = fopen("file.txt", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}



	populate();//POPULATE
	evaluate();//EVALUATE


	while (G < 50) { //REPEAT UNTIL TERMINATION CONDITION IS SATISFIED ... i is number of generations to go through



		for (int i = 0; i < P; i++) {// tournament SELECT PAIRS OF PARENTS
			parent1 = rand() % P;
			parent2 = rand() % P;

			if (population[parent1].fitness >= population[parent2].fitness)
				offspring[i] = population[parent1];
			else
				offspring[i] = population[parent2];
		}


		for (int o = 0; o < P; o += 2) {//go through offspring to split in 2's and pair them 
			ran = rand() % N;

			for (int r = ran; r < N; r++) {//crossover for pairs of offspring
				int temp = offspring[o].gene[r];
				offspring[o].gene[r] = offspring[o + 1].gene[r];
				offspring[o + 1].gene[r] = temp;
			}

		}


		for (int o = 0; o < P; o++) {// mutate each offsprings individual values
			for (int r = 0; r < N; r++) {//iterate through number of genes in each offspring
				ranx = 0;
				ranm = 0;
				ranx = rand() % 10000;
				ranm = (float)(ranx / 10000);
				if (ranm < mut) {

					if (offspring[o].gene[r] < 1)
						offspring[o].gene[r] = 0;

					else offspring[o].gene[r] = 1;
				}
			}

		}
		for (int v = 0; v < P; v++) {//reassign the offspring values back to basic population for next iteration
			population[v] = offspring[v];
		}


		evaluate();//evaluate current population
		totalfitness = 0;
		averagefitness = 0;
		highestfitness = 0;

		for (int s = 0; s < P; s++)
		{
			if (population[s].fitness > highestfitness) {
				highestfitness = population[s].fitness;
			}

			totalfitness = totalfitness + population[s].fitness;
		}

		averagefitness = (float)(totalfitness / P);

		printf("highest fitness of generation %d is %d \n", G, highestfitness);
		printf("average fitness of generation %d is %f %d \n", G, averagefitness, totalfitness);

		fprintf(f, "highest fitness of generation %d is %d \n", G, highestfitness);//printtofile
		fprintf(f, "average fitness of generation %d is %f %d \n", G, averagefitness, totalfitness);//printtofile
		G++;
	}//end of while loop


	getchar();
	fclose(f);

	return 0;

}
