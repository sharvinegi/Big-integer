#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

void push(struct node **h, int val) 
{
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->data = val;
    temp->next=NULL;
    if(*h==NULL)
    {
        *h=temp;
        return;
    }
    temp->next = *h;
    *h = temp;
    return;
}

struct BigInteger initialize(char *s) 
{
    int d,i;
    struct BigInteger b1;
    b1.length = 0;
    b1.sign = 1;
    b1.l = NULL;

    if (s[0] == '-') 
    {
        b1.sign = -1;
        s++;  // Skip the negative sign
    }
    for (i = 0; s[i] != '\0'; i++) 
    {
        b1.length++;
        d=s[i]-'0';  // Convert character to integer
        push(&b1.l, d);
    }
   return b1;
}

struct BigInteger add(struct BigInteger a, struct BigInteger b) 
{
    struct BigInteger result;
    struct node *res=(struct node*)malloc(sizeof(struct node));
    struct node *p1=a.l;   //making new list and assigning values to them of big integer's list
    struct node *p2=b.l;
    res=NULL;


    int c=0,d=0,sum=0;
    if(p1==NULL || p2==NULL)  //if any node is Null returning value of non-Null node
    {                       //if both nodes are null then also returning value of p2 i.e Null
        if(p1!=NULL)
        return a;
        else
        return b;
    }
    while(p1 && p2)
    {
      sum=(p1->data)+(p2->data) +c;           // inserting the addition of both the linked list to another list by adding everytime with carry
      if((sum)%10!=0 || (sum)%10==0)                         
      {
        d=sum;                                 //d is total addition i.e 8+8=16
        sum=sum%10;                            //sum is without carry i.e sum is 6
        c=d/10;                                //d is carry i.e 1
        push(&res,sum);           
      }
     p1=p1->next;
     p2=p2->next;
    }
    while (p1 || p2)       //for unequal size of numbers i.e if some numbers are left
    {
        if(p1)
        {
          sum=p1->data+c;
          if((sum)%10!=0)                         
          {
          d=sum;                                 //d is total addition i.e 8+8=16
          sum=sum%10;                            //sum is without carry i.e sum is 6
          c=d/10;                                //d is carry i.e 1
          push(&res,sum);         
          }
          else
          {
          push(&res,sum);
          c=0;
          }
          p1=p1->next;
        }
        else
        {
          sum=p2->data+c; 
          if((sum)%10!=0)                         
          {
          d=sum;
          sum=sum%10;
          c=d/10;
          push(&res,sum);           
          }
          else
          {
          push(&res,sum);
          c=0;
          }
          p2=p2->next;
        }
    }
    if(c)           //adding remaining carry(if any) to sum
    {
        push(&res,c);
    }  
   result.l=res;
   return result;
}

int length(struct node *ptr)   //finding length of numbers 
{
    int l=0;
    if(!ptr)
    {
        return 0;
    }
    while(ptr!=NULL)
    {
        l++;
        ptr=ptr->next;
    }
    return l;
}


struct BigInteger sub(struct BigInteger a, struct BigInteger b) 
{
    struct BigInteger result;
    
    struct node* res=(struct node*)malloc(sizeof(struct node));
    res=NULL;
    struct node *p1=a.l;   //making new list and assigning values to them of big integer's list
    struct node *p2=b.l;
    int d=0,diff=0;
    int l1=length(p1);
    int l2=length(p2);
   if(l1<l2)
   {
     struct node*temp=p1;
     p1=p2;
     p2=temp;           //nodes are exchanged i.e p1 is higher and p2 is lower
     int templ=l1;       //templ is temporary length used to swap lengths
     l1=l2;
     l2=templ;          //lengths are also exchanged i.e l1 is greater than l2
   }
  if(p1==NULL&& p2==NULL)
    {
      if(p1)
        return a;       //same comments as sum
      return b;   
    }

    while (p1 || p2)
     {
        diff=d;
        if (p1) 
        {
            diff = p1->data-diff ;   //if 23-14=?
        }

        if(p2) 
        {
            diff =diff-p2->data;     //if 3-4=-1
        }

        if(diff<0)                    //(-1<0)
        {
          p1->data+=10;                  //working as borrow(3+10=13) so(13-4-0=9)
          diff=p1->data - p2->data -d;   // diff is now 9
          d=1;                            //next time 2 of p1->data gets subtracted by -1
        }                                   //so (2-1-1=0)
        else
        {
          d=0;
        }
        if(p1)                    //checking if p1 is not null, if yes then move to next
         p1=p1->next;
        if(p2)                   //checking if p2 is not null, if yes then move to next
         p2=p2->next;
        push(&res,diff);
      
    }
    result.l=res;
    return result;
}

struct BigInteger mul(struct BigInteger a, struct BigInteger b) 
{
    struct BigInteger result;

