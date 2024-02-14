//Baþak Su Gedik 21118080072



#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define CIRCULAR_QUEUE_SIZE 20
#define MAX_LINE_LENGTH 100

int circularQueue[CIRCULAR_QUEUE_SIZE];
int firstFrontIndex = 0;
int firstRearIndex = 0;
int firstQueueSize = 10;
int secondFrontIndex = 10;
int secondRearIndex = 10;
int secondQueueSize = 10;

void enqueueCommand(char *queueName, int queueInputValue);
void dequeueCommand(char *queueName);
void printCommand(char *queueName);

void enqueueFirst(int queueInputValue);
void enqueueSecond(int queueInputValue);

void resizeSecond(void);

void dequeueFirst(void);
void dequeueSecond(void);

void printFirst(void);
void printSecond(void);

bool isFirstFull(void);
bool isSecondFull(void);

bool isFirstEmpty(void);
bool isSecondEmpty(void);


int main(void) {
    FILE *inputFile;
    char line[MAX_LINE_LENGTH];
    char *token;
    char *queueName;
    int queueInputValue;
    memset(circularQueue, 0, CIRCULAR_QUEUE_SIZE);

    // Dosyayı aç
    inputFile = fopen("/Users/ugurcan/Desktop/Basak/Assignment2/Assignment2/input.txt", "r");
    if (inputFile == NULL) {
        printf("Dosya açma hatası");
        return 1;
    }

    // Dosyanın sonuna kadar satır satır oku
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        // Satırdaki '\n' karakterini kaldır
        line[strcspn(line, "\n")] = '\0';

        // Satırı tokenize et
        token = strtok(line, " ");
        // Komut tipine göre işlem yap
        if (strcmp(token, "ENQUEUE") == 0) {
            queueName = strtok(NULL, " ");
            token = strtok(NULL, " ");
            queueInputValue = atoi(token);
            enqueueCommand(queueName, queueInputValue);
        } else if (strcmp(token, "DEQUEUE") == 0) {
            queueName = strtok(NULL, " ");
            dequeueCommand(queueName);
        } else if (strcmp(token, "PRINT") == 0) {
            queueName = strtok(NULL, " ");
            printCommand(queueName);
        } else {
            printf("Hatalı komut: %s\n", token);
        }
    }
    fclose(inputFile);
    return 0;
}

void enqueueCommand(char *queueName, int queueInputValue) {
    if (strcmp(queueName, "FIRST") == 0) {
        if (isFirstFull() && isSecondEmpty()) {
            resizeSecond();
            enqueueFirst(queueInputValue);
        } else {
            enqueueFirst(queueInputValue);
        }
    } else if (strcmp(queueName, "SECOND") == 0) {
        enqueueSecond(queueInputValue);
    } else {
        printf("UNKNOWN ENQUEUE QUEUENAME\n");
    }
}

// DEQUEUE komutunu işleyen fonksiyon
void dequeueCommand(char *queueName) {
    if (strcmp(queueName, "FIRST") == 0) {
        dequeueFirst();
    } else if (strcmp(queueName, "SECOND") == 0) {
        dequeueSecond();
    } else {
        printf("UNKNOWN DEQUEUE QUEUENAME\n");
    }
}

// PRINT komutunu işleyen fonksiyon
void printCommand(char *queueName) {
    if (strcmp(queueName, "FIRST") == 0) {
        printFirst();
    } else if (strcmp(queueName, "SECOND") == 0) {
        printSecond();
    } else {
        printf("UNKNOWN PRINT QUEUENAME\n");
    }
}

void enqueueFirst(int queueInputValue) {
    if(isFirstFull()) {
        printf("Queue\tFIRST\tis full\n");
    } else {
        firstRearIndex = (firstRearIndex + 1) % firstQueueSize;
        circularQueue[firstRearIndex] = queueInputValue;
        printf("%d\tis inserted to queue\tFIRST\n",queueInputValue);
    }
}

void enqueueSecond(int queueInputValue) {
    if (isSecondFull()) {
        printf("Queue\tSECOND\tis full\n");
    } else {
        secondRearIndex = firstQueueSize + ((secondRearIndex + 1) % secondQueueSize);
        circularQueue[secondRearIndex] = queueInputValue;
        printf("%d\tis inserted to queue\tSECOND\n",queueInputValue);
    }
}

void dequeueFirst(void) {
    if (isFirstEmpty()) {
        printf("Queue\tFIRST\tis empty\n");
    } else {
        firstFrontIndex = (firstFrontIndex + 1) % firstQueueSize;
        if (firstFrontIndex == firstRearIndex) {
            firstFrontIndex = 0;
            firstRearIndex = 0;
        }
        int dequeueValue = circularQueue[firstFrontIndex];
        circularQueue[firstFrontIndex] = 0;
        printf("%d\tis deleted from queue\tFIRST\n",dequeueValue);
    }
}

