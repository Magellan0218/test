#include <iostream>
#include <memory>
#include <thread>

class OperatingSystem
{
    public:
        using OperatingSystemPtr = std::shared_ptr<OperatingSystem>;

    public:
        virtual void setName(void) = 0;

        virtual void showName(void) = 0;
    
    protected:
        std::string name_;
};

class IosSystem : public OperatingSystem
{
    public:
        void setName(void) override
        {
            name_ = "IOS";
        }

        void showName(void) override
        {
            std::cout << name_ << std::endl;
        }
};

class AndroidSystem : public OperatingSystem
{
    public:
        void setName(void) override
        {
            name_ = "Android";
        }

        void showName(void) override
        {
            std::cout << name_ << std::endl;
        }
};

class HarmonySystem : public OperatingSystem
{
    public:
        void setName(void) override
        {
            name_ = "Harmony";
        }

        void showName(void) override
        {
            std::cout << name_ << std::endl;
        }
};

class Phone
{
    public:
        using PhonePtr = std::shared_ptr<Phone>;

    public:
        virtual void setName(void) = 0;

        virtual void showName(void) = 0;

        virtual void setOperatingSystem(OperatingSystem::OperatingSystemPtr system) = 0;

        virtual void showOperatingSystemName(void) = 0;

    protected:
        std::string name_;
        OperatingSystem::OperatingSystemPtr system_;
};

class Iphone : public Phone
{
    public:
        void setName(void) override
        {
            name_ = "Iphone";
        }

        void showName(void) override
        {
            std::cout << name_ << std::endl;
        }

        void setOperatingSystem(OperatingSystem::OperatingSystemPtr system) override
        {
            system_ = system;
        }

        void showOperatingSystemName(void) override
        {
            system_->showName();
        }
};

class MiPhone : public Phone
{
    public:
        void setName(void) override
        {
            name_ = "MiPhone";
        }

        void showName(void) override
        {
            std::cout << name_ << std::endl;
        }

        void setOperatingSystem(OperatingSystem::OperatingSystemPtr system) override
        {
            system_ = system;
        }

        void showOperatingSystemName(void) override
        {
            system_->showName();
        }
};

class HuaWeiPhone : public Phone
{
    public:
        void setName(void) override
        {
            name_ = "HuaWeiPhone";
        }

        void showName(void) override
        {
            std::cout << name_ << std::endl;
        }

        void setOperatingSystem(OperatingSystem::OperatingSystemPtr system) override
        {
            system_ = system;
        }

        void showOperatingSystemName(void) override
        {
            system_->showName();
        }

};

class A
{
    public:
        A()
        {
            std::cout << "A()" << std::endl;
        }

        A(const A &a)
        {
            std::cout << "copy A()" << std::endl;
        }

        A &operator= (const A &a)
        {
            std::cout << "copy =A()" << std::endl;
        }

        A(A &&a)
        {
            std::cout << "move A()" << std::endl;
        }

        A &operator =(A &&a)
        {
            std::cout << "move =A()" << std::endl;
        }

        ~A()
        {
            std::cout << "~A()" << std::endl;
        }
};

#include <vector>

int main(int argc, char **argv)
{
    OperatingSystem::OperatingSystemPtr operatingSystem = std::make_shared<IosSystem>();
    operatingSystem->setName();
    
    Phone::PhonePtr phone = std::make_shared<Iphone>();
    phone->setOperatingSystem(operatingSystem);
    phone->setName();
    phone->showName();
    phone->showOperatingSystemName();
    
    std::vector<A> v;

    A a;
    v.emplace_back(a);
    return 0;
}