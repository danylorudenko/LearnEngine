//#include <rapidjson\document.h>
//#include <rapidjson\filereadstream.h>
//
//#include <fstream>
//#include <iostream>
//#include <chrono>
//
//int jsonmain()
//{
//    using namespace rapidjson;
//
//    auto startTime = std::chrono::high_resolution_clock::now();
//
//    FILE* file/* = std::fopen("D:\Git_local\LearnEngine\LearnEngine\LearnEngine\Resources\Config", "r")*/;
//
//    fopen_s(&file, R"(D:\Git_local\LearnEngine\LearnEngine\LearnEngine\Resources\Config\main_config.json)", "r");
//    char readBuffer[0xFFFF];
//    FileReadStream read_stream(file, readBuffer, sizeof(readBuffer));
//
//    Document document;
//    document.ParseStream(read_stream);
//
//    fclose(file);
//
//    auto endTime = std::chrono::high_resolution_clock::now();
//
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
//
//    std::cout << duration.count() << std::endl;
//
//    system("pause");
//    return 0;
//}