#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct items{
    char item[20];
    float price;
    int qty;
};
struct orders {
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];     //structure within structure
};
//FUNCTIONS to GENERATE bill
void generateBillHeader(char name[50],char date[50]){
    printf("\n\n");
    printf("\t     ROYAL RESTAURANT");
    printf("\n\t ------------------------");
    printf("\nDate: %s",date);
    printf("\nTime: %s",__TIME__);
    printf("\nInvoice To: %s",name);
    printf("\n");
    printf("----------------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
     printf("\n----------------------------------------------");
    printf("\n\n");
}
void generateBillBody(char item[30],int qty,float price){
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%.2f\t\t",qty*price);
    printf("\n");
}

void generateBillFooter(float total){
    printf("\n");
    float dis=0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal+2*cgst;
     printf("----------------------------------------------\n");
     printf("Sub Total\t\t\t%0.2f",total);
     printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
     printf("\n\t\t\t\t--------");
     printf("\nNet Total\t\t\t%.2f",netTotal);
     printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
     printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
       printf("\n----------------------------------------------");
       printf("\nGrand Total\t\t\t%.2f",grandTotal);
          printf("\n----------------------------------------------\n");
        }
int main(){ 
     int opt,n;
float total;
struct orders ord;
struct orders order;

char saveBill= 'y',contFlag='y';
char name[50];
FILE*fp;               //file pointer has been initialised
int flag=0;
while(contFlag=='y'){
    float total=0;
   int invoiceFound=0;
    printf("\n\n");
    printf("\t=============ROYAL RESTAURANT=============");
     printf("\n\nPlease select your preferred operation:\t ");
    printf("\n1.Generate Invoice");
    printf("\n2.Show allInvoices");
    printf("\n3.Search Invoice");
    printf("\n4.Exit");
     printf("\n\nYour choice:\t\t\t\t");
     scanf("%d",&opt);
     fgetc(stdin);       // to comsume \n other wise it will be comsidered as an input to the next scanf/ fgets
     switch(opt){
         case 1:
         
         system("clear");           //to hide menu
         printf("\nPlease enter the name of the customer:\t");
        fgets(ord.customer,sizeof(ord.customer),stdin);
        ord.customer[strlen(ord.customer)-1]=0;
        strcpy(ord.date,__DATE__);
        printf("\nPlease enter the number of items:\t");
        scanf("%d",&n);
        ord.numOfItems=n;
        for(int i=0;i<n;i++){
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item:\t\t\t%d)",i+1);
            fgets(ord.itm[i].item,sizeof(ord.itm[i].item),stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("Please enter the quantity: \t\t");
            scanf("%d",&ord.itm[i].qty);
            printf("Please enter the unit price:\t\t");
            scanf("%f",&ord.itm[i].price);
            total+=ord.itm[i].qty*ord.itm[i].price;
        }

        generateBillHeader(ord.customer,ord.date);
        for(int i=0;i<ord.numOfItems;i++){
        generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);

        }
        generateBillFooter(total);

        printf("\nDo you want to save the invoice[y/n]: ");
        getchar();
        scanf("%c",&saveBill);
        if(saveBill=='y'){
            fp=fopen("RestaurantBill.dat","a+");
            fwrite(&ord,sizeof(struct orders),1,fp); //we use fwrite to print whole structure variable- into the file and 1 is no of instance we use structure orders
           
           
           
           
           
            if(fwrite!=0){
            printf("\n Successfully saved");}
            else{
               printf("\n Error saving"); 
            }
        }
               fclose(fp); 
            break;

            case 2:
            system("clear");
            fp=fopen("RestaurantBill.dat","r+");
            printf("   \n********Your Previous Invoices********\n");
            while(fread(&order,sizeof( struct orders),1,fp)) 
{
    generateBillHeader(order.customer,order.date);
    for(int i=0;i< order.numOfItems;i++ ){
        generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
        total+=order.itm[i].qty * order.itm[i].price;
    }
    generateBillFooter(total);
}
fclose(fp);
break;
case 3:
printf("Enter the name of the customer:\t");
//fgetc(stdin);
fgets(name,50,stdin);
name[strlen(name)-1]=0;
            system("clear");
            fp=fopen("RestaurantBill.dat","r");
            printf("   \n\t*****Invoice of %s*****\n",name);
            while(fread(&order,sizeof( struct orders),1,fp)){
            float tot=0;
            if(strcmp(order.customer,name)==0){
               generateBillHeader(order.customer,order.date);
    for(int i=0;i< order.numOfItems;i++ ){
        generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
        tot+=order.itm[i].qty * order.itm[i].price;
    }
    generateBillFooter(tot); 
    invoiceFound=1;
            }


   
        }
        if(invoiceFound=0){
            printf("Sorry!!!  the invoice for %s doesn't exists ",name);
        }
fclose(fp);
break;


case 4:
printf("\n\t\t Bye Bye :) ");
exit(0);
break;
default:
printf("Sorry invalid option");
break;
        }
        printf("\nDo you want to perform another operation?[y/n]:\t");
        scanf("%s",&contFlag);
}
      printf("\n\n");


    return 0;

}