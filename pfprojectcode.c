#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void showCertificate(char *firstName, char *lastName, int rollNumber, int totalScore, int totalMarks) {
    float percentage = ((float)totalScore / totalMarks) * 100;
    printf("\n\n--------------------------------------------------------\n");
    printf("                      \033[0;33mCERTIFICATE\033[0m                       \n");
    printf("--------------------------------------------------------\n");
    printf("This is to certify that \033[0;32m%s %s\033[0m (Roll No: \033[0;32m%d\033[0m)\n", firstName, lastName, rollNumber);
    printf("has successfully completed the quiz program with a\n");
    printf("total score of \033[38;5;208m%d/%d\033[0m (\033[0;32m%.2f%%\033[0m).\n", totalScore, totalMarks, percentage);
    printf("Keep up the excellent work!\n");
    printf("--------------------------------------------------------\n\n\n");
}

void saveStudentRecord(const char *firstName, const char *lastName, int rollNumber, const char *testName, int score, int totalMarks) {
    FILE *recordFile = fopen("quizData.txt", "a");
    if (recordFile == NULL) {
        printf("\033[0;31mError: Could not open the record file!\033[0m\n");
        return;
    }

    float percentage = ((float)score / totalMarks) * 100;

    fprintf(recordFile, "%s %s | Roll No: %d | %s : %d/%d | Percentage: %.2f%%\n", firstName, lastName, rollNumber, testName, score, totalMarks, percentage);
    fclose(recordFile);
}

int getValidInput(int min, int max) {
    char input[10];
    int choice;
    while (1) {
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &choice) == 1 && choice >= min && choice <= max) {
            return choice;
        }
        printf("\033[0;31mInvalid input! Please enter a number between %d and %d:\033[0m ", min, max);
    }
}

int conductQuiz(const char *fileName, const int correctAnswers[]) {
    FILE *ptr = fopen(fileName, "r");
    if (ptr == NULL) {
        printf("Error opening file: %s\n", fileName);
        return 0;
    }

    char question[500];
    int score = 0, questionNumber = 0, userAnswer;

    while (fgets(question, sizeof(question), ptr) != NULL) {
        printf("\n\033[0;33mQuestion %d\033[0m: %s", ++questionNumber, question);
        printf("\033[0;33mChoose the correct option (1, 2, 3, 4):\033[0m ");
        userAnswer = getValidInput(1, 4);

        if (userAnswer == correctAnswers[questionNumber - 1]) {
            printf("\033[0;32mCorrect!\033[0m\n");
            score++;
        } else {
            printf("\033[0;31mIncorrect!\033[0m The correct answer is: %d\n", correctAnswers[questionNumber - 1]);
        }
    }

    fclose(ptr);
    return score;
}

