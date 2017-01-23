#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>

//This is process 2, we send a message in the arguments

int main ()
{
  

  key_t shm_key = 6166529;  //shared memory with process 1
  const int shm_size = 1024;
  int shm_id;
  char* shmaddr, *ptr;
  int value;
  //This is the segment of memory to share messages (IPC)
 // char* shared_memory[3];
  char* shared_memory;
  int *p;


  /*shared memory with process 1*/
  key_t shm_key_proc3 = 6168529;
  int shm_id_proc3;
  char* shmaddr_proc3, *ptr_proc3;
  int next_proc3[2];
  /*shared memory with process 3*/

  /* Asignación memoria. */
  shm_id = shmget (shm_key, shm_size, IPC_CREAT | S_IRUSR | S_IWUSR);

  /* Reserva el monto de memoria.. */
  shmaddr = (char*) shmat (shm_id, 0, 0);

  printf ("Memoria asignada en la posicion %p\n", shmaddr);

  /* Leer información. */
  p = (int *)shmaddr;
  //ptr = shmaddr + sizeof (int) * 2;
  ptr = shmaddr + sizeof (int) * 2;
  shared_memory = ptr;
  printf("Mensaje Recibido:%s\n",shared_memory);
  /* Liberar memoria. */
  shmdt (shmaddr);

  /*Ahora toca en el proceso 3*/

  /* Asigna un segmento de memoria. */
  shm_id_proc3 = shmget (shm_key_proc3, shm_size, IPC_CREAT | S_IRUSR | S_IWUSR);

  /* Reserva el monto de memoria. */
  shmaddr_proc3 = (char*) shmat (shm_id_proc3, 0, 0);

  printf ("Memoria asignada en la posici\'on' %p\n", shmaddr);

  /* Aqui escribimos el mensaje que enviaremos. */
  ptr_proc3 = shmaddr_proc3 + sizeof (next_proc3);
  next_proc3[0] = sprintf (ptr_proc3, "7777") + 1;
  ptr_proc3 += next_proc3[0];
  next_proc3[1] = sprintf (ptr_proc3, "8888") + 1;
  ptr_proc3 += next_proc3[1];
  sprintf (ptr_proc3, " 9999");
  memcpy(shmaddr_proc3, &next_proc3, sizeof (next_proc3));
  printf ("ENVIANDO MENSAJE AL PROCESO 3.\n");

  /*calling the other process*/
  system("./process3.o");

  /* Retira el uso de la memoria. */
  shmdt (shmaddr_proc3);
  /* Libera la memoria solicitada.*/
  shmctl (shm_id_proc3, IPC_RMID, 0);

  /*Ahora toca el el proceso 3*/

  return 0;
}
