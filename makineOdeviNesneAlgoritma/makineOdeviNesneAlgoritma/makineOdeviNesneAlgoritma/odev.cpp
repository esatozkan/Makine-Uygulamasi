#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


class Machines
{
private:
    int operationCode;
    float machineSpeed;

public:
    Machines& SetMachineSpeed(float machineSpeed)
    {
        this->machineSpeed = machineSpeed;
        return *this;
    }
    Machines& SetOperationCode(int operationCode)
    {
        this->operationCode = operationCode;
        return *this;
    }
    float GetMachineSpeed() const
    {
        return machineSpeed;
    }
    int GetOperationCode() const
    {
        return operationCode;
    }
};

class SetupDurations
{
private:
    int chancing1;
    int chancing2;
    int setupDuration;

public:
    SetupDurations& SetChancing1(int chancing1)
    {
        this->chancing1 = chancing1;
        return *this;
    }
    SetupDurations& SetChancing2(int chancing2)
    {
        this->chancing2 = chancing2;
        return *this;
    }
    SetupDurations& SetSetupDuration(int setupDuration)
    {
        this->setupDuration = setupDuration;
        return *this;
    }
    int GetChancing1() const
    {
        return chancing1;
    }
    int GetChancing2() const
    {
        return chancing2;
    }
    int GetSetupDuration() const
    {
        return setupDuration;
    }
};

class Orders
{
private:
    int orderNo;
    float amountOfWork;
    int wantedOperationCode;
    int deadLine;
    int siralama;

public:
    Orders& SetAmountOfWork(float amountOfWork)
    {
        this->amountOfWork = amountOfWork;
        return *this;
    }
    Orders& SetDeadLine(int deadLine)
    {
        this->deadLine = deadLine;
        return *this;
    }
    Orders& SetOrderNo(int orderNo)
    {
        this->orderNo = orderNo;
        return *this;
    }
    Orders& SetSiralama(int siralama)
    {
        this->siralama = siralama;
        return *this;
    }
    Orders& SetWantedOperationCode(int wantedOperationCode)
    {
        this->wantedOperationCode = wantedOperationCode;
        return *this;
    }
    float GetAmountOfWork() const
    {
        return amountOfWork;
    }
    int GetDeadLine() const
    {
        return deadLine;
    }
    int GetOrderNo() const
    {
        return orderNo;
    }
    int GetSiralama() const
    {
        return siralama;
    }
    int GetWantedOperationCode() const
    {
        return wantedOperationCode;
    }
};

vector<Machines> machines;
vector<SetupDurations> setupDurations;
vector<Orders> orders;

Machines machine;
SetupDurations setupDuration;
Orders order;
Orders temp;

string satir;
int hesap;
int chancePeriod = 0;
int times = 0;
int indis = 0;

int periodCalculation(int i, int chancePeriods)
{
    if (i == orders.size() - 1) {
        return chancePeriod;
    }
    else
    {
        if (orders[i].GetWantedOperationCode() == orders[i + 1].GetWantedOperationCode())
        {
            chancePeriod = 0;
            return chancePeriod;
        }
        else
        {
            for (int j = 0;j < setupDurations.size();j++)
            {
                if ((orders[i].GetWantedOperationCode() == setupDurations[j].GetChancing1() && orders[i + 1].GetWantedOperationCode() == setupDurations[j].GetChancing2()) || (orders[i].GetWantedOperationCode() == setupDurations[j].GetChancing2() && orders[i + 1].GetWantedOperationCode() == setupDurations[j].GetChancing1()))
                {
                    chancePeriod = setupDurations[j].GetSetupDuration();
                    return chancePeriod;
                }
            }
        }
    }
}

int timeCalculation(int i, int timess)
{
    for (int j = 0;j < machines.size();j++)
    {
        if (orders[i].GetWantedOperationCode() == machines[j].GetOperationCode())
        {
            times += ceil(orders[i].GetAmountOfWork() / machines[j].GetMachineSpeed()) + chancePeriod;
            return times;
        }
    }
}

