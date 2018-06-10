all: monte_carlo run

run: monte_carlo
	mpirun -n 20 --hostfile hosts ./monte_carlo
monte_carlo: project.c calculate.s gen_rand.s
	mpicc -o monte_carlo project.c calculate.s gen_rand.s

