// Julliane J. Tampus My personal banking system project in C programming
// Bancking System Version 1.0



#include <stdio.h>


//-----------------------------------This is the Function Prototype of the Program-----------------------------

void create_user();
void display_user();

//-------------------------------------------------------------------------------------------------------------



//-------------------------------------This is The main Fuction of The Program--------------------------------- 

int main(){

//-------------------------------------This is the main Variable of the Program--------------------------------


    int cd, pin, id, toid, pass, bln,ammount;
    char name[10];


//-------------------------------------------------------------------------------------------------------------

//------------------------------------This is the welcome promt of the program---------------------------------
//---------------------------This will tell the user to create a user or log a user----------------------------
    printf("Welcome to Bank C\n\n\t[1.] Login\n\t[2.] Create User\n\t[3.] Display Users\n\t[0.] Exit\n\nEnter a Command: ");
    scanf("%d", &cd);

//-------------------------------------------------------------------------------------------------------------

//-------------------This code will check the condition if the user wamts to login or create a user------------ 

    if(cd == 1)
    {

//------------------ --------------this part will promt the user to log in a user------------------------------

        log_in://This is a flag so that if the log in is error it will loop back
        printf("Enter your id: ");
        scanf("%d", &id);
        printf("Enter your pin: ");
        scanf("%d", &pin);
        check_user(id, pin);

        if(check_user(id,pin) == 1)// This Call a Fuction to check if the user is valid of in the data base
        {

//-------------------------------------This is the file handiling of this condition-----------------------------


            FILE * old = fopen("record.txt", "r");//This wil read the file to use to the new file

            FILE * new = fopen("new_record.txt", "w");// this will create a new or update file of the old file


//---------------------------------------------------------------------------------------------------------------

            bank_cd://this is a flag to loop back the user if error occur

//---------------------------This part is to promt the user if they what to deposite or widthraw-----------------           


            printf("\n\t[1.] Deposite\n\t[2.] Widthraw\n\t[0.] Log Out\n\nEnter a command:");
            scanf("%d", &cd);


            // This part will check if the user wants to exit if not then it will procced to the next promting
                if(cd == 0)
                {
                    while(fscanf(old, "%d\n%s\n%d\n%d", &toid,name,&pass,&bln) != EOF){
                         fprintf(new, "%d\n%s\n%d\n%d\n", toid,name,pass,bln);
                    }
                    printf("\nLoging out..........\n");
                    goto file_ex;
                }

            printf("Enter a Ammount: ");
            scanf("%d", &ammount);


//-----------------------------------------------------------------------------------------------------------------


//----this part will loop and print to the new file all the old conrent and also update the ammount that change-----


            while(fscanf(old, "%d\n%s\n%d\n%d", &toid,name,&pass,&bln) != EOF){

                if(cd == 1)//This is for the Deposite Condition 
                {

                    if(toid != id)
                    {
                        fprintf(new, "%d\n%s\n%d\n%d\n", toid,name,pass,bln);
                    }
                    else
                    {
                        fprintf(new, "%d\n%s\n%d\n%d\n", toid,name,pass,bln+=ammount);
                    }

                }
                else if(cd == 2)//This is for the Widthraw Condition
                {

                    if(toid != id)
                    {
                        fprintf(new, "%d\n%s\n%d\n%d\n", toid,name,pass,bln);
                    }
                    else
                    {
                        if(ammount < bln)
                        {
                            fprintf(new, "%d\n%s\n%d\n%d\n", toid,name,pass,bln-=ammount);
                        }else
                        {
                            printf("\nTransaction Failed: (Don't Have Enough Balance)\n");
                        }
                        
                    }

                }
                else
                {
                    goto bank_cd;
                }
            }
            file_ex:
            fclose(old);// this will close the file on old
            fclose(new);// this will close the file on new

//-------------------------------------------------------------------------------------------------------------------

//-----------------------------------------This Part will apply the new file to the old file-------------------------


            remove("record.txt");//This will remove the old file 

            rename("new_record.txt", "record.txt");//V
            //This wil rename the new file same name as the old file so the file will be updated

//--------------------------------------------------------------------------------------------------------------------
 
 
//--------------------------------------------This Part is the Saving notification------------------------------------
            printf("Saving");
            for(int i = 50; i > 0; i--){
                printf(".");
            }
            printf("\n");
            main(); 


//----------------------------------------------------------------------------------------------------------------------            
 
        }
        else
        {
           printf("\nNo User found\n");
           main();
        }

//--------------------------------------------------------------------------------------------------------------



//---------------------------------This part will tell the user to create a user--------------------------------

    }
    else if(cd == 2)
    {
        create_user();// this will call a fuction to insert a user to thw data base 
    }
    else if(cd == 3)
    {
        printf("\n----------Bank C Users----------\n");
        display_user();
        main();
    }
    else if(cd == 0)
    {
        printf("\nExiting....\n");
    }
    else
    {
        printf("\n!!!Wrong Command!!!\n");// this will tell the user that they enter a wrong command
        main();// amd if they enter a wrong command this will call the main function again
    }
//--------------------------------------------------------------------------------------------------------------
    return 0;
}
//-------------------------------------This is The End Of the Main Fuction---------------------------------------