  long long int n1=0,n2=0,n3=0;
  struct node*temp1,*temp2=NULL,*temp3,*temp4=NULL;
  struct node *p1=a.l;   //making new list and assigning values to them of big integer's list
  struct node *p2=b.l;
  while(p1||p2)       
  {
   if(p1)          
   {
    temp1=p1->next;    
    p1->next=temp2;    
    temp2=p1;          
    p1=temp1;          
   }
   if(p2)            //reversing lists
   {
    temp3=p2->next;
    p2->next=temp4;
    temp4=p2;         
    p2=temp3;
   }
  }
  p1=temp2;         //assigning p1 and p2 to reversed lists
  p2=temp4;
  while(p1||p2)
  {
    if(p1){
    n1=(n1*10 +(p1->data));
    p1=p1->next;                   //multiplying each list's single node data and storing in n1 i.e 12345 is now considered as a number
    }
    if(p2){
    n2=(n2*10+(p2->data));          //multiplying each list's single node data and storing in n2
    p2=p2->next;
    }
  }
  n3=(n1*n2);           //finally multiplying n1 and n2

     if (n3 == 0) 
     {
        result.length = 1;
        push(&result.l, 0);
        return result;
    }
    while (n3 > 0) {
        int digit = n3 % 10;
        push(&result.l, digit);
        result.length++;
        n3 /= 10;
    }
    return result;
}


struct BigInteger div1(struct BigInteger a, struct BigInteger b) 
{
struct BigInteger result;
long long int n1=0,n2=0,n3=0;
struct node*temp1,*temp2=NULL,*temp3,*temp4=NULL;
struct node *p1=a.l;   //making new list and assigning values to them of big integer's list
  struct node *p2=b.l;
  while(p1||p2)       
  {
   if(p1)          
   {
    temp1=p1->next;    
    p1->next=temp2;    
    temp2=p1;          
    p1=temp1;          
   }
   if(p2)            //reversing lists
   {
    temp3=p2->next;
    p2->next=temp4;
    temp4=p2;         
    p2=temp3;
   }
  }
  p1=temp2;         //assigning p1 and p2 to reversed lists
  p2=temp4;
  while(p1||p2)
  {
    if(p1){
    n1=(n1*10 +(p1->data));
    p1=p1->next;                   //multiplying each list's single node data and storing in n1 i.e 12345 is now considered as a number
    }
    if(p2){
    n2=(n2*10+(p2->data));          //multiplying each list's single node data and storing in n2
    p2=p2->next;
    }
  }
  if(n1>n2)
  {
  n3=(n1/n2);           //finally dividing n1 and n2
  }
  else if(n1==n2)
  {
  n3=(n1/n2);           //finally multiplying n1 and n2
  }
  else
  {
    n3=(n2/n1);           //finally multiplying n1 and n2
  }

     if (n3 == 0) 
     {
        result.length = 1;
        push(&result.l, 0);
        return result;
    }
    while (n3 > 0) {
        int digit = n3 % 10;
        push(&result.l, digit);
        result.length++;
        n3 /= 10;
    }
    return result;
}

struct BigInteger mod(struct BigInteger a, struct BigInteger b) 
{
struct BigInteger result;
long long int n1=0,n2=0,n3=0;
struct node*temp1,*temp2=NULL,*temp3,*temp4=NULL;
struct node *p1=a.l;   //making new list and assigning values to them of big integer's list
  struct node *p2=b.l;
  while(p1||p2)       
  {
   if(p1)          
   {
    temp1=p1->next;    
    p1->next=temp2;    
    temp2=p1;          
    p1=temp1;          
   }
   if(p2)            //reversing lists
   {
    temp3=p2->next;
    p2->next=temp4;
    temp4=p2;         
    p2=temp3;
   }
  }
  p1=temp2;         //assigning p1 and p2 to reversed lists
  p2=temp4;
  while(p1||p2)
  {
    if(p1){
    n1=(n1*10 +(p1->data));
    p1=p1->next;                   //multiplying each list's single node data and storing in n1 i.e 12345 is now considered as a number
    }
    if(p2){
    n2=(n2*10+(p2->data));          //multiplying each list's single node data and storing in n2
    p2=p2->next;
    }
  }
  if(n1>n2)
  {
  n3=(n1%n2);           //finally finding remainder of n1 and n2
  }
  else if(n1==n2)
  {
  n3=(n1%n2);           //finally finding remainder of n1 and n2
  }
  else
  {
    n3=(n2%n1);           //finally finding remainder of n1 and n2
  }

     if (n3 == 0) 
     {
        result.length = 1;
        push(&result.l, 0);
        return result;
    }
    while (n3 > 0) {
        int digit = n3 % 10;
        push(&result.l, digit);
        result.length++;
        n3 /= 10;
    }
    return result;
}

void freeLinkedList(struct node *head) 
{
    struct node *current = head;
    while (current != NULL) 
    {
        struct node *next = current->next;
        free(current);
        current = next;
    }
}

void print(struct node *res) 
{
    
    if(res==NULL)
    {
        return;
    }
    struct node *ptr = res;
    while (ptr != NULL)
    {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
    return;
}
