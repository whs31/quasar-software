#include <filesystem>
#include <fstream>
#include <string>
#include <stdint.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

const int MAX_PACK_SIZE = 1024;

struct nav_t{
        float pitch     = 0.0;// град
        float roll      = 0.0;// град
        float ele       = 0.0;// м
        double lat      = 0.0;
        double lon      = 0.0;
        float velocity  = 0.0;// м/c
        float course    = 0.0;// град
        float track_ang = 0.0;// course + drift_ang
}__attribute__((packed));

struct img_t{
    float dx                = 0.0;//
    float dy                = 0.0;//
    float course            = 0.0;
    float roll              = 0.0;
    float x0                = 0.0;//
    uint8_t word_size       = 0.0;
    uint8_t polarization    = 0.0;
    int16_t y               = 0.0;
    uint16_t nx             = 0.0;//
    uint16_t ny             = 0.0;//
    float k                 = 0.0;//
}__attribute__((packed));

struct head_t{
    uint16_t marker     = 0;
    uint16_t version    = 0;
    uint16_t size       = 0;        //
    uint16_t cnt        = 0;        //
    uint16_t id         = 0;
    uint16_t type       = 0;
}__attribute__((packed));

template<typename T>
class ArrayReader{

public:
    ArrayReader(T* _ptr) : ptr(_ptr){}

    void read(T* dst, uint32_t n){
        uint32_t size_bytes = n * sizeof(T);
        memcpy( (void*) dst, (void*) ptr, size_bytes );
        ptr += n;
        read_cnt += n;
    }

    uint32_t readed(){
       return read_cnt;
    }

private:
    T* ptr = nullptr;
    uint32_t read_cnt = 0;
};


std::tuple<const uint8_t*, int> read_file(fs::path path){
    std::ifstream f(path, std::ios::in | std::ios::binary);

    if(!f.is_open()){
        std::cerr << "Have no file " << path << "\n";
        return {nullptr, 0};
    }

    const auto sz = fs::file_size(path);
    const uint8_t* file_ptr = (const uint8_t*)malloc(sz);
    f.read((char*)file_ptr, sz);

    return {file_ptr, sz};
}



int main(){

    // Тут будет пакет из сокета
    // Читаю полный файл т.к. заранее неизвестно какой размер пакета будет
    // в сокете же гарантированно приходит полный пакет, содержащий n чанков
    // В данном случае считаем, что это просто один большой пакет
/*
    auto file = read_file("utils/data.bin");
    const uint8_t* data = std::get<0>(file);
    int data_size = std::get<1>(file);
    const int header_size = sizeof(head_t) + sizeof(img_t) + sizeof(nav_t);

    std::cout << "header_size " << header_size << "\n";
    std::cout << "data_size " << data_size << "\n";
*/
    

    // ArrayReader<uint8_t> ar((uint8_t*)data);

    const int header_size = sizeof(head_t) + sizeof(img_t) + sizeof(nav_t);

    uint8_t* header = (uint8_t*)malloc(header_size);
    uint8_t* buf = (uint8_t*)malloc(MAX_PACK_SIZE - header_size);
    float* fbuf = (float*)malloc( (MAX_PACK_SIZE - header_size) * sizeof(float));


    int x = 0;
    int y = 0;

    // Вот эта матрица в наземке будет увеличиваться постоянно
    // Тут она соответствует по количеству элементов размеру "пакета"
    // В ней хранится промежуточный результат, который будет преобразован в uint8_t
    // Возможно, ее придется кешировать на диск, ибо она довольно быстро станет очень толстой
    // std::vector<float> fmatrix;

    int i = 0;
    char path[128];
    while(1){
        getchar();

        // printf("Read\n");

        sprintf(path, "pack/%d", i);
        auto file = read_file(path);
        const uint8_t* data = std::get<0>(file);

        if(!data){
            break;
        }
        
        int data_size = std::get<1>(file);

        ArrayReader<uint8_t> ar((uint8_t*)data); 

        if( (data_size - ar.readed()) < header_size ){
            std::cerr << "bad data allign!\n";
            break;
        }

        ar.read(header, header_size);
        ArrayReader<uint8_t>header_reader(header);

        head_t head;
        nav_t nav;
        img_t img;

        header_reader.read((uint8_t*)&head, sizeof(head_t));
        header_reader.read((uint8_t*)&nav, sizeof(nav_t));
        header_reader.read((uint8_t*)&img, sizeof(img_t));

        printf("i: %d\n", i);
        printf("cnt: %d\n", head.cnt);
        printf("Size: %d\n", head.size);
        printf("x: %f\n", img.x0);
        printf("y: %f\n", (float)img.y/10.0 );
        
        if(head.cnt == 0){
            x = img.nx;
            y += img.ny;
        }
        
        ar.read((uint8_t*) buf, head.size );

        // Запись промежуточного результата в матрицу
        // for(int i = 0; i < head.size; i++){
            // fmatrix.push_back( (float)buf[i] * img.k);
        // }
        i++;
    }

    // Эти значения нужно пересчитывать каждый раз при выводе матрицы на экран
    // Лучше сделать вычисление максимального значения рекуррентно,
    // т.к. с ростом матрицы многокрано увеличится объем обработки и будет тормозить
    // const float max_value = *max_element(fmatrix.begin(), fmatrix.end());
    // const float k = max_value / 255.0f;

    // std::cout << "Matrix size: { " << x << ", " << y << " }\n";
    // std::cout << "max_value: " << max_value << " }\n";

    // int out_size = x*y;
    // uint8_t* out_buf = (uint8_t*)malloc(out_size);

    // обратное масштабирование
    // for(int i = 0; i < out_size; i++){
        // out_buf[i] = fmatrix[i] / k;
    // }

    // Сохранение результата в бинарь
    // У меня отображением занимается plotresult.py, там все тривиально
    // В наземке этот буфер будет на экран выводиться
    // std::ofstream f("fmatrix.bin", std::ios_base::out);
    // f.write( (const char*)out_buf, out_size );
    // f.close();


    // free((void*)data);
    free((void*)header);
    free((void*)buf);
    free((void*)fbuf);
    // free((void*)out_buf);
    return 0;
}
