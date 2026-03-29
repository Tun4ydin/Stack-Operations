#include <iostream>
#include <string>
#include <cctype>
using namespace std;


class Fixer
{
private:
    string postfix;
    string infix;
    int precedence;
public:
    Fixer():infix(""), postfix(""){}
    void getInfix(string n)
    {
        infix = n;
    }
    int setPrecedence(const char &c)
    {
        if(c == '+' || c == '-')
        {
            precedence = 1;
            
        }
        else if(c == '*' || c == '/')
        {
            precedence = 2;
        }
        return precedence;
    }
    string showInfix(){return infix;}
    string showPostfix(){return postfix;}
    void toPostfix();
    void calcPostfx();
};
template <typename T>class StackArray
{
    static const int MAX = 8;
    T items[MAX];
    T top;
public:
    StackArray(): top(-1){}
    bool isEmpty()
    {
        return top == -1;
    }
    bool isFull()
    {
        return top == MAX - 1;
    }
    void push(T e)
    {
        if (MAX-1 <= top)
        {
            throw out_of_range("Stack Overflow");
        }
        top++;
        items[top] = e;
    }
    T getTop()
    {
        if (isEmpty())
        {
            throw out_of_range("Empty Stack.\n");
        }
        return items[top];
    }
    void pop()
    {
        if (isEmpty())
        {
            throw out_of_range("Empty Stack.\n");
        }
        top--;
    }
};

template <typename T> class StackLinked
{
    struct Node
    {
        T data;
        Node* next;
    };
    Node* head;
public:
    StackLinked():head(nullptr){}
    void pop()
    {
        if (head == nullptr)
        {
            cout << "Empty List." << endl;
            return;
        }
        else if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            return;
        }
        Node* walk = head;
        head = head->next;
        walk->next = nullptr;
        delete walk;
    }
    T getTop()
    {
        if (head == nullptr)
        {
            throw out_of_range("Empty List.\n");
        }
        else
        {
            return head->data;
        }
    }
    void push(T e)
    {
        Node* walk = new Node(e);
        walk->next = head;
        head = walk;
    }
    bool isEmpty()
    {
        return head == nullptr;
    }
};

int strSize(char binString[])
{
    int ind = 0;
    while(binString[ind] != '\0')
        ind++;

    return ind;
}
int binaryToDecimal(char binString[])
{
    StackArray<int> s;
    for(int i = 0; binString[i] != '\0'; i++)
    {
        if(binString[i] != '1' || binString[i] != '0')
        {
            throw out_of_range("Binary numbers can only contain 1's or 0's");
        }
        s.push(i);
    }
    int dec = 0;
    for(int i = 0; binString[i] != '\0'; i++)
    {
        dec += int(binString[i] - '0') * pow(2,s.getTop());
        s.pop();
    }
    return dec;
}

void Fixer::toPostfix()
{
     StackLinked<char> st;
     Fixer fx;
     postfix = "";
     for(int i = 0; i < infix.size(); i++)
     {
         if(isnumber(infix[i]))
         {
             postfix += infix[i];
             postfix += " ";
         }
         else if(infix[i] == '(')
         {
             st.push(infix[i]);
         }
         else if(infix[i] == ')')
         {
             while (!st.isEmpty() && st.getTop() != '(')
             {
                    postfix += st.getTop();
                    postfix += " ";
                    st.pop();
             }
             if(!st.isEmpty()) st.pop();
         }
         else if(infix[i] == '+' || infix[i] == '-' || infix[i] == '/' || infix[i] == '*')
         {
             while (!st.isEmpty() && st.getTop() != '(' &&fx.setPrecedence(st.getTop()) >= fx.setPrecedence(infix[i]))
             {
                postfix += st.getTop();
                postfix += " ";
                st.pop();
            }
             st.push(infix[i]);
         }
     }
     
     while (!st.isEmpty())
     {
        postfix += st.getTop();
        postfix += " ";
        st.pop();
     }
}

bool isBalanced(string s)
{
    StackArray<char> st;

    for (char c : s)
    {
        if (c == '(')
            st.push(c);
        else if (c == ')')
        {
            if (st.isEmpty())
                return false;
            st.pop();
        }
    }
    return st.isEmpty();
}

bool isValid(string s)
{
    bool flag = true;

    for (int i = 0; i < s.size(); i++)
    {
        char c = s[i];

        if (c == ' ') continue;

        if (isdigit(c) || isalpha(c))
        {
            flag = false;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            if (flag)
                return false;

            flag = true;
        }
        else if (c == '(')
        {
            flag = true;
        }
        else if (c == ')')
        {
            flag = false;
        }
        else
        {
            return false;
        }
    }

    return !flag;
}
void Fixer::calcPostfx()
{
    StackArray<int> st;

    for (int i = 0; i < postfix.size(); i++)
    {
        char sym = postfix[i];

        if (sym == ' ') continue;

        if (isdigit(sym))
        {
            st.push(sym - '0');
        }
        else
        {
            int b = st.getTop(); st.pop();
            int a = st.getTop(); st.pop();
            
            int result = 0;
            
            if (sym == '+')
            {
                result = a + b;
            }
            else if (sym == '-')
            {
                result = a - b;
            }
            else if (sym == '*')
            {
                result = a * b;
            }
            else if (sym == '/')
            {
                result = a / b;
            }

            st.push(result);
        }
    }

    cout << st.getTop() << endl;
}

int main()
{
    try
    {
        char binString[15];
        cout << "Enter: ";
        cin >> binString;
        int i = binaryToDecimal(binString);
        cout << "To decimal: " << i << endl;
        
        Fixer infix;
        
        infix.getInfix("1 + 8 - 7");
        cout << "Infix: "<< infix.showInfix() << endl;
        infix.toPostfix();
        cout << "Postfix: "<< infix.showPostfix() << " = ";
        infix.calcPostfx();
        
        infix.getInfix("( (1*8) + (2/2) ) * (3+7)");
        cout << "Infix: "<< infix.showInfix() << endl;
        infix.toPostfix();
        cout << "Postfix: "<< infix.showPostfix() << " = ";
        infix.calcPostfx();
        
        cout << "Enter expression: ";
        string s;
        cin.ignore(1000, '\n');
        getline(cin, s);
        if(!isValid(s))
        {
            cout << "Not a valid Expression." << endl;
            return 1;
        }
        infix.getInfix(s);
        cout << "Infix: "<< infix.showInfix() << endl;
        if(!isBalanced(infix.showInfix()))
        {
            cout << " Unbalanced Expression. Syntax Error" << endl;
        }
        else
        {
            infix.toPostfix();
            cout << "Postfix: "<< infix.showPostfix() << " = ";
            infix.calcPostfx();
        }
    }
    catch(const out_of_range& e)
    {
        cout << "Error: " << e.what() << endl;
    }
}
