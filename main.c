#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void right_dominant(char input[], int *longest);

void reset(int *palindrome_count,char **palindrome, int *longest){

    int i;
    for(i=0;i<*palindrome_count;i++)
            free(palindrome[i]);
        *longest=0;
        *palindrome_count=0;
}
int is_palindrome(char input[]){
    int i,strlen_input = strlen(input);

    for(i=0;i<strlen_input;i++){
        if(input[i]!=input[strlen_input-1-i])
            return 0;
    }
    return 1;
}

void left_dominant(char input[], int *longest){
    char copy_input[strlen(input)+2];
    int i,j;

    if(strlen(input)>=*longest){
        return;
    }


    for(i=0;i<=strlen(input);i++){
        copy_input[i]=input[i];
    }

    for(i=0;i<strlen(copy_input);i++){
        if(copy_input[i]!=copy_input[strlen(copy_input)-1-i]){
            for(j=strlen(input);j>=strlen(copy_input)-1-i;j--){
                copy_input[j+1]=copy_input[j];
            }
            copy_input[strlen(copy_input)-1-i]=copy_input[i];
            break;
        }
    }
    if(is_palindrome(copy_input)){
        if(strlen(copy_input)<*longest)
        *longest=strlen(copy_input);
        //printf("%s %d\n",copy_input);
        return;
    }
    right_dominant(copy_input, longest);
    left_dominant(copy_input, longest);
    return;


}
void right_dominant(char input[], int *longest){
    char copy_input[strlen(input)+2];
    int i,j;

    if(strlen(input)>=*longest){
        return;
    }

    for(i=0;i<=strlen(input);i++){
        copy_input[i]=input[i];
    }

    for(i=0;i<strlen(copy_input);i++){
        if(copy_input[i]!=copy_input[strlen(copy_input)-1-i]){
            for(j=strlen(input);j>=i;j--){
                copy_input[j+1]=copy_input[j];
            }
            copy_input[i]=copy_input[strlen(copy_input)-1-i];
            break;
        }
    }
    if(is_palindrome(copy_input)){
        if(strlen(copy_input)<*longest)
            *longest=strlen(copy_input);
        //printf("%s %d\n",copy_input);
        return;

    }
    right_dominant(copy_input,longest);
    left_dominant(copy_input,longest);
    return;
}

int main()
{
    char input[1001];
    int input_len,longest=9999;

    while(fgets(input,1000,stdin)!=NULL){
        if(input[0]=='\0'){
            return 0;
        }
        input_len = strlen(input);
        input[input_len-1]='\0'; //Vyradenie \n z pola
        input_len--;

        if(is_palindrome(input)){
            printf("0\n\n",input);
            continue;
        }
        left_dominant(input,&longest);
        right_dominant(input,&longest);

        printf("%d\n\n",longest-input_len);

    longest=9999;
    }
}
