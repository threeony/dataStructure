#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STUDNUM 20000

typedef struct {
    int stdnum;
    char name[11];
    unsigned int phone;
}STUDENT;

STUDENT info[STUDNUM];
STUDENT selection[STUDNUM];
STUDENT quick[STUDNUM];
STUDENT heap[STUDNUM + 1];

void grantStud(void) {
    int i = 0, r, pr;
    int onenine = 0, twozero = 0, twoone = 0, twotwo = 0;

    srand((unsigned int)time(NULL));

    for (i = 0; i < STUDNUM; i++) {
        int j = 0;
        int num = 19000000;
        unsigned int phnum = 1000000000;
        char stdname[11];
        r = rand() % 200;
        for (int a = 0; a < r; a++) {
            int randnum = 0;
            randnum = rand();
            if (num + randnum < 23000000)
                num += randnum;
        }
        pr = rand() % 5000;
        for (int a = 0; a < pr; a++) {
            int randnum;
            randnum = rand();
            if (phnum + randnum < 1100000000)
                phnum += randnum;
        }
        for (int m = 0; m < 10; m++) {
            stdname[m] = rand() % 26 + 'a';
        }
        stdname[10] = '\0';

        for (j = 0; j < i; j++) {            //중복체크
            if (info[j].stdnum == num) {
                break;
            }
        }
        if (j != i) {
            i--;                        //중복 발생 시 재실행
        }
        else {                           //저장
            if (num < 20000000) {
                if (onenine < STUDNUM / 4) {
                    info[i].stdnum = num;
                    strcpy(info[i].name, stdname);
                    info[i].phone = phnum;
                    onenine++;
                }
                else {
                    i--;
                }
            }
            else if (num < 21000000) {
                if (twozero < STUDNUM / 4) {
                    info[i].stdnum = num;
                    strcpy(info[i].name, stdname);
                    info[i].phone = phnum;
                    twozero++;
                }
                else {
                    i--;
                }
            }
            else if (num < 22000000) {
                if (twoone < STUDNUM / 4) {
                    info[i].stdnum = num;
                    strcpy(info[i].name, stdname);
                    info[i].phone = phnum;
                    twoone++;
                }
                else {
                    i--;
                }
            }
            else {
                if (twotwo < STUDNUM / 4) {
                    info[i].stdnum = num;
                    strcpy(info[i].name, stdname);
                    info[i].phone = phnum;
                    twotwo++;
                }
                else {
                    i--;
                }
            }
        }
        selection[i] = info[i];
        quick[i] = info[i];
        heap[i + 1] = info[i];
    }
    printf("19: %d  20: %d  21: %d  22: %d\n", onenine, twozero, twoone, twotwo);
}


void SWAP(STUDENT list[], int a, int b) {
    STUDENT temp;

    temp = list[a];
    list[a] = list[b];
    list[b] = temp;
}

void selection_stdnum(void) {
    int i, j, least;

    for (i = 0; i < STUDNUM - 1; i++) {
        least = i;
        for (j = i + 1; j < STUDNUM; j++) {
            if (selection[j].stdnum < selection[least].stdnum) least = j;
        }
        SWAP(selection, i, least);
    }
    return;
}
void selection_name(void) {
    int i, j, least;

    for (i = 0; i < STUDNUM - 1; i++) {
        least = i;
        for (j = i + 1; j < STUDNUM; j++) {
            if (strcmp(selection[j].name, selection[least].name) < 0) least = j;
        }
        SWAP(selection, i, least);
    }
    return;
}


