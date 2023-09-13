#include "testing/TestDomain.h"
#include "testing/TestFileRepository.h"
#include "testing/TestHTMLRepository.h"
#include "testing/TestService.h"
#include "presentation/MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {

    TestDomain testDomain;
    TestFileRepository testRepository;
    TestHTMLRepository testUserHtmlRepository;
    TestService testService;

    const std::string &adminFile = "../files/file1.txt", userFile = "../files/file3.html";
    auto adminRepository = std::make_shared<FileRepository<Dog>>(adminFile);
    auto userRepository = std::make_shared<HTMLRepository<Dog>>(userFile);
    Service service(adminRepository, userRepository);
    QApplication app(argc, argv);
    MainWindow optionWindow(service);
    optionWindow.show();
    return app.exec();
}