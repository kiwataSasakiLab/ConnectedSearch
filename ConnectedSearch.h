#include "magic.h"

class ConnectedSearch {
private:
    int ElementNumber;
    int** ElementData;

    int TargetMaterial;
    int Narea;

    int** Eadj;
    int* EadjRow;

public:
    ConnectedSearch();
    ConnectedSearch(int ElementNum, int** Element, int TargetMaterial);
    ~ConnectedSearch();

	void make_Eadj();
    bool find(int a, vector<int>& vec);
	void ElementSearch(int adjele, vector<int>& flag);
	
    void Search();
    int  get_Narea() const{return Narea;};
};