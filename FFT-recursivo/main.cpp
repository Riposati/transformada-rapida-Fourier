#include <bits/stdc++.h>

// to compile in terminal with g++ -> g++ main.cpp -o main

using namespace std;

typedef complex<double> cd;
const double PI = acos(-1); 

vector<cd> fft(vector<cd> a){
    int n = a.size();
    if(n == 1)
        return a;
    vector<cd> a0(n/2);
    vector<cd> a1(n/2);
    for(int i=0; i<n/2; i++){
        a0[i] = a[2*i];
        a1[i] = a[2*i + 1];
    }
    a0 = fft(a0); 
    a1 = fft(a1);
    cd w(1);
    cd wn(cos((2*PI)/n), sin((2*PI)/n));
    for(int i=0; i<n; i++){
        a[i] = a0[i%(n/2)] + w*a1[i%(n/2)];
        w = w*wn;
    }
    return a;
}

vector<cd> inv_fft(vector<cd> a){
    int n = a.size();
    if(n == 1)
        return a;
    vector<cd> a0(n/2);
    vector<cd> a1(n/2);
    for(int i=0; i<n/2; i++){
        a0[i] = a[2*i];
        a1[i] = a[2*i + 1];
    }
    a0 = inv_fft(a0); 
    a1 = inv_fft(a1);
    cd w(1);
    cd wn(cos((-2*PI)/n), sin((-2*PI)/n));
    for(int i=0; i<n; i++){
        a[i] = a0[i%(n/2)] + w*a1[i%(n/2)];
        a[i] /= 2;
        w = w*wn;
    }
    return a;
}

//C(x) = A(x)*B(x)
// multiplica dois polinomios
vector<long long> multiply(vector<int> a, vector<int> b){
    int n=1;
    while(n < a.size() + b.size())
        n *= 2;
    vector<cd> va(a.begin(), a.end());
    vector<cd> vb(b.begin(), b.end());
    va.resize(n);
    vb.resize(n);
    va = fft(va);
    vb = fft(vb);
    vector<cd> vc(n);
    for(int i=0; i<n; i++)
        vc[i] = va[i]*vb[i];
    vc = inv_fft(vc);
    vector<long long> c(n);
    for(int i=0; i<n; i++)
        c[i] = roundl(vc[i].real());
    return c;
}

int main(){
    vector<int>a =  {1,-2,3};
    vector<int>b = {1,0,1};
    vector <long long> c = multiply(a,b);

    int aux = c.size()-1;

    while(c[aux--] == 0){
        c.pop_back();
    }

    for(auto i: c){
        printf("%lld ",i);
    }
    printf("\n");
    return 0;
}