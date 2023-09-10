#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <chrono>

using namespace std;

//Problem 2
 double exact(double x){// we define out exact solution as a function of a double x
     return (1-(1-exp(-10))*x-exp(-10*x));
 }

void maketxt(int n, string filename){
    vector<double> x_values(n);
    double step = 1.0 / static_cast<double>(n - 1); // calculating step size
    for (int i = 0; i < n; ++i) {
        x_values[i] = i * step; // we create an array of x values from 0 to 1 with step size step
    }
    ofstream ofile;
    // this line of code opens the file so that we can write information into it
    ofile.open(filename);
    // we define the width we wish to apply to our file format
    int width=12;
    for (int i=0; i<n;i++){
            // The 'ofile' command writes the information to our file, with formats defined by setw(), setprecision() and scientific
            ofile << scientific << x_values[i] << setw(width) <<  setprecision(3) << scientific << exact(x_values[i]) << endl;
    }
    ofile.close();  // after writing all our information into the text file, we close the file
}


//Problem 6
double gurl(double x, double step){
    return 100*exp(-10*x)*pow(step,2);
}
pair<vector<double>, vector<double>> solveTriGen(int n, vector<double> a , vector<double> b,  vector<double> c) {
    int j=a.size();
    vector<double> x(n); //an empty vector for x-values, with size n
    vector<double> g(n); // an empty g-array with size n
    double step = 1.0 / static_cast<double>(n - 1); // we calculate step size
    for (int i = 0; i < n; ++i) {
        x[i] = x[i-1]+step; // the x-array is filled with values between 0 and 1
        g[i] = gurl(x[i],step); //the g-array is filled with the value for the corresponding x-value
    }
    double beta;
    vector<double> alpha(n);
    vector<double> v(n);
    v[0] = g[0]/(beta=b[0]);
    // forward elimination
    for (j=1;j<n;j++){
        alpha[j]=c[j-1]/beta;
        beta=b[j]-a[j]*alpha[j];
        v[j]=(g[j]-a[j]*v[j-1])/beta;
        }
    // backward substitution
    for (j=(n-2);j>=0;j--){
        v[j] -= alpha[j+1]*v[j+1];
        }
     return make_pair(v, x);// we return both x-array and v-array so the data can be used to plot later
}

//Problem 7
void Problem7(int n,  vector<double> a, vector<double> b,  vector<double> c, string filename){
     pair<vector<double>, vector<double>> yer = solveTriGen(n,a,b,c); // solves the equation for given a, b and c vectors
     vector<double> v = yer.first;
     vector<double> x = yer.second;
     // we write the information into a file
     ofstream ofile;
     ofile.open(filename);
     int width=12;
     for (int i=0; i<=n;i++){
            ofile << scientific << x[i] << setw(width) <<  setprecision(3) << scientific << v[i] << endl;
    }
    ofile.close();
}

//Problem 9
pair<vector<double>, vector<double>> solveTriSpec(int n,double a_value,double b_value,double c_value) {
    vector<double> a(n, a_value);
    vector<double> b(n, b_value);
    vector<double> c(n, c_value);
    vector<double> x(n);
    vector<double> g(n);
    int j=n;
    double step = 1.0 / static_cast<double>(n - 1);
    for (int i = 0; i < n; ++i) {
        x[i] = x[i-1]+step;
        g[i] = gurl(x[i],step);
    }
    double beta;
    vector<double> alpha(n);
    vector<double> v(n);
    // Forward elimination
    v[0] = g[0]/(beta=b[0]);
    for (j=1;j<n;j++){
        alpha[j]=c[j-1]/beta;
        beta=b[j]-a[j]*alpha[j];
        v[j]=(g[j]-a[j]*v[j-1])/beta;
        }
    // Backward substitution
    for (j=(n-2);j>=0;j--){
        v[j] -= alpha[j+1]*v[j+1];
        }
     return make_pair(v, x);
}
void Problem9(int n, double a_value, double b_value, double c_value, string filename){
     pair<vector<double>, vector<double>> yer = solveTriSpec(n,a_value,b_value,c_value);
     vector<double> v = yer.first;
     vector<double> x = yer.second;
     ofstream ofile;
     ofile.open(filename);
     int width=12;
     for (int i=0; i<=n;i++){
            ofile << scientific << x[i] << setw(width) <<  setprecision(3) << scientific << v[i] << endl;
    }
    ofile.close();
}

void runTime(vector<double> gen, vector<double> spes){
    ofstream ofile;
    ofile.open("Times.txt");
    int width=20;
    for (int i=0; i<=4;i++){
            ofile << scientific << gen[i] << setw(width) << scientific << spes[i] << endl;
    }
    ofile.close();
}

