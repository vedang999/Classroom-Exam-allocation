//No of slots and classrooms are fixed
//every course has its course code e.g co 27
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define noc 12 //number of classrooms
#define nslot 6
#define nclass 3
typedef struct student
{
    char name[10];
    int roll;
    int courses[5];
    struct student *next;

}student;
typedef struct Node
{
    int roll;
    struct Node *next;
    
}Node;


typedef struct course
{
    int code;
    char name[10];
    int strength;
    int slot;
    int year;
    Node *right;//student
    struct course *down;

}course;

course* create_course(FILE **fp){
    int n,y;
    char str[10];
    int slot;
    fscanf(*fp, "%s %d %d %d", str, &n, &y, &slot);
    //scanf("%s", str);
    //scanf("%d", &n);
    //scanf("%d", &y);
    
    //scanf("%d", &slot);
    course* c=(course*)malloc(sizeof(course));
    c->code=n;
    strcpy(c->name,str);
    c->strength=0;
    c->slot=slot;
    c->year=y;
    c->right=NULL;
    c->down=NULL;
    return c;
}

course* insert_at_head_course(course* head, FILE **fp)
{
    course* c=create_course(fp);
    c->down=head;
    //printf("**\n");
    
    head=c;
    return head;
}



int check(int arr[], course *root)
{
   int retval=1;
   int temp[6]={0,0,0,0,0,0};
   for(int i=0;i<5 && retval==1;i++)
   {
    course *ptr=root;
    while(ptr!=NULL &&  ptr->code!=arr[i])
    {
        ptr=ptr->down;

    }
    //printf("%d \n", arr[i]);
    if(ptr!=NULL)
    {
        if(temp[ptr->slot]==0)
        {
            temp[ptr->slot]=1;
        }
        else
        {
            retval=0;
        }

    }

    
   }
   return retval;

}
void append(course* ptr, int n){
    Node* new=(Node*)malloc(sizeof(Node));
    new->roll=n;
    // new->nex
    new->next=NULL;
    if(ptr->right==NULL){
        
//printf("#\t");
        ptr->right=new;
    }
    else{
        Node* lptr=ptr->right;
        while(lptr->next!=NULL)lptr=lptr->next;
        lptr->next=new;
        new->next=NULL;
    }
}

student* create_student(course *root, FILE **fp)
{
    student * s=(student*)malloc(sizeof(student));
    // printf("enter name & roll no. & course codes\n");
    char str[10];
    int n;
    fscanf(*fp, "%s",str);
    fscanf(*fp, "%d",&n);
    
    int temp[5];
    for(int i=0; i<5;i++)
    {
        fscanf(*fp, "%d", &temp[i]);
    }
 
    
    int ret=check(temp, root);//ret=0 phirse daalo
    //printf("%d\t", ret);
    if(ret==0)
    {
        printf("terminated\n, No entry is made\n");
        s=NULL;
        

        
        //s=create_student(root);

    }
    else
    {
       
       
       strcpy(s->name,str);
       //printf("%s\n", s->name);
       s->roll=n;
       //printf("%d\n", s->roll);
       for(int i=0; i<5;i++)
       {
        //printf("--\t");
        s->courses[i]=temp[i];
       }
       for(int i=0;i<5;i++)
       {
        int x=s->courses[i];
        course* ptr=root;
        while(ptr!=NULL)
        {
            if(ptr->code==x)
            {
                append(ptr,n);
                ptr->strength+=1;
            }
            ptr=ptr->down;
        }
       }
       s->next=NULL;

    }
    
    return s;//s will be null at failure

}
student* insert_at_head_stdlist(student* head,course* root, FILE**fp){
    student* new=create_student(root, fp);
    if(new!=NULL)
     {
        new->next=head;
        head=new;
     }
    return head;
    

}

