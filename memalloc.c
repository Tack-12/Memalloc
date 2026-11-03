#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

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


void* myalloc(size_t size){

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


int main(){
   int* name = (int*) myalloc(10);
}