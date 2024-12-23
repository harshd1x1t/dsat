#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <fstream>
#include <sstream>
#include <iostream>
typedef struct
{ 
 char name[25]; 
 char phone_no[15]; 
 char address[50]; 
}Contact; 
struct node
{ 
 Contact data; 
 struct node *next; 
 struct node *prev; 
}; 
typedef struct node *NODE; 
NODE getnode(Contact contact) 
{ 
 NODE x; 

 x=(NODE)malloc(sizeof(struct node)); 
 if(x==NULL) 
 { 
 printf("\nInsufficient memory"); 
 exit(0); 
 } 
 x->data = contact; 
 x->prev = NULL; 
 x->next = NULL; 
 return(x); 
} 

NODE phonebook;
void insert_contact(NODE head,Contact contact,int flag) 
{ 
    if(flag == 1) {
        
    }
 NODE temp,cur,back; 
 temp = getnode(contact); 
 cur=head->next; 
 back=head; 
 while(cur!=NULL) 
 { 
 if(strcmp(temp->data.name,cur->data.name)<0) 
 {
    cur->prev=temp; 
 temp->next=cur; 
 break; 
 } 
 back = cur; 
 cur=cur->next; 
 } 
 
 back->next=temp; 
 temp->prev=back; 
 if(flag == 1) {
    std::ofstream databook;
    databook.open("data.txt", std::ios::app);
    databook << temp->data.name << " " << temp->data.phone_no << " " << temp->data.address << std::endl;
    databook.close();
 }
} 
void delete_contact(NODE head,char name[25]) 
{ 
    std::ofstream databook;
    databook.open("data.txt");
 NODE second,cur,back; 
 if(head->next==NULL) 
 { 
 printf("\nList is empty"); 
 } 
 cur=head->next; 
 while(cur!=NULL) 
 { 
 if(strcmp(cur->data.name,name)==0) 
 { 
 printf("%s Details are deleted",cur->data.name); 
 second=cur->next; 
 back=cur->prev; 
 free(cur); 
 back->next=second; 
 
 if(second != NULL) 
 second->prev = back; 
 return; 
 } 
 databook << cur->data.name << " " << cur->data.phone_no << " " << cur->data.address << std::endl;
 cur=cur->next; 
 } 
 printf("%s is not found",name); 
} 
void search_contact(NODE head,char name[25]) 
{ 
 NODE cur; 
 if(head->next==NULL) 
 { 
 printf("\nList is empty"); 
 return; 
 } 
 cur=head->next; 
 while(cur!=NULL)
 { 
 if(strcmp(cur->data.name,name)==0) 
 { 
 printf("\n%s is found \n",name); 
 printf("\n\n|Name:%s|\n|Phone number:%s|\t\n|Address:%s|\n\n",cur->data.name,cur->data.phone_no,cur->data.address); 
 return; 
 } 
 cur=cur->next; 
 } 
 printf("%s is not found. ",name); 
 return; 
} 
void display(NODE head) 
{ 
 NODE cur; 
 if(head->next==NULL) 
 { 
 printf("\nlist is empty"); 
 return; 
 } 
 printf("\nContacts in Phone book are"); 
 cur=head->next; 

 while(cur!=NULL) 
 { 
 printf("\n\n|Name:%s|\n|Phone number:%s|\n|Address:%s|\n\n",cur->data.name,cur->data.phone_no,cur->data.address); 
 cur=cur->next; 
 } 
} 

void initialize(){
    std::ifstream databook;
    databook.open("data.txt");
    Contact contact;
    
    std::string temp_string;
    while(!databook.eof()) {
        std::getline(databook,temp_string);
        std::stringstream temp_string_stream{temp_string};
        temp_string_stream >> contact.name >> contact.phone_no >> contact.address;

        // insert_contact(phonebook, contact, 0);

    }
    databook.close();
}

int main() 
{ 
//    std::ofstream databook;
//    databook.open("data.txt");
 int choice; 
 char name[25]; 
 Contact contact; 
 NODE phonebook = getnode(contact); 
 initialize();
 std::string complete_file;
 std::string single_contact;
 std::stringstream complete_file_stream;
 std::stringstream single_contact_stream{single_contact};
 std::string name2, phone_no, address;
 while(1) 
 { 
 printf("\n*WELCOME TO PHONEBOOK*\n"); 
 printf("\n1-ADD CONTACT\n2-DELETE CONTACT\n3-SEARCH CONTACT\n4-DISPLAY CONTACTS\n5-EXIT"); 
 printf("\nEnter your choice: "); 
 scanf("%d",&choice); 
 switch(choice) 
 { 
 case 1:printf("\nEnter name: \n");
 scanf("%s",&contact.name); 
 printf("\nEnter Phone number: \n"); 
 scanf("%s",&contact.phone_no); 
 printf("\nEnter address: \n"); 
 scanf("%s",&contact.address); 
 insert_contact(phonebook,contact, 1); 
 //databook << contact.name << " " << contact.phone_no <<" "<<contact.address <<std::endl;
 break; 
 case 2:printf("\nEnter name to delete the contact info: \n");
 {
    std::ifstream databook;
 databook.open("data.txt"); 
 scanf("%s",&name); 
 delete_contact(phonebook,name);
 //std::stringstream single_contact_stream;
 complete_file_stream.clear();
 complete_file_stream << databook.rdbuf();
 complete_file = complete_file_stream.str(); 
 databook.close();

 std::ofstream write_book;
 write_book.open("data.txt");
 while(std::getline(complete_file_stream,single_contact)){
    single_contact_stream.clear();
    single_contact_stream << single_contact;
    single_contact_stream >> name2 >> phone_no >> address;
    if(name2 == name){

    }else{
        write_book << name2 << " " << phone_no << " " << address << std::endl;
    }
 }
 }
 
 break; 
 case 3:
 printf("\nEnter name to search the contact info: \n"); 
 scanf("%s",&name); 
 search_contact(phonebook,name); 
 break; 
 case 4:display(phonebook); 
 break; 
 case 5:exit(0); 
 default:printf("\n*Invalid choice*\n");
 }
 }
return 0;
}