//------------------------------This is the function to create a user on the data base-----------------------------


void create_user(){


//-------------------------------------This is the variables of this fuction----------------------------------------


    int id , pin, balance = 0;
    char name[10];
    FILE * data = fopen("record.txt", "a");// this will open a file to the root directory of program 


//------------------------------------------------------------------------------------------------------------------


//----------------------------------------This will promt the user to create a user---------------------------------

    printf("Enter your id: ");// Ask to enter the ID they wamt
    scanf("%d", &id);

    printf("Enter your Username: ");//Ask to enter there name
    scanf("%s", name);

    printf("Enter your pin: ");// Ask to enter a pin that they want
    scanf("%d", &pin);

//-----------------------------------------------------------------------------------------------------------------

//--------------------------------This is the part where the program save the information--------------------------


    fprintf(data, "%d\n%s\n%d\n%d\n", id,name, pin, balance); // This will print the information in the file

    fclose(data);// this will close the file

    printf("User Created Successfully!\n");// this print to the console to know the user is successfully created 
    //note once the user created the balance of the user will set to 0 

    main();//this will call the main fuction to loop back


 //------------------------------------------------------------------------------------------------------------------   
}
//--------------------------------------This is the end of the function to create a user-----------------------------




//-------------------------------------This is the fuction to check the user-----------------------------------------

int check_user(int toid, int pass){

//-------------------------------------This is the Variable on this function-----------------------------------------


    int id, pin, balance;
    char name[60];
    FILE * data = fopen("record.txt", "r");// This will read the content of the file

//-------------------------------------------------------------------------------------------------------------------

//-----------------------This part is the Looping condition to check if the user Exists in the file------------------



    while(fscanf(data, "%d\n%s\n%d\n%d", &id,name,&pin,&balance) != EOF)
    {
        if(toid == id)
        {
            if(pass == pin){
                printf("\nWelcome To Bank C\nUser: %s\nBalance: %d\n\n", name,balance);
                fclose(data); 
                return 1;// This will return 1 to tell the condition that the user is in the record file 
            }else{
                fclose(data); 
                return 0;// this will return 0 telling the condition that the user is not in the file.
            }
        }
    }
    
       


//-------------------------------------------------------------------------------------------------------------------
}
//-----------------------------------End of this Funtion-------------------------------------------------------------


//-----------------------------This is the funtion to display all the user on the record-----------------------------


void display_user(){

//--------------------------------This part is the variable for this function----------------------------------------


    int id, toid, pass, bln;
    char name[10];
    FILE * user = fopen("record.txt", "r");


//-------------------------------------------------------------------------------------------------------------------
    
    while(fscanf(user, "%d\n%s\n%d\n%d", &toid,name,&pass,&bln) != EOF)
    {
        printf("\nUser: %d\n\tName: %s\n\tBalance: %d\n\n", toid,name,bln);
        // This will loop and print all the data inside of the function
    }
    fclose(user);

}
//--------------------------------------------End for this funtion---------------------------------------------------