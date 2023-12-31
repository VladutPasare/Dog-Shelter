cmake_minimum_required(VERSION 3.25)
project(Dog_Shelter)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "/Users/pasarevladutflavius/Qt/6.5.0/macos/lib/cmake")
set(QT_VERSION 6)
set(REQUIRED_LIBS Core Gui Widgets Charts)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Charts)

add_executable(Dog_Shelter main.cpp domain/Dog.h domain/Dog.cpp infrastructure/FileRepository.h infrastructure/FileRepository.cpp infrastructure/HTMLRepository.h infrastructure/HTMLRepository.cpp bussiness/Service.h bussiness/Service.cpp exceptions/RepositoryExeption.cpp exceptions/ServiceException.cpp exceptions/UIException.cpp validation/DogValidator.cpp testing/TestFileRepository.h testing/TestDomain.h testing/TestService.h testing/TestHTMLRepository.h testing/TestDomain.cpp testing/TestFileRepository.cpp testing/TestService.cpp testing/TestHTMLRepository.cpp infrastructure/Repository.cpp infrastructure/Repository.h bussiness/Command.cpp bussiness/Command.h exceptions/Exception.cpp exceptions/Exception.h presentation/MainWindow.cpp presentation/MainWindow.h presentation/AdminWindow.cpp presentation/AdminWindow.h presentation/UserWindow.cpp presentation/UserWindow.h presentation/DogsTableModel.cpp presentation/DogsTableModel.h presentation/CustomTable.cpp presentation/CustomTable.h presentation/DogPictureDelegate.cpp presentation/DogPictureDelegate.h presentation/DogInfoLayout.cpp presentation/DogInfoLayout.h presentation/FilterDialog.cpp presentation/FilterDialog.h presentation/AddDogDialog.cpp presentation/AddDogDialog.h presentation/UpdateDogDialog.cpp presentation/UpdateDogDialog.h presentation/StatisticsWindow.cpp presentation/StatisticsWindow.h presentation/CustomButton.cpp presentation/CustomButton.h presentation/NewDogsDialog.cpp presentation/NewDogsDialog.h presentation/ImageDrop.cpp presentation/ImageDrop.h presentation/DropHereRectangle.cpp presentation/DropHereRectangle.h infrastructure/CSVRepository.cpp infrastructure/CSVRepository.h presentation/Window.cpp presentation/Window.h testing/TestValidation.cpp testing/TestValidation.h)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})