void delete(student *head, course *root, int roll)
{
    student *temp=head;
    while(temp!=NULL)
    {
        temp=temp->next;
    }
    temp=head;
    student *prev_std;
    while(temp->roll!=roll)
    {
        prev_std=temp;
        temp=temp->next;
    }
    int arr[5];
    for(int i=0;i<5;i++)
    {
        arr[i]=temp->courses[i];
    }
    for(int i=0;i<5;i++)
    {
        course *t=root;
        while(t->code!=arr[i])
        {
            t=t->down;
        }
        Node *node_temp=t->right;
        Node *prev=NULL;
        while(node_temp->roll!=roll)
        {
           prev=node_temp;
           node_temp=node_temp->next;
        }
        if(prev!=NULL)
        prev->next=node_temp->next;
        else
        t->right=node_temp->next;
        free(node_temp);

    }
    if(prev_std!=NULL)
        prev_std->next=temp->next;
    
    free(temp);   
}

void del_course(course *root, student *head, int code)
{
    student *temp=head;
    int flag=0;
    while(flag==0 && temp!=NULL)
    {
       for(int i=0;i<5 && flag==0;i++)
       {
        if(temp->courses[i]==code)
        {
            flag=1;
        }
       }
       temp=temp->next;
    }
    if(flag==1)
    {
        printf("Course cannot be deleted\n");

    }
    else
    {
        course *t=root;
        course *del;
        while(t->down->code!=code)
        {
             t=t->down;
        }
        del=t->down;
        t->down=del->down;
        free(del);
    }
}

