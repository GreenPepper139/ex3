/******************
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};


void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}

//returns whether the asignment was succesful or not
int asignToBrand(int brandIndex, int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    if((brandIndex < 0) || (brandIndex >= NUM_OF_BRANDS)){
        return 0;
    } 
    // creating an array to manage the sales input easier
    int salesSums[NUM_OF_TYPES] = {0};
    scanf("%d %d %d %d", &salesSums[0], &salesSums[1], &salesSums[2], &salesSums[3]);
    for(int i = 0; i < NUM_OF_TYPES; i++) {
        cube[day][brandIndex][i] = salesSums[i];
    }
    return 1;
}

//returns the index of the max value in an array
int maxInArray(int A[], int length) {
    int max = 0;
    for(int i = 1; i < length; i++) {
        if(A[i] > A[max])
            max = i;
    }
    return max;
}

int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    for(int i = 0; i < DAYS_IN_YEAR; i++) {
        for(int j = 0; j < NUM_OF_BRANDS; j++) {
            for(int k = 0; k < NUM_OF_TYPES; k++)
            {
                cube[i][j][k] = -1;
            }
        }
    }
    int day = 0;
    int choice;
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice){
            case addOne:{
                int brandIndex, isValid = 0;
                scanf("%d", &brandIndex);
                isValid = asignToBrand(brandIndex, day, cube);
                if(!isValid)
                    printf("This brand is not valid\n");
                break;
            }
            case addAll: {
                // creating an array whether the sales for that brand is already known
                int isKnown[NUM_OF_BRANDS] = {0};
                // i tells the amount of brands with known sales numbers
                int i = 0;
                while(i < NUM_OF_BRANDS){
                    printf("No data for brands");
                    for(int j = 0; j < NUM_OF_BRANDS; j++) {
                        if(!isKnown[j])
                            printf(" %s", brands[j]);
                    }
                    printf("\nPlease complete the data\n");
                    int brandIndex, isValid = 0;
                    scanf("%d", &brandIndex);
                    if(!isKnown[brandIndex])
                        isValid = asignToBrand(brandIndex, day, cube);
                    if(!isValid) {
                        printf("This brand is not valid\n");
                        continue;
                    }
                    isKnown[brandIndex] = 1;
                    i++;
                }
                day++;
                break;
            }
            case stats: {
                // initialized bestSoldBrand and bestSoldType to 0 and later i will compare them with the rest
                int dayScaned, isValid = 0;
                while(!isValid) {
                    printf("What day would you like to analyze?\n");
                    scanf("%d", &dayScaned);
                    //user POV is 1-365 while ours is 0-364 so we need to decrease by 1
                    dayScaned--;
                    isValid = dayScaned >= 0 && dayScaned < day;
                    if(!isValid)
                        printf("Please enter a valid day.\n");
                }
                int salesSum = 0, salesPerBrand[NUM_OF_BRANDS] = {0}, salesPerType[NUM_OF_TYPES] = {0};
                for(int i = 0; i < NUM_OF_BRANDS; i++) {
                    for(int j = 0; j < NUM_OF_TYPES; j++) {
                        int sold = cube[dayScaned][i][j];
                        salesSum += sold;
                        salesPerBrand[i] += sold;
                        salesPerType[j] += sold;
                    }
                }
                int bestBrand = maxInArray(salesPerBrand, NUM_OF_BRANDS);
                int bestType = maxInArray(salesPerType, NUM_OF_TYPES);
                printf("In day number %d:\n", dayScaned + 1);
                printf("The sales total was %d\n", salesSum);
                printf("The best sold brand with %d sales was %s\n", salesPerBrand[bestBrand], brands[bestBrand]);
                printf("The best sold type with %d sales was %s\n", salesPerType[bestType], types[bestType]);
                break;
            }
            case print: {
                printf("*****************************************\n\n");
                for(int i = 0; i < NUM_OF_BRANDS; i++) {
                    printf("Sales for %s:\n", brands[i]);
                    //whether the brand made any sales
                    int madeSales = 0;
                    for(int j = 0; (j < day) && !madeSales; j++) {
                        for(int k = 0; k < NUM_OF_TYPES; k++) {
                            if(cube[j][i][k] > 0) {
                                madeSales = 1;
                                break;
                            }
                        }
                    }
                    if(!madeSales)
                        continue;
                    for(int j = 0; j < day; j++) {
                        //user POV is 1-365 while ours is 0-364 so we need to increase by 1
                        printf("Day %d-", j + 1);
                        for(int k = 0; k < NUM_OF_TYPES; k++) {
                            printf(" %s: %d", types[k], cube[j][i][k]);
                        }
                        printf("\n");
                    }
                }
                printf("\n\n*****************************************\n");
                break;
            }
            case insights: {
                int salesPerBrand[NUM_OF_BRANDS] = {0}, salesPerType[NUM_OF_TYPES] = {0};
                int salesPerDay[DAYS_IN_YEAR] = {0};
                for(int i = 0; i < day; i++) {
                    for(int j = 0; j < NUM_OF_BRANDS; j++) {
                        for(int k = 0; k < NUM_OF_TYPES; k++) {
                            int sales = cube[i][j][k];
                            salesPerDay[i] += sales;
                            salesPerBrand[j] += sales;
                            salesPerType[k] += sales;
                        }
                    }
                }
                int mostSalesDay = maxInArray(salesPerDay, DAYS_IN_YEAR);
                int bestBrand = maxInArray(salesPerBrand, NUM_OF_BRANDS);
                int bestType = maxInArray(salesPerType, NUM_OF_TYPES);
                printf("The best-selling brand overall is %s: %d$\n", brands[bestBrand], salesPerBrand[bestBrand]);
                printf("The best-selling type of car is %s: %d$\n", types[bestType], salesPerType[bestType]);
                // user POV is 1-365 while ours is 0-364 so we need to increase by 1
                printf("The most profitable day was day number %d: %d$\n", mostSalesDay + 1, salesPerDay[mostSalesDay]);
                break;
            }
            case deltas: {
                for(int i = 0; i < NUM_OF_BRANDS; i++) {
                    int salesFirst = 0, salesLast = 0;
                    for(int j = 0; j < NUM_OF_TYPES; j++){
                        salesFirst += cube[0][i][j];
                    }
                    for(int j = 0; j < NUM_OF_TYPES; j++){
                        salesLast += cube[day - 1][i][j];
                    }
                    // sum of deltas has to be the delta between the last and first day
                    double avgDelta = (double)(salesLast - salesFirst) / (day - 1);
                    printf("Brand: %s, Average Delta: %lf\n", brands[i], avgDelta);
                }
                break;
            }
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}