int main(){
    maketxt(11,"Problem2n11.txt");
    maketxt(101,"Problem2n101.txt");
    maketxt(1001,"Problem2n1001.txt");
    maketxt(10001,"Problem2n10001.txt");
    maketxt(100001,"Problem2n5.txt");
    maketxt(1000001,"Problem2n6.txt");
    maketxt(10000001,"Problem2n7.txt");

    vector<double> timesGen(5,0);
    vector<double> timesSpes(5,0);

    auto t1 = std::chrono::high_resolution_clock::now();
    vector<double> a(11, -1);
    vector<double> b(11, 2);
    vector<double> c(11, -1);
    Problem7(11,a,b,c,"Problem7n11.txt");
    auto t2 = std::chrono::high_resolution_clock::now();
    timesGen[0] = std::chrono::duration<double>(t2 - t1).count();

    auto t3 = std::chrono::high_resolution_clock::now();
    vector<double> d(101, -1);
    vector<double> e(101, 2);
    vector<double> f(101, -1);
    Problem7(101,d,e,f,"Problem7n101.txt");
    auto t4 = std::chrono::high_resolution_clock::now();
    timesGen[1] = std::chrono::duration<double>(t4 - t3).count();

    auto t5 = std::chrono::high_resolution_clock::now();
    vector<double> g(1001, -1);
    vector<double> h(1001, 2);
    vector<double> i(1001, -1);
    Problem7(1001,g,h,i,"Problem7n1001.txt");
    auto t6 = std::chrono::high_resolution_clock::now();
    timesGen[2] = std::chrono::duration<double>(t6 - t5).count();

    auto t7 = std::chrono::high_resolution_clock::now();
    vector<double> j(10001, -1);
    vector<double> k(10001, 2);
    vector<double> l(10001, -1);
    Problem7(10001,j,k,l,"Problem7n10001.txt");
    auto t8 = std::chrono::high_resolution_clock::now();
    timesGen[3] = std::chrono::duration<double>(t8 - t7).count();

    auto t9 = std::chrono::high_resolution_clock::now();
    vector<double> m(100001, -1);
    vector<double> n(100001, 2);
    vector<double> o(100001, -1);
    Problem7(100001,m,n,o,"Problem7n5.txt");
    auto t10 = std::chrono::high_resolution_clock::now();
    timesGen[4] = std::chrono::duration<double>(t10 - t9).count();

    auto t11 = std::chrono::high_resolution_clock::now();
    vector<double> p(1000001, -1);
    vector<double> q(1000001, 2);
    vector<double> r(1000001, -1);
    Problem7(1000001,p,q,r,"Problem7n6.txt");
    auto t12 = std::chrono::high_resolution_clock::now();
    timesGen[5] = std::chrono::duration<double>(t12 - t11).count();

    vector<double> s(10000001, -1);
    vector<double> t(10000001, 2);
    vector<double> u(10000001, -1);
    Problem7(10000001,s,t,u,"Problem7n7.txt");

    auto t13 = std::chrono::high_resolution_clock::now();
    Problem9(11,-1,2,-1,"Problem9n11.txt");
    auto t14 = std::chrono::high_resolution_clock::now();
    timesSpes[0] = std::chrono::duration<double>(t14 - t13).count();

    auto t15 = std::chrono::high_resolution_clock::now();
    Problem9(101,-1,2,-1,"Problem9n101.txt");
    auto t16 = std::chrono::high_resolution_clock::now();
    timesSpes[1] = std::chrono::duration<double>(t16 - t15).count();

    auto t17 = std::chrono::high_resolution_clock::now();
    Problem9(1001,-1,2,-1,"Problem9n1001.txt");
    auto t18 = std::chrono::high_resolution_clock::now();
    timesSpes[2] = std::chrono::duration<double>(t18 - t17).count();

    auto t19 = std::chrono::high_resolution_clock::now();
    Problem9(10001,-1,2,-1,"Problem9n10001.txt");
    auto t20 = std::chrono::high_resolution_clock::now();
    timesSpes[3] = std::chrono::duration<double>(t19 - t20).count();

    auto t21 = std::chrono::high_resolution_clock::now();
    Problem9(100001,-1,2,-1,"Problem9n100001.txt");
    auto t22 = std::chrono::high_resolution_clock::now();
    timesSpes[4] = std::chrono::duration<double>(t22 - t21).count();

    auto t23 = std::chrono::high_resolution_clock::now();
    Problem9(1000001,-1,2,-1,"Problem9n1000001.txt");
    auto t24 = std::chrono::high_resolution_clock::now();
    timesSpes[5] = std::chrono::duration<double>(t24 - t23).count();
    runTime(timesGen,timesSpes);
    return 0;
}