// /////////////////////////////////////////////////que 4
void sort_courses_by_strength_descending(course *head) {
    int swapped;
    course *ptr1;
    course *lptr = NULL;
    if (head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->down != lptr) {
            if (ptr1->strength < ptr1->down->strength) {
                //Swap the data 
                int temp_code = ptr1->code;
                ptr1->code = ptr1->down->code;
                ptr1->down->code = temp_code;

                char temp_name[10];
                strcpy(temp_name, ptr1->name);
                strcpy(ptr1->name, ptr1->down->name);
                strcpy(ptr1->down->name, temp_name);

                int temp_strength = ptr1->strength;
                ptr1->strength = ptr1->down->strength;
                ptr1->down->strength = temp_strength;

                int temp_slot = ptr1->slot;
                ptr1->slot = ptr1->down->slot;
                ptr1->down->slot = temp_slot;

                int temp_year = ptr1->year;
                ptr1->year = ptr1->down->year;
                ptr1->down->year = temp_year;

                Node *temp_right = ptr1->right;
                ptr1->right = ptr1->down->right;
                ptr1->down->right = temp_right;

                swapped = 1;
            }
            ptr1 = ptr1->down;
        }
        lptr = ptr1;
    } while (swapped);
}///sort function
void sort_years_by_strength_descending(course* arr[], int size) {
    int i, j;
    for (i = 0; i < size-1; i++) {
        for (j = 0; j < size-i-1; j++) {
            if (arr[j]->strength < arr[j+1]->strength) {
                // Swap arr[j] and arr[j+1]
                course* temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
//sort Year[] array
void lectures(course* root, FILE **fp){
//assuming 4 years
//array of pointers...to subject with strength x

course* Year[5];
for(int i=0;i<5;i++)Year[i]=NULL;

// int i=4;
// while(i--)printf("%d",i);
course* tra=root;
// course*tra2=root;
while(tra!=NULL){
    int curr=tra->year;
    // if(Year[curr])printf("%d ",curr);
    course* new=(course*)malloc(sizeof(course));
    new->slot=tra->slot;
    new->year=tra->year;
    new->code=tra->code;
    new->right=NULL;
    new->strength=tra->strength;
    fprintf(*fp, "%d ",new->strength);
    if(Year[curr]==NULL){
        // printf("%d ini ",curr);
        Year[curr]=new;
        new->down=NULL;
    }
    else{
        // printf("%d ",curr);
        new->down=Year[curr];
        Year[curr]=new;
    }

    tra=tra->down;
}
course* new=(course*)malloc(sizeof(course));
new->strength=0;
new->year=0;
Year[0]=new;//to counter the probleum with year 0
fprintf(*fp, "\nstep 1:\n");
for (int i = 0; i < 5; i++) {
    course* tra=Year[i];
    while(tra!=NULL){
        fprintf(*fp, "%d ",tra->strength);
        tra=tra->down;
    }
    fprintf(*fp,"\n");

}
fprintf(*fp, "\nstep 2:\n");
// //function to sort this array while allocation
for (int i = 0; i < 5; i++) {
    sort_courses_by_strength_descending(Year[i]);
}
for (int i = 0; i < 5; i++) {
    course* tra=Year[i];
    while(tra!=NULL){
        fprintf(*fp,"%d ",tra->strength);
        tra=tra->down;
    }
    fprintf(*fp,"\n");

}

printf("\n");
// course*arr[4]={Year[1],Year[2],Year[3],Year[4]};
sort_years_by_strength_descending(Year, 5);
for (int i = 0; i < 5; i++) {
    course* tra=Year[i];
    while(tra!=NULL){
        fprintf(*fp,"%d ",tra->strength);
        tra=tra->down;
    }
    fprintf(*fp,"\n");
    
}
//assuming 12 classes strength C1 C2 so on decreasing ..  & 6 slots
//case where allotment not possible.......if appropriate size classes in a slot for all subjects are not available 
//ex req 60 60 60 and we have 60 60 48

//assume to give top 4 classes with space to 4 years as per their max strength of any course
int Building[12][6];
int crs[12]={24,12,12,12,12,12,12,12,12,12,12,12};//class room size    ........already filled
for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 6; j++) {
        Building[i][j] = 0;
    }
}
for(int i=0;i<4;i++){
                        // printf(" %d",i);
        course* ptr=Year[i];
        while(ptr!=NULL){
            if(Building[i][ptr->slot]==0){
                if(crs[i]>=ptr->strength)Building[i][ptr->slot]=ptr->code;//replace course code with roll to use same struct
                else{
                    fprintf(*fp, "error case");
                    return;/////////////////////////case
                }
            }
            else{
                int l=12,flag=0;
                while(l-- && flag==0){
                    if(Building[12-l][ptr->slot]==0 && crs[12-l]>=ptr->strength){
                        Building[12-l][ptr->slot]=ptr->code;
                        flag=1;
                    }
                }
                if(flag==0){
                    fprintf(*fp, "error case");
                    return;/////////////////////////case
                }
            }

            ptr=ptr->down;
            }
        }
for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 6; j++) {
        if(Building[i][j]!=0){
            fprintf(*fp,"course %d in room A%d,slot %d\n",Building[i][j],i,j);
        }
    }
}
}
void exam_allot(course* root, FILE **fp){

// lets fill seat 1 then 3 with same subject. Then for next subject same. If 1 is filled seat on 2. if then 3 is free,sit there 
course* slots[6];
for(int i=0;i<6;i++){
    slots[i]=NULL;
}
course*tra=root;
course*tra2=root;
while(tra!=NULL){
    tra2=tra;
    tra=tra->down;
    int ss=tra2->slot;
    if(slots[ss]==NULL){
            // printf("Enter no of courses\n");
        slots[ss]=tra2;
        tra2->down=NULL;
    }
    else{
                    // printf("Enter no of courses\n");

        tra2->down=slots[ss];
        slots[ss]=tra2;
    }
}
int crs[8]={12,48,24,24,24,24,24,24};//class room size    ........already filled
// int columns=10;/////////default;
int i=6;
while(i--){
    int xam[8][4][20];
            for(int q=0;q<8 ;q++)
                for(int w=0;w<4 ;w++)
                    for(int e=0;e<20 ;e++)xam[q][w][e]=0;
    course* ptr=slots[i];
    while(ptr!=NULL){
    printf(" %s ",ptr->name);
        Node* lptr=ptr->right;
        int flag=1;
        if(lptr==NULL)flag=0;
        // while(lptr!=NULL){
        //     printf(" %d ",lptr->roll);
        //     lptr=lptr->next;
        // }
        //     printf("0");
        
        for(int q=0;q<8 && flag==1;q++){
            for(int w=0;w<4 && flag==1;w++){
                for(int e=0;e<crs[q]/4 && flag==1;e+=3){
                    // if(lptr!=NULL)printf(" %d ",q);
                    if(xam[q][w][e]==0){
                        xam[q][w][e]=lptr->roll;
                        lptr=lptr->next;
                        if(lptr!=NULL){
                            xam[q][w][e+2]=lptr->roll;
                            lptr=lptr->next;
                        }
                    }   
                    else if(xam[q][w][e+1]==0){
                        xam[q][w][e+1]=lptr->roll;
                        lptr=lptr->next;
                    }
                    else if(xam[q][w][e+2]==0){
                        xam[q][w][e+2]=lptr->roll;
                        lptr=lptr->next;
                    }

                    // lptr=lptr->next;
                    if(lptr==NULL)flag=0;
                }
            }
        }
        ptr=ptr->down;
    }
    
fprintf(*fp, "slot %d \n",i);
for(int q=0;q<8 ;q++){
    fprintf(*fp, "Class A%d \n",q);
    for(int w=0;w<4 ;w++){
        for(int e=0;e<crs[q]/4 ;e++){
            if(xam[q][w][e])fprintf(*fp, " r%d c%d -> %d \n",w,e,xam[q][w][e]);
        }}}
        fprintf(*fp, "\n");
}
}


