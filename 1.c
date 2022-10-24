#include<stdio.h>
#include<stdlib.h>

#define VEC_CAPACITY 1
#define TOTAL 0
#define make_vector(vec) vector vec;\
		initialise(&vec)
 
typedef struct VECTOR vector;//forward declaration (data type - node,vector)
typedef struct NODE node;//no forward declaration , which works in g++, not gcc.


struct NODE{
	void**g_array;
	int total;
	int capacity;
};

struct VECTOR{
	node N;
	int 	(*fptr_size)(vector*);
	int 	(*fptr_capacity)(vector*);
	void	*(*fptr_get)(vector*,int);
	void 	(*fptr_insert)(vector*,void*,int);
	void	(*fptr_push_back)(vector*,void*);
	void	(*fptr_resize)(vector*,int);
	void	(*fptr_free)(vector*);
};

int Min(int x,int y)
{
	//return minimum.
	return (x<=y);
}

int size(vector*v)
{
	//return number of elements present.
	int totalCount = 0;
    if(v)
    {
        totalCount = v->N.total;
    }
    return totalCount;
};

int capacity(vector*v)
{
	//return maximum number of element's vector can currently hold.
	int totalCount = 0;
    if(v)
    {
        totalCount = v->N.capacity;
    }
    return totalCount;
};

void _free(vector*v)
{
	//free all the element's of vector.
	v->N.total=0;
	for(int i=0;i< v->N.capacity;i++)
	{
		free(v->N.g_array[i]);
	}
	v->N.capacity=0;
	return;
}

void resize(vector*v,int sz)
{
	//resize the vector to given size.
	v->N.g_array=(void**)realloc(v->N.g_array, sz*sizeof(void*));
	if(Min(v->fptr_size(v),sz)==0)
	{
		v->N.total=sz;
	}
	else v->N.capacity = sz; 
	return;
}

void *get(vector*v,int index)
{
	//get the element at index specified.
	void *readData = NULL;
    if(v)
    {
        if ((index>=0) && (index<(v->N.capacity)))
        {
            readData = v->N.g_array[index];
        }
    }
    return readData;
};

void push_back(vector*v,void*item)
{
	//pushback the items to end.
	if(v && (v->fptr_size(v))< (v->fptr_capacity(v)))
	{
		int index=v->fptr_size(v);
		v->N.g_array[index]=item;
		(v->N.total)=(v->N.total)+1;
	}
	else
	{
		v->N.capacity=(v->N.capacity)*2;
		v->fptr_resize(v,v->N.capacity);
		int index=v->fptr_size(v);
		v->N.g_array[index]=item;
		(v->N.total)=(v->N.total)+1;
	}
	
}

void insert(vector*v,void*item,int index)
{
	//insert the element at specified index.
	if(v && index<(v->fptr_capacity(v)))
	{
		v->N.g_array[index]=item;
		v->N.total++;
		return;
	}
	else if(index==(v->N.capacity))
	{
		//increase the capacity by 2 when exceeds limit.
		(v->N.capacity)=((v->N.capacity)<<1);
		v->fptr_resize(v,v->N.capacity);
		v->N.g_array[index]=item;
		v->N.total++;
		return;
	}
	else return;
};


void initialise(vector* v)
{
	// initialise the vector.
	v->N.g_array=(void**)malloc(VEC_CAPACITY*sizeof(void*));
	v->N.total=TOTAL;
	v->N.capacity=VEC_CAPACITY;
	
	//function pointer's for vector method's.
	v->fptr_size=size; // return's vector size.
	v->fptr_capacity=capacity;// return's vector capacity.
	v->fptr_get=get;// return's the element at given position.
	v->fptr_insert=insert;// insert's element at given position.
	v->fptr_resize=resize;// resize's the vector.
	v->fptr_free=_free;// free's the vector.
	v->fptr_push_back=push_back;// push_back the element's in vector.
	return;	
};


int main() 
{
	/*
	Vector implementation in C using void pointer's.
	
	CREATION :
	make_vector(v1); // creates vector with handle v1.
	
	OPERATIONS: 
	//create a pointer of desired type and assign the value to vector instance.
	
	operations supported :
	
	int *x=(int*)malloc(sizeof(int)),*x=666;
	
	v1.fptr_insert(&v1,x,0); //insert at an index;
	v1.fptr_push_back(&v1,x); //push to the end
	v1.fptr_get(&v1,x); // get item at index (returns void pointer);
	v1.fptr_resize(&v1,x); // resizes the vector.
	v1.fptr_size(&v1); // return's no of element's in vector.
	v1.fptr_capacity(&v1); // return's capacity of the vector.
	v1.fptr_free(&v1); // clear's vector.
	
	*/
	return 0;
}
