#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
struct user
{
	int pin;
	int balance;
	char name[50];
};
void main()
{
	system("color 9");
	time_t now;
	time(&now);
	printf("\n    ===========================================================================\n");
    printf("\n                                                         %s",ctime(&now));
	printf("\n");
	printf("                               WELCOME TO                              \n");
	printf("                                    ATM SERVICES                       \n");
	printf("\n");
    printf("\n    ===========================================================================\n");
	int pin=0,balance=0;
	FILE *fp=fopen("username.csv","r");
	char a[50];
	fgets(a,50,fp);
	char *item;
	struct user u[50];
	int i=0;
	while(fgets(a,50,fp))
	{
		item=strtok(a,",");
		u[i].pin=atoi(item);
		item=strtok(NULL,",");
		strcpy(u[i].name,item);
		item=strtok(NULL,",");
		u[i].balance=atoi(item);
		i++;
	}
	int n=i;
	fclose(fp);
	int input_pin;
	char user_name[50];
	int t,trial=1,count=0,user=0;
	while(trial<4)
	{
		while(count!=1)
		{
			printf("\n      Enter pin: ");
			scanf("%d",&input_pin);
			for(t=0;t<n;t++)
			{
				if(input_pin==u[t].pin)
				{
					count++; //count becomes 1 if pin matches, else 0
					user=t; //this user is to get the serial no. of user
				}
			}
			if(count==1)
			{
				pin=u[user].pin;
				balance=u[user].balance;
				strcpy(user_name,u[user].name);
			}
			else
			{
				Beep(300,250);
				printf("\n      Invalid pin, check again!!!!\n");
			}
		}
		trial++;
	}
	int option,amount=1,continueTransaction=1,cur_pin=0,new_pin=0,r_pin=0;
	while(continueTransaction!=0)
	{
		//printf("Hello %s\n",user_name);
	    printf("\n    ********** Available Transactions **********\n");
	    printf("\n    ||1. Withdrawl     ||\n");
	    printf("    ||2. Deposit       ||\n");
	    printf("    ||3. Balance Check ||\n");
		printf("    ||4. Change Pin    ||\n");
		printf("    ||5. Exit          ||\n");
	    printf("\n    =================================================");
        printf("\n\n    Enter an option between 1 and 5: ");
    	scanf("%d",&option);
    	switch(option)
    	{
	       	case 1: 
		    	printf("\n    Enter the amount: ");
		    	scanf("%d",&amount);
			    if(amount%100 != 0)
    		    {
			    	printf("\n    Amount should be a multiple of 100");
					Beep(300,250);
			    	amount=1;
			    	break;
		    	}
			    else if(balance<amount)
			    {
		    		printf("\n    Insufficient Balance");
					Beep(300,250);
		    		amount=1;
		    		break;
		    	}
		    	else
		    	{
			    	printf("\n    Amount Withdrawn: %d",amount);
			    	balance -= amount;
			    	amount=1;
			    	printf("\n    Updated balance: %d\n",balance);
			    	break;
		    	}
	    	case 2:
	    		printf("\n    Enter the amount: ");
		    	scanf("%d",&amount);
			    printf("\n    Amount Deposited: %d",amount);
			    balance += amount;
			    printf("\n    Updated balance: %d\n",balance);
    			amount=1;
    			break;
	    	case 3:
    			printf("\n    Account Balance: %d\n",balance);
	    		break;
			case 4:
				printf("\n            You have chosen to change pin          \n");
				printf("\n    Enter current pin: ");
				scanf("%d",&cur_pin);
				if(cur_pin==pin)
				{
					printf("\n    Enter new pin: ");
					scanf("%d",&new_pin);
					if(new_pin==cur_pin)
					{
						printf("\n            New pin is same as current pin");
						printf("\n            Pin Change Unsuccessful\n");
						Beep(300,250);
					}
					if(new_pin<999 || new_pin>9999) //pin is not 4 digit no.
					{
						printf("\n            Enter 4 digit pin");
						printf("\n            Pin Change Unsuccessful\n");
						Beep(300,250);
					}
					if(new_pin!=cur_pin && new_pin>999 && new_pin<9999) //condition for 4 digit pin
					{
						printf("\n    Re-enter new pin: ");
						scanf("%d",&r_pin);
						if(r_pin!=new_pin)
						{
							printf("\n            Re-entered pin should be same as new pin");
							printf("\n            Pin Change Unsuccessful\n");
							Beep(300,250);
						}
						else
						{
							//printf("Old pin: %d\n",pin);
							pin=new_pin;
							//printf("New pin: %d\n",pin);
							printf("\n            Pin Changed Successfully\n");
						}
					}	
				}
				else
				{
					printf("\n            Incorrect pin!!!");
					printf("\n            Pin Change Unsuccessful\n");
					Beep(300,250);
				}
				break;
			case 5:
				exit(0);
				break;
		    default:
				printf("\n    Please enter a valid option\n");
		}
		printf("\n\n    ********** Do you wish to perform one more transaction? **********\n");
		printf("\n                 Press 1 for yes and 0 for no: ");
		scanf("%d",&continueTransaction);
	}
}