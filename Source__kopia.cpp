#include "mpi.h"
#include<iostream>
using namespace std;
int razm = 10000;

void s_send(int argc, char **argv)
{
	int rank, size;
	bool chet = false;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int arraiv = 0;
	double starttime, endtime;
	cout << "-------------------------Ssend ";
	starttime = MPI_Wtime();
	for (long i = 0; i < razm; i++)
	{
		if (rank == 0)
		{
			MPI_Ssend(&arraiv, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		}
		else if (rank == 1)
		{
			MPI_Recv(&arraiv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	}
	endtime = MPI_Wtime();
	cout << "Time sended " << (endtime - starttime) / razm << endl;
	MPI_Finalize();
}
void one_msg(int argc, char **argv)
{
	int rank, size;
	bool chet = false;
	int arraiv = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		arraiv = 1;
		MPI_Send(&arraiv, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	else if (rank == 1)
	{
		MPI_Recv(&arraiv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout << "Proc 1 reciv number = " << arraiv << " from 0" << endl << endl;
	}
	MPI_Finalize();
}
void chet_nech(int argc, char **argv)
{
	int rank, size;
	bool chet = false;
	int arraiv = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (size % 2 == 0)
		chet = 1;
	else
		chet = 2;
	for (int i = 0; i <= size / 2 - chet; i++)
	{
		if (rank == i * 2)
		{
			arraiv++;
			MPI_Send(&arraiv, 1, MPI_INT, i * 2 + 1, 0, MPI_COMM_WORLD);
			cout << "Proc " << 2 * i << " send number = " << arraiv << " to " << 2 * i + 1;
		}
		else
			if (rank == i * 2 + 1)
			{
				MPI_Recv(&arraiv, 1, MPI_INT, i * 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				cout << "Proc " << i * 2 + 1 << " reciv number = " << arraiv << " from " << i * 2;
			}

	}
	cout << endl;
	MPI_Finalize();
}
void cyrcle(int argc, char **argv)
{
	int rank, size;
	bool chet = false;
	int arraiv = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for (int j = 0; j<2; j++)
	{
		if (rank != 0)
		{
			//arraiv++;
			MPI_Recv(&arraiv, 1, MPI_INT, (rank - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			cout << "Proc " << rank << " reciv number = " << arraiv << " from " << (rank - 1) << endl;

		}
		arraiv++;

		MPI_Send(&arraiv, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
		if (rank == 0)
		{
			{
				MPI_Recv(&arraiv, 1, MPI_INT, (size - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				//arraiv++;
				cout << "Proc " << rank << " reciv number = " << arraiv << " from " << (size - 1) << endl;
			}
		}
	}
	MPI_Finalize();
}
void send(int argc, char **argv)
{
	int rank, size;
	bool chet = false;
	int arraiv = 0;
	double starttime, endtime;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	starttime = MPI_Wtime();
	for (long i = 0; i < razm; i++)
	{
		if (rank == 0)
		{
			MPI_Send(&arraiv, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		}
		else if (rank == 1)
		{
			MPI_Recv(&arraiv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	}
	endtime = MPI_Wtime();
	cout << " Send Time sended " << (endtime - starttime) / razm << endl;
	MPI_Finalize();
}
void b_send(int argc, char **argv)
{
	int rank, size;
	bool chet = false;
	int arraiv = 0;
	double starttime, endtime;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	starttime = MPI_Wtime();

	char mes[] = "Lol";
	cout << "--------------Bsend ";
	int buffsize;
	MPI_Pack_size(4, MPI_CHAR, MPI_COMM_WORLD, &buffsize);
	int data_size = buffsize + MPI_BSEND_OVERHEAD;
	char* buf = (char*)malloc(data_size*razm);
	MPI_Buffer_attach(buf, data_size*razm);
	starttime = MPI_Wtime();
	for (long i = 0; i < razm; i++)
	{
		if (rank == 0)
		{
			MPI_Bsend(&mes, 4, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
		}
		else if (rank == 1)
		{
			char revMsg[4 + MPI_BSEND_OVERHEAD];
			MPI_Recv(&revMsg, 4, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	}
	endtime = MPI_Wtime();
	int a = data_size * razm;
	MPI_Buffer_detach(buf, &a);
	free(buf);
	cout << "Time sended " << (endtime - starttime) / razm << endl;

	MPI_Finalize();
}
void i_send(int argc, char **argv)
{
	int rank, size;
	bool chet = false;
	int* arraiv = new int[razm];
	double starttime, endtime;
	
	MPI_Status* Get_statuses = new MPI_Status[razm];
	
	MPI_Status status;

	for (int i = 0; i < razm; i++)
	{
		arraiv[i] = 0;
	}

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	cout << "--------Isend ";	
	starttime = MPI_Wtime();
	

		if (rank == 0)
		{
			MPI_Request* Send_request = new MPI_Request[razm];
			for (long i = 0; i < razm; i++)
			{
				arraiv[i] = i;
				MPI_Isend(arraiv + i, 1, MPI_INT, 1, i, MPI_COMM_WORLD, Send_request + i);
				//cout << "send " << i<<endl;				
			}
			MPI_Waitall(razm, Send_request, Get_statuses);
			delete[] Send_request;
		}
		else if (rank == 1)
		{
			MPI_Request* Get_requests = new MPI_Request[razm];
			for (long i = 0; i < razm; i++)
			{
				char revMsg[4 + MPI_BSEND_OVERHEAD];
				MPI_Irecv(arraiv + i, 1, MPI_INT, 0, i, MPI_COMM_WORLD, Get_requests + i);				
			}
			MPI_Waitall(razm, Get_requests, Get_statuses);
			/*for (long i = 0; i < razm; i++)
			{
				cout << "reciv " << arraiv[i]<<endl;
			}*/
			
		}
	endtime = MPI_Wtime();
	cout << "Time sended " << (endtime - starttime) / razm << endl;
	MPI_Finalize();
	delete[] arraiv;
}
void gather(int argc, char **argv) {

	int const nstrings = 5;
		const char *const strings[nstrings] = { "Hello","world!","Bonjour","le","monde!" };

	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	/* Everyone gets a string */

	int myStringNum = rank % nstrings;
	char *mystring = (char *)strings[myStringNum];
	int mylen = strlen(mystring);

	printf("Rank %d: %s\n", rank, mystring);

	/*
	* Now, we Gather the string lengths to the root process,
	* so we can create the buffer into which we'll receive the strings
	*/

	const int root = 0;
	int *recvcounts = NULL;

	/* Only root has the received data */
	if (rank == root)
		recvcounts = (int*) malloc(size * sizeof(int));

	MPI_Gather(&mylen, 1, MPI_INT,
		recvcounts, 1, MPI_INT,
		root, MPI_COMM_WORLD);

	/*
	* Figure out the total length of string,
	* and displacements for each rank
	*/

	int totlen = 0;
	int *displs = NULL;
	char *totalstring = NULL;

	if (rank == root) {
		displs = (int*) malloc(size * sizeof(int));

		displs[0] = 0;
		totlen += recvcounts[0] + 1;

		for (int i = 1; i<size; i++) {
			totlen += recvcounts[i] + 1;   /* plus one for space or \0 after words */
			displs[i] = displs[i - 1] + recvcounts[i - 1] + 1;
		}

		/* allocate string, pre-fill with spaces and null terminator */
		totalstring = (char*) malloc(totlen * sizeof(char));
		for (int i = 0; i<totlen - 1; i++)
			totalstring[i] = ' ';
		totalstring[totlen - 1] = '\0';
	}

	/*
	* Now we have the receive buffer, counts, and displacements, and
	* can gather the strings
	*/

	MPI_Gatherv(mystring, mylen, MPI_CHAR,
		totalstring, recvcounts, displs, MPI_CHAR,
		root, MPI_COMM_WORLD);


	if (rank == root) {
		printf("%d: <%s>\n", rank, totalstring);
		free(totalstring);
		free(displs);
		free(recvcounts);
	}

	MPI_Finalize();
}

void analog_gatherv(int argc, char **argv)
{
	int const nstrings = 5;
	const char *const strings[nstrings] = { "Hello","world!","Bonjour","le","monde!" };

	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	/* Everyone gets a string */

	int myStringNum = rank % nstrings;
	char *mystring = (char *)strings[myStringNum];
	int mylen = strlen(mystring);

	printf("Rank %d: %s\n", rank, mystring);

	/*
	* Now, we Gather the string lengths to the root process,
	* so we can create the buffer into which we'll receive the strings
	*/

	const int root = 0;
	int *recvcounts = NULL;

	/* Only root has the received data */
	if (rank == root)
		recvcounts = (int*)malloc(size * sizeof(int));

	MPI_Gather(&mylen, 1, MPI_INT,
		recvcounts, 1, MPI_INT,
		root, MPI_COMM_WORLD);

	/*
	* Figure out the total length of string,
	* and displacements for each rank
	*/

	int totlen = 0;
	int *displs = NULL;
	char *totalstring = NULL;

	if (rank == root) {
		displs = (int*)malloc(size * sizeof(int));

		displs[0] = 0;
		totlen += recvcounts[0] + 1;

		for (int i = 1; i<size; i++) {
			totlen += recvcounts[i] + 1;   /* plus one for space or \0 after words */
			displs[i] = displs[i - 1] + recvcounts[i - 1] + 1;
		}

		/* allocate string, pre-fill with spaces and null terminator */
		totalstring = (char*)malloc(totlen * sizeof(char));
		for (int i = 0; i<totlen - 1; i++)
			totalstring[i] = ' ';
		totalstring[totlen - 1] = '\0';
	}

	/*
	* Now we have the receive buffer, counts, and displacements, and
	* can gather the strings
	*/

	MPI_Gatherv(mystring, mylen, MPI_CHAR,
		totalstring, recvcounts, displs, MPI_CHAR,
		root, MPI_COMM_WORLD);


	if (rank == root) {
		printf("%d: <%s>\n", rank, totalstring);
		free(totalstring);
		free(displs);
		free(recvcounts);
	}

	MPI_Finalize();
}

int main(int argc, char **argv)
{
	int rank;
	
	//one_msg(argc, argv);
	//chet_nech(argc, argv);
	//cyrcle(argc, argv);
	//send(argc, argv);
	//s_send(argc, argv);
	//b_send(argc, argv);
	//i_send(argc, argv);
	//cout << "The number of processes: " << size << " my number is " << rank << endl;	
	//cin >> rank;
	gather(argc, argv);
	cin >> rank;
	return 0;
}