void expiryCalculation()
{
    for (int i = 0;i < orders.size() - 1;i++) {
        for (int j = 0;j < orders.size() - 1;j++) {
            if (orders[j].GetSiralama() > orders[j + 1].GetSiralama()) {
                temp.SetSiralama(orders[j].GetSiralama());
                temp.SetAmountOfWork(orders[j].GetAmountOfWork());
                temp.SetDeadLine(orders[j].GetDeadLine());
                temp.SetOrderNo(orders[j].GetOrderNo());
                temp.SetWantedOperationCode(orders[j].GetWantedOperationCode());
                orders[j].SetSiralama(orders[j + 1].GetSiralama());
                orders[j].SetAmountOfWork(orders[j + 1].GetAmountOfWork());
                orders[j].SetDeadLine(orders[j + 1].GetDeadLine());
                orders[j].SetOrderNo(orders[j + 1].GetOrderNo());
                orders[j].SetWantedOperationCode(orders[j + 1].GetWantedOperationCode());
                orders[j + 1].SetSiralama(temp.GetSiralama());
                orders[j + 1].SetAmountOfWork(temp.GetAmountOfWork());
                orders[j + 1].SetDeadLine(temp.GetDeadLine());
                orders[j + 1].SetOrderNo(temp.GetOrderNo());
                orders[j + 1].SetWantedOperationCode(temp.GetWantedOperationCode());
            }
        }
    }
}

int main()
{


    ifstream operationReading("Operations.txt");

    if (operationReading.is_open())
    {
        while (getline(operationReading, satir)) {
            stringstream ss(satir);
            getline(ss, satir, ';');
            machine.SetOperationCode(stoi(satir));
            getline(ss, satir, ';');
            machine.SetMachineSpeed(stoi(satir));

            machines.push_back(machine);
        }
        operationReading.close();
    }


    ifstream setupReading("setupDuration.txt");

    if (setupReading.is_open())
    {
        while (getline(setupReading, satir))
        {
            stringstream ss(satir);
            getline(ss, satir, ';');
            setupDuration.SetChancing1(stoi(satir));
            getline(ss, satir, ';');
            setupDuration.SetChancing2(stoi(satir));
            getline(ss, satir, ';');
            setupDuration.SetSetupDuration(stoi(satir));

            setupDurations.push_back(setupDuration);
        }
        setupReading.close();
    }


    ifstream orderNoReading("Orders.txt");

    if (orderNoReading.is_open())
    {
        while (getline(orderNoReading, satir))
        {
            stringstream ss(satir);
            getline(ss, satir, ';');
            order.SetOrderNo(stoi(satir));
            getline(ss, satir, ';');
            order.SetAmountOfWork(stoi(satir));
            getline(ss, satir, ';');
            order.SetWantedOperationCode(stoi(satir));
            hesap = stoi(satir);
            getline(ss, satir, ';');
            order.SetDeadLine(stoi(satir));

            orders.push_back(order);

            for (int i = 0;i < machines.size();i++)
            {
                if (hesap == machines[i].GetOperationCode())
                {
                    orders[indis].SetSiralama(orders[indis].GetDeadLine() - ceil(orders[indis].GetAmountOfWork() / machines[i].GetMachineSpeed()));
                }
            }
            indis++;
        }
    }

    expiryCalculation();

    ofstream dosyaYaz("Schedule.txt");
    if (dosyaYaz.is_open())
    {
        for (int i = 0;i < orders.size();i++)
        {
            if (times > orders[i].GetDeadLine())
            {
                dosyaYaz << "Time's Up" << endl;
            }
            else
            {
                dosyaYaz << times << ";" << orders[i].GetWantedOperationCode() << ";" << orders[i].GetOrderNo() << ";" << orders[i].GetAmountOfWork() << ";" << chancePeriod << endl;
                periodCalculation(i, chancePeriod);
                timeCalculation(i, times);
            }
        }
        dosyaYaz.close();
    }
}

