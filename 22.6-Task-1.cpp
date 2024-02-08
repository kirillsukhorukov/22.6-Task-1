#include <iostream>
#include <string>
#include <sstream>
#include <locale>
#include <map>

void hello()
{
std::cout << "----- Hello! Welcome to the 'Telephone Directory' program. -----" << std::endl << std::endl;
std::cout << " - Enter the phone number (xx-xx-xx) and last name of the subscriber to add the subscriber to the directory." << std::endl;
std::cout << " - Enter the phone number (xx-xx-xx) to find out the subscriber's last name." << std::endl;
std::cout << " - Enter the subscriber's last name to find out the phone numbers of subscribers with this last name." << std::endl;
std::cout << " - Enter 'L' to view directory entries." << std::endl;
std::cout << " - Enter 'Q' to exit the program." << std::endl << std::endl;
return;
}

//Функция ввода запроса и определение его типа
std::string req_input(int &reqType)
{
    std::string str;
    bool error = false;
    do
    {
        //Сброс ошибки
        error = false;

        //Ввод строки с запросом
        std::cout << "Please enter your request: ";
        std::getline(std::cin, str);

        //Проверка запроса на выход из программы
        if (str == "Q")
        {
            reqType=5;
            return str;
        }

        //Проверка запроса на просмотр записей справочника
        if (str == "L")
        {
            reqType=4;
            return str;
        }
        //Проверка наличия номера телефона в запросе
        if (str.length()>7 & isdigit(str[0]) & isdigit(str[1]) & isdigit(str[3]) & 
            isdigit(str[4]) & isdigit(str[6]) & isdigit(str[7]) & str[2]=='-' & str[5]=='-')
        {
            if (str.length()==8)  //Если запрос содержит только номер телефона, то вернуть код запроса - 2
            {
                reqType=2;
                return str;
            }
            else if (str.length()>8 & str[8]==' ') //Если есть разделительный пробел, то проверить, что оставшаяся строка состоит из букв
            {
                for (int i=9; i<str.length(); i++)
                {
                    if (!isalpha(str[i]))
                    {
                        error = true;
                        i = str.length() - 1;
                    }
                }

                if (!error) //Если запрос прошел проверку, то вернуть код запроса - 1, если нет выдать сообщение об ошибке
                {
                    reqType=1;
                    return str;
                } 
                else 
                {
                    std::cerr << "Error when entering last name! Repeat input." << std::endl;
                }
            }
            else //Если восьмой символ не разделительный пробел - вывести ошибку ввода запроса
            {
                std::cerr << "Error when entering request! Repeat input." << std::endl;
                error = true;
            }
            
        }
        //Если запрос не содержит номер телефона, то проверить, что запрос состоит из букв
        else 
        {
            for (int i=0; i<str.length(); i++)
                {
                    if (!isalpha(str[i]))
                    {
                        error = true;
                        i = str.length() - 1;
                    }
                }

                if (!error) //Если запрос прошел проверку, то вернуть код запроса - 3, если нет выдать сообщение об ошибке
                {
                    reqType=3;
                    return str;
                } 
                else 
                {
                    std::cerr << "Error when entering last name! Repeat input." << std::endl;
                }
        }
    } while (error);
    return str;
}

//Функция добавления абонента в словарь
void add_subscr (std::map<std::string, std::string> &phonebook, std::string &req)
{
    std::string key;
    std::string value;

    //Выделяем из строки ключ и значение
    for (int i=0; i<req.length(); i++)
        {
            if (i<8) key +=req[i];
            if (i>8) value +=req[i];
        }

    phonebook[key] = value;

    std::cout << std::endl << "The entry is included in the directory." << std::endl << std::endl;

    return;
}

//Функция поиска фамилии абонента по телефону
void find_subscr (std::map<std::string, std::string> &phonebook, std::string &key)
{
    std::cout << std::endl;

    if(phonebook.find(key) != phonebook.end()) 
    {
        std::cout << "Phone - "<< phonebook.find(key)->first << std::endl;
        std::cout << "Last name - "<< phonebook.find(key)->second << std::endl;
    }
    else
    {
        std::cerr << "There is no entry!" << std::endl;
    }

    std::cout << std::endl;

    return;
}

void find_phone (std::map<std::string, std::string> &phonebook, std::string &request)
{

}

//Функция просмотра записей книги
void view_dict (std::map<std::string, std::string> &phonebook)
{
    std::cout << std::endl << "Phone:   Last name:" << std::endl;

    for (std::map<std::string, std::string>::iterator it=phonebook.begin(); it != phonebook.end(); ++it)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }

    std::cout << std::endl;

    return;
}

int main()
{
    
    std::map<std::string, std::string> phonebook;

    hello();

    int reqType = 0; //Переменная с кодом запроса

    std::string request;

    do
    {
        request = req_input(reqType);
        if (reqType == 1) add_subscr (phonebook, request);
        if (reqType == 2) find_subscr (phonebook, request);
        if (reqType == 3) find_phone (phonebook, request);
        if (reqType == 4) view_dict (phonebook);
    } while (reqType!=5);
    
    std::cout << std::endl << "Program completed. Press any key...";
    std::cin.get();

    return 0;
}