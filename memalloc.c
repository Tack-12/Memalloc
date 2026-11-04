#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

// Memory header_t
typedef struct  header_t{
    size_t size;
    struct header_t *next;
    bool inuse;
} header_t;

//Global Head to store the total space
header_t * head ;
header_t * tail;

// First fit -> loop throught the memory header_t and find if the size of the 
// memory header_t is bigger or equal to the memory asked by alloc if yes return the 
// space.

header_t* getfreeSpace(size_t size){

    header_t* curr = head; 
    
    while (curr != NULL)
    {
        if (curr->inuse == false && curr->size >= size){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}


void* mymalloc(size_t size){

    ssize_t total_size = sizeof(header_t) + size;

    header_t* header;

    if (!size){
        return NULL;
    }

    header = getfreeSpace(size);
    
    if (header){
        header->inuse = true;
        return (void*) (header+1); // +1 cause the byte right after the header space is the memory allocated for the user.
    }

    void* newSpace = sbrk(total_size);

    if (newSpace == (void *)-1){
        return NULL;
    }

    //If there isnt enough space ask the srbk to get you space to get memory from create from srbk and add to the list.
    header = newSpace; // Space aligned for the memory with the header in it.
    header->inuse = true;
    header->size = size;
    header->next = NULL;

    if (!head){
        head = header;
    }

    if (tail != NULL){
        tail->next = header;
    }else{
        tail = header;
    }

    return (void*)(header+ 1);
}

void* mycalloc(size_t no_elem, size_t size){

    if( !no_elem || !size){
        return NULL;
    }

    size_t newsize = no_elem * size; //Calculate the number of elements to be put into the memeory.

    if ( size != newsize/no_elem){
        return NULL; //If the number are not same integer has overflown.
    }

    void* mem_block = sbrk(newsize);

     if (mem_block == (void*)-1 ){
        return NULL;
     }
    memset(mem_block, 0, newsize);
    return mem_block;
}

void free(void* block_mem){

    if (!block_mem){
        return;
    }
    
    header_t* tmp;

    header_t* header = (header_t*)block_mem - 1;
    void* program_brk = sbrk(0);

// This is use to see if the full Memory or the end of the list is getting freed by the user.
// If Yes = return the memory back to OS if not change the struct var (inuse) to false.
// P.S. Uses Char so the calculation for size is in 1 Byte.
    
    if((char *)block_mem + header->size  == program_brk){ 

        if(head == tail){
            head = NULL;
            tail = NULL;
        }else{
            tmp = head;
            while(tmp->next != NULL){
                if(tmp->next == tail){
                    tmp->next = NULL;
                    tail = tmp;
                }
                tmp = tmp->next;
            }
        }

        void* freepointer = sbrk(0- sizeof(header_t) - header->size);

        if (freepointer == (void*)-1){
            printf("There was an error in SRBK freeing.");
            return;
        }
        return ;
    }
    header->inuse = false;
}

int main(){
   void* name =  mymalloc(10);
    free(name);
}