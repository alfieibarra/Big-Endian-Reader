#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#pragma pack(push, 1)
typedef struct{
    int int1;
    int int2;
    double double1;
    short short1;
    short short2;
    short short3;
    int int3;
}record;
#pragma pack(pop)

double ntohd(const char *data) {
    double reversed;
    char *tmp =(char *) &reversed;
    for (int i = 0; i < sizeof(double); i++) {
        tmp[i] = data[sizeof(double) - i - 1];
    }
    return reversed;
}

int main() {

    FILE *ifile = fopen("binout.dat", "rb");
    record f_struct;
    printf("record size is 26 bytes\n\n");
    int num = 0;

    while(fread(&f_struct, 26, 1, ifile) != 0) {

        f_struct.int1 = ntohl(f_struct.int1);
        f_struct.int2 = ntohl(f_struct.int2);
        f_struct.double1 = ntohd((char*) &f_struct.double1);
        f_struct.short1 = ntohs(f_struct.short1);
        f_struct.short2 = ntohs(f_struct.short2);
        f_struct.short3 = ntohs(f_struct.short3);
        f_struct.int3 = ntohl(f_struct.int3);

        printf("Record: %d\n", num);

        printf("i1: %d 0x%x\n", f_struct.int1, f_struct.int1);
        printf("i2: %d 0x%x\n", f_struct.int2, f_struct.int2);
        printf("d1: %lf\n", f_struct.double1); 
        printf("s1: %hd 0x%x\n", f_struct.short1, f_struct.short1);
        printf("s2: %hd 0x%x\n", f_struct.short2, f_struct.short2);
        printf("s3: %hd 0x%hx\n", f_struct.short3, f_struct.short3);
        printf("i3: %d 0x%x\n", f_struct.int3, f_struct.int3);
        printf("\n\n");

        num++;
    }
}
