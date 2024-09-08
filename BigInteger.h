#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H
struct node 
{
    int data;
    struct node* next;
};
struct BigInteger 
{
    struct node* l;
    int length;
    int sign;
};
void push(struct node **h, int val);
struct BigInteger initialize(char *s);
void truncate(struct BigInteger* num);
struct BigInteger add(struct BigInteger a, struct BigInteger b);
int length(struct node *ptr);
struct BigInteger sub(struct BigInteger a, struct BigInteger b);
struct BigInteger mul(struct BigInteger a, struct BigInteger b);
struct BigInteger div1(struct BigInteger a, struct BigInteger b);
struct BigInteger mod(struct BigInteger a, struct BigInteger b);
void freeLinkedList(struct node *head);
void print(struct node *res);
#endif
