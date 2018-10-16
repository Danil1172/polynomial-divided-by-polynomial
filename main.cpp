#include <iostream>
using namespace std;
#include <cstring>
#include <cstdlib>
class mnogozlen
{
        int degree;//степень
        double*koef;//массив коэффицентов
public:
        mnogozlen(){};//конструктор по умолчанию
        mnogozlen(const mnogozlen& pol);//Конструктор копирования
        mnogozlen(int count);//Конструктор преобразования типа
        ~mnogozlen(){delete[] koef;}//Деструктор
        mnogozlen operator+(mnogozlen&);//Сумма
        mnogozlen operator-(mnogozlen&);//Разность
        mnogozlen& operator=(mnogozlen&);//присваивание
        mnogozlen operator*(mnogozlen&);//Умножение полинома на полином
        mnogozlen operator/(mnogozlen&);//Целая часть от деления
        mnogozlen operator%(mnogozlen&);//Остаток от деления
        int GetDegr(){return degree;}//Получение степени
        double calcul(int); //Расчет значения
        int push(double,double* );//Ввод полинома
        friend ostream &operator<<(ostream &, mnogozlen &);// Перегрузка оператора << для вывода в поток
};

mnogozlen::mnogozlen(int count)
{
        degree=count;
        koef=new double[degree+1];
}
mnogozlen::mnogozlen(const mnogozlen& ob)
{
        degree=ob.degree;
        koef=new double[degree+1];
        for(int i=degree;i>=0;i--)
                koef[i]=ob.koef[i];
}
int mnogozlen::push(double n, double *k)
{
        degree=n;
        koef=new double[degree+1];
        for(int i=n;i>=0;i--)
        koef[i]=k[i];
        return 0;
}

ostream &operator<<(ostream &fo, mnogozlen &o)
{
int f=0;

    for (int i=o.degree;i>=0;i--)
        if (o.koef[i]!=0){
        if(f==0){
        if(i!=0) fo <<o.koef[i]<<"*x^"<<i;
        else fo <<o.koef[i]; f++;}
        else {
        if(i!=0)
        if(o.koef[i]>0) fo <<"+"<<o.koef[i]<<"*x^"<<i;
        else fo <<o.koef[i]<<"*x^"<<i;
        else  if(o.koef[i]>0) fo <<"+"<<o.koef[i];
        else fo <<o.koef[i]; f++;} }
        if (f==0) {fo <<0;}

        fo <<endl;

        return fo;
}


mnogozlen mnogozlen::operator+(mnogozlen& ob)
{
        if(degree==ob.degree)
        {
                mnogozlen temp(degree);
                for(int i=ob.degree;i>=0;i--)
                        temp.koef[i]=koef[i]+ob.koef[i];
                return temp;
        }
        if(degree<ob.degree)
        {
                mnogozlen temp(ob.degree);
                for(int i=degree;i>=0;i--)
                        temp.koef[i]=koef[i]+ob.koef[i];
                for(int i=ob.degree;i>=degree+1;i--)
                        temp.koef[i]=ob.koef[i];
                return temp;
        }
        if(degree>ob.degree)
        {
                mnogozlen temp(degree);
                for(int i=ob.degree;i>=0;i--)
                        temp.koef[i]=koef[i]+ob.koef[i];
                for(int i=degree;i>=ob.degree+1;i--)
                        temp.koef[i]=koef[i];
                return temp;
        }
        return *this;
}
mnogozlen mnogozlen::operator-(mnogozlen& ob)
{
        if(degree==ob.degree)
        {
                mnogozlen temp(degree);
                for(int i=ob.degree;i>=0;i--)
                        temp.koef[i]=koef[i]-ob.koef[i];
                return temp;
        }
        if(degree<ob.degree)
        {
                mnogozlen temp(ob.degree);
                for(int i=degree;i>=0;i--)
                        temp.koef[i]=koef[i]-ob.koef[i];
                for(int i=ob.degree;i>=degree+1;i--)
                        temp.koef[i]=ob.koef[i];
                return temp;
        }
        if(degree>ob.degree)
        {
                mnogozlen temp(degree);
                for(int i=ob.degree;i>=0;i--)
                        temp.koef[i]=koef[i]-ob.koef[i];
                for(int i=degree;i>=ob.degree+1;i--)
                        temp.koef[i]=koef[i];
                return temp;
        }
        return *this;
}
mnogozlen mnogozlen::operator *(mnogozlen& ob)
{
                mnogozlen temp;
                temp.degree=degree+ob.degree;
                temp.koef=new double[temp.degree+1];
                memset(temp.koef, 0, (temp.degree+1)*sizeof(double));
                for(int i=0;i<=degree;i++)
                {
                        for(int j=0;j<=ob.degree;j++)
                                {
                                        temp.koef[i+j] +=koef[i]*ob.koef[j];
                                }
                }
                return temp;
}


double mnogozlen::calcul(int n)
{
    int g=1, j=1;
    double p=0;
        for(int i=0; i<=degree; i++)
        {
            while(j==i){j++; g*=n; }
                p+=koef[i]*g;
        }
        return p;
}

int main()
{
        setlocale(LC_ALL, "Russian");
        int n=0;
        int k=0;
        int u=0;
        double *koef, *koef1;

        cout<<"Введите степень первого многочлена\n";
        cin>>n;

        mnogozlen p(n);
        koef=new double[n+1];
        for(int i=0;i<=n;i++)
            {
                    cout<<"Koef["<<i<<"] ";
                    cin>>koef[i];
            }
        p.push(n, koef);

        int m=0;
        cout<<"Введите степень второго многочлена\n";
        cin>>m;

        mnogozlen s(m);
        koef1=new double[m+1];
        for(int i=0;i<=m;i++)
            {
                    cout<<"Koef["<<i<<"] ";
                    cin>>koef1[i];
            }
        s.push(m, koef1);

        cout<<"Первый многочлен: " << p <<'\n';
        cout<<"Второй многочлен: " << s <<'\n';

        if(p.GetDegr()>=s.GetDegr())
                k=p.GetDegr();
        else
                k=s.GetDegr();

        mnogozlen t(k);
        //t=p+s;
        cout<<"Сумма многочленов = " << t <<'\n';

        mnogozlen t1(k);
        //t1=p-s;
        cout<<"Разность многочленов = " << t1 <<'\n';

        mnogozlen x(p.GetDegr()+s.GetDegr());
        //x=p*s;
        cout<<"Произведение многочленов = "<<x<<'\n';

        cout<<"Деление многочленов:" <<'\n';
        mnogozlen y(p.GetDegr()-s.GetDegr());
        //y=p/s;
        cout<<"Частное от деления = " <<y<<'\n';


        cout<<"Введите значение x = ";
        cin>>u;
        cout<<endl;
        cout<<"Первый многочлен = "<<p.calcul(u)<<endl;
        cout<<"Второй многочлен = "<<s.calcul(u)<<endl;

        return 0;
}
