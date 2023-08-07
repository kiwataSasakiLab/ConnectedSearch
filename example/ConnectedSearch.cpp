#include "ConnectedSearch.h"

ConnectedSearch::ConnectedSearch() {
    this->Narea = 0;
    this->ElementNumber  = 0;
    this->TargetMaterial = 0;

    this->ElementData = new int*[ElementNumber]();
    for(int i = 0; i < ElementNumber; i++) {
        this->ElementData[i] = new int[4]();
    }

    this->Eadj = new int*[ElementNumber]();
	for(int ele = 0; ele < ElementNumber; ele++) {
		this->Eadj[ele] = new int[3]();
	}
	this->EadjRow = new int[ElementNumber]();
}

ConnectedSearch::ConnectedSearch(int ElementNum, int** Element, int TargetMaterial) {
    this->Narea = 0;
    this->ElementNumber  = ElementNum;
    this->TargetMaterial = TargetMaterial;

    this->ElementData = new int*[ElementNumber]();
    for(int i = 0; i < ElementNumber; i++) {
        this->ElementData[i] = new int[4]();
    }

    for(int i = 0; i < ElementNumber; i++) {
        for(int j = 0; j < 4; j++) {
            this->ElementData[i][j] = Element[i][j];
        }
    }

    this->Eadj = new int*[ElementNumber]();
	for(int ele = 0; ele < ElementNumber; ele++) {
		this->Eadj[ele] = new int[3]();
	}
	this->EadjRow = new int[ElementNumber]();
}

ConnectedSearch::~ConnectedSearch() {
    for(int i = 0; i < ElementNumber; i++) {
        delete[] ElementData[i];
        delete[] Eadj[i];
    }
    delete[] ElementData;
    delete[] Eadj;
    delete[] EadjRow;
}

void ConnectedSearch::make_Eadj() {
	for(int nn = 0; nn < ElementNumber; nn++) {
        int num = 0;
        int ne1 = ElementData[nn][1];
        int ne2 = ElementData[nn][2];
        int ne3 = ElementData[nn][3];
        int ne[3] = {ne1, ne2, ne3};

        for(int ele = 0; ele < ElementNumber; ele++) {
            if(ele != nn) {
                int judge[3] = {0, 0, 0};
                int e1 = ElementData[ele][1];
                int e2 = ElementData[ele][2];
                int e3 = ElementData[ele][3];
                int e[3] = {e1, e2, e3};

                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        if(ne[i] == e[j]) {
                            judge[i] = 1;
                        }
                    }
                }
                
                if(judge[0] + judge[1] + judge[2] == 2) {
                    Eadj[nn][num] = ele;
                    EadjRow[nn]  += 1;
                    num += 1;
                }
                if(num > 3) {
                    cout << "error :: over 3 in Dadj[i][j]" << endl;
                    exit(EXIT_FAILURE);
				}
            }
        }
    }
}

bool ConnectedSearch::find(int a, vector<int>& vec) {
    bool find = false;
    for(int i = 0; i < vec.size(); i++) {
        if(vec[i] == a) {
            find = true;
            break;
        }
    }
    return find;
}

void ConnectedSearch::ElementSearch(int adjele, vector<int>& flag) { 
	bool FIND = find(adjele, flag);
    if(FIND == false) {
        flag.push_back(adjele);
        for(int j = 0; j < EadjRow[adjele]; j++) {
            int adj      = Eadj[adjele][j];
            int material = ElementData[adj][0];
            if(material == TargetMaterial) {
                ElementSearch(adj, flag);
            }
        }
    }
}

void ConnectedSearch::Search() {
    vector<int> flag;
	make_Eadj();
    for(int ele = 0; ele < ElementNumber; ele++) {
        int material = ElementData[ele][0];
        if(material == TargetMaterial) {
            bool FIND = find(ele, flag);
            if(FIND == false) {
                flag.push_back(ele);
                for(int i = 0; i < EadjRow[ele]; i++) {
                    int adjele   = Eadj[ele][i];
                    int Material = ElementData[adjele][0];
                    if(Material == TargetMaterial) {
                        ElementSearch(adjele, flag);
                    }
                }
                Narea += 1;
            }
        }
    }
}