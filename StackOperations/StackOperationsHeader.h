#define MAXSTACKSIZE 7
/*struct Element{
    char type;
    void* val;
};*/
typedef void (*Constructor)();
//typedef void (*Push)(struct Element);
typedef void (*Push)(int);
//typedef struct Element (*Pop)();
typedef int (*Pop)();
typedef void (*Display)();

typedef struct Stack{
    int top;
//    struct Element arr[MAXSTACKSIZE];
    int arr[MAXSTACKSIZE];
    Constructor constructor;
    Push push;
    Pop pop;
    Display display;
} StackDataType;
