#include <iostream>
#include <string>
#include <climits>
using namespace std;

int main(){
    int nTest, nLiczb, obecnaLiczba=0, obecnyTest=0;
    string ciag, tempLiczba="";
    
    cin>>nTest;
    int suma[nTest];
    if(0<nTest<100){
        for(int i=0; i<nTest; i++){
            cin.ignore();
            cin>>nLiczb;
            int liczby[nLiczb];
            cout<<"Ilosc liczb: "<<nLiczb<<endl;

            ciag="";
            cin.ignore();
            getline(cin,ciag);

            tempLiczba="";
            for(int j=0; j<ciag.length(); j++){
                if(ciag[j]!=' '){
                    tempLiczba+=ciag[j];
                }else{
                    liczby[obecnaLiczba]=stoi(tempLiczba);
                    obecnaLiczba+=1;
                    tempLiczba="";
                };
            };
            liczby[obecnaLiczba]=stoi(tempLiczba);
            obecnaLiczba+=1;

            for(int j=0; j<nLiczb; j++){
                cout<<"Cala Liczba: "<<liczby[j]<<endl;
            };
            /*suma[obecnyTest]=0;
            for(int j=0; j<nLiczb; j++){
                suma[obecnyTest]+=liczby[j];
            };*/

            obecnyTest++;
        };
        /*for(int i=0; i<nTest; i++){
            cout<<suma[nTest];
        };*/
    };
    cin.ignore();
    cin.get();
    return 0;
};