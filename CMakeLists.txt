cmake_minimum_required(VERSION 3.25)
project(Dog_Shelter)

set(CMAKE_CXX_STANDARD 17)

add_executable(Dog_Shelter main.cpp domain/Dog.h domain/Dog.cpp infrastructure/AdminRepository.h infrastructure/AdminRepository.cpp infrastructure/UserRepository.h infrastructure/UserRepository.cpp infrastructure/UserHTMLRepository.h infrastructure/UserHTMLRepository.cpp bussiness/Service.h bussiness/Service.cpp presentation/AdminUI.h presentation/AdminUI.cpp presentation/MainUI.h presentation/MainUI.cpp presentation/UI.cpp presentation/UserUI.h presentation/UserUI.cpp exceptions/RepositoryExeption.cpp exceptions/ServiceException.cpp exceptions/UIException.cpp validation/DogValidator.cpp testing/TestAdminRepository.h testing/TestDomain.h testing/TestService.h testing/TestUserHTMLRepository.h testing/TestDomain.cpp testing/TestAdminRepository.cpp testing/TestService.cpp testing/TestUserHTMLRepository.cpp)
