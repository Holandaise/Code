#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *name;
    int id;
    int salary;

}User;

User makeUser(char *name, int id, int salary){
    User x;
    x.name = name;
    x.id = id;
    x.salary = salary;
 
    return x;
}

void printUser(User user){

    printf("Username: %s\nUserID: %d\nSalary: %d\n",user.name,user.id,user.salary);

}

int main()
{
    User Adam=makeUser("Adam",1,1200);
    printUser(Adam);
    return 0;
}
