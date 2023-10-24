#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;


void bubbleSort(vector < int16_t > & a) {
    int16_t i, j, k, swap, flag;
    int16_t len = a.size();

    for (int16_t i = len; i > 0; i--) {
        flag = 0;

        for (j = 0, k = 1; k < i; j++, k++) {
            if (a[j] > a[k]) {
                swap = a[j];
                a[j] = a[k];
                a[k] = swap;
                flag = 1;
            }

        }
    }

}

void mergeSortedIntervals(vector<int16_t>& v, int s, int m, int e) {
    vector<int16_t> temp;

    int16_t i, j;
    i = s;
    j = m + 1;

    while (i <= m && j <= e) {

        if (v[i] <= v[j]) {
            temp.push_back(v[i]);
            ++i;
        }
        else {
            temp.push_back(v[j]);
            ++j;
        }

    }

    while (i <= m) {
        temp.push_back(v[i]);
        ++i;
    }

    while (j <= e) {
        temp.push_back(v[j]);
        ++j;
    }

    for (int i = s; i <= e; ++i)
        v[i] = temp[i - s];

}

void mergeSort(vector<int16_t>& v, int16_t s, int16_t e) {
    if (s < e) {
        int16_t m = (s + e) / 2;
        mergeSort(v, s, m);
        mergeSort(v, m + 1, e);
        mergeSortedIntervals(v, s, m, e);
    }
}


int16_t calc(const vector<vector<int16_t>> &mat, int p1, int p2, int prag,string & type){
    int pos1_i,pos1_j,pos2_i,pos2_j;
    pos1_i=p1-prag;
    pos1_j=p2-prag;
    pos2_i=p1+prag;
    pos2_j=p2+prag;
    vector<int16_t> border;
    for(int i = pos1_i ; i<=pos2_i;i++) {

        for (int j = pos1_j; j <= pos2_j; j++) {
            //--------------------------------------- //colt stanga sus
            if (i < 0 && j < 0) {
                border.push_back(mat[0][0]);
                continue;
            }
            if (i < 0 && j >= 0 && (j < mat[0].size())) {
                border.push_back(mat[0][j]);
                continue;
            }
            if (i >= 0 && j < 0 && i < mat.size()) {
                border.push_back(mat[i][0]);
                continue;
            }
            //--------------------------------------- colt dreapta sus
            if (i < 0 && j >= mat[0].size()) {
                border.push_back(mat[0][mat[0].size() - 1]);
                continue;
            }
            if (i < 0 && j < mat[0].size()) {
                border.push_back(mat[0][j]);
                continue;
            }
            if (i >= 0 && j >= mat[0].size() && i < mat.size()) {
                border.push_back(mat[i][mat[0].size() - 1]);
                continue;
            }
            //--------------------------------------- colt stanga jos
            if (i < mat.size() && j < 0 && i >= 0) {
                border.push_back(mat[i][0]);
                continue;
            }
            if (i >= mat.size() && j < 0) {
                border.push_back(mat[mat.size() - 1][0]);
                continue;
            }
            if (i >= mat.size() && j >= 0 && j < mat[0].size()) {
                border.push_back(mat[mat.size() - 1][j]);
                continue;
            }
//--------------------------------------- colt dreapta jos
            if (i < mat.size() && j >= mat[0].size()) {
                border.push_back(mat[i][mat[0].size() - 1]);
                continue;
            }
            if (i >= mat.size() && j >= mat[0].size()) {
                border.push_back(mat[mat.size() - 1][mat[0].size() - 1]);
                continue;
            }
            if (i >= mat.size() && j >= 0 && j < mat[0].size()) {
                border.push_back(mat[mat.size() - 1][j]);
                continue;
            }
//-------------------------------
            if (i >= 0 && i < mat.size() && j >= 0 && j < mat[0].size()) {
                // cout<<i<<" "<<j<<" "<<mat[i][j]<<endl;
                border.push_back(mat[i][j]);
            }
        }
    }

    if(type == "test") sort(border.begin(),border.end());
    if(type == "bubble") bubbleSort(border);
    if(type == "merge") mergeSort(border,0,border.size()-1);
    //for(int i = 0 ;i<border.size();i++) cout<<border[i]<<" ";
    //cout<<endl;
    return border[border.size()/2];
}
int main() {
    ifstream f;
    string s;
    vector<vector<int16_t>> mat;
    string sort,input_file,output_file,type;
    int dim;
    cin>>sort>>dim>>input_file>>output_file;
    f.open(input_file);
    f>>type;
    int n,m,gray_max;
    f>>m>>n;
    f>>gray_max;
    for(int i = 0 ;i<n;i++) {
        vector<int16_t> linie;
        for (int j = 0; j < m; j++) {
            int16_t x;
            f >> x;
            linie.push_back(x);
        }
        mat.push_back(linie);
    }
    int pas = dim/2;
    vector<vector<int16_t>> mat1=mat;
    for(int i = 0 ;i<n;i++){
        for(int j=0;j<m;j++){
    
            mat1[i][j]=calc(mat,i,j,pas,sort);
        }


    }
    ofstream outfile;
    outfile.open(output_file);
    outfile<<"P2"<<endl;
    outfile<<m<<" "<<n<<endl;
    outfile<<255<<endl;
    for(int i= 0; i <n; i++)
    {
        for (int j = 0;j<m;j++)
        {

            outfile << mat1[i][j]<<" ";
        }
    }


    outfile.close();
    f.close();
}
