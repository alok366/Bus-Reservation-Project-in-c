/**
*************************************
* Program Description:              *
* Bus Reservation                   *
* Filename : busproject.c           *
* Author : Alok Panwar              *
* Date :   30-JAN-2023              *
*************************************
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define PR 500
typedef struct busdata
{
    char name[20];
    int seatno;
    float price;
    char bus_servc[100];
}bus;
bus b1,b2[20];
char buslist[][50]={"Vishwanath","Himalayan","UTC"};
void select_bus()
{
    printf("\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Select Bus Service \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
    printf("\t\t\t1: %s\n",buslist[0]);
    printf("\t\t\t2: %s\n",buslist[1]);
    printf("\t\t\t3: %s\n",buslist[2]);
    printf("\t\t\t");
}
int num_seats(char *file)
{
    int count=0;
    FILE *fp;
    fp=fopen(file,"r");
    while ( fscanf ( fp, "%s %d %f %s", b1.name, &b1.seatno, &b1.price, b1.bus_servc ) != EOF )
            {
                count+=b1.seatno;
            }
    fclose(fp);
    return count;
}
void book()
{
    char name[20];
    int bus_servc;
    FILE *fp;
    char file[100];
    select_bus();
    int numseats=0;
    scanf("%d",&bus_servc);
    strcpy(file,buslist[bus_servc-1]);
    strcat(file,".dat");
    numseats=num_seats(file);
    printf("\t\t\tNumber of seats left in %s is %d\n",buslist[bus_servc-1],40-numseats);
    if(numseats>=40)
    return;
    if(bus_servc>0&&bus_servc<=3)
    {
        fp=fopen(file,"a");
        if(fp==NULL)
        {
            printf("\t\t\tCannot open file\n");
            exit(0);
        }
        printf("\t\t\tEnter your name\n\t\t\t");
        scanf("%s",b1.name);
        seat:
        printf("\t\t\tEnter number of seats\n\t\t\t");
        scanf("%d",&b1.seatno);
        if(b1.seatno+numseats>40)
        {
            printf("\t\t\tYou can\'t book more than %d seats\n",40-numseats);
            goto seat;
        }
        b1.price=b1.seatno*PR;
        printf("\t\t\tPrice to be paid for %d tickets: %f\n",b1.seatno,b1.price);
        strcpy(b1.bus_servc,buslist[bus_servc-1]);
        fprintf(fp,"%s %d %f %s\n",b1.name,b1.seatno,b1.price,b1.bus_servc);
        fclose(fp);
    }
    else 
    printf("\t\t\tInvalid selection\n");    
}
void display()
{
    int bus_servc;
    FILE *fp;
    select_bus();
    scanf("%d",&bus_servc);
    char file[100];
    strcpy(file,buslist[bus_servc-1]);
    if(bus_servc>0&&bus_servc<=3)
    {
        strcat(file,".dat");
        fp=fopen(file,"r");
        if(fp==NULL)
        {
            printf("\t\t\tCannot open file\n");
            exit(0);
        }
        char name[20];
        printf("\t\t\tEnter your name\n\t\t\t");
            scanf("%s",name);
            while ( fscanf ( fp, "%s %d %f %s", b1.name, &b1.seatno, &b1.price, b1.bus_servc ) != EOF )
            {
                if(strcmp(b1.name,name)==0)
                printf ( "\t\t\t%s %d %f %s\n", b1.name, b1.seatno, b1.price,b1.bus_servc ) ;
            }
        fclose(fp);
    }
    else
    printf("\t\t\tInvalid selection\n");
}
void cancel()
{
    int flag=0,count=0;
    int bus_servc;
    FILE *fp;
    select_bus();
    scanf("%d",&bus_servc);
    char file[100],name[20];
    strcpy(file,buslist[bus_servc-1]);
    strcat(file,".dat");
    if(bus_servc>0&&bus_servc<=3)
    {
        fp=fopen(file,"r");
        if(fp==NULL)
        {
            printf("\t\t\tCannot open file\n");
            exit(0);
        }
        printf("\t\t\tEnter your name\n\t\t\t");
            scanf("%s",name);
            int i=0;
            while ( fscanf ( fp, "%s %d %f %s", b1.name, &b1.seatno, &b1.price, b1.bus_servc ) != EOF )
            {
                if(strcmp(b1.name,name)==0)
                {
                printf ( "\t\t\tRecord deleted for: %s\n", b1.name );
                printf("\t\t\tAmount %f will be refunded in 3-5 bussiness days\n",b1.price);
                flag=1;
                continue;
                }
                strcpy(b2[count].name,b1.name);
                b2[count].seatno=b1.seatno;
                b2[count].price=b1.price;
                strcpy(b2[count].bus_servc,b1.bus_servc);
                count++;
            }
        fclose(fp);
    }
    else
    printf("\t\t\tInvalid selection\n");
    if(flag)
    {
        FILE *fp=fopen(file,"w");
        for(int i=0;i<count;i++)
        fprintf(fp,"%s %d %f %s\n",b2[i].name,b2[i].seatno,b2[i].price,b2[i].bus_servc);
        fclose(fp);
    }
    else
    printf("\t\t\tNO record for %s was found\n",name);
}
int main()
{
    int ch;
    char ans[4];
    do
    {
        printf("\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Bus Reservation \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
        printf("\t\t\tPress 1 to book your seat\n");
        printf("\t\t\tPress 2 to display your detail\n");
        printf("\t\t\tPress 3 to cancel\n");
        printf("\t\t\t");
        scanf("%d",&ch);
        switch (ch)
        {
        case 1:
        system("cls");
            book();
            break;
        case 2:
        system("cls");
        display();
        break;
        case 3:
        system("cls");
        cancel();
        break;
        
        default:
        printf("\t\t\tWrong choice\n");
            break;
        }
        printf("\t\t\tTo continue type yes");
        scanf("%s",ans);
    } while (strcmp(ans,"yes")==0||strcmp(ans,"YES")==0);
    return 0;
}
    
