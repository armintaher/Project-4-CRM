/* 
 * EE312 Simple CRM Project
 *
 * Armin Mohammadtaher
 * am74657
 */

#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"
#include <string.h>

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;
int new_cutomer = 0;
int current_customer;
bool customer_exist;
bool allowed_to_process;
int bottles = 0;
int diapers = 0;
int rattles = 0;
int new_bottles = 0;
int new_diapers = 0;
int new_rattles = 0;
int num_diapers=0;
int num_bottles = 0;
int num_rattles = 0;

String Bottles_Customer;
String Diapers_Customer;
String Rattles_Customer;

/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */


/* clear the inventory and reset the customer database to empty */
void reset(void) {
    for (int i =0; i < num_customers; i++){
        customers[i].diapers = 0;
        customers[i].bottles = 0;
        customers[i].rattles = 0;
        for (int j =0; j < customers[i].name.len; j++){
            customers[i].name.ptr[j]=0;
        }
        customers[i].name.len=0;
    }
    num_customers = 0;
    new_cutomer = 0;
    bottles = 0;
    diapers = 0;
    rattles = 0;
    new_bottles = 0;
    new_diapers = 0;
    new_rattles = 0;
    num_diapers=0;
    num_bottles = 0;
    num_rattles = 0;
    current_customer=0;
    customer_exist = false;
}

void processSummarize() {
    for (int i =0; i < num_customers; i++){
        if(num_diapers < customers[i].diapers){
            num_diapers = customers[i].diapers;
            new_diapers = i;
            Diapers_Customer = customers[i].name;
        }
    }
    for (int i =0; i < num_customers; i++){
        if(num_rattles < customers[i].rattles){
            num_rattles = customers[i].rattles;
            new_rattles = i;
            Rattles_Customer = customers[i].name;
        }
    }
    for (int i =0; i < num_customers; i++){
        if(num_bottles < customers[i].bottles){
            num_bottles = customers[i].bottles;
            new_bottles = i;
            Bottles_Customer = customers[i].name;
        }
    }

    printf("There are %d Bottles, %d Diapers and %d Rattles in inventory\n", bottles, diapers, rattles);
    printf("we have had a total of %d different customers\n", new_cutomer);
    if (customers[new_bottles].bottles !=0){
        StringPrint(&Bottles_Customer);
        printf(" has purchased the most Bottles (%d)\n",customers[new_bottles].bottles);
    }
    else{
        printf("no one has purchased any Bottles\n");
    }

    if (customers[new_diapers].diapers !=0){
        StringPrint(&Diapers_Customer);
        printf(" has purchased the most Diapers (%d)\n",customers[new_diapers].diapers);
    }
    else{
        printf("no one has purchased any Diapers\n");
    }

    if (customers[new_rattles].rattles !=0){
        StringPrint(&Rattles_Customer);
        printf(" has purchased the most Rattles (%d)\n",customers[new_rattles].rattles);
    }
    else{
        printf("no one has purchased any Rattles\n");
    }

}

void processPurchase() {
    allowed_to_process = true;
    String Customer_Name;
    String Item;
    int Item_Quantity =0;
    readString(&Customer_Name);
    readString(&Item);
    readNum(&Item_Quantity);
    if(strcmp(Item.ptr, "Bottles") == 0){
        if(Item_Quantity > bottles){
            allowed_to_process = false;
        }
    }
    if(strcmp(Item.ptr, "Rattles") == 0){
        if(Item_Quantity > rattles){
            allowed_to_process = false;
        }
    }
    if(strcmp(Item.ptr, "Diapers") == 0){
        if(Item_Quantity > diapers){
            allowed_to_process = false;
        }
    }
    if (allowed_to_process){
        if(Item_Quantity>0) {
            for (int i = 0; i <= num_customers; i++) {
                if (customers[i].name.ptr != 0){
                if (strcmp(customers[i].name.ptr, Customer_Name.ptr) == 0) {
                    current_customer = i;
                    customer_exist = true;
                    break;
                }}
                customer_exist = false;
            }
            if (customer_exist) {
                if (strcmp(Item.ptr, "Bottles") == 0) { customers[current_customer].bottles += Item_Quantity; bottles -= Item_Quantity;};
                if (strcmp(Item.ptr, "Rattles") == 0) { customers[current_customer].rattles += Item_Quantity; rattles -= Item_Quantity;};
                if (strcmp(Item.ptr, "Diapers") == 0) { customers[current_customer].diapers += Item_Quantity; diapers -= Item_Quantity;};
            }
            if (!customer_exist) {
                customers[num_customers].name.len = Customer_Name.len;
                customers[num_customers].name.ptr = Customer_Name.ptr;
                if (strcmp(Item.ptr, "Bottles") == 0) { customers[num_customers].bottles += Item_Quantity; bottles -= Item_Quantity;};
                if (strcmp(Item.ptr, "Rattles") == 0) { customers[num_customers].rattles += Item_Quantity; rattles -= Item_Quantity;};
                if (strcmp(Item.ptr, "Diapers") == 0) { customers[num_customers].diapers += Item_Quantity; diapers -= Item_Quantity;};
                current_customer = num_customers;
                num_customers += 1;
                new_cutomer += 1;
          }
        }
    }
    if (!allowed_to_process){
        printf("Sorry ");
        StringPrint(&Customer_Name);
        if(strcmp(Item.ptr, "Bottles") == 0){
            printf(", we only have %d ", bottles);
        }
        if(strcmp(Item.ptr, "Rattles") == 0){
            printf(", we only have %d ", rattles);
        }
        if(strcmp(Item.ptr, "Diapers") == 0) {
            printf(", we only have %d ", diapers);
        }
        StringPrint(&Item);
        printf("\n");
    }
}

void processInventory() {//This function checks for new inventories and update the inventory values
    String Item;    //make string type value for item's name
    int Item_Quantity =0;
    readString(&Item);
    readNum(&Item_Quantity);

    if (strcmp(Item.ptr,"Bottles") == 0){bottles += Item_Quantity;};
    if (strcmp(Item.ptr,"Rattles") == 0){rattles += Item_Quantity;};
    if (strcmp(Item.ptr,"Diapers") == 0){diapers += Item_Quantity;};
}