void dequeueSecond(void) {
    if (isSecondEmpty()) {
        printf("Queue\tSECOND\tis empty\n");
    } else {
        secondFrontIndex = firstQueueSize + ((secondFrontIndex + 1) % secondQueueSize);
        if (secondFrontIndex == secondRearIndex) {
            secondFrontIndex = firstQueueSize + (secondFrontIndex % secondQueueSize);
            secondRearIndex = secondFrontIndex;
        } else {
            printf("asnfnkdflksdfnlkdafnkjldfnklds\n");
        }
        int dequeueValue = circularQueue[secondFrontIndex];
        circularQueue[secondFrontIndex] = 0;
        printf("%d\tis deleted from queue\tSECOND\n",dequeueValue);
    }
}

void resizeSecond(void) {
    if (firstQueueSize != secondFrontIndex)  {
        firstQueueSize ++;
        secondQueueSize --;
    }
}

bool isFirstFull(void) {
    if ((firstFrontIndex == (firstRearIndex + 1) % firstQueueSize) || (firstFrontIndex == 0 && firstRearIndex == firstQueueSize - 1)) {
        return true;
    } else {
        return false;
    }
}

bool isSecondFull(void) {
    if ((secondFrontIndex == firstQueueSize + ((secondRearIndex + 1) % secondQueueSize)) || (secondFrontIndex == firstQueueSize && secondRearIndex == CIRCULAR_QUEUE_SIZE - 1)) {
        return true;
    } else {
        return  false;
    }
}

bool isFirstEmpty(void) {
    if (firstFrontIndex == firstRearIndex) {
        return true;
    } else {
        return  false;
    }
}

bool isSecondEmpty(void) {
    if (secondFrontIndex == secondRearIndex) {
        return true;
    } else {
        return  false;
    }
}

void printFirst(void) {
    int size;
    if ((firstRearIndex-firstFrontIndex) < 0) {
        size = firstQueueSize + (firstRearIndex-firstFrontIndex);
    } else {
        size = firstRearIndex-firstFrontIndex;
    }
    printf("QUEUE:FIRST\tFRONT:%d\tREAR:%d\tSIZE:%d\n",firstFrontIndex,firstRearIndex,size);
    if (isFirstEmpty()) {
        printf("NO_CONTENT\n");
    } else {
        int i = firstFrontIndex;
        while (i < size) {
            i ++;
            if (i == size && firstFrontIndex > 0) {
                i = 0;
                printf("%d ",circularQueue[i]);
            } else {
                if (i == firstFrontIndex) {
                    printf("\n");
                    return;
                }
                printf("%d ",circularQueue[i]);
            }
        }
        printf("\n");
    }
}

void printSecond(void) {
    int size;
    if ((secondRearIndex-secondFrontIndex) < 0) {
        size = secondQueueSize + (secondRearIndex-secondFrontIndex);
    } else {
        size = secondRearIndex-secondFrontIndex;
    }
    printf("QUEUE:SECOND\tFRONT:%d\tREAR:%d\tSIZE:%d\n",secondFrontIndex,secondRearIndex,size);
    if (isSecondEmpty()) {
        printf("NO_CONTENT\n");
    } else {
        for (int i = secondFrontIndex + 1; i != secondRearIndex + 1; i++) {
            if (i < CIRCULAR_QUEUE_SIZE) {
                printf("%d ",circularQueue[i]);
            } else {
                i = secondQueueSize - 1;
            }
        }
        printf("\n");
    }
}

//Baþak Su Gedik 21118080072

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*// Separate numbers
void parseLine(char line[],int numbers[]){
    int count = 0;
    char *token = strtok(line, " ");
    while(token != NULL){
        int number = atoi(token);
        numbers[count] = number;
        token = strtok(NULL, " ");
        count++;

    }
}

//Reading the dimension from first line
int parseFirstLine(char line[]){
    int dimension = 0;
    char *token = strtok(line, " ");
    while (token != NULL){
        dimension = atoi(token);
        token = strtok(NULL, " ");
    }
    return dimension;
}

//Calculating the amount of numbers in an upper triangular matrix excluding zeros
int calculateRequiredAmountOfNumbers(int matrixDimension){
    return(matrixDimension * (matrixDimension + 1)) / 2;
}

