#include<iostream>
#include<vector>
using namespace std;

/**
 * ��������� ����������� ��������� ����� ���������� ������� ������������. ��
 * ����� ��������� ����� ��� ���������� �������.
 */
class Handler 
{
public:
    virtual Handler* SetNext(Handler* handler) = 0;
    virtual string Handle(string request) = 0;
};
/**
 * ��������� ������� �� ��������� ����� ���� ����������� ������ �������� ������
 * �����������.
 */
class AbstractHandler : public Handler
{
private:
    Handler* next_handler_;

public:
    AbstractHandler() : next_handler_(nullptr) {}
    Handler* SetNext(Handler* handler) override
    {
        this->next_handler_ = handler;
        // ������� ����������� ������ �������� ������� ����������� ������� ��������,
        // ��� ���:
        // $monkey->setNext($squirrel)->setNext($dog);
        return handler;
    }
    string Handle(string request) override
    {
        if (this->next_handler_)
        {
            return this->next_handler_->Handle(request);
        }

        return {};
    }
};
/**
 * ��� ���������� ����������� ���� ������������ ������, ���� �������� ���
 * ���������� ����������� � �������.
 */
class MonkeyHandler : public AbstractHandler 
{
public:
    string Handle(string request) override 
    {
        if (request == "Banana") {
            return "Monkey: I'll eat the " + request + ".\n";
        }
        else 
        {
            return AbstractHandler::Handle(request);
        }
    }
};
class SquirrelHandler : public AbstractHandler 
{
public:
    string Handle(string request) override
    {
        if (request == "Nut") 
        {
            return "Squirrel: I'll eat the " + request + ".\n";
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};
class DogHandler : public AbstractHandler {
public:
    string Handle(string request) override
    {
        if (request == "MeatBall") 
        {
            return "Dog: I'll eat the " + request + ".\n";
        }
        else 
        {
            return AbstractHandler::Handle(request);
        }
    }
};
/**
 * ������ ���������� ��� ������������ ��� ������ � ������������ ������������. �
 * ����������� ������� ������� ���� ����������, ��� ���� ���������� ��������
 * ������ �������.
 */
void ClientCode(Handler& handler)
{
    vector<string> food = { "Nut", "Banana", "Cup of coffee" };
    for (const string& f : food) 
    {
        cout << "Client: Who wants a " << f << "?\n";
        const std::string result = handler.Handle(f);
        if (!result.empty())
        {
            cout << "  " << result;
        }
        else
        {
            std::cout << "  " << f << " was left untouched.\n";
        }
    }
}
/**
 * ������ ����� ����������� ���� ������� ���� �������.
 */
int main() 
{
    MonkeyHandler* monkey = new MonkeyHandler;
    SquirrelHandler* squirrel = new SquirrelHandler;
    DogHandler* dog = new DogHandler;
    monkey->SetNext(squirrel)->SetNext(dog);

    /**
     * ������ ������ ����� ����������� ���������� ������ ������ �����������, � ��
     * ������ ������� � �������.
     */
    cout << "Chain: Dog > Squirrel > Monkey\n\n";
    ClientCode(*dog);
    cout << "\n";
    cout << "Subchain: Squirrel > Dog\n\n";
    ClientCode(*monkey);

    delete monkey;
    delete squirrel;
    delete dog;

    return 0;
}