void quick_stdnum(int left, int right) {
    if (left < right) {
        int pivot;
        int low, high, q;

        low = left;
        high = right + 1;
        pivot = quick[left].stdnum;

        do {
            do {
                low++;
            } while (low <= right && quick[low].stdnum < pivot);
            do {
                high--;
            } while (high >= left && quick[high].stdnum > pivot);
            if (low < high)
                SWAP(quick, low, high);
        } while (low < high);

        SWAP(quick, left, high);

        q = high;

        quick_stdnum(left, q - 1);
        quick_stdnum(q + 1, right);
    }
}
void quick_name(int left, int right) {
    if (left < right) {
        int pivot;
        int low, high, q;

        low = left;
        high = right + 1;
        pivot = left;

        do {
            do {
                low++;
            } while (low <= right && strcmp(quick[low].name, quick[pivot].name) < 0);
            do {
                high--;
            } while (high >= left && strcmp(quick[high].name, quick[pivot].name) > 0);
            if (low < high)
                SWAP(quick, low, high);
        } while (low < high);

        SWAP(quick, left, high);
        q = high;

        quick_name(left, q - 1);
        quick_name(q + 1, right);
    }
}



void adjust_stdnum(int root, int n) {
    int child, rootkey;
    STUDENT temp;
    temp = heap[root];
    rootkey = heap[root].stdnum;
    child = root * 2;
    while (child <= n) {
        if ((child < n) && heap[child].stdnum < heap[child + 1].stdnum)
            child++;
        if (rootkey > heap[child].stdnum)
            break;
        else {
            heap[child / 2] = heap[child];
            child *= 2;
        }
    }
    heap[child / 2] = temp;
}
void adjust_name(int root, int n) {
    int child;
    char rootkey[11];
    STUDENT temp;
    temp = heap[root];
    strcpy(rootkey, heap[root].name);
    child = root * 2;
    while (child <= n) {
        if ((child < n) && strcmp(heap[child].name, heap[child + 1].name) < 0)
            child++;
        if (strcmp(rootkey, heap[child].name) > 0)
            break;
        else {
            heap[child / 2] = heap[child];
            child *= 2;
        }
    }
    heap[child / 2] = temp;
}
void heapsort(void (*fp)(int, int), int n) {
    int i;

    for (i = n / 2; i > 0; i--) {
        fp(i, n);
    }
    for (i = n - 1; i > 0; i--) {
        SWAP(heap, 1, i + 1);
        fp(1, i);
    }
}


int check_stdnum(STUDENT list[], int root, int n) {
    int temp;
    temp = list[root].stdnum;
    for (int i = root + 1; i < n; i++) {
        if (list[i].stdnum < temp)
            return 0;
        temp = list[i].stdnum;
    }
    return 1;
}
int check_name(STUDENT list[], int root, int n) {
    char temp[11];
    strcpy(temp, list[root].name);
    for (int i = root + 1; i < n; i++) {
        if (strcmp(list[i].name, temp) < 0)
            return 0;
        strcpy(temp, list[i].name);
    }
    return 1;
}


void compareStudnum(const void* m, const void* n) {
    return (((STUDENT*)m)->stdnum - ((STUDENT*)n)->stdnum);
}
void compareName(const void* m, const void* n) {
    return (strcmp(((STUDENT*)m)->name, ((STUDENT*)n)->name));
}


