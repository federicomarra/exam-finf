//Federico Marra 7025997
//Bubble sorting algorithm

#include <stdio.h>
#include <stdlib.h>

typedef unsigned short int boolean;
#define TRUE 1
#define FALSE 0

struct list {
    int value;
    struct list *next_ptr;
};


void bubble_sort(struct list **ptrptr);
void swap(struct list **b);
struct list* fake_consume(struct list **ptr);
void fake_preinsert(struct list **ptrptr, struct list *ptr);
void init(struct list **ptrptr);

void visit(struct list *ptr);

void pre_insert(struct list **ptrptr, int value);

void suf_insert(struct list **ptrptr, int value);

int main() {
    struct list *ptr;
    int value;

    init(&ptr);

    printf("Inserire numeri interi nella lista, per fermare l'inserimento immettere -1:\n");
    scanf("%d", &value);
    if (value == -1) {
        visit(ptr);
        return 0;
    }
    pre_insert(&ptr, value);
    do {
        scanf("%d", &value);
        if (value != -1)
            suf_insert(&ptr, value);
    } while (value != -1);

    visit(ptr);

    bubble_sort(&ptr);

    printf("\nLista riordinata in ordine crescente:\n");
    visit(ptr);

    return 0;
}


void bubble_sort(struct list **ptrptr) {
    boolean swapped;
    struct list **ptrA;
    struct list *ptrB = NULL;
    if (*ptrptr == NULL)
        return;
    do {
        swapped = FALSE;
        ptrA = ptrptr;
        while (*ptrA != NULL && (*ptrA)->next_ptr != ptrB) {
            if ((*ptrA)->value > ((*ptrA)->next_ptr)->value) {
                swap(ptrA);
                swapped = TRUE;
            }
            ptrA = &((*ptrA)->next_ptr);
        }
        ptrB = *ptrA;
    } while (swapped == TRUE);
}

void swap(struct list **b) {
    fake_preinsert(b, fake_consume(&(*b)->next_ptr));
}

struct list *fake_consume(struct list **ptr) {
    struct list *tmp_ptr = *ptr;
    *ptr = (*ptr)->next_ptr;
    return tmp_ptr;
}

void fake_preinsert(struct list **ptrptr, struct list *ptr) {
    struct list *tmp_ptr = *ptrptr;
    *ptrptr = ptr;
    ptr->next_ptr = tmp_ptr;
}

void init(struct list **ptrptr) {
    *ptrptr = NULL;
}

void visit(struct list *ptr) {
    if (ptr == NULL) {
        printf("Lista vuota: { }");
        return;
    }
    printf("{ ");
    while (ptr != NULL) {
        printf("%d ", ptr->value);
        ptr = ptr->next_ptr;
    }
    printf("}\n");
}

void pre_insert(struct list **ptrptr, int value) {
    struct list *tmp_ptr;
    tmp_ptr = (struct list *) malloc(sizeof(struct list));
    tmp_ptr->value = value;
    tmp_ptr->next_ptr = *ptrptr;
    *ptrptr = tmp_ptr;
}

void suf_insert(struct list **ptrptr, int value) {
    while (*ptrptr != NULL)
        ptrptr = &((*ptrptr)->next_ptr);
    pre_insert(ptrptr, value);
}