void menu() {
    char firstName[15], lastName[15];
    int rollNo, score, choice, retryChoice;
    int totalScore = 0, totalMarks = 0;
    int attempt[4] = {0, 0, 0, 0};

    printf("\n\n");
    printf("                    \033[0;32m\"Welcome to the Educational Quiz Program!\"\033[0m                   ");
    printf("\n\nEnter your First Name: ");
    scanf("%s", firstName);
    while (getchar() != '\n');

    printf("Enter your Last Name: ");
    scanf("%s", lastName);
    while (getchar() != '\n');

    printf("Enter your Roll Number: ");
    scanf("%d", &rollNo);
    while (getchar() != '\n');

    do {
        printf("\n\033[0;32mWelcome!\033[0m Please select an option:\n\n");
        printf("\033[0;33m1. Physics Test\n2. English Test\n3. Mathematics Test\n4. General Knowledge Test\n5. Exit\033[0m\n\n");
        printf("Your choice (1, 2, 3, 4, 5): ");
        choice = getValidInput(1, 5);

        int physicsAnswers[10] = {3, 3, 1, 3, 4, 4, 1, 4, 2, 3};
        int englishAnswers[10] = {1, 1, 2, 3, 3, 2, 2, 2, 1, 2};
        int mathAnswers[10] = {3, 2, 3, 2, 3, 4, 1, 1, 3, 2};
        int gkAnswers[10] = {3, 2, 2, 2, 2, 2, 3, 4, 1, 2};

        if (choice >= 1 && choice <= 4) {
            if (attempt[choice - 1]) {
                printf("\033[0;31m\nYou have already attempted this test. Please select another.\033[0m\n");
                continue;
            }
        }

        switch (choice) {
            case 1:
                printf("\n\033[0;32mYou Selected Physics Test!\033[0m\n");
                score = conductQuiz("phy.txt", physicsAnswers);
                totalMarks += 10;
                saveStudentRecord(firstName, lastName, rollNo, "Physics", score, 10);
                break;
            case 2:
                printf("\n\033[0;32mYou Selected English Test!\033[0m\n");
                score = conductQuiz("eng.txt", englishAnswers);
                totalMarks += 10;
                saveStudentRecord(firstName, lastName, rollNo, "English", score, 10);
                break;
            case 3:
                printf("\n\033[0;32mYou Selected Maths Test!\033[0m\n");
                score = conductQuiz("math.txt", mathAnswers);
                totalMarks += 10;
                saveStudentRecord(firstName, lastName, rollNo, "Mathematics", score, 10);
                break;
            case 4:
                printf("\n\033[0;32mYou Selected General Knowledge Test!\033[0m\n");
                score = conductQuiz("gk.txt", gkAnswers);
                totalMarks += 10;
                saveStudentRecord(firstName, lastName, rollNo, "General Knowledge", score, 10);
                break;
            case 5:
                printf("\033[0;32m\nThank you for using the program!\033[0m\n");
                return;
        }

        attempt[choice - 1] = 1;
        totalScore += score;

        if (score >= 6) {
            printf("\033[0;32m\nYou passed the quiz successfully with the score of %d/10.\033[0m\n", score);
        } else {
            printf("\033[0;31m\nYou did not pass the quiz. Your score is %d/10.\033[0m\n", score);
        }

        printf("\nDo you want to:\n");
        printf("\033[0;33m\n1. Return to the main menu\n2. Exit\033[0m\n\n");
        printf("Your choice (1 Or 2): ");
        retryChoice = getValidInput(1, 2);

        if (retryChoice == 2) {
            showCertificate(firstName, lastName, rollNo, totalScore, totalMarks);
            saveStudentRecord(firstName, lastName, rollNo, "Final Score", totalScore, totalMarks);  // Save final score
            printf("\033[0;32mStudents record saved successfully. Thank you for completing the quiz!\033[0m\n");
            return;
        }

    } while (1);
}

void facultyAccess() {
    char username[30] = "faculty@iobm.edu.pk";
    char password[30] = "facultyiobm098";
    char enteredUsername[20], enteredPassword[20];
    FILE *recordFile;

    while (1) {
        printf("\nEnter Faculty Username: ");
        scanf("%s", enteredUsername);
        printf("Enter Faculty Password: ");
        scanf("%s", enteredPassword);
        if (strcmp(enteredUsername, username) == 0 && strcmp(enteredPassword, password) == 0) {
            recordFile = fopen("quizData.txt", "r");
            printf("\033[0;32m\nAccess granted! Opening the student records...\n\033[0m\n");
            if (recordFile == NULL) {
                printf("\033[0;31mNo records found. No one has attempted the quiz yet.\033[0m\n");
            } else {
                char record[500];
                while (fgets(record, sizeof(record), recordFile) != NULL) {
                    printf("%s", record);
                }
                fclose(recordFile);
            }
            return;
        } else {
            printf("\033[0;31mIncorrect credentials! Please try again.\033[0m\n");
        }
    }
}


int main() {
    int choice;

    printf("                    \033[0;32m\"Welcome to the Dashborad!\"\033[0m                   ");
    printf("\n\n\n\033[0;33mPlease Select an Option: \033[0m");
    printf("\n\n\033[0;34m1. Faculty Access\n2. Quiz Portal\033[0m");
    printf("\n\n\033[0;33mYour Choice (1 or 2):\033[0m ");
    choice = getValidInput(1, 2);

    if (choice == 1) {
        facultyAccess();
    } else if (choice == 2) {
        menu();
    }

    return 0;
}
