/*!
 *  @file arrayreader.h
 *  @author Dmitry Ryazancev
 *  @date 22.06.2023
 *  @copyright Radar-MMS 2023
 */

#pragma once

#include <cstdint>
#include <cstring>

//! @brief Пространство имен для низкоуровневого декодирования и обработки данных.
namespace Processing
{
  /*!
   * @brief Класс для чтения массива данных из указателя.
   * @details Класс служит оберткой над операцией копирования между
   * двумя указателями.
   * @tparam T - тип указателя на цель копирования.
   */
  template<typename T>
  class ArrayReader
  {
    public:
      ArrayReader(T* pointer) : ptr(pointer) {}

      /*!
       * @brief Читает N байт из источника в цель.
       * @param destination - укаазатель на цель копирования.
       * @param n - количество байт для копирования.
       */
      void read(T* destination, uint32_t n)
      {
        uint32_t size_bytes = n * sizeof(T);
        memcpy((void*)destination, (void*)ptr, size_bytes);
        ptr += n;
        read_cnt += n;
      }

      //! @brief Возвращает количесто прочтенных байт этим экземпляром класса.
      uint32_t readed()
      {
        return read_cnt;
      }

    private:
      T* ptr = nullptr;
      uint32_t read_cnt = 0;
  };
} // Processing