int main(void) {
    clock_t qstart, qfin;
    clock_t sstart, sfin;
    clock_t qustart, qufin;
    clock_t hstart, hfin;
    float qtime1, qtime2, stime1, stime2, qutime1, qutime2, htime1, htime2;
    int qcheck1, qcheck2, scheck1, scheck2, qucheck1, qucheck2, hcheck1, hcheck2;

    grantStud();

    qstart = clock();
    qsort(info, STUDNUM, sizeof(info[0]), compareStudnum);
    qfin = clock();
    qtime1 = (float)(qfin - qstart) / CLOCKS_PER_SEC;
    qcheck1 = check_stdnum(info, 0, STUDNUM);
    /*for (int i = 0; i < STUDNUM; i++) {
        printf("%d %s %011d\n", info[i].stdnum, info[i].name, info[i].phone);
    }*/
    printf("QCHECK:  %d  QSTART:  %d  QFIN:  %d   %.3f\n", qcheck1, qstart, qfin, qtime1);
    qstart = clock();
    qsort(info, STUDNUM, sizeof(info[0]), compareName);
    qfin = clock();
    qtime2 = (float)(qfin - qstart) / CLOCKS_PER_SEC;
    qcheck2 = check_name(info, 0, STUDNUM);
    /*for (int i = 0; i < STUDNUM; i++) {
        printf("%d %s %011d\n", info[i].stdnum, info[i].name, info[i].phone);
    }*/
    printf("QCHECK:  %d  QSTART:  %d  QFIN:  %d   %.3f\n", qcheck2, qstart, qfin, qtime2);

    sstart = clock();
    selection_stdnum();
    sfin = clock();
    stime1 = (float)(sfin - sstart) / CLOCKS_PER_SEC;
    scheck1 = check_stdnum(selection, 0, STUDNUM);
    /*for (int i = 0; i < STUDNUM; i++) {
        printf("%d %s %011d\n", selection[i].stdnum, selection[i].name, selection[i].phone);
    }*/
    printf("SCHECK:  %d  SSTART:  %d  SFIN:  %d   %.3f\n", scheck1, sstart, sfin, stime1);
    sstart = clock();
    selection_name();
    sfin = clock();
    stime2 = (float)(sfin - sstart) / CLOCKS_PER_SEC;
    scheck2 = check_name(selection, 0, STUDNUM);
    /*for (int i = 0; i < STUDNUM; i++) {
        printf("%d %s %011d\n", selection[i].stdnum, selection[i].name, selection[i].phone);
    }*/
    printf("SCHECK:  %d  SSTART:  %d  SFIN:  %d   %.3f\n", scheck2, sstart, sfin, stime2);

    qustart = clock();
    quick_stdnum(0, STUDNUM - 1);
    qufin = clock();
    qutime1 = (float)(qufin - qustart) / CLOCKS_PER_SEC;
    qucheck1 = check_stdnum(quick, 0, STUDNUM);
    /*for (int i = 0; i < STUDNUM; i++) {
        printf("%d %s %011d\n", quick[i].stdnum, quick[i].name, quick[i].phone);
    }*/
    printf("QUCHECK: %d  QUSTART: %d  QUFIN: %d   %.3f\n", qucheck1, qustart, qufin, qutime1);
    qustart = clock();
    quick_name(0, STUDNUM - 1);
    qufin = clock();
    qutime2 = (float)(qufin - qustart) / CLOCKS_PER_SEC;
    qucheck2 = check_name(quick, 0, STUDNUM);
    /*for (int i = 0; i < STUDNUM; i++) {
        printf("%d %s %011d\n", quick[i].stdnum, quick[i].name, quick[i].phone);
    }*/
    printf("QUCHECK: %d  QUSTART: %d  QUFIN: %d   %.3f\n", qucheck2, qustart, qufin, qutime2);

    hstart = clock();
    heapsort(adjust_stdnum, STUDNUM);
    hfin = clock();
    htime1 = (float)(hfin - hstart) / CLOCKS_PER_SEC;
    hcheck1 = check_stdnum(heap, 1, STUDNUM + 1);
    /*for (int i = 1; i < STUDNUM + 1; i++) {
        printf("%d %s %011d\n", heap[i].stdnum, heap[i].name, heap[i].phone);
    }*/
    printf("HCHECK:  %d  HSTART:  %d  HFIN:  %d   %.3f\n", hcheck1, hstart, hfin, htime1);
    hstart = clock();
    heapsort(adjust_name, STUDNUM);
    hfin = clock();
    htime2 = (float)(hfin - hstart) / CLOCKS_PER_SEC;
    hcheck2 = check_name(heap, 1, STUDNUM + 1);
    /*for (int i = 1; i < STUDNUM + 1; i++) {
        printf("%d %s %011d\n", heap[i].stdnum, heap[i].name, heap[i].phone);
    }*/
    printf("HCHECK:  %d  HSTART:  %d  HFIN:  %d   %.3f\n", hcheck2, hstart, hfin, htime2);
}