 #include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>

//Process 1

int main ()
{
  key_t shm_key = 6166529;  //The shared segment to share
  const int shm_size = 1024;  
  int shm_id;  //Identifier of the shared memory
  char* shmaddr, *ptr;
  //int message[2];
  int pos_memoria[2];

  //char *message="Que onda";

  printf("Write a message.\n");

  /* Asigna un segmento de memoria. */
  shm_id = shmget (shm_key, shm_size, IPC_CREAT | S_IRUSR | S_IWUSR);

  /* Once assigned is necessary to attach the memory in an adress space*/
  shmaddr = (char*) shmat (shm_id, 0, 0);  

  printf ("Memoria asignada en la posici\'on' %p\n", shmaddr);

  /* Aqui escribimos el mensaje que enviaremos. 
  // Obtenemos la posición de memoria
  ptr = shmaddr + sizeof (message);
  //Se almacena la dirección donde está el primer mensaje
  message[0] = sprintf (ptr, "Que Onda") + 1;
  //Se apunta al primer mensaje
  ptr += message[0];
  //Se almacena la dirección donde se guardará el segundo mensaje
  message[1] = sprintf (ptr, "73453916") + 1;
  //Se apunta al segundo mensaje
  ptr += message[1];
  //Se almacena ptr al último mensaje
  sprintf (ptr, " QUE TAL");
  memcpy(shmaddr, &message, sizeof (message));
*/

  ptr=shmaddr+sizeof(pos_memoria);
  pos_memoria[0]=sprintf (ptr, "88888")+1;
  memcpy(shmaddr, &pos_memoria, sizeof (pos_memoria));

  /*calling the other process 2. Process 2 should read to the same shared memory*/
  system("./process2.o");

  /* Retira el uso de la memoria. */
  shmdt (shmaddr);
  /* Libera la memoria solicitada.*/
  shmctl (shm_id, IPC_RMID, 0);

  return 0;
}