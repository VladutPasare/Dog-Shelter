#include "testing/TestDomain.h"
#include "testing/TestFileRepository.h"
#include "testing/TestHTMLRepository.h"
#include "testing/TestService.h"
#include "testing/TestValidation.h"
#include "presentation/MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    TestDomain testDomain;
    TestFileRepository testRepository;
    TestHTMLRepository testUserHtmlRepository;
    TestService testService;
    TestValidation testValidation;

    const std::string &adminFile = "../files/dogs.txt", userFile = /*"../files/adoption_list.csv";//*/"../files/adoption_list.html";
    auto adminRepository = std::make_shared<FileRepository<Dog>>(adminFile);
    auto userRepository = std::make_shared<HTMLRepository<Dog>>(userFile);
    userRepository->clearFile();

    Service service(adminRepository, userRepository);
    QApplication app(argc, argv);
    MainWindow optionWindow(service);
    optionWindow.show();
    return app.exec();
}