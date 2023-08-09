#include "presentation/MainUI.h"
#include "presentation/AdminUI.h"
#include "presentation/UserUI.h"
#include "testing/TestDomain.h"
#include "testing/TestAdminRepository.h"
#include "testing/TestUserHTMLRepository.h"
#include "testing/TestService.h"

#define ADMINISTRATOR_MODE "1"
#define USER_MODE "2"
#define EXIT "3"

int main() {
    TestDomain testDomain;
    TestAdminRepository testRepository;
    TestUserHTMLRepository testUserHtmlRepository;
    TestService testService;

    std::string txt_file = "a.txt", html_file = "c.html";

    AdminRepository<Dog> adminRepo(txt_file);
    UserRepository<Dog>* userRepository;
    UserHTMLRepository<Dog> userHtmlRepository(html_file);
    userRepository = &userHtmlRepository;
    Service service(adminRepo, userRepository);

    AdminUI adminUI(service);
    UserUI userUI(service, html_file);

    while(true) {
        const std::string option = MainUI::getOption();
        if(option == ADMINISTRATOR_MODE){
            adminUI.start();
        }
        else if(option == USER_MODE) {
            userUI.start();
        }
        else if(option == EXIT) {
            break;
        }
    }
}