int main()
{
    course * root;
    int num, roll;
    FILE *fp=fopen("course.txt", "r");
    FILE *input, *read, *out, *allot;
    printf("Enter no of courses\n");
    scanf("%d", &num);
    root=create_course(&fp);
    for(int i=0;i<num-1;i++){
        root=insert_at_head_course(root, &fp);
    }

    course* temp=root;
    while(temp!=NULL)
    {
     //printf("%d\n", temp->code);
     temp=temp->down;
    }
    student * head;
    FILE *fpp=fopen("student.txt", "r");
    
    int n;
    printf("Enter no of students\n");
    scanf("%d", &n);
    head=create_student(root, &fpp);
    for(int i=0;i<n-1;i++)
    {
       head=insert_at_head_stdlist(head, root, &fpp);
       
    }
    
    int question;
     
    do{
    printf("Enter the question number or -1 to exit()\n");
    scanf("%d", &question);
    switch(question)
    {
        case 1:
         printf("adding student to student list, write details of student in input_std.txt fiile\n");
         input=fopen("input_std.txt", "r");

         head=insert_at_head_stdlist(head, root, &input);
         fclose(input);

         
         break;
        case 2:
          printf("Deletion of student from student list\n");
          printf("Enter the roll no to delete");
          scanf("%d", &roll);
          delete(head, root, roll);



         break;
        case 3:
         printf("Adding a course to course list\n");
         printf("Enter the details in file read.txt\n");
         read=fopen("read.txt", "r");
         root=insert_at_head_course(root, &read);
         fclose(read);
         //char ch;
         
         

         
         break;
        case 4:
         out=fopen("lect.txt", "w");
         lectures(root, &out);
         
         break;
        case 6:
         allot=fopen("allot.txt", "w");
         exam_allot(root, &allot);

    
    }}
    while(question>0);
    //output on output.txt file
    FILE *output=fopen("output.txt", "w");
    //adding student list only roll no
    student *tem=head;
    while(tem!=NULL)
    {
     fprintf(output, "%d\n", tem->roll);
     tem=tem->next;
    }
    course *tep=root;
    while(tep!=NULL)
    {
     fprintf(output, "%d\n", tep->code);
     tep=tep->down;
    }
    fclose(output);
    
    

    
}
