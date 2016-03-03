//solution by Wsl_F
#include <bits/stdc++.h>
#include "ReadBMP.cpp"

using namespace std;


typedef vector<int> vi;
typedef double dbl;
#define pb(x)  push_back(x)

class BAM
{
private:
    dbl** matrix;
    int n;
    int m;
    const dbl theta= 0;
    const dbl eps= 1e-3;

public:
    BAM(int n0, int m0)
    {
        this->n= n0;
        this->m= m0;
        matrix= new dbl*[n];
        for (int i= 0; i<n; i++)
            matrix[i]= new dbl[m];
    }

    void learn(vector<vi> inputs, vector<vi> outputs)
    {
        if (inputs.size() != outputs.size()) return;
        int sz= inputs.size();

        for (int i= 0; i<n; i++)
            for (int j= 0; j<m; j++)
            {
                matrix[i][j]= 0;
                for (int k= 0; k<sz; k++)
                    matrix[i][j]+= inputs[k][i] * outputs[k][j];
            }
    }

    dbl f(dbl u)
    {
        if (abs(u-theta) < 1e-6)  return u;
        if (u>theta) return 1;
        return -1;
    }

    void initX(vi input, vi &uInX, vi &uOutX)
    {
        for (int i= 0; i<n; i++)
            uInX[i]= input[i];

        for (int i= 0; i<n; i++)
            uOutX[i]= f(uInX[i]);
    }

    bool calcX(vi &uInX, vi &uOutX, vi &uInY, vi &uOutY)
    {
        bool result= 1;
        for (int i= 0; i<n; i++)
        {
            dbl sum= 0;
            for (int j= 0; j<m; j++)
                sum+= matrix[i][j]*uOutY[j];
            uInX[i]= sum;
            sum= f(uInX[i]);

            result&= (abs(uOutX[i]-sum) < eps);
            uOutX[i]= sum;
        }

        return result;
    }

    void initY(vi input, vi &uInY, vi &uOutY)
    {
        for (int i= 0; i<m; i++)
            uInY[i]= input[i];

        for (int i= 0; i<m; i++)
            uOutY[i]= f(uInY[i]);
    }

    bool calcY(vi &uInX, vi &uOutX, vi &uInY, vi &uOutY)
    {
        bool result= 1;
        for (int j= 0; j<m; j++)
        {
            dbl sum= 0;
            for (int i= 0; i<n; i++)
                sum+= matrix[i][j]*uOutX[i];
            uInY[j]= sum;
            sum= f(uInY[j]);

            result&= (abs(uOutY[j]-sum) < eps);
            uOutY[j]= sum;
        }

        return result;
    }

    vi process(vi input)
    {
        int sz= input.size();

        int t= 0;
        vi uInX(n), uOutX(n), uInY(m), uOutY(m);
        if (sz==n)
        {
            initX(input,uInX,uOutX);
            calcY(uInX,uOutX,uInY,uOutY);
        }
        else
        {
            initY(input,uInY,uOutY);
            calcX(uInX,uOutX,uInY,uOutY);
            calcY(uInX,uOutX,uInY,uOutY);
        }

        bool f= 0;

        while (!f)
        {
            f= calcX(uInX,uOutX,uInY,uOutY);
            f&= calcY(uInX,uOutX,uInY,uOutY);
        }

        return uOutY;
    }
};

void simple_example()
{
    BAM bam(12,3);
    cout<<"Created!"<<endl;

    vi in1= {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    vi out1= {-1, -1, 1};
    vi in2= {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    vi out2= {1, 1, 1};

    vector<vi> input;
    input.pb(in1);
    input.pb(in2);
    input.pb(in2);

    vector<vi> output;
    output.pb(out1);
    output.pb(out2);
    output.pb(out2);

    bam.learn(input, output);
    cout<<"Learned!"<<endl;

    vi out= bam.process(in2);
    cout<<"Processed!"<<endl;

    cout<<out.size()<<endl;
    for (int i= 0; i<out.size(); i++)
        cout<<out[i]<<" ";
    cout<<endl;
}

void example_WF()
{
    vi W= ReadBMP::readBlackWhiteBMP("W.bmp");
    vi F= ReadBMP::readBlackWhiteBMP("F.bmp");

    for (int i= 0; i<W.size(); i++)
        W[i]= 2*W[i]-1;
    for (int j= 0; j<F.size(); j++)
        F[j]= 2*F[j]-1;

    BAM bam(W.size(), F.size());
    cout<<"Created!"<<endl;

    vector<vi> input;
    input.pb(W);

    vector<vi> output;
    output.pb(F);

    bam.learn(input, output);
    cout<<"Learned!"<<endl;

    cout<<endl<<endl;
    vi W2= ReadBMP::readBlackWhiteBMP("W3.bmp");
    for (int i= 0; i<W.size(); i++)
        W2[i]= 2*W2[i]-1;
    cout<<endl<<endl;

    vi out= bam.process(W2);
    cout<<"Processed!"<<endl;

    for (int i= 0; i<out.size(); i++)
        out[i]= (out[i]+1)/2;

/*    for (int i= 0; i<out.size(); i++)
        cout<<out[i]<<" ";
    cout<<endl;
    cout<<endl<<endl<<endl<<endl;
*/
    ReadBMP::printBlackWhite(out,40,40);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout<<fixed;
    cout<<setprecision(9);

    example_WF();

    return 0;
}