int main()
{
    FILE*file;
    char line[1024];
    char firstLine[1024];
    char secondLine[1024];
    char thirdLine[1024];
    int lineCount= 0;
    int matrixDimension = 0;
    int requiredAmountOfNumbers = 0;

    //Reading numbers from input.txt
    file=fopen("input.txt", "r");
    if(file==NULL){
        printf("File can't be found.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL){
        if(lineCount == 0){
            strncpy(firstLine, line, 1024);
            //printf("First line is %s",firstLine);
        }
        if(lineCount == 1){
            strncpy(secondLine, line, 1024);
            //printf("Second line is %s",secondLine);
        }
        if(lineCount == 2){
            strncpy(thirdLine, line, 1024);
            //printf("Third line is %s",thirdLine);
        }
        lineCount++;
    }

    printf("\n");
    fclose(file);

    matrixDimension = parseFirstLine(firstLine);
    requiredAmountOfNumbers = calculateRequiredAmountOfNumbers(matrixDimension);
    int matrixANumbers[requiredAmountOfNumbers];
    int matrixBNumbers[requiredAmountOfNumbers];
    int matrixCNumbers[requiredAmountOfNumbers];
    parseLine(secondLine,matrixANumbers);
    parseLine(thirdLine,matrixBNumbers);

    //Filling arrays with the numbers that is given in the text
    printf("Matrix A Numbers : ");
    for(int i=0; i<requiredAmountOfNumbers;++i){
        printf("%d ",matrixANumbers[i]);
    }
    printf("\n");
    printf("Matrix B Numbers : ");
    for(int j=0; j<requiredAmountOfNumbers;++j){
        printf("%d ",matrixBNumbers[j]);
    }

    //Multiplying two matrices
    int resultIndex = 0;
    int matrixEqualityIndex = 0;
    int indexIncreaseAmount = matrixDimension;

    for(int i = 0; i < matrixDimension; i++){
        for(int j = 0; j < matrixDimension; j++){
            if(j >= i){
                if(j == i){
                    matrixEqualityIndex = resultIndex;
                }
                matrixCNumbers[resultIndex] = 0;
                if(resultIndex == matrixEqualityIndex){//Diagonal calculation (c4 = a4 * b4)
                    matrixCNumbers[resultIndex] = matrixANumbers[matrixEqualityIndex] * matrixBNumbers[matrixEqualityIndex];
                    indexIncreaseAmount --;
                } else {
                    int matrixBIndexValue = resultIndex;
                    for (int k = 0; k <= resultIndex - matrixEqualityIndex; k++){//Calculating how many summation will be needed
                        if(k == 0){//First calculation (c1 += a0*b1 or c2 += a0 * b2)
                            matrixCNumbers[resultIndex] += matrixANumbers[matrixEqualityIndex] * matrixBNumbers[matrixBIndexValue];
                        } else {// Other calculations (c1 += a1 * b4 or c2 += a1 * b5 + a2 * b7)
                            matrixBIndexValue += ((indexIncreaseAmount + 1) - k);
                            matrixCNumbers[resultIndex] += matrixANumbers[matrixEqualityIndex + k] * matrixBNumbers[matrixBIndexValue];
                        }
                    }
                }
                    resultIndex ++;
            }
        }
    }

    //Print Matrix C As a 1d Array
    printf("\n");
    printf("Matrix C Numbers : ");
    for(int a = 0; a < requiredAmountOfNumbers; ++a){
        printf("%d ",matrixCNumbers[a]);
    }
    printf("\n");

    //Print Matrix C as an an upper triangular matrix
    printf("Matrix C in an upper triangular matrix form : \n");
    int printIndex = 0;
    for(int b = 0;b < matrixDimension ; b++){
        for (int c = 0;c < matrixDimension; c++){
            if(c >= b){
                printf("%d\t", matrixCNumbers[printIndex]);
                printIndex ++;
            } else {
                printf("0\t");
            }
        }
        printf("\n");
    }

    return 0;
}
*/
#define SIZE 20

int items[SIZE];
int front = -1;
int rear = -1;

int isFull(){
    if((front == rear + 1) || (front == 0 && rear == SIZE - 1)) return 1;
    return 0;
}

int isEmpty(){
    if(front == -1){
        return 1;
    }
    return 0;
}

void enqueue(int element) {
    if (isFull())
        printf("\n queue is full \n");
    else{
        if(front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        items[rear] = element;
        printf("\n inserted %d", element);
    }
}

int dequeue(){
    int element;
    if(isEmpty()) {
        printf("\n queue is empty");
        return (-1);
    }
    else {
        element = items[front];
        if(front == rear){
            front = -1;
            rear = -1;
        }
        else{
            front = (front + 1) % SIZE;
        }
        printf("\n deleted element %d", element);
        return (element);
    }
}

void display(){
    int i;
    if(isEmpty()) {
        printf("\n queue is empty");
    }
    else {
        printf("\n front %d", front);
        printf("\n items ");
        for(i = front; i!= rear; i = (i+1) % SIZE){
            printf("%d ",items[i]);
        }
        printf("%d", items[i]);
        printf("\n rear %d", rear);
    }
}
int main(){
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    enqueue(5);

    enqueue(1);
    display();
    dequeue();
    display();
    return 0;
}

