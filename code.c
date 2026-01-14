#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define STUDENTS 10
#define SUBJECTS 5

struct Student {
    char id[20];
    char name[50];
    int marks[SUBJECTS];
    int total;
    float percentage;
    float cgpa;
    char grade[3];
};
int validName(char name[]);
void computeResult(struct Student *s);
void assignGrade(float p, char grade[]);

int main() {
    FILE *fin, *fout;
    struct Student s[STUDENTS];
    int i, j;
    float classAvg = 0.0, high, low;
    int countO = 0, countAp = 0, countA = 0, countBp = 0;
    int countB = 0, countC = 0, countP = 0, countF = 0;

    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    if (fin == NULL || fout == NULL) {
        printf("Error: Cannot open file!\n");
        return 1;
    }
    fscanf(fin, "%d\n", &i);
    for (i = 0; i < STUDENTS; i++) {
        fscanf(fin, "%s ", s[i].id);
        fgets(s[i].name, sizeof(s[i].name), fin);
        s[i].name[strcspn(s[i].name, "\n")] = '\0';
        if (!validName(s[i].name)) {
            printf("Invalid name detected for student %d\n", i + 1);
            return 1;
        }
        for (j = 0; j < SUBJECTS; j++) {
            fscanf(fin, "%d", &s[i].marks[j]);
            if (s[i].marks[j] < 0 || s[i].marks[j] > 100) {
                printf("Invalid marks detected!\n");
                return 1;
            }
        }
        computeResult(&s[i]);
        classAvg += s[i].cgpa;
        if (strcmp(s[i].grade, "O") == 0) countO++;
        else if (strcmp(s[i].grade, "A+") == 0) countAp++;
        else if (strcmp(s[i].grade, "A") == 0) countA++;
        else if (strcmp(s[i].grade, "B+") == 0) countBp++;
        else if (strcmp(s[i].grade, "B") == 0) countB++;
        else if (strcmp(s[i].grade, "C") == 0) countC++;
        else if (strcmp(s[i].grade, "P") == 0) countP++;
        else if (strcmp(s[i].grade, "F") == 0) countF++;
    }
    fclose(fin);

    classAvg /= STUDENTS;
    high = low = s[0].cgpa;
    for (i = 1; i < STUDENTS; i++) {
        if (s[i].cgpa > high) high = s[i].cgpa;
        if (s[i].cgpa < low) low = s[i].cgpa;
    }

    fprintf(fout, "+-----------------------------------------------------------------------------------+\n");
    fprintf(fout, "| ID        | Name                     | Total | CGPA | Grade |\n");
    fprintf(fout, "+-----------------------------------------------------------------------------------+\n");

    for (i = 0; i < STUDENTS; i++) {
        fprintf(fout, "| %-9s | %-24s | %-5d | %-4.2f | %-5s |\n",
                s[i].id, s[i].name, s[i].total,
                s[i].cgpa, s[i].grade);
    }

    fprintf(fout, "+-----------------------------------------------------------------------------------+\n");
    fprintf(fout, "| Class Average CGPA : %-58.2f |\n", classAvg);
    fprintf(fout, "| Highest CGPA       : %-58.2f |\n", high);
    fprintf(fout, "| Lowest CGPA        : %-58.2f |\n", low);
    fprintf(fout, "+-----------------------------------------------------------------------------------+\n\n");

    fprintf(fout, "+-------------------+\n");
    fprintf(fout, "| Grade | Students  |\n");
    fprintf(fout, "+-------------------+\n");
    fprintf(fout, "| O     | %-9d |\n", countO);
    fprintf(fout, "| A+    | %-9d |\n", countAp);
    fprintf(fout, "| A     | %-9d |\n", countA);
    fprintf(fout, "| B+    | %-9d |\n", countBp);
    fprintf(fout, "| B     | %-9d |\n", countB);
    fprintf(fout, "| C     | %-9d |\n", countC);
    fprintf(fout, "| P     | %-9d |\n", countP);
    fprintf(fout, "| F     | %-9d |\n", countF);
    fprintf(fout, "+-------------------+\n");

    fclose(fout);
    printf("Result successfully written to output.txt\n");
    return 0;
}
int validName(char name[]) {
    int i;
    for (i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ')
            return 0;
    }
    return 1;
}
void computeResult(struct Student *s) {
    int i;
    s->total = 0;
    for (i = 0; i < SUBJECTS; i++)
        s->total += s->marks[i];
    s->percentage = s->total / 5.0;
    s->cgpa = s->percentage / 10.0;
    assignGrade(s->percentage, s->grade);
}
void assignGrade(float p, char grade[]) {
    if (p >= 90)
        strcpy(grade, "O");
    else if (p >= 85)
        strcpy(grade, "A+");
    else if (p >= 75)
        strcpy(grade, "A");
    else if (p >= 65)
        strcpy(grade, "B+");
    else if (p >= 60)
        strcpy(grade, "B");
    else if (p >= 55)
        strcpy(grade, "C");
    else if (p >= 50)
        strcpy(grade, "P");
    else
        strcpy(grade, "F");
}
