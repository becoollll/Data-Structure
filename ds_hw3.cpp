#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Term
{
    public:
    int coef; // coefficient係數
    int exp; // exponent指數
    Term *next; // pointer to the next term
    Term():coef(0), exp(0), next(NULL){} // default constructor
    Term(Term& t) // copy constructor
    {
        coef = t.coef;
        exp = t.exp;
        next = NULL;
    }
};
class Poly
{
    public:
    int n_terms; // number of terms in the polynomial多項式項數
    Term *p; // the pointer to the first term in the linked list第一項pointer
    Poly():n_terms(0), p(NULL) {} // default constructor
    Poly(Poly& p); // copy constructor
    void Add(Term *t); // add a single term pointed by t to the polynomial將 t 指向的單個項添加到多項式
    void Add(Poly* p); // add a polynomial pointed by p to this polynomial (update this polynomial with the result directly)將 p 指向的多項式添加到該多項式（直接用結果更新該多項式）    
    void Mul(Term* t); // multiply the polynomial with a single term pointed by t (update this polynomial with the result directly)將多項式與 t 指向的單個項相乘（直接用結果更新該多項式）
    void Mul(Poly* p); // multiply the polynomial with a polynomial pointed by p (update this polynomial with the result directly)多項式乘以 p 指向的多項式（直接用結果更新這個多項式）
    void Print(); // display the polynomial
};

Poly::Poly(Poly &poly)
{
    Term *q = poly.p; // get the first term of the source poly
    p = NULL; // clear the list of this polynomial
    while (q) // add to this polynomial by copying terms in the source poly one by one
    {
        Term *t = new Term(*q); // copy the current term of the source poly
        Add(t); // add the term to this polynomial
        q = q->next; // get the next term of the source poly
    }
}

void Poly::Print()
{
    Term *q = p; // start from the first term
    while (q && q->coef==0) // find the first term with a non-zero coefficient
        q = q->next;
    if (q) // output the found first term 
        cout << q->coef << "x^" << q->exp;
    q = q->next; // get the next term
    while (q) // visit the terms one by one for output
    {
        int c = q->coef; // if positive coefficient, then preced this term with a plus sign
        char op = '+'; // plus sign
        if (q->coef<0) // otherwise, preced this term with a minus sign
        {
            op = '-';
            c = -c; // change the sign of coeff since it has been preceded with a minus
        }
        if (q->coef!=0) // output this term if coeff is not zero
            cout << op << c << "x^" << q->exp;
        q = q->next; // get the next term 
    }
    cout << endl;
}

Poly *GeneratePoly(int n)
{
    Poly* poly = new Poly();
    for (int i=0; i<n; i++)
    {
        //cout << "yo this is gen" << endl;
        Term* t = new Term();
        t->coef = rand() % 100 - 50;
        //cout << "t->coef: " << t->coef << endl; 
        t->exp = rand() % 20;
        //cout << "t->exp: " << t->exp << endl; 
        poly->Add(t);
    }
    return poly;
}
void Poly::Add(Term* t)
{
    Term* temp = p;
    if(temp == NULL){//first
        p = t;
        n_terms++;
        return;
    }
    if(t->exp < temp->exp){//放前面
        t->next = temp;
        p = t;
        n_terms++;
        return;
    }
    while(temp->next != NULL && temp->next->exp <= t->exp){
        temp = temp->next;
    }

    if(temp->exp == t->exp){
        //cout << "+++++++++++" << endl;
        temp->coef += t->coef;
        return;
    }
    if (temp->next == NULL){
        temp->next = t;
        n_terms++;
        return;
    }
    Term* insert = temp->next;
    temp->next = t;
    t->next = insert;
    n_terms++;
}

void Poly::Add(Poly* poly)
{
    // add the terms of the source poly to this poly
    Term* q = poly->p;
    while (q)
    {
        Term* t = new Term(*q);
        Add(t);
        q = q->next;
    }

}

void Poly::Mul(Term* t)
{
    // multiply the polynomial with a single term pointed by t (update this polynomial with the result directly)
    Term* temp = p;
    while(temp != NULL){
        temp->coef *= t->coef;
        temp->exp += t->exp;
        temp = temp->next;
    }

}

void Poly::Mul(Poly* poly)
{

    Poly *ptr1, *ptr2;
    Poly *ptr3 = new Poly();//多一個poly 用這個存，最後再把他加到this poly
    ptr1 = this;
    ptr2 = poly;
    Term *original = poly->p;//紀錄原本的poly的頭
    while (ptr1->p != NULL) {
        while (ptr2->p != NULL) {
            int coeff, power;//用兩個int來存計算結果
            Term* temp = new Term();//新的term來存計算結果的coef exp
            coeff = ptr1->p->coef * ptr2->p->coef;
            //cout << ptr2->p->coef << "*" << ptr1->p->coef << "=" << coeff << endl;
            power = ptr1->p->exp + ptr2->p->exp;
            //cout << ptr1->p->exp << "+" << ptr2->p->exp << "=" << power << endl << endl;
            //cout << "power: " << power << endl << endl;
            temp->coef = coeff;
            //cout << "coeff: " << temp->coef << endl;
            temp->exp = power;
             //cout << "power: " << temp->exp << endl;
            ptr3->Add(temp);//把計算結果加到ptr3
 
            // move the pointer of 2nd polynomial
            // two get its next term
            if(ptr2->p->next != NULL){//如果ptr2的下一個不是NULL就繼續下一個
                ptr2->p = ptr2->p->next;
            }       
            else{//如果ptr2的下一個是NULL就把ptr2的p指向原本的poly的頭
                break;
            }
               
        }
        //cout << "ptr2: " << ptr2->p << endl;
        ptr2->p = original;//從頭開始
 
        // move the pointer of 1st polynomial
        ptr1->p = ptr1->p->next;//換下一個
        //cout << "ptr1: " << ptr1->p << endl;
    }

    this->p = ptr3->p;//結果放回this
}

int main(){
    
    srand(123);
    Term* t = new Term();
    t->coef = rand() % 100 - 50;
    cout << "t->coef: " << t->coef << endl; 
    t->exp = rand() % 20;
    cout << "t->exp: " << t->exp << endl;
    Poly* pl1 = GeneratePoly(8); // randomly generate a polynomial of at most 8 terms
    pl1->Print(); // display the pl1
    Poly* pl2 = GeneratePoly(3); // randomly generate a polynomial of at most 3 terms
    //pl1->Mul(t); // multiply pl1 with pl2
    //pl1->Print();

    pl2->Print(); // display the pl2
    pl1->Mul(pl2); // perform the polynomial mulitiplication between pl1 and pl2 and the result is stored on pl1
    pl1->Print(); // display the multiplication result
}