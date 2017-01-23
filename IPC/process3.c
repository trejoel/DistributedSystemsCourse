#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

//This is process 2

int main ()
{
  

  key_t shm_key = 6168529;  //shared memory with process 1
  const int shm_size = 1024;
  int shm_id;
  char* shmaddr, *ptr;
  char* shared_memory[3];
  int *p;

  /* Asignación memoria. */
  shm_id = shmget (shm_key, shm_size, IPC_CREAT | S_IRUSR | S_IWUSR);

  /* Reserva el monto de memoria.. */
  shmaddr = (char*) shmat (shm_id, 0, 0);

  printf ("Memoria asignada en la posicion %p\n", shmaddr);

  /* Leer información. */
  p = (int *)shmaddr;
  ptr = shmaddr + sizeof (int) * 2;
  shared_memory[0] = ptr;
  ptr += *p++;
  shared_memory[1] = ptr;
  ptr += *p;
  shared_memory[2] = ptr;
  printf ("Buffer 0=%s\n", shared_memory[0]);
  printf ("Buffer 1=%s\n", shared_memory[1]);
  printf ("Buffer 2=%s\n", shared_memory[2]);

  /* Liberar memoria. */
  shmdt (shmaddr);
  return 0;
}
