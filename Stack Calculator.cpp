#include <iostream>
#include<stack>

using namespace std;

enum operations
{
    bracket_open,
    bracket_close,
    difference,
    sum,
    modulo,
    multiplying
};

void dividing_into_operations(char str[], int n_str, stack<int> &numb_stack, stack<operations> &oper_stack, int& numb_of_brackets);
int ariphmetical_calc(int a, int b, operations operation);
int calculating(stack<int> numbers, stack<operations> opers, int n_1_prior);
int calculator(char str[], int n);

int main()
{
    

    int n_total;
    cout << "enter the number of symbols in the expression: ";
    cin >> n_total;

    char* the_str = new char[n_total];
    cout << "enter the expression: ";
    for (int i = 0;i < n_total;i++)
    {
        cin >> the_str[i];
    }

    cout << "the result is: " << calculator(the_str, n_total);
    
    return 0;
}

void dividing_into_operations(char str[], int n_str, stack<int> &numb_stack, stack<operations> &oper_stack, int& numb_of_brackets)
{
    numb_of_brackets = 0;
    for (int i = 0;i < n_str;i++)
    {
        if (str[i] >= 48 && str[i] <= 57)
        {
            numb_stack.push((int)(str[i] - '0'));
        }
        else
            switch (str[i])
            {
            case 40:
                oper_stack.push(bracket_open);
                break;
            case 41:
                oper_stack.push(bracket_close);
                numb_of_brackets++;
                break;
            case 42:
                oper_stack.push(multiplying);
                break;
            case 43:
                oper_stack.push(sum);
                //cout << " we got sum ";
                break;
            case 45:
                oper_stack.push(difference);
                break;
            case 37:
                oper_stack.push(modulo);
                break;
            default:
                cout << "there was a wrong symbol";
            }

    }

}

int ariphmetical_calc(int a, int b, operations operation)
{
    if (operation == sum)
        return a + b;
    if (operation == difference)
        return a - b;
    if (operation == multiplying)
        return a * b;
    if (operation == modulo)
        return a % b;
    return -1;
}


int calculating(stack<int> numbers, stack<operations> opers, int n_1_prior)
{

    stack<int> temp_numbs;
    stack<operations> temp_opers;
    
    while (n_1_prior != 0)
    {
        if (opers.top() != multiplying && opers.top() != modulo)
        {
            temp_opers.push(opers.top());
            opers.pop();

            temp_numbs.push(numbers.top());
            numbers.pop();
            
        }
        else
        {
            int number1 = numbers.top();
            numbers.pop();
            int number2 = numbers.top();
            numbers.pop();

            numbers.push(ariphmetical_calc(number1, number2, opers.top()));
            opers.pop();
            n_1_prior--;
        }
    }
    
    while (!(temp_opers.empty()))
    {
        numbers.push(temp_numbs.top());
        temp_numbs.pop();
        

        opers.push(temp_opers.top());
        temp_opers.pop();
    }
    if (!temp_numbs.empty())
    {
        numbers.push(temp_numbs.top());
        temp_numbs.pop();
    }

    while (!(opers.empty()))
    {
        int number1 = numbers.top();
        numbers.pop();
        int number2 = numbers.top();
        numbers.pop();

        numbers.push(ariphmetical_calc(number1, number2, opers.top()));
        opers.pop();
    }

    return numbers.top();
}


int calculator(char str[], int n)
{
    stack<int> numb_stack;
    stack<operations> operation_stack;
    int rem_numb_of_br;
    dividing_into_operations(str, n, numb_stack, operation_stack, rem_numb_of_br);
    
    int res;

    stack<int> help_numb_stack;
    stack<operations> help_operation_stack;
    
    int numb_of_1st_prior_oper_without_brackets = 0;
    do
    {
       
        if ( operation_stack.empty() == true || operation_stack.top() != bracket_close  )
        {
            
            if (!operation_stack.empty())
            {
                help_operation_stack.push(operation_stack.top());
                if (help_operation_stack.top() == multiplying || help_operation_stack.top() == modulo)
                    numb_of_1st_prior_oper_without_brackets++;
                operation_stack.pop();
            }

            help_numb_stack.push(numb_stack.top());
            numb_stack.pop();
            
        }
        else
        {
            operation_stack.pop();
            stack<int> temp_calc_numb;
            stack<operations> temp_calc_oper;
           
            int temp_numb_of_1st_prior = 0;
            
            do
            {
                temp_calc_oper.push(operation_stack.top());
                if (operation_stack.top() == multiplying || operation_stack.top() == modulo)
                    temp_numb_of_1st_prior++;
                operation_stack.pop();

                temp_calc_numb.push(numb_stack.top());
                numb_stack.pop();
                
            } while (operation_stack.top() != bracket_open);

            temp_calc_numb.push(numb_stack.top());
            numb_stack.pop();
            operation_stack.pop();
            numb_stack.push(calculating(temp_calc_numb, temp_calc_oper, temp_numb_of_1st_prior));

            rem_numb_of_br--;
        }
        
        
    } while (!(numb_stack.empty()));

    
    res = calculating(help_numb_stack, help_operation_stack, numb_of_1st_prior_oper_without_brackets);
    return res;

}


