#include <iostream>

class Library
{
    public:
        Library() = default;
        virtual ~Library()
        {
            std::cout << "~Library" << std::endl;
        }
        
    protected:
        void run(void)
        {
            step1();
            step2();
            step3();
            step4();
            step5();
        }

        void step1(void)
        {
            std::cout << "Library::step1" << std::endl;
        }

        void step2(void)
        {
            std::cout << "Library::step2" << std::endl;
        }
        
        void step3(void)
        {
            std::cout << "Library::step3" << std::endl;
        }

        virtual void step4(void) = 0;

        virtual void step5(void) = 0;
};

class App : public Library, std::enable_shared_from_this<App>
{
    public:
        App() = default;
        ~App()
        {
            std::cout << "~App" << std::endl;
        }

        void step4(void) override final
        {
            std::cout << "App::step4" << std::endl;
        }

        void step5(void) override final
        {
            std::cout << "App::step5" << std::endl;
        }

        std::shared_ptr<App> getSelf(void)
        {
            return shared_from_this();
        }
};

int main(void)
{
    {
        std::shared_ptr<Library> lib = std::make_shared<App>();
        lib->run();
    }
    return 0;
}
