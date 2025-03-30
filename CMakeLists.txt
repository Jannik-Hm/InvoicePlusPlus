cmake_minimum_required(VERSION 3.19)
project(Invoice++ LANGUAGES CXX)

find_package(Qt6 6.8.2 REQUIRED COMPONENTS Core Widgets)
find_package(Iconv REQUIRED)
find_package(ZLIB REQUIRED)

set(CMAKE_CXX_STANDARD 23)

qt_standard_project_setup()

qt_add_executable(Invoice++
    WIN32 MACOSX_BUNDLE
    main.cpp
        ui/mainwindow.cpp
        ui/mainwindow.h
        ui/customWidgets/productWidget/productWidget.h
        ui/customWidgets/productWidget/productWidget.cpp
        ui/customWidgets/representativeWidget/representativeWidget.cpp
        ui/customWidgets/representativeWidget/representativeWidget.h
        ui/customWidgets/inputWidget/textInputWidget.cpp
        ui/customWidgets/inputWidget/textInputWidget.h
        ui/customWidgets/inputWidget/spinBoxInputWidget.cpp
        ui/customWidgets/inputWidget/spinBoxInputWidget.h
        ui/customWidgets/inputWidget/dateInputWidget.cpp
        ui/customWidgets/inputWidget/dateInputWidget.h
        pdf/invoice.cpp
        pdf/invoice.h
        data_objects/product_data.h
        pdf/pdf_utils.h
        utils.h
        data_objects/invoice_data.h
        pdf/product_table.cpp
        pdf/product_table.h
        data_objects/representative_data.h
        pdf/pdf_exception.h
)

target_link_libraries(Invoice++
    PRIVATE
        Qt::Core
        Qt::Widgets
        /opt/homebrew/lib/libhpdf.a
        ZLIB::ZLIB
        Iconv::Iconv
)

include(GNUInstallDirs)

install(TARGETS Invoice++
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Invoice++
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
