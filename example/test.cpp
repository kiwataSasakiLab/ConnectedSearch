#include "ConnectedSearch.h"
#include "const.h"

void read_csv(const char* fn, int NumRow, int NumCol, int** Data) {
    FILE* fp = fopen(fn, "r");
    if(fp == NULL) {
        cout << "error at read_csv: " << fn << "might be wrong" << endl;
    }
    else {
        for(int i = 0; i < NumRow; i++) {
            for(int j = 0; j < NumCol; j++) {
                if(j == NumCol-1) {
                    fscanf(fp, "%d", &Data[i][j]);
                }
                else {
                    fscanf(fp, "%d,", &Data[i][j]);
                }
            }
        }
    }
    fclose(fp);
}

void test(int case_num) {
    //  element data path
    string fn_ele = "./test_data/element"+to_string(case_num)+".csv";
    
    //  load element data
    int** ElementData = new int*[TotalElementNumber]();
    for(int i = 0; i < TotalElementNumber; i++) {
        ElementData[i] = new int[4]();
    }
    read_csv(fn_ele.c_str(), TotalElementNumber, 4, ElementData);

    //  Connected Search class
    ConnectedSearch ConnectedSearch(TotalElementNumber, ElementData, IronNumber);
    ConnectedSearch.Search();
    cout << "Narea is " << ConnectedSearch.get_Narea() << endl;
    
    for(int i = 0; i < TotalElementNumber; i++) {
        delete[] ElementData[i];
    }
    delete[] ElementData;
}